#include "Order.h"

#include <fstream>
#include <iomanip>
#include <limits>
#include <sstream>
#include <stdexcept>

using namespace std;

namespace {
tm localDateTime(time_t time) {
    const tm* result = localtime(&time);
    if (result == nullptr) {
        throw runtime_error("Khong doc duoc ngay gio he thong.");
    }
    return *result; // Sao chep vi localtime dung bo nho noi bo.
}

string formatDateTime(time_t time, const char* format) {
    tm date = localDateTime(time);
    ostringstream output;
    output << put_time(&date, format);
    return output.str();
}

time_t addCalendarDays(time_t time, int days) {
    tm date = localDateTime(time);
    if (days > numeric_limits<int>::max() - date.tm_mday) {
        throw overflow_error("So ngay giao hang vuot gioi han xu ly.");
    }
    date.tm_mday += days;
    date.tm_isdst = -1; // De thu vien xac dinh lai gio mua he neu co.
    // mktime tu chuan hoa ngay qua cuoi thang, cuoi nam, nam nhuan.
    const time_t result = mktime(&date);
    if (result == static_cast<time_t>(-1)) {
        throw runtime_error("Khong tinh duoc ngay giao du kien.");
    }
    return result;
}

bool fileExists(const string& filename) {
    ifstream input(filename);
    return input.is_open();
}
}

string formatMoney(long long amount) {
    string number = to_string(amount);
    const int firstDigit = (amount < 0) ? 1 : 0;
    // Chen tu phai sang trai; khong dung so thuc nen khong mat chinh xac.
    for (int position = static_cast<int>(number.size()) - 3;
         position > firstDigit; position -= 3) {
        number.insert(static_cast<size_t>(position), ".");
    }
    return number + " VND";
}

void writeItemsTable(ostream& output, const vector<CartItem>& items) {
    const string line(96, '-');
    output << line << '\n'
           << left << setw(30) << "San pham"
           << right << setw(10) << "SL"
           << setw(28) << "Don gia"
           << setw(28) << "Thanh tien" << '\n'
           << line << '\n';

    for (const CartItem& item : items) {
        const string& name = item.getProduct().getName();
        output << left << setw(30) << name.substr(0, 28)
               << right << setw(10) << item.getQuantity()
               << setw(28) << formatMoney(item.getProduct().getPrice())
               << setw(28) << formatMoney(item.getTotalPrice()) << '\n';
        // Ten dai duoc xuong dong, khong mat ten day du trong hoa don.
        for (size_t start = 28; start < name.size(); start += 28) {
            output << name.substr(start, 28) << '\n';
        }
    }
    output << line << '\n';
}

Order::Order(const Customer& customer, const vector<CartItem>& items)
    : Order(customer, items, StandardShipping()) {
    // Constructor cu uy quyen cho constructor co phuong thuc giao hang.
}

Order::Order(const Customer& customer, const vector<CartItem>& items,
             const ShippingMethod& shipping)
    : customer(customer), items(items), orderTime(time(nullptr)),
      shippingFee(shipping.getFee()), deliveryDays(shipping.getDeliveryDays()) {
    // Goi virtual qua tham chieu ShippingMethod, thuc thi override cua lop con.
    // Hai thanh vien du lieu o tren la BAN SAO, khong tham chieu gio goc.
    if (this->items.empty()) {
        throw invalid_argument("Khong the tao don hang voi gio rong.");
    }
    if (orderTime == static_cast<time_t>(-1)) {
        throw runtime_error("Khong lay duoc thoi gian dat hang.");
    }
    if (shippingFee < 0 || deliveryDays < 0) {
        throw invalid_argument("Phi va so ngay giao hang khong duoc am.");
    }
    for (const CartItem& item : this->items) {
        if (item.getQuantity() <= 0 || item.getProduct().getPrice() <= 0) {
            throw invalid_argument("Don hang co gia hoac so luong khong hop le.");
        }
    }
    // Kiem tra tong ngay khi tao don, truoc khi bao dat hang thanh cong.
    getTotalPayment();
}

const Customer& Order::getCustomer() const {
    return customer;
}

const vector<CartItem>& Order::getItems() const {
    return items;
}

string Order::getOrderDate() const {
    return formatDateTime(orderTime, "%d/%m/%Y");
}

string Order::getEstimatedDeliveryDate() const {
    return formatDateTime(addCalendarDays(orderTime, deliveryDays), "%d/%m/%Y");
}

long long Order::getShippingFee() const {
    return shippingFee;
}

long long Order::getSubtotal() const {
    long long subtotal = 0;
    for (const CartItem& item : items) {
        const long long total = item.getTotalPrice();
        if (total < 0 || total > numeric_limits<long long>::max() - subtotal) {
            throw overflow_error("Tong tien hang vuot gioi han long long.");
        }
        subtotal += total;
    }
    return subtotal;
}

long long Order::getTotalPayment() const {
    const long long subtotal = getSubtotal();
    if (subtotal > numeric_limits<long long>::max() - shippingFee) {
        throw overflow_error("Tong thanh toan vuot gioi han long long.");
    }
    return subtotal + shippingFee;
}

string Order::getReceiptText() const {
    ostringstream output;
    const string line(96, '=');
    output << line << '\n'
           << "                                      MINISHOP\n"
           << "                                  HOA DON DAT HANG\n"
           << line << "\n\n"
           << "Khach hang   : " << customer.getName() << '\n'
           << "So dien thoai: " << customer.getPhone() << '\n'
           << "Dia chi      : " << customer.getAddress() << "\n\n"
           << "Ngay dat     : " << getOrderDate() << '\n'
           << "Gio dat      : " << formatDateTime(orderTime, "%H:%M:%S") << '\n'
           << "Ngay giao DK : " << getEstimatedDeliveryDate() << "\n\n";
    writeItemsTable(output, items);
    output << left << setw(68) << "Tam tinh:"
           << right << setw(28) << formatMoney(getSubtotal()) << '\n'
           << left << setw(68) << "Phi van chuyen:"
           << right << setw(28) << formatMoney(getShippingFee()) << "\n\n"
           << left << setw(68) << "TONG THANH TOAN:"
           << right << setw(28) << formatMoney(getTotalPayment()) << '\n'
           << line << '\n';
    return output.str();
}

string Order::saveReceiptToFile(const string& filename) const {
    string path = filename;
    if (path.empty()) {
        const string base = "hoadon_" + formatDateTime(orderTime, "%Y%m%d_%H%M%S");
        path = base + ".txt";
        int suffix = 1;
        while (fileExists(path)) {
            path = base + "_" + to_string(suffix++) + ".txt";
        }
    } else if (fileExists(path)) {
        throw runtime_error("File da ton tai, khong ghi de: " + path);
    }

    // Tao noi dung truoc khi mo file, tranh tao file rong neu du lieu bi loi.
    const string receipt = getReceiptText();
    ofstream output(path);
    if (!output.is_open()) {
        throw runtime_error("Khong mo duoc file de ghi: " + path);
    }
    output << receipt;
    output.close(); // Kiem tra ca loi ghi/flush khi dong file.
    if (!output) {
        throw runtime_error("Ghi hoa don that bai: " + path);
    }
    return path;
}
