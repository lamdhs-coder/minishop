#include <iostream>
#include "Customer.h"
#include "Product.h"
#include "Order.h"

using namespace std;

int main() {
    // 1. Kh?i t?o thông tin khách hàng mua máy tính
    Customer customer("Nguyen Van A", "123 Le Loi, Quan 1, TP.HCM", "0901234567");

    // 2. T?o danh sách các s?n ph?m công ngh?
    // Dùng S? NGUYÊN (ví d?: 1, 2, 3) cho tham s? d?u tiên thay vì chu?i ("SP01")
    Product p1(1, "Laptop Dell XPS 13", 25000000);
    
    Product p2;
    p2.setId(2);
    p2.setName("Chuot khong day Logitech");
    p2.setPrice(2500000);

    Product p3(3, "Ban phim co Keychron K8", 1800000);

    // 3. Kh?i t?o gi? hàng / don hàng
    Order order(customer);
    order.addItem(p1, 1); 
    order.addItem(p2, 1); 
    order.addItem(p3, 2); 

    // 4. In hóa don ra màn hình
    cout << order.getReceiptText() << endl;

    // L?nh d?ng màn hình d? xem k?t qu? trên Dev-C++
    system("pause");

    return 0;
}
