#pragma once

#include "CartItem.h"

class ShoppingCart {
public:
    static const int MAX_ITEMS = 100;

private:
    CartItem items[MAX_ITEMS];
    int itemCount;
    int findProduct(int productId) const;

public:
    ShoppingCart();
    bool addProduct(const Product& product);
    bool increaseQuantity(int productId);
    bool decreaseQuantity(int productId);
    bool removeProduct(int productId);
    int getItemCount() const;
    long long getSubtotal() const;
    int getTotalQuantity() const;
    bool isEmpty() const;
    void clear();
    void print() const;
};
