#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include <ctime>
#include "Customer.h"
#include "Product.h" // ho?c "CartItem.h" tùy tên file c?a b?n

struct OrderItem {
    Product product;
    int quantity;
};

class Order {
private:
    Customer customer;
    std::vector<OrderItem> items;
    time_t createdAt;

public:
    // Constructor nh?n 1 tham s? Customer
    Order(const Customer& customer);

    // Các phuong th?c
    void addItem(const Product& product, int quantity);
    long long calculateTotal() const;
    std::string getReceiptText() const;
};

#endif
