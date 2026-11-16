#include "Customer.h"
#include <stdexcept>

using namespace std;

Customer::Customer(const string& name, const string& phone,
                   const string& address)
    : name(name), phone(phone), address(address) {
    // Kiem tra tai class de du lieu van hop le khi tao ngoai menu.
    if (name.find_first_not_of(" \t\r\n\f\v") == string::npos) {
        throw invalid_argument("Ten khach hang khong duoc de trong.");
    }
    if (address.find_first_not_of(" \t\r\n\f\v") == string::npos) {
        throw invalid_argument("Dia chi giao hang khong duoc de trong.");
    }
    if (phone.size() != 10 || phone[0] != '0') {
        throw invalid_argument("So dien thoai phai gom 10 chu so, bat dau bang 0.");
    }
    for (char digit : phone) {
        if (digit < '0' || digit > '9') {
            throw invalid_argument("So dien thoai chi duoc chua chu so.");
        }
    }
}

const string& Customer::getName() const {
    return name;
}

const string& Customer::getPhone() const {
    return phone;
}

const string& Customer::getAddress() const {
    return address;
}
