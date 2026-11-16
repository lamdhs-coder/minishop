#include "ShoppingCart.h"
#include <iostream>

using namespace std;

ShoppingCart::ShoppingCart() {
    itemCount = 0;
}

int ShoppingCart::findProduct(int productId) const {
    for (int i = 0; i < itemCount; i++) {
        if (items[i].getProduct().getId() == productId) {
            return i;
        }
    }
    return -1;
}

bool ShoppingCart::addProduct(const Product& product) {
    if (!product.isValid()) {
        return false;
    }
    for (int i = 0; i < itemCount; i++) {
        if (items[i].getProduct() == product) {
            return items[i].increaseQuantity();
        }
    }
    if (itemCount == MAX_ITEMS) {
        return false;
    }
    items[itemCount] = CartItem(product);
    itemCount++;
    return true;
}

bool ShoppingCart::increaseQuantity(int productId) {
    int index = findProduct(productId);
    if (index == -1) {
        return false;
    }
    return items[index].increaseQuantity();
}

bool ShoppingCart::decreaseQuantity(int productId) {
    int index = findProduct(productId);
    if (index == -1) {
        return false;
    }
    items[index].decreaseQuantity();
    if (items[index].getQuantity() == 0) {
        removeProduct(productId);
    }
    return true;
}

bool ShoppingCart::removeProduct(int productId) {
    int index = findProduct(productId);
    if (index == -1) {
        return false;
    }
    // Don cac phan tu phia sau sang trai mot vi tri.
    for (int i = index; i < itemCount - 1; i++) {
        items[i] = items[i + 1];
    }
    itemCount--;
    return true;
}

int ShoppingCart::getItemCount() const {
    return itemCount;
}

long long ShoppingCart::getSubtotal() const {
    long long total = 0;
    for (int i = 0; i < itemCount; i++) {
        total += items[i].getTotalPrice();
    }
    return total;
}

int ShoppingCart::getTotalQuantity() const {
    int total = 0;
    for (int i = 0; i < itemCount; i++) {
        total += items[i].getQuantity();
    }
    return total;
}

bool ShoppingCart::isEmpty() const {
    return itemCount == 0;
}

void ShoppingCart::clear() {
    itemCount = 0;
}

void ShoppingCart::print() const {
    if (isEmpty()) {
        cout << "Gio hang dang rong.\n";
        return;
    }
    for (int i = 0; i < itemCount; i++) {
        items[i].print();
    }
    cout << "Tong so luong: " << getTotalQuantity() << '\n';
    cout << "Tong tien hang: " << getSubtotal() << " VND\n";
}
