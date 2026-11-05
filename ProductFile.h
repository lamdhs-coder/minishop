#ifndef PRODUCT_FILE_H
#define PRODUCT_FILE_H

#include <string>
#include <vector>
#include "Product.h"

// MEMBER 2: Khong mo duoc file / du lieu sai -> nem std::runtime_error.
// Moi dong: id|name|price. Khong tra danh sach gia khi doc that bai.
std::vector<Product> loadProductsFromFile(const std::string& filename);

#endif
