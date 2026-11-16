#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>

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
    // Hai san pham cung ma duoc xem la cung mot mat hang.
    bool operator==(const Product& other) const;
};

// MEMBER 3: Loc ca hai dau mut; tu doi cho neu nhap khoang gia nguoc.
// Dung long long de so sanh chinh xac voi gia VND cua Product.
std::vector<Product> filterByPriceRange(const std::vector<Product>& products,
                                       long long minPrice, long long maxPrice);

#endif
