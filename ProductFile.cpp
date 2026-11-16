#include "ProductFile.h"
#include <fstream>
#include <filesystem>
#include <sstream>
#include <stdexcept>
#include <unordered_set>

using namespace std;

namespace {
template <typename T>
T parsePositiveInteger(const string& field) {
    istringstream input(field);
    T value = 0;
    if (!(input >> value) || value <= 0) {
        throw invalid_argument("So nguyen duong khong hop le hoac vuot gioi han.");
    }
    input >> ws;
    if (!input.eof()) {
        throw invalid_argument("So nguyen co ky tu thua.");
    }
    return value;
}
}

vector<Product> loadProductsFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Khong mo duoc file san pham: " + filename);
    }

    vector<Product> products;
    unordered_set<int> ids;
    string line;
    size_t lineNumber = 0;
    while (getline(file, line)) {
        ++lineNumber;
        try {
            const auto first = line.find('|');
            const auto second = first == string::npos
                ? string::npos : line.find('|', first + 1);
            if (second == string::npos || line.find('|', second + 1) != string::npos) {
                throw invalid_argument("Can dung 3 truong id|name|price.");
            }
            const int id = parsePositiveInteger<int>(line.substr(0, first));
            const long long price = parsePositiveInteger<long long>(line.substr(second + 1));
            if (!ids.insert(id).second) {
                throw invalid_argument("Ma san pham bi trung: " + to_string(id));
            }
            products.emplace_back(id, line.substr(first + 1, second - first - 1), price);
        } catch (const invalid_argument& error) {
            throw runtime_error(filename + ": dong " + to_string(lineNumber) + ": " + error.what());
        }
    }
    if (file.bad() || (file.fail() && !file.eof())) {
        throw runtime_error("Loi doc file san pham: " + filename
                                 + " sau dong " + to_string(lineNumber));
    }
    return products;
}

void appendProductToFile(const string& filename, const Product& product) {
    if (product.getName().find_first_of("|\r\n") != string::npos) {
        throw invalid_argument("Ten san pham khong duoc chua | hoac xuong dong.");
    }
    // Doc lai de xac nhan file ton tai, du lieu hop le va ID chua co tren dia.
    const vector<Product> existing = loadProductsFromFile(filename);
    for (const Product& item : existing) {
        if (item.getId() == product.getId()) {
            throw invalid_argument("Ma san pham da ton tai trong file.");
        }
    }

    // in|out chi mo file da co, khong tao file moi va khong cat mat noi dung.
    // Kiem tra quyen ghi ngay ca khi thu muc cho phep thay the file.
    fstream writable(filename, ios::in | ios::out | ios::binary);
    if (!writable.is_open()) {
        throw runtime_error("File san pham khong cho phep ghi: " + filename);
    }
    writable.seekg(0, ios::end);
    const streampos size = writable.tellg();
    if (size == streampos(-1)) {
        throw runtime_error("Khong doc duoc kich thuoc file san pham.");
    }
    bool needsNewline = false;
    if (size > streampos(0)) {
        writable.seekg(-1, ios::end);
        char last;
        if (!writable.get(last)) {
            throw runtime_error("Khong doc duoc cuoi file san pham.");
        }
        needsNewline = (last != '\n');
    }
    writable.close(); // Dong truoc khi thay file, de chay duoc tren Windows.
    if (!writable) {
        throw runtime_error("Khong dong duoc file san pham.");
    }

    const filesystem::path original(filename);
    const filesystem::path temporary(filename + ".tmp");
    if (filesystem::exists(temporary)) {
        throw runtime_error("File tam da ton tai, hay kiem tra truoc khi thu lai: "
                                 + temporary.string());
    }
    bool copied = false;
    try {
        // copy_file khong ghi de file tam co san; giu nguyen tung byte du lieu cu.
        filesystem::copy_file(original, temporary);
        copied = true;
        ofstream output(temporary, ios::binary | ios::app);
        if (!output.is_open()) {
            throw runtime_error("Khong mo duoc file tam de ghi san pham.");
        }
        if (needsNewline) {
            output << '\n';
        }
        output << product.getId() << '|' << product.getName()
               << '|' << product.getPrice() << '\n';
        output.close();
        if (!output) {
            throw runtime_error("Ghi/dong file tam that bai. File goc duoc giu nguyen.");
        }
        // Kiem tra lai ca file truoc khi thay the, tranh luu dong sai/trung ma.
        loadProductsFromFile(temporary.string());
        filesystem::rename(temporary, original);
    } catch (...) {
        if (copied) {
            error_code ignored;
            filesystem::remove(temporary, ignored);
        }
        throw;
    }
}
