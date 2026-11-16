#ifndef PRODUCT_FILE_H
#define PRODUCT_FILE_H

#include <string>
#include <vector>
#include "Product.h"

using namespace std;

// MEMBER 2: Khong mo duoc file / du lieu sai -> nem runtime_error.
// Moi dong: id|name|price. Khong tra danh sach gia khi doc that bai.
vector<Product> loadProductsFromFile(const string& filename);

// Luu qua file tam cung thu muc, chi thay file goc sau khi ghi/dong thanh cong.
// Nem exception neu file thieu/khong ghi duoc, ma trung hoac ten sai dinh dang.
// Khong thay doi vector san pham cua ben goi.
void appendProductToFile(const string& filename, const Product& product);

#endif
