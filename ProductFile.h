#pragma once

#include "Product.h"

// Loi: tra false, count = 0 va ghi ly do vao error (toi da 199 ky tu).
bool loadProductsFromFile(const char filename[], Product products[],
                          int capacity, int& count, char error[]);
