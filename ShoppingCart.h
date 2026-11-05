#ifndef SHOPPING_CART_H
#define SHOPPING_CART_H

#include <vector>
#include "CartItem.h"

// MEMBER 2: Noi duy nhat quan ly cac thay doi trong gio hang.
class ShoppingCart {
private:
    std::vector<CartItem> items;

public:
    // Them moi voi SL 1; neu trung id thi tang SL 1.
    void addProduct(const Product& product);
    // Tra false neu khong tim thay id; true khi da thay doi.
    bool increaseQuantity(int productId);
    bool decreaseQuantity(int productId);
    bool removeProduct(int productId);
    const std::vector<CartItem>& getItems() const;
    long long getSubtotal() const;
    long long getTotalQuantity() const;
    bool isEmpty() const;
    void clear();
};

#endif
