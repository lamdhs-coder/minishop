#ifndef CART_ITEM_H
#define CART_ITEM_H

#include "Product.h"

// MEMBER 2: Mot dong trong gio; so luong 0 se duoc ShoppingCart xoa.
class CartItem {
private:
    Product product;
    int quantity;

public:
    CartItem(const Product& product, int quantity = 1);
    const Product& getProduct() const;
    int getQuantity() const;
    void increaseQuantity();
    void decreaseQuantity();
    long long getTotalPrice() const;
};

#endif
