#include "Product.h"
#include <stdexcept>

Product::Product(int id, const std::string& name, long long price)
    : id(id), name(name), price(price) {
    // TODO: MEMBER 3 - Kiem tra id > 0, ten khong rong, price > 0.
    throw std::logic_error("TODO: MEMBER 3 - Product::Product");
}

int Product::getId() const {
    // TODO: MEMBER 3 - Tra ve ma san pham.
    throw std::logic_error("TODO: MEMBER 3 - Product::getId");
}

const std::string& Product::getName() const {
    // TODO: MEMBER 3 - Tra ve ten san pham.
    throw std::logic_error("TODO: MEMBER 3 - Product::getName");
}

long long Product::getPrice() const {
    // TODO: MEMBER 3 - Tra ve don gia (long long).
    throw std::logic_error("TODO: MEMBER 3 - Product::getPrice");
}
