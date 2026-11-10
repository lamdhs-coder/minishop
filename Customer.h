#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer {
private:
    std::string name;
    std::string address;
    std::string phone;

public:
    Customer();
    Customer(const std::string& name, const std::string& address, const std::string& phone);

    std::string getName() const;
    std::string getAddress() const;
    std::string getPhone() const;

    void setName(const std::string& name);
    void setAddress(const std::string& address);
    void setPhone(const std::string& phone);
};

#endif
