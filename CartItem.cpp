#include "CartItem.h"
#include <stdexcept>

CartItem::CartItem(const Product& product, int quantity)
    : product(product), quantity(quantity) {
    // TODO: MEMBER 2 - Kiem tra so luong ban dau > 0.
    throw std::logic_error("TODO: MEMBER 2 - CartItem::CartItem");
}

const Product& CartItem::getProduct() const {
    // TODO: MEMBER 2 - Tra ve san pham.
    throw std::logic_error("TODO: MEMBER 2 - CartItem::getProduct");
}

int CartItem::getQuantity() const {
    // TODO: MEMBER 2 - Tra ve so luong.
    throw std::logic_error("TODO: MEMBER 2 - CartItem::getQuantity");
}

void CartItem::increaseQuantity() {
    // TODO: MEMBER 2 - Tang 1; kiem tra tran int va tran thanh tien.
    throw std::logic_error("TODO: MEMBER 2 - CartItem::increaseQuantity");
}

void CartItem::decreaseQuantity() {
    // TODO: MEMBER 2 - Giam 1; khong cho xuong duoi 0.
    throw std::logic_error("TODO: MEMBER 2 - CartItem::decreaseQuantity");
}

long long CartItem::getTotalPrice() const {
    // TODO: MEMBER 2 - Don gia * so luong; kiem tra tran long long.
    throw std::logic_error("TODO: MEMBER 2 - CartItem::getTotalPrice");
}
