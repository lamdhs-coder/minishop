#include <iostream>
#include <string>

class Customer {
private:
    std::string fullName;     // Họ và tên
    std::string phoneNumber;  // Số điện thoại
    std::string address;      // Địa chỉ

public:
    // 1. Hàm khởi tạo mặc định (Default Constructor)
    Customer() : fullName(""), phoneNumber(""), address("") {}

    // 2. Hàm khởi tạo có tham số (Parameterized Constructor)
    Customer(std::string fullName, std::string phoneNumber, std::string address)
        : fullName(fullName), phoneNumber(phoneNumber), address(address) {}

    // --- GETTER (Lấy giá trị của các thuộc tính) ---
    std::string getFullName() const {
        return fullName;
    }

    std::string getPhoneNumber() const {
        return phoneNumber;
    }

    std::string getAddress() const {
        return address;
    }

    // --- SETTER (Thay đổi giá trị của các thuộc tính) ---
    void setFullName(const std::string& newFullName) {
        fullName = newFullName;
    }

    void setPhoneNumber(const std::string& newPhoneNumber) {
        phoneNumber = newPhoneNumber;
    }

    void setAddress(const std::string& newAddress) {
        address = newAddress;
    }

    // --- PHƯƠNG THỨC HIỂN THỊ ---
    void display() const {
        std::cout << "-----------------------------------" << std::endl;
        std::cout << "Ho va ten:     " << fullName << std::endl;
        std::cout << "So dien thoai: " << phoneNumber << std::endl;
        std::cout << "Dia chi:       " << address << std::endl;
    }
};