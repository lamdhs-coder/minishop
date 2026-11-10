#include "Product.h"

Product::Product() : id(0), name(""), price(0) {}

Product::Product(int id, const std::string& name, long long price)
    : id(id), name(name), price(price) {}

int Product::getId() const {
    return id;
}

std::string Product::getName() const {
    return name;
}

long long Product::getPrice() const {
    return price;
}

void Product::setId(int id) {
    this->id = id;
}

void Product::setName(const std::string& name) {
    this->name = name;
}

void Product::setPrice(long long price) {
    this->price = price;
}
