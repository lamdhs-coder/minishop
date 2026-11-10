#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Order.h"
#include "ProductFile.h"
#include "ShoppingCart.h"

// Chi doi thanh true SAU KHI MEMBER 2 va MEMBER 3 hoan thanh cac TODO.
constexpr bool MEMBER_LOGIC_READY = false;

std::string trim(const std::string& text) {
    const std::size_t first = text.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }
    const std::size_t last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

bool readLine(const std::string& prompt, std::string& text) {
    std::cout << prompt;
    if (!std::getline(std::cin, text)) {
        return false; // EOF: thoat luong nhap, khong lap vo han.
    }
    text = trim(text);
    return true;
}

bool readInt(const std::string& prompt, int minimum, int maximum, int& value) {
    std::string text;
    while (readLine(prompt, text)) {
        std::istringstream input(text);
        int number;
        char extra;
        // "2abc", "2.5", so qua lon va chuoi rong deu bi tu choi.
        if ((input >> number) && !(input >> extra)
            && number >= minimum && number <= maximum) {
            value = number;
            return true;
        }
        std::cout << "[LOI] Vui long nhap so nguyen tu "
                  << minimum << " den " << maximum << ".\n";
    }
    return false;
}

bool readRequiredText(const std::string& prompt, std::string& text) {
    while (readLine(prompt, text)) {
        if (!text.empty()) {
            return true;
        }
        std::cout << "[LOI] Thong tin khong duoc de trong.\n";
    }
    return false;
}

bool isValidPhone(const std::string& phone) {
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

bool readPhone(std::string& phone) {
    while (readLine("So dien thoai (10 chu so, bat dau bang 0): ", phone)) {
        if (isValidPhone(phone)) {
            return true;
        }
        std::cout << "[LOI] So dien thoai phai gom 10 chu so va bat dau bang 0.\n";
    }
    return false;
}

bool askYesNo(const std::string& prompt, bool& answer) {
    int choice;
    if (!readInt(prompt + " (1: Co, 0: Khong): ", 0, 1, choice)) {
        return false;
    }
    answer = (choice == 1);
    return true;
}

void waitForMenu() {
    std::string ignored;
    readLine("\nNhan Enter de ve menu chinh...", ignored);
}

void showMainMenu() {
    std::cout << "\n==========================================\n"
              << "                 MINISHOP\n"
              << "            UNG DUNG DAT HANG\n"
              << "==========================================\n"
              << "1. Xem danh sach san pham\n"
              << "2. Tim kiem san pham\n"
              << "3. Them san pham vao gio\n"
              << "4. Xem gio hang\n"
              << "5. Chinh sua gio hang\n"
              << "6. Dat hang\n"
              << "0. Thoat\n"
              << "==========================================\n";
}

std::string shortName(const std::string& name) {
    return name.size() <= 32 ? name : name.substr(0, 29) + "...";
}

void showProducts(const std::vector<Product>& products) {
    if (products.empty()) {
        std::cout << "[THONG BAO] Khong co san pham de hien thi.\n";
        return;
    }
    std::cout << std::string(66, '-') << '\n'
              << std::left << std::setw(6) << "Ma"
              << std::setw(32) << "Ten san pham"
              << std::right << std::setw(28) << "Don gia" << '\n'
              << std::string(66, '-') << '\n';
    for (const Product& product : products) {
        std::cout << std::left << std::setw(6) << product.getId()
                  << std::setw(32) << shortName(product.getName())
                  << std::right << std::setw(28) << formatMoney(product.getPrice()) << '\n';
    }
    std::cout << std::string(66, '-') << '\n';
}

std::string lowercaseAscii(std::string text) {
    for (char& letter : text) {
        if (letter >= 'A' && letter <= 'Z') {
            letter = static_cast<char>(letter - 'A' + 'a');
        }
    }
    return text;
}

void searchProducts(const std::vector<Product>& products) {
    std::string keyword;
    if (!readRequiredText("Nhap mot phan ten san pham: ", keyword)) {
        return;
    }
    keyword = lowercaseAscii(keyword);
    std::vector<Product> matches; // Ket qua tim kiem, khong phai gio hang.
    for (const Product& product : products) {
        if (lowercaseAscii(product.getName()).find(keyword) != std::string::npos) {
            matches.push_back(product);
        }
    }
    if (matches.empty()) {
        std::cout << "[THONG BAO] Khong tim thay san pham phu hop.\n";
    } else {
        showProducts(matches);
    }
}

void addToCart(const std::vector<Product>& products, ShoppingCart& cart) {
    showProducts(products);
    if (products.empty()) {
        return;
    }
    int productId;
    if (!readInt("Nhap ma san pham (0: Quay lai): ", 0,
                 std::numeric_limits<int>::max(), productId)
        || productId == 0) {
        return;
    }
    for (const Product& product : products) {
        if (product.getId() == productId) {
            cart.addProduct(product); // ShoppingCart tu xu ly san pham trung.
            std::cout << "[THANH CONG] Da them san pham vao gio.\n";
            return;
        }
    }
    std::cout << "[LOI] Ma san pham khong ton tai.\n";
}

void showCart(const ShoppingCart& cart) {
    if (cart.isEmpty()) {
        std::cout << "[THONG BAO] Gio hang dang rong.\n";
        return;
    }
    std::cout << "\nGIO HANG\n";
    writeItemsTable(std::cout, cart.getItems());
    std::cout << "Tong so luong: " << cart.getTotalQuantity() << '\n'
              << "Tong tien hang: " << formatMoney(cart.getSubtotal()) << '\n';
    std::cout << "Ma san pham trong gio: ";
    for (const CartItem& item : cart.getItems()) {
        std::cout << item.getProduct().getId() << " ";
    }
    std::cout << '\n';
}

void editCart(ShoppingCart& cart) {
    while (std::cin) {
        showCart(cart);
        if (cart.isEmpty()) {
            return;
        }
        std::cout << "\n1. Tang so luong them 1\n"
                  << "2. Giam so luong bot 1 (ve 0 thi xoa)\n"
                  << "3. Xoa san pham\n0. Quay lai\n";
        int action;
        if (!readInt("Chon thao tac: ", 0, 3, action) || action == 0) {
            return;
        }
        int productId;
        if (!readInt("Nhap ma san pham (0: Quay lai): ", 0,
                     std::numeric_limits<int>::max(), productId)
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
        std::cout << (changed ? "[THANH CONG] Da cap nhat gio hang.\n"
                              : "[LOI] Ma san pham khong co trong gio.\n");
    }
}

void checkout(ShoppingCart& cart) {
    if (cart.isEmpty()) {
        std::cout << "[LOI] Khong the dat hang khi gio rong.\n";
        return;
    }
    std::string name, phone, address;
    if (!readRequiredText("Ho va ten: ", name) || !readPhone(phone)
        || !readRequiredText("Dia chi giao hang: ", address)) {
        return;
    }
    const Customer customer(name, phone, address);

    // Ban xem truoc chi hien thi: khong ghi file, khong sua gio.
    const Order preview(customer, cart.getItems());
    std::cout << "\n[XEM TRUOC - CHUA XAC NHAN DAT HANG]\n"
              << preview.getReceiptText();
    bool confirmed;
    if (!askYesNo("Ban xac nhan dat hang?", confirmed) || !confirmed) {
        std::cout << "[THONG BAO] Chua dat hang. Gio hang duoc giu nguyen.\n";
        return;
    }

    // Tao lai de lay thoi gian HE THONG ngay sau khi khach xac nhan.
    const Order order(customer, cart.getItems());
    cart.clear(); // Don da giu ban sao, xoa gio khong lam mat hoa don.
    std::cout << "\n[THANH CONG] Dat hang thanh cong!\n"
              << order.getReceiptText();

    bool save;
    if (!askYesNo("Ban muon luu hoa don TXT?", save) || !save) {
        return;
    }
    try {
        const std::string path = order.saveReceiptToFile();
        std::cout << "[THANH CONG] Da luu hoa don: " << path << '\n';
    } catch (const std::exception& error) {
        // Loi luu file khong huy don da xac nhan.
        std::cout << "[LOI] Don da xac nhan nhung khong luu duoc hoa don: "
                  << error.what() << '\n';
    }
}

int main() {
    std::vector<Product> products;
    ShoppingCart cart; // Constructor mac dinh chi tao vector, khong goi stub.

    std::cout << "Chao mung ban den voi MiniShop!\n";
    if (!MEMBER_LOGIC_READY) {
        std::cout << "[TRANG THAI] Phan Leader va MEMBER 3 da viet; dang cho logic MEMBER 2.\n";
    } else {
        try {
            products = loadProductsFromFile("products.txt");
        } catch (const std::exception& error) {
            std::cerr << "[LOI] Khong tai duoc danh sach san pham: "
                      << error.what() << "\nHay kiem tra products.txt va chay lai.\n";
            return 1;
        }
    }

    while (std::cin) {
        showMainMenu();
        int choice;
        if (!readInt("Nhap lua chon: ", 0, 6, choice) || choice == 0) {
            break;
        }
        // Chan tat ca 6 muc truoc khi goi bat ky ham TODO nao.
        if (!MEMBER_LOGIC_READY) {
            std::cout << "Chuc nang dang duoc thanh vien phat trien.\n";
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
            }
        } catch (const std::exception& error) {
            std::cout << "[LOI] " << error.what() << '\n';
        }
        waitForMenu();
    }
    std::cout << "\nCam on ban da su dung MiniShop. Tam biet!\n";
    return 0;
}
