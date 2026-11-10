#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    int id;
    std::string name;
    long long price;

public:
    Product();
    Product(int id, const std::string& name, long long price);

    // CH? KHAI BÁO, KHÔNG VI?T THÂN HÀM TRONG FILE .H
    int getId() const;
    std::string getName() const;
    long long getPrice() const;

    void setId(int id);
    void setName(const std::string& name);
    void setPrice(long long price);
};

#endif
