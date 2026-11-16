#include "CartItem.h"
#include <iostream>

using namespace std;

CartItem::CartItem(const Product& product, int quantity) : product(product) {
    this->quantity = 0;
    if (product.isValid() && quantity > 0 && quantity <= MAX_QUANTITY) {
        this->quantity = quantity;
    }
}

const Product& CartItem::getProduct() const {
    return product;
}

int CartItem::getQuantity() const {
    return quantity;
}

bool CartItem::increaseQuantity() {
    if (!product.isValid() || quantity >= MAX_QUANTITY) {
        return false;
    }
    quantity++;
    return true;
}

void CartItem::decreaseQuantity() {
    if (quantity > 0) {
        quantity--;
    }
}

long long CartItem::getTotalPrice() const {
    return product.getPrice() * quantity;
}

void CartItem::print() const {
    cout << product.getId() << " | " << product.getName()
         << " | SL: " << quantity << " | Don gia: " << product.getPrice()
         << " | Thanh tien: " << getTotalPrice() << " VND\n";
}
