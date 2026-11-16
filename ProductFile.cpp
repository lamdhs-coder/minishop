#include "ProductFile.h"
#include <fstream>
#include <filesystem>
#include <sstream>
#include <stdexcept>
#include <unordered_set>

namespace {
template <typename T>
T parsePositiveInteger(const std::string& field) {
    std::istringstream input(field);
    T value = 0;
    if (!(input >> value) || value <= 0) {
        throw std::invalid_argument("So nguyen duong khong hop le hoac vuot gioi han.");
    }
    input >> std::ws;
    if (!input.eof()) {
        throw std::invalid_argument("So nguyen co ky tu thua.");
    }
    return value;
}
}

std::vector<Product> loadProductsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Khong mo duoc file san pham: " + filename);
    }

    std::vector<Product> products;
    std::unordered_set<int> ids;
    std::string line;
    std::size_t lineNumber = 0;
    while (std::getline(file, line)) {
        ++lineNumber;
        try {
            const auto first = line.find('|');
            const auto second = first == std::string::npos
                ? std::string::npos : line.find('|', first + 1);
            if (second == std::string::npos || line.find('|', second + 1) != std::string::npos) {
                throw std::invalid_argument("Can dung 3 truong id|name|price.");
            }
            const int id = parsePositiveInteger<int>(line.substr(0, first));
            const long long price = parsePositiveInteger<long long>(line.substr(second + 1));
            if (!ids.insert(id).second) {
                throw std::invalid_argument("Ma san pham bi trung: " + std::to_string(id));
            }
            products.emplace_back(id, line.substr(first + 1, second - first - 1), price);
        } catch (const std::invalid_argument& error) {
            throw std::runtime_error(filename + ": dong " + std::to_string(lineNumber) + ": " + error.what());
        }
    }
    if (file.bad() || (file.fail() && !file.eof())) {
        throw std::runtime_error("Loi doc file san pham: " + filename
                                 + " sau dong " + std::to_string(lineNumber));
    }
    return products;
}

void appendProductToFile(const std::string& filename, const Product& product) {
    if (product.getName().find_first_of("|\r\n") != std::string::npos) {
        throw std::invalid_argument("Ten san pham khong duoc chua | hoac xuong dong.");
    }
    // Doc lai de xac nhan file ton tai, du lieu hop le va ID chua co tren dia.
    const std::vector<Product> existing = loadProductsFromFile(filename);
    for (const Product& item : existing) {
        if (item.getId() == product.getId()) {
            throw std::invalid_argument("Ma san pham da ton tai trong file.");
        }
    }

    // in|out chi mo file da co, khong tao file moi va khong cat mat noi dung.
    // Kiem tra quyen ghi ngay ca khi thu muc cho phep thay the file.
    std::fstream writable(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!writable.is_open()) {
        throw std::runtime_error("File san pham khong cho phep ghi: " + filename);
    }
    writable.seekg(0, std::ios::end);
    const std::streampos size = writable.tellg();
    if (size == std::streampos(-1)) {
        throw std::runtime_error("Khong doc duoc kich thuoc file san pham.");
    }
    bool needsNewline = false;
    if (size > std::streampos(0)) {
        writable.seekg(-1, std::ios::end);
        char last;
        if (!writable.get(last)) {
            throw std::runtime_error("Khong doc duoc cuoi file san pham.");
        }
        needsNewline = (last != '\n');
    }
    writable.close(); // Dong truoc khi thay file, de chay duoc tren Windows.
    if (!writable) {
        throw std::runtime_error("Khong dong duoc file san pham.");
    }

    const std::filesystem::path original(filename);
    const std::filesystem::path temporary(filename + ".tmp");
    if (std::filesystem::exists(temporary)) {
        throw std::runtime_error("File tam da ton tai, hay kiem tra truoc khi thu lai: "
                                 + temporary.string());
    }
    bool copied = false;
    try {
        // copy_file khong ghi de file tam co san; giu nguyen tung byte du lieu cu.
        std::filesystem::copy_file(original, temporary);
        copied = true;
        std::ofstream output(temporary, std::ios::binary | std::ios::app);
        if (!output.is_open()) {
            throw std::runtime_error("Khong mo duoc file tam de ghi san pham.");
        }
        if (needsNewline) {
            output << '\n';
        }
        output << product.getId() << '|' << product.getName()
               << '|' << product.getPrice() << '\n';
        output.close();
        if (!output) {
            throw std::runtime_error("Ghi/dong file tam that bai. File goc duoc giu nguyen.");
        }
        // Kiem tra lai ca file truoc khi thay the, tranh luu dong sai/trung ma.
        loadProductsFromFile(temporary.string());
        std::filesystem::rename(temporary, original);
    } catch (...) {
        if (copied) {
            std::error_code ignored;
            std::filesystem::remove(temporary, ignored);
        }
        throw;
    }
}
