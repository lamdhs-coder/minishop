#include "Order.h"

#include <fstream>
#include <iomanip>
#include <limits>
#include <sstream>
#include <stdexcept>

namespace {
std::tm localDateTime(std::time_t time) {
    const std::tm* result = std::localtime(&time);
    if (result == nullptr) {
        throw std::runtime_error("Khong doc duoc ngay gio he thong.");
    }
    return *result; // Sao chep vi localtime dung bo nho noi bo.
}

std::string formatDateTime(std::time_t time, const char* format) {
    std::tm date = localDateTime(time);
    std::ostringstream output;
    output << std::put_time(&date, format);
    return output.str();
}

std::time_t addCalendarDays(std::time_t time, int days) {
    std::tm date = localDateTime(time);
    date.tm_mday += days;
    date.tm_isdst = -1; // De thu vien xac dinh lai gio mua he neu co.
    // mktime tu chuan hoa ngay qua cuoi thang, cuoi nam, nam nhuan.
    const std::time_t result = std::mktime(&date);
    if (result == static_cast<std::time_t>(-1)) {
        throw std::runtime_error("Khong tinh duoc ngay giao du kien.");
    }
    return result;
}

bool fileExists(const std::string& filename) {
    std::ifstream input(filename);
    return input.is_open();
}
}

std::string formatMoney(long long amount) {
    std::string number = std::to_string(amount);
    const int firstDigit = (amount < 0) ? 1 : 0;
    // Chen tu phai sang trai; khong dung so thuc nen khong mat chinh xac.
    for (int position = static_cast<int>(number.size()) - 3;
         position > firstDigit; position -= 3) {
        number.insert(static_cast<std::size_t>(position), ".");
    }
    return number + " VND";
}

void writeItemsTable(std::ostream& output, const std::vector<CartItem>& items) {
    const std::string line(96, '-');
    output << line << '\n'
           << std::left << std::setw(30) << "San pham"
           << std::right << std::setw(10) << "SL"
           << std::setw(28) << "Don gia"
           << std::setw(28) << "Thanh tien" << '\n'
           << line << '\n';

    for (const CartItem& item : items) {
        const std::string& name = item.getProduct().getName();
        output << std::left << std::setw(30) << name.substr(0, 28)
               << std::right << std::setw(10) << item.getQuantity()
               << std::setw(28) << formatMoney(item.getProduct().getPrice())
               << std::setw(28) << formatMoney(item.getTotalPrice()) << '\n';
        // Ten dai duoc xuong dong, khong mat ten day du trong hoa don.
        for (std::size_t start = 28; start < name.size(); start += 28) {
            output << name.substr(start, 28) << '\n';
        }
    }
    output << line << '\n';
}

Order::Order(const Customer& customer, const std::vector<CartItem>& items)
    : customer(customer), items(items), orderTime(std::time(nullptr)),
      shippingFee(30000) {
    // Hai thanh vien du lieu o tren la BAN SAO, khong tham chieu gio goc.
    if (this->items.empty()) {
        throw std::invalid_argument("Khong the tao don hang voi gio rong.");
    }
    if (orderTime == static_cast<std::time_t>(-1)) {
        throw std::runtime_error("Khong lay duoc thoi gian dat hang.");
    }
    for (const CartItem& item : this->items) {
        if (item.getQuantity() <= 0 || item.getProduct().getPrice() <= 0) {
            throw std::invalid_argument("Don hang co gia hoac so luong khong hop le.");
        }
    }
    // Kiem tra tong ngay khi tao don, truoc khi bao dat hang thanh cong.
    getTotalPayment();
}

const Customer& Order::getCustomer() const {
    return customer;
}

const std::vector<CartItem>& Order::getItems() const {
    return items;
}

std::string Order::getOrderDate() const {
    return formatDateTime(orderTime, "%d/%m/%Y");
}

std::string Order::getEstimatedDeliveryDate() const {
    return formatDateTime(addCalendarDays(orderTime, 3), "%d/%m/%Y");
}

long long Order::getShippingFee() const {
    return shippingFee;
}

long long Order::getSubtotal() const {
    long long subtotal = 0;
    for (const CartItem& item : items) {
        const long long total = item.getTotalPrice();
        if (total < 0 || total > std::numeric_limits<long long>::max() - subtotal) {
            throw std::overflow_error("Tong tien hang vuot gioi han long long.");
        }
        subtotal += total;
    }
    return subtotal;
}

long long Order::getTotalPayment() const {
    const long long subtotal = getSubtotal();
    if (subtotal > std::numeric_limits<long long>::max() - shippingFee) {
        throw std::overflow_error("Tong thanh toan vuot gioi han long long.");
    }
    return subtotal + shippingFee;
}

std::string Order::getReceiptText() const {
    std::ostringstream output;
    const std::string line(96, '=');
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
    output << std::left << std::setw(68) << "Tam tinh:"
           << std::right << std::setw(28) << formatMoney(getSubtotal()) << '\n'
           << std::left << std::setw(68) << "Phi van chuyen:"
           << std::right << std::setw(28) << formatMoney(getShippingFee()) << "\n\n"
           << std::left << std::setw(68) << "TONG THANH TOAN:"
           << std::right << std::setw(28) << formatMoney(getTotalPayment()) << '\n'
           << line << '\n';
    return output.str();
}

std::string Order::saveReceiptToFile(const std::string& filename) const {
    std::string path = filename;
    if (path.empty()) {
        const std::string base = "hoadon_" + formatDateTime(orderTime, "%Y%m%d_%H%M%S");
        path = base + ".txt";
        int suffix = 1;
        while (fileExists(path)) {
            path = base + "_" + std::to_string(suffix++) + ".txt";
        }
    } else if (fileExists(path)) {
        throw std::runtime_error("File da ton tai, khong ghi de: " + path);
    }

    // Tao noi dung truoc khi mo file, tranh tao file rong neu du lieu bi loi.
    const std::string receipt = getReceiptText();
    std::ofstream output(path);
    if (!output.is_open()) {
        throw std::runtime_error("Khong mo duoc file de ghi: " + path);
    }
    output << receipt;
    output.close(); // Kiem tra ca loi ghi/flush khi dong file.
    if (!output) {
        throw std::runtime_error("Ghi hoa don that bai: " + path);
    }
    return path;
}
