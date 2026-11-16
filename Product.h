#pragma once

class Product {
private:
    int id;
    char name[100];
    long long price;

public:
    static const int MAX_PRICE = 1000000000;

    Product(int id = 0, const char name[] = "", long long price = 0);
    int getId() const;
    const char* getName() const;
    long long getPrice() const;
    bool isValid() const;
    bool operator==(const Product& other) const;
    void print() const;
};
