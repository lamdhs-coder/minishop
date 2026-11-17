# MiniShop – Ứng dụng đặt hàng Console

Đồ án OOP nhập môn dùng C++17, G++ và STL. Chương trình có 5 lớp chính:
Product, Customer, CartItem, ShoppingCart, Order; thêm ShippingMethod và
StandardShipping để dùng kế thừa và đa hình trong tính phí giao hàng.
Không cần thư viện bên thứ ba.

## Chức năng hiện tại

Menu chỉ còn mục 0–6. Chương trình đọc danh sách có sẵn trong products.txt;
các thao tác mua hàng không sửa file này.

| Chức năng | Người phụ trách |
| --- | --- |
| Đọc sản phẩm từ file và báo lỗi dữ liệu | Quốc Vĩ |
| Lưu và kiểm tra thông tin sản phẩm, khách hàng | Bích |
| Xem danh sách, tìm sản phẩm theo một phần tên | Lâm |
| Thêm vào giỏ; thêm cùng mã thì tăng số lượng | Quốc Vĩ xử lý; Lâm làm menu |
| Xem giỏ, thành tiền, tổng tiền và tổng số lượng | Quốc Vĩ tính; Lâm hiển thị |
| Tăng, giảm số lượng hoặc xóa sản phẩm khỏi giỏ | Quốc Vĩ xử lý; Lâm làm menu |
| Nhập khách, xem trước, hủy hoặc xác nhận đặt hàng | Lâm |
| Tính phí, ngày giao, tổng thanh toán và in/lưu hóa đơn TXT | Lâm làm đơn; Quốc Vĩ cung cấp phí và số ngày giao |

Ba chức năng sáng tạo đang giữ: tìm theo tên (S01), sửa giỏ (S02), lưu TXT (S03).

## Build và chạy

Mở terminal tại thư mục chứa main.cpp và products.txt:

```bash
g++ -std=c++17 -Wall -Wextra -static main.cpp Product.cpp Customer.cpp CartItem.cpp ShoppingCart.cpp Order.cpp ProductFile.cpp -o minishop.exe
./minishop.exe
```

Trong PowerShell có thể dùng `.\minishop.exe`.
Đã kiểm tra bằng G++ 16.2.0 của MSYS2 UCRT64 và chạy EXE trong PowerShell/Git Bash.
G++ cần có trong PATH; nếu chưa có, dùng đường dẫn đầy đủ tới g++.exe.

Giữ `-static` để EXE mang theo thư viện C++ cần thiết của G++, tránh Git Bash
nạp nhầm libstdc++/libgcc đi kèm Git khiến chương trình im lặng rồi thoát.
Thư viện hệ thống Windows vẫn do Windows cung cấp.

## Menu và cách test bằng tay

```text
1. Xem danh sach san pham
2. Tim kiem san pham
3. Them san pham vao gio
4. Xem gio hang
5. Chinh sua gio hang
6. Dat hang
0. Thoat
```

Nhấn Enter khi được nhắc để quay về menu chính.

1. Chọn **1**: xem toàn bộ danh sách đọc từ products.txt.
2. Chọn **2**, nhập **CHUOT**: tìm tên chứa chuot, không phân biệt hoa thường ASCII.
3. Chọn **3**, nhập mã **1**; lặp lại thêm mã **1** rồi mã **2**.
4. Chọn **4**: với giá mẫu mã 1 là 250000, mã 2 là 850000, giỏ có tổng số lượng
   **3**, tiền hàng **1.350.000 VND**.
5. Chọn **5**: thử tăng/giảm/xóa theo mã. Giảm từ 1 về 0 sẽ xóa mặt hàng.
   Chọn 0 trong menu sửa để quay lại.
6. Chọn **6**, nhập tên, số điện thoại 10 chữ số bắt đầu bằng 0 và địa chỉ.
   Xem trước rồi chọn **0** để hủy: giỏ vẫn còn.
7. Chọn **6** lần nữa, xác nhận **1** rồi chọn có/không lưu TXT.
   Với giỏ ở bước 4 chưa sửa, phí **30.000 VND**, tổng **1.380.000 VND**.
   Sau xác nhận giỏ rỗng, hóa đơn vẫn giữ đủ các mặt hàng.
8. Thử nhập chữ, số thập phân hoặc 7/8 ở menu chính: được báo chỉ nhận số nguyên 0–6.
   Thử đặt khi giỏ rỗng, nhập mã không tồn tại và nhập điện thoại sai.

Các con số minh họa phụ thuộc giá thật trong products.txt. File có thể chứa
nhiều sản phẩm hơn dữ liệu mẫu; chương trình không giới hạn cố định 10 sản phẩm.

## Vai trò các file

| File | Công việc |
| --- | --- |
| main.cpp | Nhập liệu, menu, hiển thị và điều phối đặt hàng |
| Product.h/.cpp | Mã, tên, giá và phép so sánh hai sản phẩm theo mã |
| Customer.h/.cpp | Tên, điện thoại, địa chỉ; kiểm tra dữ liệu khách |
| CartItem.h/.cpp | Một sản phẩm trong giỏ, số lượng và thành tiền |
| ShoppingCart.h/.cpp | Thêm/tăng/giảm/xóa, tổng tiền và tổng số lượng |
| ProductFile.h/.cpp | Đọc products.txt, tách ba trường, kiểm tra dữ liệu |
| ShippingMethod.h | Lớp cha giao hàng và lớp giao thường: 30.000 VND, 3 ngày |
| Order.h/.cpp | Bản sao khách/giỏ, ngày đặt/giao, phí/tổng và hóa đơn |
| TASKS.md | Phân công Lâm, Quốc Vĩ, Bích |
| docs/ON_TAP_OOP.md | Ví dụ từ code và câu hỏi ôn cả 7 chương |

## Kiến thức cả 7 chương

| Chương | Minh chứng đang dùng thật |
| --- | --- |
| 1 – Tổng quan OOP | Đóng gói dữ liệu; giỏ chứa CartItem, CartItem chứa Product; các đối tượng gọi phương thức của nhau |
| 2 – Lớp và đối tượng | Constructor, getter const, tham chiếu const, this, bản sao mặc định, static constexpr; protected và destructor ảo trong lớp giao hàng |
| 3 – Quá tải toán tử | Product::operator== so sánh mã; dùng khi gộp sản phẩm trùng trong giỏ |
| 4 – Kế thừa | StandardShipping kế thừa public từ ShippingMethod |
| 5 – Đa hình | Abstract class, pure virtual, override; Order gọi qua const ShippingMethod& |
| 6 – Template | parsePositiveInteger<T> tự viết, gọi với int cho ID và long long cho giá |
| 7 – STL | vector, push_back, empty, clear, iterator/erase và find_if với lambda |

Đây là kiến thức trọng tâm từng chương. Source không dùng friend, đa kế thừa,
class template tự viết, map hay sort; không khẳng định đã có mọi kỹ thuật nhỏ
trong giáo trình. Các lớp giữ số/string/vector nên dùng copy constructor và
destructor mặc định; không cần tự quản lý bộ nhớ bằng new/delete.

## Quy tắc xử lý

- Mỗi dòng products.txt có đúng dạng `id|name|price`. ID và giá phải nguyên dương,
  ID không trùng, tên có nội dung. Lỗi báo tên file và số dòng; thiếu file thì
  chương trình thoát mã 1. File rỗng là danh sách rỗng hợp lệ.
- Bộ đọc dùng getline tách trường và vòng lặp kiểm tra mã trùng.
  Cách duyệt này dễ theo dõi, phù hợp danh sách nhỏ của đồ án.
- Tiền dùng long long theo VND. Kiểm tra tràn trước khi cộng/nhân và trước khi
  đổi số lượng; thao tác vượt giới hạn giữ nguyên giỏ.
- Menu dùng getline/istringstream, từ chối ký tự thừa và số vượt giới hạn.
  EOF kết thúc nhập, không lặp vô hạn.
- Xem trước không ghi file, không xóa giỏ. Hủy/EOF ở bước xác nhận giữ giỏ.
  Sau đồng ý, tạo Order chính thức theo giờ hệ thống rồi mới xóa giỏ.
- Order giữ bản sao khách và các mặt hàng. Constructor hai tham số dùng giao thường;
  constructor ba tham số nhận ShippingMethod bằng tham chiếu và lấy phí/ngày qua
  hàm ảo, sau đó lưu hai giá trị. Không giữ tham chiếu đến đối tượng giao hàng.
- Ngày giao cộng 3 ngày lịch bằng localtime/mktime, tự chuẩn hóa cuối tháng/năm.
  Ngày giờ theo múi giờ hệ điều hành.
- TXT dùng nội dung giống hóa đơn Console. Tên mặc định
  hoadon_YYYYMMDD_HHMMSS.txt, thêm hậu tố khi trùng; tên được chỉ định mà đã tồn tại
  sẽ bị từ chối ghi đè. Lỗi lưu được báo riêng, đơn đã xác nhận vẫn có hiệu lực.
- Tìm kiếm chỉ đổi hoa thường ASCII. Căn bảng theo độ dài byte; tên Unicode
  có thể hiển thị lệch cột tùy terminal.

## Kiểm tra sau khi làm gọn code

| Nhóm kiểm tra cục bộ | Kết quả |
| --- | --- |
| Build C++17, -Wall -Wextra, -static | Thành công, không cảnh báo |
| Product và Customer | 32 PASS, 0 FAIL |
| Toán tử, kế thừa, hàm ảo và dữ liệu giao hàng | 23 PASS, 0 FAIL |
| Bộ đọc, giỏ, giới hạn số, Order và ghi hóa đơn | 52 PASS, 0 FAIL |
| Các điều kiện kiểm tra menu, EOF, dữ liệu thật và chạy Git Bash | 44 PASS, 0 FAIL |

Các nhóm có thể kiểm tra cùng một chức năng. Đây là số điều kiện kiểm tra,
không phải số tính năng. File/hóa đơn thử được tạo trong thư mục tạm;
products.txt thật được đối chiếu giữ nguyên từng byte.

Thư mục tests/, các file *.exe và hoadon_*.txt được .gitignore bỏ qua.
Tests chỉ có cục bộ, không đi kèm khi clone repo. Có thể dùng các bước menu ở trên
để kiểm tra trên máy khác. Build lại EXE sau mỗi lần sửa source.
