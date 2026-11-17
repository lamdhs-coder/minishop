#pragma once

#include <string>

using namespace std;

// MEMBER 3: Du lieu cua mot san pham. Gia tinh bang VND.
class Product {
private:
    int id;
    string name;
    long long price;

public:
    // Nem invalid_argument neu id/gia <= 0 hoac ten chi co khoang trang.
    Product(int id, const string& name, long long price);
    int getId() const;
    const string& getName() const;
    long long getPrice() const;
    // Hai san pham cung ma duoc xem la cung mot mat hang.
    bool operator==(const Product& other) const;
};
