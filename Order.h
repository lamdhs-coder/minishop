#ifndef ORDER_H
#define ORDER_H

#include <ctime>
#include <ostream>
#include <string>
#include <vector>
#include "Customer.h"
#include "CartItem.h"
#include "ShippingMethod.h"

using namespace std;

// Hai ham trinh bay dung chung cho Console va hoa don TXT.
string formatMoney(long long amount);
void writeItemsTable(ostream& output, const vector<CartItem>& items);

class Order {
private:
    Customer customer;
    vector<CartItem> items;
    time_t orderTime;
    long long shippingFee;
    int deliveryDays;

public:
    Order(const Customer& customer, const vector<CartItem>& items);
    // Nhan qua tham chieu lop cha de goi phuong thuc ao cua lop con.
    // Chi luu gia tri phi/ngay; khong giu tham chieu den shipping.
    Order(const Customer& customer, const vector<CartItem>& items,
          const ShippingMethod& shipping);
    const Customer& getCustomer() const;
    const vector<CartItem>& getItems() const;
    string getOrderDate() const;
    string getEstimatedDeliveryDate() const;
    long long getShippingFee() const;
    long long getSubtotal() const;
    long long getTotalPayment() const;
    string getReceiptText() const;
    // file trong: tu tao ten theo thoi gian, them hau to neu trung.
    // Tra ve duong dan da ghi; nem runtime_error neu ghi that bai.
    string saveReceiptToFile(const string& filename = "") const;
};

#endif
