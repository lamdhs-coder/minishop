#pragma once

#include <string>

using namespace std;

// MEMBER 3: Chi luu du lieu, khong nhap/xuat Console.
class Customer {
private:
    string name;
    string phone;
    string address;

public:
    // Ten/dia chi phai co noi dung; SDT gom 10 chu so, bat dau bang 0.
    // Du lieu sai -> nem invalid_argument; khong nhap/xuat Console.
    Customer(const string& name, const string& phone,
             const string& address);
    const string& getName() const;
    const string& getPhone() const;
    const string& getAddress() const;
};
