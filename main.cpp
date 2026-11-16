#include <iostream>
#include "Order.h"
#include "Text.h"
#include "ProductFile.h"

using namespace std;

// Doc het mot dong, khong ghi vuot mang va khong de lai ky tu du.
bool readText(const char prompt[], char text[], int capacity) {
    while (true) {
        cout << prompt;
        int length = 0;
        bool tooLong = false;
        bool gotLine = false;
        char letter;
        while (cin.get(letter)) {
            gotLine = true;
            if (letter == '\n') {
                break;
            }
            if (length < capacity - 1) {
                text[length] = letter;
                length++;
            } else {
                tooLong = true;
            }
        }
        text[length] = '\0';
        if (!gotLine) {
            return false;
        }
        if (!tooLong && hasText(text)) {
            return true;
        }
        cout << "[LOI] Nhap noi dung tu 1 den " << capacity - 1 << " ky tu.\n";
        if (!cin) {
            return false;
        }
    }
}

bool readInt(const char prompt[], int minimum, int maximum, int& value) {
    char text[32];
    while (readText(prompt, text, 32)) {
        int number = 0;
        bool valid = true;
        for (int i = 0; text[i] != '\0'; i++) {
            if (text[i] < '0' || text[i] > '9') {
                valid = false;
                break;
            }
            int digit = text[i] - '0';
            // Kiem tra truoc khi nhan 10, tranh tran int khi nhap so dai.
            if (number > maximum / 10
                || (number == maximum / 10 && digit > maximum % 10)) {
                valid = false;
                break;
            }
            number = number * 10 + digit;
        }
        if (valid && number >= minimum) {
            value = number;
            return true;
        }
        cout << "[LOI] Nhap so nguyen tu " << minimum << " den " << maximum << ".\n";
    }
    return false;
}

void showProducts(const Product products[], int count) {
    if (count == 0) {
        cout << "Danh sach san pham rong.\n";
        return;
    }
    cout << "\nMa | Ten san pham | Don gia\n";
    for (int i = 0; i < count; i++) {
        products[i].print();
    }
}

void searchProducts(const Product products[], int count) {
    char keyword[100];
    if (!readText("Nhap mot phan ten san pham: ", keyword, 100)) {
        return;
    }
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (containsText(products[i].getName(), keyword)) {
            products[i].print();
            found = true;
        }
    }
    if (!found) {
        cout << "Khong tim thay san pham.\n";
    }
}

void addToCart(const Product products[], int count, ShoppingCart& cart) {
    showProducts(products, count);
    int id;
    if (!readInt("Ma san pham (0: Quay lai): ", 0, 2147483647, id) || id == 0) {
        return;
    }
    for (int i = 0; i < count; i++) {
        if (products[i].getId() == id) {
            if (cart.addProduct(products[i])) {
                cout << "Da them san pham vao gio.\n";
            } else {
                cout << "Gio da day hoac so luong da dat 999.\n";
            }
            return;
        }
    }
    cout << "Khong tim thay ma san pham.\n";
}

void editCart(ShoppingCart& cart) {
    while (!cart.isEmpty()) {
        cart.print();
        cout << "1. Tang so luong\n2. Giam so luong\n3. Xoa san pham\n0. Quay lai\n";
        int action, id;
        if (!readInt("Chon thao tac: ", 0, 3, action) || action == 0
            || !readInt("Ma san pham (0: Quay lai): ", 0, 2147483647, id) || id == 0) {
            return;
        }
        bool changed;
        if (action == 1) {
            changed = cart.increaseQuantity(id);
        } else if (action == 2) {
            changed = cart.decreaseQuantity(id);
        } else {
            changed = cart.removeProduct(id);
        }
        if (changed) {
            cout << "Da cap nhat gio hang.\n";
        } else {
            cout << "Ma khong co trong gio hoac so luong da dat 999.\n";
        }
    }
    cout << "Gio hang dang rong.\n";
}

void checkout(ShoppingCart& cart) {
    if (cart.isEmpty()) {
        cout << "Khong the dat hang khi gio rong.\n";
        return;
    }
    char name[100], phone[11], address[200];
    if (!readText("Ho va ten: ", name, 100)) {
        return;
    }
    while (true) {
        if (!readText("Dien thoai (10 chu so, bat dau bang 0): ", phone, 11)) {
            return;
        }
        if (Customer::isValidPhone(phone)) {
            break;
        }
        cout << "So dien thoai khong hop le.\n";
    }
    if (!readText("Dia chi: ", address, 200)) {
        return;
    }
    Customer customer(name, phone, address);
    StandardShipping shipping;
    Order order(customer, cart, shipping);
    if (!order.isValid()) {
        cout << "Khong tao duoc don hang.\n";
        return;
    }
    cout << "\n[XEM TRUOC - CHUA DAT HANG]\n";
    order.print();
    int confirm;
    if (!readInt("Xac nhan dat hang? (1: Co, 0: Huy): ", 0, 1, confirm) || confirm == 0) {
        cout << "Chua dat hang. Gio hang duoc giu nguyen.\n";
        return;
    }
    cart.clear();
    cout << "Dat hang thanh cong!\n";
    order.print();
}

void showMenu() {
    cout << "\n========== MINISHOP ==========\n"
         << "1. Xem san pham\n2. Tim kiem san pham\n3. Them vao gio\n"
         << "4. Xem gio hang\n5. Chinh sua gio hang\n6. Dat hang\n0. Thoat\n";
}

int main() {
    Product products[100];
    int productCount;
    char error[200];
    if (!loadProductsFromFile("products.txt", products, 100, productCount, error)) {
        cout << "[LOI] " << error << '\n';
        return 1;
    }
    ShoppingCart cart;
    while (true) {
        showMenu();
        int choice;
        if (!readInt("Chon: ", 0, 6, choice) || choice == 0) {
            break;
        }
        switch (choice) {
            case 1: showProducts(products, productCount); break;
            case 2: searchProducts(products, productCount); break;
            case 3: addToCart(products, productCount, cart); break;
            case 4: cart.print(); break;
            case 5: editCart(cart); break;
            case 6: checkout(cart); break;
        }
    }
    cout << "Tam biet!\n";
    return 0;
}
