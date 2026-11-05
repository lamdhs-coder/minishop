#ifndef ORDER_H
#define ORDER_H

#include <ctime>
#include <ostream>
#include <string>
#include <vector>
#include "Customer.h"
#include "CartItem.h"

// Hai ham trinh bay dung chung cho Console va hoa don TXT.
std::string formatMoney(long long amount);
void writeItemsTable(std::ostream& output, const std::vector<CartItem>& items);

class Order {
private:
    Customer customer;
    std::vector<CartItem> items;
    std::time_t orderTime;
    long long shippingFee;

public:
    Order(const Customer& customer, const std::vector<CartItem>& items);
    const Customer& getCustomer() const;
    const std::vector<CartItem>& getItems() const;
    std::string getOrderDate() const;
    std::string getEstimatedDeliveryDate() const;
    long long getShippingFee() const;
    long long getSubtotal() const;
    long long getTotalPayment() const;
    std::string getReceiptText() const;
    // file trong: tu tao ten theo thoi gian, them hau to neu trung.
    // Tra ve duong dan da ghi; nem runtime_error neu ghi that bai.
    std::string saveReceiptToFile(const std::string& filename = "") const;
};

#endif
