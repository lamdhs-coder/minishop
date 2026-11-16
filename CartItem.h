#pragma once

#include "Product.h"

class CartItem {
private:
    Product product;
    int quantity;

public:
    static const int MAX_QUANTITY = 999;

    CartItem(const Product& product = Product(), int quantity = 1);
    const Product& getProduct() const;
    int getQuantity() const;
    bool increaseQuantity();
    void decreaseQuantity();
    long long getTotalPrice() const;
    void print() const;
};
