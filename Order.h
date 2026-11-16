#pragma once

#include "Customer.h"
#include "ShoppingCart.h"
#include "ShippingMethod.h"

class Order {
private:
    Customer customer;
    ShoppingCart cart;
    long long shippingFee;
    int deliveryDays;

public:
    Order(const Customer& customer, const ShoppingCart& cart,
          const ShippingMethod& shipping);
    bool isValid() const;
    long long getShippingFee() const;
    int getDeliveryDays() const;
    long long getSubtotal() const;
    long long getTotalPayment() const;
    void print() const;
};
