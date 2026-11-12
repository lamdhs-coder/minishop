#include "ShoppingCart.h"
#include <limits>
#include <stdexcept>

void ShoppingCart::addProduct(const Product& product) {
    for (CartItem& item : items) {
        if (item.getProduct().getId() == product.getId()) {
            item.increaseQuantity();
            return;
        }
    }
    items.emplace_back(product);
}
bool ShoppingCart::increaseQuantity(int productId) {
    for (CartItem& item : items) {
        if (item.getProduct().getId() == productId) {
            item.increaseQuantity();
            return true;
        }
    }
    return false;
}
bool ShoppingCart::decreaseQuantity(int productId) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->getProduct().getId() == productId) {
            it->decreaseQuantity();
            if (it->getQuantity() == 0) items.erase(it);
            return true;
        }
    }
    return false;
}
bool ShoppingCart::removeProduct(int productId) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->getProduct().getId() == productId) {
            items.erase(it);
            return true;
        }
    }
    return false;
}
const std::vector<CartItem>& ShoppingCart::getItems() const { return items; }
long long ShoppingCart::getSubtotal() const {
    long long sum = 0;
    for (const CartItem& item : items) {
        const long long value = item.getTotalPrice();
        if (value > std::numeric_limits<long long>::max() - sum)
            throw std::overflow_error("Cart subtotal overflow");
        sum += value;
    }
    return sum;
}
long long ShoppingCart::getTotalQuantity() const {
    long long sum = 0;
    for (const CartItem& item : items) sum += item.getQuantity();
    return sum;
}
bool ShoppingCart::isEmpty() const { return items.empty(); }
void ShoppingCart::clear() { items.clear(); }
