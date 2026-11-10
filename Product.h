#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

// MEMBER 3: Du lieu cua mot san pham. Gia tinh bang VND.
class Product {
private:
    int id;
    std::string name;
    long long price;

public:
    // Nem std::invalid_argument neu id/gia <= 0 hoac ten chi co khoang trang.
    Product(int id, const std::string& name, long long price);
    int getId() const;
    const std::string& getName() const;
    long long getPrice() const;
};

#endif
