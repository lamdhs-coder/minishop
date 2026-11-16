#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <utility>

#include "Order.h"
#include "ProductFile.h"
#include "ShoppingCart.h"

using namespace std;

// Logic cac thanh vien da duoc ghep; bat cac chuc nang tren menu.
constexpr bool MEMBER_LOGIC_READY = true;

string trim(const string& text) {
    const size_t first = text.find_first_not_of(" \t\r\n");
    if (first == string::npos) {
        return "";
    }
    const size_t last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

bool readLine(const string& prompt, string& text) {
    cout << prompt;
    if (!getline(cin, text)) {
        return false; // EOF: thoat luong nhap, khong lap vo han.
    }
    text = trim(text);
    return true;
}

bool readInt(const string& prompt, int minimum, int maximum, int& value) {
    string text;
    while (readLine(prompt, text)) {
        istringstream input(text);
        int number;
        char extra;
        // "2abc", "2.5", so qua lon va chuoi rong deu bi tu choi.
        if ((input >> number) && !(input >> extra)
            && number >= minimum && number <= maximum) {
            value = number;
            return true;
        }
        cout << "[LOI] Vui long nhap so nguyen tu "
                  << minimum << " den " << maximum << ".\n";
    }
    return false;
}

bool readRequiredText(const string& prompt, string& text) {
    while (readLine(prompt, text)) {
        if (!text.empty()) {
            return true;
        }
        cout << "[LOI] Thong tin khong duoc de trong.\n";
    }
    return false;
}

bool readPrice(const string& prompt, long long& price, bool allowZero = true) {
    string text;
    while (readLine(prompt, text)) {
        istringstream input(text);
        long long value;
        char extra;
        if ((input >> value) && !(input >> extra) && value >= 0
            && (allowZero || value > 0)) {
            price = value;
            return true;
        }
        cout << "[LOI] Gia phai la so nguyen VND "
                  << (allowZero ? "khong am" : "lon hon 0") << ", khong vuot "
                  << numeric_limits<long long>::max()
                  << ". Vi du: 250000.\n";
    }
    return false;
}

bool isValidPhone(const string& phone) {
    if (phone.size() != 10 || phone[0] != '0') {
        return false;
    }
    for (char digit : phone) {
        if (digit < '0' || digit > '9') {
            return false;
        }
    }
    return true;
}

bool readPhone(string& phone) {
    while (readLine("So dien thoai (10 chu so, bat dau bang 0): ", phone)) {
        if (isValidPhone(phone)) {
            return true;
        }
        cout << "[LOI] So dien thoai phai gom 10 chu so va bat dau bang 0.\n";
    }
    return false;
}

bool askYesNo(const string& prompt, bool& answer) {
    int choice;
    if (!readInt(prompt + " (1: Co, 0: Khong): ", 0, 1, choice)) {
        return false;
    }
    answer = (choice == 1);
    return true;
}

void waitForMenu() {
    string ignored;
    readLine("\nNhan Enter de ve menu chinh...", ignored);
}

void showMainMenu() {
    cout << "\n==========================================\n"
              << "                 MINISHOP\n"
              << "            UNG DUNG DAT HANG\n"
              << "==========================================\n"
              << "1. Xem danh sach san pham\n"
              << "2. Tim kiem san pham\n"
              << "3. Them san pham vao gio\n"
              << "4. Xem gio hang\n"
              << "5. Chinh sua gio hang\n"
              << "6. Dat hang\n"
              << "7. Loc san pham theo khoang gia\n"
              << "8. Them san pham moi vao shop\n"
              << "0. Thoat\n"
              << "==========================================\n";
}

string shortName(const string& name) {
    return name.size() <= 32 ? name : name.substr(0, 29) + "...";
}

void showProducts(const vector<Product>& products) {
    if (products.empty()) {
        cout << "[THONG BAO] Khong co san pham de hien thi.\n";
        return;
    }
    cout << string(66, '-') << '\n'
              << left << setw(6) << "Ma"
              << setw(32) << "Ten san pham"
              << right << setw(28) << "Don gia" << '\n'
              << string(66, '-') << '\n';
    for (const Product& product : products) {
        cout << left << setw(6) << product.getId()
                  << setw(32) << shortName(product.getName())
                  << right << setw(28) << formatMoney(product.getPrice()) << '\n';
    }
    cout << string(66, '-') << '\n';
}

string lowercaseAscii(string text) {
    for (char& letter : text) {
        if (letter >= 'A' && letter <= 'Z') {
            letter = static_cast<char>(letter - 'A' + 'a');
        }
    }
    return text;
}

void searchProducts(const vector<Product>& products) {
    string keyword;
    if (!readRequiredText("Nhap mot phan ten san pham: ", keyword)) {
        return;
    }
    keyword = lowercaseAscii(keyword);
    vector<Product> matches; // Ket qua tim kiem, khong phai gio hang.
    for (const Product& product : products) {
        if (lowercaseAscii(product.getName()).find(keyword) != string::npos) {
            matches.push_back(product);
        }
    }
    if (matches.empty()) {
        cout << "[THONG BAO] Khong tim thay san pham phu hop.\n";
    } else {
        showProducts(matches);
    }
}

void showProductsByPrice(const vector<Product>& products) {
    long long minPrice, maxPrice;
    if (!readPrice("Gia thap nhat (VND): ", minPrice)
        || !readPrice("Gia cao nhat (VND): ", maxPrice)) {
        return;
    }
    if (minPrice > maxPrice) {
        cout << "[THONG BAO] Khoang gia bi nguoc, tu doi cho hai moc gia.\n";
    }
    const vector<Product> matches = filterByPriceRange(products, minPrice, maxPrice);
    if (matches.empty()) {
        cout << "[THONG BAO] Khong co san pham trong khoang gia nay.\n";
    } else {
        showProducts(matches);
    }
}

void addNewProduct(vector<Product>& products) {
    cout << "\n==========================================\n"
              << "           THEM SAN PHAM MOI\n"
              << "==========================================\n";
    int id;
    while (true) {
        if (!readInt("Nhap ma san pham (0: Huy): ", 0,
                     numeric_limits<int>::max(), id)) {
            return;
        }
        if (id == 0) {
            cout << "[THONG BAO] Da huy them san pham.\n";
            return;
        }
        bool duplicate = false;
        for (const Product& item : products) {
            if (item.getId() == id) {
                duplicate = true;
                break;
            }
        }
        if (!duplicate) {
            break;
        }
        cout << "[LOI] Ma san pham da ton tai. Vui long nhap ma khac.\n";
    }

    string name;
    while (true) {
        if (!readRequiredText("Nhap ten san pham: ", name)) {
            return;
        }
        if (name.find_first_not_of(" \t\r\n\f\v") != string::npos
            && name.find_first_of("|\r\n") == string::npos) {
            break;
        }
        cout << "[LOI] Ten phai co noi dung, khong chua | hoac xuong dong.\n";
    }
    long long price;
    if (!readPrice("Nhap gia san pham (VND): ", price, false)) {
        return;
    }
    Product product(id, name, price);
    // Du bo nho truoc khi ghi. Sau khi luu, move Product khong cap phat chuoi lai.
    products.reserve(products.size() + 1);
    appendProductToFile("products.txt", product);
    products.push_back(move(product));
    const Product& saved = products.back();
    cout << "[THANH CONG] Da them san pham moi vao shop.\n"
              << "Ma SP : " << saved.getId() << '\n'
              << "Ten SP: " << saved.getName() << '\n'
              << "Gia   : " << formatMoney(saved.getPrice()) << '\n';
}

void addToCart(const vector<Product>& products, ShoppingCart& cart) {
    showProducts(products);
    if (products.empty()) {
        return;
    }
    int productId;
    if (!readInt("Nhap ma san pham (0: Quay lai): ", 0,
                 numeric_limits<int>::max(), productId)
        || productId == 0) {
        return;
    }
    for (const Product& product : products) {
        if (product.getId() == productId) {
            cart.addProduct(product); // ShoppingCart tu xu ly san pham trung.
            cout << "[THANH CONG] Da them san pham vao gio.\n";
            return;
        }
    }
    cout << "[LOI] Ma san pham khong ton tai.\n";
}

void showCart(const ShoppingCart& cart) {
    if (cart.isEmpty()) {
        cout << "[THONG BAO] Gio hang dang rong.\n";
        return;
    }
    cout << "\nGIO HANG\n";
    writeItemsTable(cout, cart.getItems());
    cout << "Tong so luong: " << cart.getTotalQuantity() << '\n'
              << "Tong tien hang: " << formatMoney(cart.getSubtotal()) << '\n';
    cout << "Ma san pham trong gio: ";
    for (const CartItem& item : cart.getItems()) {
        cout << item.getProduct().getId() << " ";
    }
    cout << '\n';
}

void editCart(ShoppingCart& cart) {
    while (cin) {
        showCart(cart);
        if (cart.isEmpty()) {
            return;
        }
        cout << "\n1. Tang so luong them 1\n"
                  << "2. Giam so luong bot 1 (ve 0 thi xoa)\n"
                  << "3. Xoa san pham\n0. Quay lai\n";
        int action;
        if (!readInt("Chon thao tac: ", 0, 3, action) || action == 0) {
            return;
        }
        int productId;
        if (!readInt("Nhap ma san pham (0: Quay lai): ", 0,
                     numeric_limits<int>::max(), productId)
            || productId == 0) {
            return;
        }
        bool changed = false;
        if (action == 1) {
            changed = cart.increaseQuantity(productId);
        } else if (action == 2) {
            changed = cart.decreaseQuantity(productId);
        } else {
            changed = cart.removeProduct(productId);
        }
        cout << (changed ? "[THANH CONG] Da cap nhat gio hang.\n"
                              : "[LOI] Ma san pham khong co trong gio.\n");
    }
}

void checkout(ShoppingCart& cart) {
    if (cart.isEmpty()) {
        cout << "[LOI] Khong the dat hang khi gio rong.\n";
        return;
    }
    string name, phone, address;
    if (!readRequiredText("Ho va ten: ", name) || !readPhone(phone)
        || !readRequiredText("Dia chi giao hang: ", address)) {
        return;
    }
    const Customer customer(name, phone, address);

    // Ban xem truoc chi hien thi: khong ghi file, khong sua gio.
    const Order preview(customer, cart.getItems());
    cout << "\n[XEM TRUOC - CHUA XAC NHAN DAT HANG]\n"
              << preview.getReceiptText();
    bool confirmed;
    if (!askYesNo("Ban xac nhan dat hang?", confirmed) || !confirmed) {
        cout << "[THONG BAO] Chua dat hang. Gio hang duoc giu nguyen.\n";
        return;
    }

    // Tao lai de lay thoi gian HE THONG ngay sau khi khach xac nhan.
    const Order order(customer, cart.getItems());
    cart.clear(); // Don da giu ban sao, xoa gio khong lam mat hoa don.
    cout << "\n[THANH CONG] Dat hang thanh cong!\n"
              << order.getReceiptText();

    bool save;
    if (!askYesNo("Ban muon luu hoa don TXT?", save) || !save) {
        return;
    }
    try {
        const string path = order.saveReceiptToFile();
        cout << "[THANH CONG] Da luu hoa don: " << path << '\n';
    } catch (const exception& error) {
        // Loi luu file khong huy don da xac nhan.
        cout << "[LOI] Don da xac nhan nhung khong luu duoc hoa don: "
                  << error.what() << '\n';
    }
}

int main() {
    vector<Product> products;
    ShoppingCart cart;

    cout << "Chao mung ban den voi MiniShop!\n";
    if (!MEMBER_LOGIC_READY) {
        cout << "[TRANG THAI] Cac chuc nang chua duoc bat tich hop.\n";
    } else {
        try {
            products = loadProductsFromFile("products.txt");
        } catch (const exception& error) {
            cerr << "[LOI] Khong tai duoc danh sach san pham: "
                      << error.what() << "\nHay kiem tra products.txt va chay lai.\n";
            return 1;
        }
    }

    while (cin) {
        showMainMenu();
        int choice;
        if (!readInt("Nhap lua chon: ", 0, 8, choice) || choice == 0) {
            break;
        }
        // Co tich hop cho phep tam tat cac chuc nang khi ghep code.
        if (!MEMBER_LOGIC_READY) {
            cout << "Chuc nang dang duoc thanh vien phat trien.\n";
            waitForMenu();
            continue;
        }
        try {
            switch (choice) {
                case 1: showProducts(products); break;
                case 2: searchProducts(products); break;
                case 3: addToCart(products, cart); break;
                case 4: showCart(cart); break;
                case 5: editCart(cart); break;
                case 6: checkout(cart); break;
                case 7: showProductsByPrice(products); break;
                case 8: addNewProduct(products); break;
            }
        } catch (const exception& error) {
            cout << "[LOI] " << error.what() << '\n';
        }
        waitForMenu();
    }
    cout << "\nCam on ban da su dung MiniShop. Tam biet!\n";
    return 0;
}
