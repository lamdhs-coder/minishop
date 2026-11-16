#include "ProductFile.h"
#include <fstream>
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
