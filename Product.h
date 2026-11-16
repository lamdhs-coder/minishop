#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>

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

// MEMBER 3: Loc ca hai dau mut; tu doi cho neu nhap khoang gia nguoc.
// Dung long long de so sanh chinh xac voi gia VND cua Product.
vector<Product> filterByPriceRange(const vector<Product>& products,
                                       long long minPrice, long long maxPrice);

#endif
