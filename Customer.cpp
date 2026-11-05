#include "Customer.h"
#include <stdexcept>

Customer::Customer(const std::string& name, const std::string& phone,
                   const std::string& address)
    : name(name), phone(phone), address(address) {
    // TODO: MEMBER 3 - Hoan thien constructor luu thong tin khach.
    throw std::logic_error("TODO: MEMBER 3 - Customer::Customer");
}

const std::string& Customer::getName() const {
    // TODO: MEMBER 3 - Tra ve ho ten.
    throw std::logic_error("TODO: MEMBER 3 - Customer::getName");
}

const std::string& Customer::getPhone() const {
    // TODO: MEMBER 3 - Tra ve so dien thoai (giu so 0 dau).
    throw std::logic_error("TODO: MEMBER 3 - Customer::getPhone");
}

const std::string& Customer::getAddress() const {
    // TODO: MEMBER 3 - Tra ve dia chi giao hang.
    throw std::logic_error("TODO: MEMBER 3 - Customer::getAddress");
}
