#include "ShoppingCart.h"
#include <stdexcept>

void ShoppingCart::addProduct(const Product& /* product */) {
    // TODO: MEMBER 2 - Duyet vector theo id, tang SL hoac emplace_back.
    throw std::logic_error("TODO: MEMBER 2 - ShoppingCart::addProduct");
}

bool ShoppingCart::increaseQuantity(int /* productId */) {
    // TODO: MEMBER 2 - Tim id, tang 1; false neu khong ton tai.
    throw std::logic_error("TODO: MEMBER 2 - ShoppingCart::increaseQuantity");
}

bool ShoppingCart::decreaseQuantity(int /* productId */) {
    // TODO: MEMBER 2 - Giam 1; erase dong khi SL tu 1 ve 0.
    throw std::logic_error("TODO: MEMBER 2 - ShoppingCart::decreaseQuantity");
}

bool ShoppingCart::removeProduct(int /* productId */) {
    // TODO: MEMBER 2 - Xoa theo id; false neu khong ton tai.
    throw std::logic_error("TODO: MEMBER 2 - ShoppingCart::removeProduct");
}

const std::vector<CartItem>& ShoppingCart::getItems() const {
    // TODO: MEMBER 2 - Tra ve tham chieu const toi items.
    throw std::logic_error("TODO: MEMBER 2 - ShoppingCart::getItems");
}

long long ShoppingCart::getSubtotal() const {
    // TODO: MEMBER 2 - Cong getTotalPrice(); kiem tra tran tong.
    throw std::logic_error("TODO: MEMBER 2 - ShoppingCart::getSubtotal");
}

long long ShoppingCart::getTotalQuantity() const {
    // TODO: MEMBER 2 - Cong so luong cac dong, dung long long.
    throw std::logic_error("TODO: MEMBER 2 - ShoppingCart::getTotalQuantity");
}

bool ShoppingCart::isEmpty() const {
    // TODO: MEMBER 2 - Tra ve items.empty().
    throw std::logic_error("TODO: MEMBER 2 - ShoppingCart::isEmpty");
}

void ShoppingCart::clear() {
    // TODO: MEMBER 2 - Xoa toan bo items.
    throw std::logic_error("TODO: MEMBER 2 - ShoppingCart::clear");
}
