#include "Customer.h"
#include "Text.h"

Customer::Customer(const char name[], const char phone[], const char address[]) {
    copyText(this->name, 100, name);
    copyText(this->phone, 11, phone);
    copyText(this->address, 200, address);
}

const char* Customer::getName() const {
    return name;
}

const char* Customer::getPhone() const {
    return phone;
}

const char* Customer::getAddress() const {
    return address;
}

bool Customer::isValidPhone(const char phone[]) {
    if (textLength(phone) != 10 || phone[0] != '0') {
        return false;
    }
    for (int i = 0; i < 10; i++) {
        if (phone[i] < '0' || phone[i] > '9') {
            return false;
        }
    }
    return true;
}

bool Customer::isValid() const {
    return hasText(name) && hasText(address) && isValidPhone(phone);
}
