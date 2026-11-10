#include "Order.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>

// Hàm d?nh d?ng ngày tháng tuong thích t?t trên m?i trình biên d?ch C++
namespace {
    std::string formatDateTime(time_t rawTime, const char* format) {
        struct tm* timeInfo = localtime(&rawTime);
        char buffer[80];
        strftime(buffer, sizeof(buffer), format, timeInfo);
        return std::string(buffer);
    }
}

// Ð?nh d?ng hi?n th? ti?n t?
std::string formatMoney(long long amount) {
    std::string number = std::to_string(amount);
    int n = number.length();
    int insertPosition = n - 3;
    while (insertPosition > 0) {
        number.insert(insertPosition, ".");
        insertPosition -= 3;
    }
    return number + " VND";
}

// Hàm kh?i t?o Order
Order::Order(const Customer& customer) : customer(customer), createdAt(time(0)) {}

void Order::addItem(const Product& product, int quantity) {
    items.push_back({product, quantity});
}

long long Order::calculateTotal() const {
    long long total = 0;
    for (const auto& item : items) {
        total += item.product.getPrice() * item.quantity;
    }
    return total;
}

// Xu?t hóa don chi ti?t
std::string Order::getReceiptText() const {
    std::stringstream ss;
    ss << "========================================\n";
    ss << "            HOA DON BAN HANG            \n";
    ss << "========================================\n";
    ss << "Thoi gian: " << formatDateTime(createdAt, "%Y-%m-%d %H:%M:%S") << "\n";
    ss << "Khach hang: " << customer.getName() << "\n";
    ss << "Dia chi   : " << customer.getAddress() << "\n";
    ss << "SÐT       : " << customer.getPhone() << "\n";
    ss << "----------------------------------------\n";
    ss << std::left << std::setw(20) << "Ten san pham" 
       << std::setw(8) << "SL" 
       << "Don gia\n";
    ss << "----------------------------------------\n";

    for (const auto& item : items) {
        ss << std::left << std::setw(20) << item.product.getName()
           << std::setw(8) << item.quantity
           << formatMoney(item.product.getPrice()) << "\n";
    }

    ss << "----------------------------------------\n";
    ss << "TONG TIEN: " << formatMoney(calculateTotal()) << "\n";
    ss << "========================================\n";
    
    return ss.str();
}
