#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

// MEMBER 3: Chi luu du lieu, khong nhap/xuat Console.
class Customer {
private:
    std::string name;
    std::string phone;
    std::string address;

public:
    Customer(const std::string& name, const std::string& phone,
             const std::string& address);
    const std::string& getName() const;
    const std::string& getPhone() const;
    const std::string& getAddress() const;
};

#endif
