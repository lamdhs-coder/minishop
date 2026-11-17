#pragma once

#include <string>
#include <vector>
#include "Product.h"

using namespace std;

// MEMBER 2: Khong mo duoc file / du lieu sai -> nem runtime_error.
// Moi dong: id|name|price. Khong tra danh sach gia khi doc that bai.
vector<Product> loadProductsFromFile(const string& filename);
