#include "Order.h"
#include <iostream>

using namespace std;

Order::Order(const Customer& customer, const ShoppingCart& cart,
             const ShippingMethod& shipping) : customer(customer), cart(cart) {
    shippingFee = shipping.getFee();
    deliveryDays = shipping.getDeliveryDays();
}

bool Order::isValid() const {
    return customer.isValid() && !cart.isEmpty()
        && shippingFee >= 0 && shippingFee <= Product::MAX_PRICE
        && deliveryDays >= 0 && deliveryDays <= 30;
}

long long Order::getShippingFee() const {
    return shippingFee;
}

int Order::getDeliveryDays() const {
    return deliveryDays;
}

long long Order::getSubtotal() const {
    return cart.getSubtotal();
}

long long Order::getTotalPayment() const {
    if (!isValid()) {
        return 0;
    }
    return getSubtotal() + shippingFee;
}

void Order::print() const {
    if (!isValid()) {
        cout << "Don hang khong hop le.\n";
        return;
    }
    cout << "\n========== HOA DON MINISHOP ==========\n";
    cout << "Khach hang: " << customer.getName() << '\n';
    cout << "Dien thoai: " << customer.getPhone() << '\n';
    cout << "Dia chi: " << customer.getAddress() << '\n';
    cart.print();
    cout << "Phi van chuyen: " << shippingFee << " VND\n";
    cout << "Tong thanh toan: " << getTotalPayment() << " VND\n";
    cout << "Du kien giao sau " << deliveryDays << " ngay.\n";
}
