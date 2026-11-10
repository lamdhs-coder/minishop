#include "Customer.h"

Customer::Customer() : name(""), address(""), phone("") {}

Customer::Customer(const std::string& name, const std::string& address, const std::string& phone)
    : name(name), address(address), phone(phone) {}

std::string Customer::getName() const {
    return name;
}

std::string Customer::getAddress() const {
    return address;
}

std::string Customer::getPhone() const {
    return phone;
}

void Customer::setName(const std::string& name) {
    this->name = name;
}

void Customer::setAddress(const std::string& address) {
    this->address = address;
}

void Customer::setPhone(const std::string& phone) {
    this->phone = phone;
}
