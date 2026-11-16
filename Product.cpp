#include "Product.h"
#include <stdexcept>
#include <utility>

using namespace std;

Product::Product(int id, const string& name, long long price)
    : id(id), name(name), price(price) {
    // Chi tao san pham khi ca ba thuoc tinh deu hop le.
    if (id <= 0) {
        throw invalid_argument("Ma san pham phai lon hon 0.");
    }
    if (name.find_first_not_of(" \t\r\n\f\v") == string::npos) {
        throw invalid_argument("Ten san pham khong duoc de trong.");
    }
    if (price <= 0) {
        throw invalid_argument("Gia san pham phai lon hon 0.");
    }
}

int Product::getId() const {
    return id;
}

const string& Product::getName() const {
    return name;
}

long long Product::getPrice() const {
    return price;
}

bool Product::operator==(const Product& other) const {
    return id == other.id;
}

vector<Product> filterByPriceRange(const vector<Product>& products,
                                       long long minPrice, long long maxPrice) {
    vector<Product> result;
    if (minPrice > maxPrice) {
        swap(minPrice, maxPrice);
    }
    for (const Product& product : products) {
        if (product.getPrice() >= minPrice && product.getPrice() <= maxPrice) {
            result.push_back(product);
        }
    }
    return result;
}
