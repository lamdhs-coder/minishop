#include "ProductFile.h"
#include "Text.h"
#include <fstream>

using namespace std;

// Chuong 6: mot cach doc so nguyen duong cho ca int va long long.
template <class T>
bool parsePositiveInteger(const char text[], T maximum, T& value) {
    T number = 0;
    if (text[0] == '\0') {
        return false;
    }
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] < '0' || text[i] > '9') {
            return false;
        }
        int digit = text[i] - '0';
        if (number > maximum / 10
            || (number == maximum / 10 && digit > maximum % 10)) {
            return false;
        }
        number = number * 10 + digit;
    }
    value = number;
    return number > 0;
}

bool loadProductsFromFile(const char filename[], Product products[],
                          int capacity, int& count, char error[]) {
    count = 0;
    error[0] = '\0';
    ifstream file(filename);
    if (!file) {
        copyText(error, 200, "Khong mo duoc file san pham.");
        return false;
    }
    char line[256];
    int loaded = 0;
    while (true) {
        if (!file.getline(line, 256)) {
            if (file.eof() && file.gcount() == 0) {
                break;
            }
            copyText(error, 200, "Loi doc file hoac dong du lieu qua dai.");
            return false;
        }
        int length = textLength(line);
        if (length > 0 && line[length - 1] == '\r') {
            line[length - 1] = '\0';
        }
        int first = -1;
        int second = -1;
        bool extra = false;
        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] == '|') {
                if (first == -1) {
                    first = i;
                } else if (second == -1) {
                    second = i;
                } else {
                    extra = true;
                }
            }
        }
        if (first == -1 || second == -1 || extra) {
            copyText(error, 200, "Moi dong phai co dang id|name|price.");
            return false;
        }
        // Chia dong thanh ba chuoi ngay trong mang line.
        line[first] = '\0';
        line[second] = '\0';
        int id;
        long long price;
        if (!parsePositiveInteger(line, 2147483647, id)
            || !parsePositiveInteger(line + second + 1, (long long) Product::MAX_PRICE, price)) {
            copyText(error, 200, "Ma hoac gia san pham khong hop le.");
            return false;
        }
        Product product(id, line + first + 1, price);
        if (!product.isValid()) {
            copyText(error, 200, "Ten san pham trong hoac qua dai.");
            return false;
        }
        for (int i = 0; i < loaded; i++) {
            if (products[i] == product) {
                copyText(error, 200, "Ma san pham bi trung.");
                return false;
            }
        }
        if (loaded >= capacity) {
            copyText(error, 200, "So san pham vuot suc chua cua mang.");
            return false;
        }
        products[loaded] = product;
        loaded++;
    }
    count = loaded;
    return true;
}
