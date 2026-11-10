#include "CartItem.h"

// Constructor
CartItem::CartItem(const Product& product, int quantity)
    : product(product), quantity(quantity) {}

// Getters
const Product& CartItem::getProduct() const {
    return product;
}

int CartItem::getQuantity() const {
    return quantity;
}

// Tang/giam so luong
void CartItem::increaseQuantity() {
    quantity++;
}

void CartItem::decreaseQuantity() {
    if (quantity > 0) {
        quantity--;
    }
}

// Tinh tong tien cho mat hang này (Gia x So luong)
long long CartItem::getTotalPrice() const {
    return product.getPrice() * quantity;
}
