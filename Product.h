#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

class Product {
private:
    std::string id;
    std::string name;
    double price;

public:
    Product() : id(""), name(""), price(0.0) {}
    Product(std::string id, std::string name, double price)
        : id(id), name(name), price(price) {}

    // Getter
    std::string getId() const { return id; }
    std::string getName() const { return name; }
    double getPrice() const { return price; }

    // --- SETTER (Gán/thay đổi giá trị của các thuộc tính) ---
    void setId(const std::string& newId) { id = newId; }

    void setName(const std::string& newName) { name = newName; }

    void setPrice(double newPrice)
    {
        if (newPrice >= 0) {
            price = newPrice;
        }
        else {
            std::cout << "Gia san pham khong hop le!\n";
        }
    }

    // --- PHƯƠNG THỨC HIỂN THỊ ---
    void display() const
    {
        std::cout << "-------------------------" << std::endl;
        std::cout << "Ma SP:  " << id << std::endl;
        std::cout << "Ten SP: " << name << std::endl;
        std::cout << "Gia:    " << std::fixed << std::setprecision(2) << price << " VNĐ" << std::endl;
    }
};

// Hàm khởi tạo danh sách dữ liệu mẫu (12 sản phẩm)
std::vector<Product> initProductList() {
    return {
        Product("SP01", "Laptop Dell XPS 13", 28500000),
        Product("SP02", "MacBook Air M2", 26990000),
        Product("SP03", "Chuot khong day Logitech MX Master 3S", 2450000),
        Product("SP04", "Ban phim co Keychron K2V2", 1950000),
        Product("SP05", "Man hinh LG UltraGear 27 inch", 6800000),
        Product("SP06", "Tai nghe Sony WH-1000XM5", 7990000),
        Product("SP07", "Dien thoai iPhone 15 Pro", 27990000),
        Product("SP08", "Dien thoai Samsung Galaxy S24", 21990000),
        Product("SP09", "O oc di dong SSD Samsung T7 1TB", 2850000),
        Product("SP10", "Sac anker PowerPort 65W", 850000),
        Product("SP11", "Webcam Logitech C920", 1650000),
        Product("SP12", "Gia do Laptop nhom Hop Kim", 350000)
    };
}

// Hàm hiển thị danh sách sản phẩm dạng bảng
void displayProducts(const std::vector<Product>& products) {
    std::cout << std::left
        << std::setw(8) << "STT"
        << std::setw(10) << "Ma SP"
        << std::setw(42) << "Ten San Pham"
        << std::right
        << std::setw(15) << "Gia (VND)" << std::endl;
    std::cout << std::string(75, '-') << std::endl;

    for (size_t i = 0; i < products.size(); ++i) {
        std::cout << std::left
            << std::setw(8) << (i + 1)
            << std::setw(10) << products[i].getId()
            << std::setw(42) << products[i].getName()
            << std::right
            << std::setw(15) << std::fixed << std::setprecision(0) << products[i].getPrice()
            << std::endl;
    }
    std::cout << std::string(75, '-') << std::endl;
}