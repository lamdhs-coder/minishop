#include "ShoppingCart.h"
#include <algorithm>
#include <limits>
#include <stdexcept>

using namespace std;

void ShoppingCart::addProduct(const Product& product) {
    // find_if tra iterator den dong dau tien thoa dieu kien.
    // Lambda dung operator== cua Product de kiem tra trung ma.
    auto item = find_if(items.begin(), items.end(),
        [&product](const CartItem& cartItem) {
            return cartItem.getProduct() == product;
        });
    if (item != items.end()) {
        if (item->getProduct().getPrice() > numeric_limits<long long>::max() - getSubtotal()) {
            throw overflow_error("Tong tien gio vuot gioi han long long.");
        }
        item->increaseQuantity();
        return;
    }
    if (product.getPrice() > numeric_limits<long long>::max() - getSubtotal()) {
        throw overflow_error("Tong tien gio vuot gioi han long long.");
    }
    items.push_back(CartItem(product));
}

bool ShoppingCart::increaseQuantity(int productId) {
    for (CartItem& item : items) {
        if (item.getProduct().getId() == productId) {
            if (item.getProduct().getPrice() > numeric_limits<long long>::max() - getSubtotal()) {
                throw overflow_error("Tong tien gio vuot gioi han long long.");
            }
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
            if (it->getQuantity() == 0) {
                items.erase(it);
            }
            // Tra ve ngay, vi erase lam iterator tai vi tri nay mat hieu luc.
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

const vector<CartItem>& ShoppingCart::getItems() const {
    return items;
}

long long ShoppingCart::getSubtotal() const {
    long long sum = 0;
    for (const CartItem& item : items) {
        const long long value = item.getTotalPrice();
        if (value > numeric_limits<long long>::max() - sum) {
            throw overflow_error("Tong tien gio vuot gioi han long long.");
        }
        sum += value;
    }
    return sum;
}

long long ShoppingCart::getTotalQuantity() const {
    long long sum = 0;
    for (const CartItem& item : items) {
        sum += item.getQuantity();
    }
    return sum;
}

bool ShoppingCart::isEmpty() const {
    return items.empty();
}

void ShoppingCart::clear() {
    items.clear();
}
