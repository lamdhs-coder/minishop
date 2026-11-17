#include "ProductFile.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

namespace {
// Dung chung cho ID (int) va gia (long long).
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
    string line;
    size_t lineNumber = 0;
    while (getline(file, line)) {
        ++lineNumber;
        try {
            istringstream row(line);
            string idText, name, priceText;
            // Hai dau | tach ID, ten; phan con lai la gia.
            if (!getline(row, idText, '|') || !getline(row, name, '|')
                || !getline(row, priceText) || priceText.find('|') != string::npos) {
                throw invalid_argument("Can dung 3 truong id|name|price.");
            }

            const int id = parsePositiveInteger<int>(idText);
            const long long price = parsePositiveInteger<long long>(priceText);
            for (const Product& product : products) {
                if (product.getId() == id) {
                    throw invalid_argument("Ma san pham bi trung: " + to_string(id));
                }
            }
            products.push_back(Product(id, name, price));
        } catch (const invalid_argument& error) {
            throw runtime_error(filename + ": dong " + to_string(lineNumber)
                                + ": " + error.what());
        }
    }
    if (file.bad() || (file.fail() && !file.eof())) {
        throw runtime_error("Loi doc file san pham: " + filename
                            + " sau dong " + to_string(lineNumber));
    }
    return products;
}
