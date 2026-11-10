#include "Product.h"
#include <stdexcept>

Product::Product(int id, const std::string& name, long long price)
    : id(id), name(name), price(price) {
    // Chi tao san pham khi ca ba thuoc tinh deu hop le.
    if (id <= 0) {
        throw std::invalid_argument("Ma san pham phai lon hon 0.");
    }
    if (name.find_first_not_of(" \t\r\n\f\v") == std::string::npos) {
        throw std::invalid_argument("Ten san pham khong duoc de trong.");
    }
    if (price <= 0) {
        throw std::invalid_argument("Gia san pham phai lon hon 0.");
    }
}

int Product::getId() const {
    return id;
}

const std::string& Product::getName() const {
    return name;
}

long long Product::getPrice() const {
    return price;
}
