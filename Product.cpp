#include "Product.h"
#include "Text.h"
#include <iostream>

using namespace std;

Product::Product(int id, const char name[], long long price) {
    this->id = id;
    copyText(this->name, 100, name);
    this->price = price;
}

int Product::getId() const {
    return id;
}

const char* Product::getName() const {
    return name;
}

long long Product::getPrice() const {
    return price;
}

bool Product::isValid() const {
    return id > 0 && hasText(name) && price > 0 && price <= MAX_PRICE;
}

bool Product::operator==(const Product& other) const {
    return id == other.id;
}

void Product::print() const {
    cout << id << " | " << name << " | " << price << " VND\n";
}
