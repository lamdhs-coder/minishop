# Phân công MiniShop

Nhóm gồm **Lâm, Quốc Vĩ và Bích**. Bảng dưới ghi rõ chức năng mỗi người phụ trách.
Các chức năng đã được ghép vào chương trình và kiểm tra chạy được.
**S05 – Thêm sản phẩm mới vào shop là phần Lâm làm.**

## Bảng phân công nhanh

| Người | Phần phụ trách |
| --- | --- |
| **Lâm** | Làm menu, hiển thị và tìm sản phẩm, nhập thông tin đặt hàng, tạo đơn, tính ngày giao/phí/tổng tiền, lưu hóa đơn, thêm sản phẩm mới, ghép code và kiểm tra chương trình. |
| **Quốc Vĩ** | Đọc sản phẩm từ file, thêm và sửa giỏ hàng, tính tiền hàng/số lượng, kiểm tra số quá lớn, làm phần cung cấp phí và số ngày giao hàng. |
| **Bích** | Làm thông tin sản phẩm và khách hàng, kiểm tra dữ liệu mẫu, lọc sản phẩm theo khoảng giá, kiểm tra hai sản phẩm có cùng mã hay không. |

## Lâm

| Chức năng/công việc | File chính | Trạng thái |
| --- | --- | --- |
| Tạo project, hướng dẫn build và chạy | README.md, các file source | Đã làm, đã kiểm tra |
| Làm menu và cho quay về menu sau mỗi thao tác | main.cpp | Đã làm, đã kiểm tra |
| Hiển thị danh sách sản phẩm và giỏ hàng thành bảng dễ đọc | main.cpp, Order.cpp | Đã làm, đã kiểm tra |
| Tìm sản phẩm theo một phần tên, không phân biệt hoa thường ASCII | main.cpp | Đã làm, đã kiểm tra |
| Nhập tên, điện thoại, địa chỉ và báo khi người dùng nhập sai | main.cpp | Đã làm, đã kiểm tra |
| Tạo đơn, ghi ngày đặt, tính ngày giao và tổng tiền cần thanh toán | Order.h/.cpp | Đã làm; giao thường 3 ngày, phí 30.000 VND |
| Cho xem trước đơn; hủy thì giữ giỏ, xác nhận xong thì xóa giỏ | main.cpp | Đã làm, đã kiểm tra |
| In hóa đơn và lưu hóa đơn TXT; báo lỗi khi không lưu được | Order.cpp, main.cpp | Đã làm, đã kiểm tra |
| Gắn bộ lọc giá của Bích vào mục 7 | main.cpp | Đã làm, đã kiểm tra |
| **S05: Thêm sản phẩm mới vào shop, lưu file và cập nhật danh sách ngay** | **main.cpp, ProductFile.h/.cpp** | **Lâm làm; đã kiểm tra** |
| Ghép code, kiểm tra lại chức năng cũ và cập nhật tài liệu | Toàn project, README.md, TASKS.md | Đã làm; cả nhóm vẫn cần tự chạy demo |

## Quốc Vĩ

| Chức năng/công việc | File chính | Trạng thái |
| --- | --- | --- |
| Đọc mã, tên, giá sản phẩm từ products.txt vào danh sách | ProductFile.cpp: loadProductsFromFile | Đã làm, đã kiểm tra |
| Báo lỗi khi thiếu file, sai dữ liệu hoặc trùng mã trong file | ProductFile.cpp | Đã làm, đã kiểm tra |
| Lưu một sản phẩm và số lượng của sản phẩm đó trong giỏ | CartItem.h/.cpp | Đã làm, đã kiểm tra |
| Thêm sản phẩm vào giỏ; thêm lại cùng mã thì tăng số lượng | ShoppingCart.cpp | Đã làm, đã kiểm tra |
| Tăng/giảm số lượng, xóa mặt hàng; giảm về 0 thì bỏ khỏi giỏ | CartItem.cpp, ShoppingCart.cpp | Đã làm, đã kiểm tra |
| Tính thành tiền từng mặt hàng, tổng tiền hàng và tổng số lượng | CartItem.cpp, ShoppingCart.cpp | Đã làm, đã kiểm tra |
| Không cho số lượng âm; từ chối thao tác khiến tiền/số lượng vượt giới hạn | CartItem.cpp, ShoppingCart.cpp | Đã làm, đã kiểm tra |
| Tìm mặt hàng đã có trong giỏ bằng find_if và phép so sánh mã của Bích | ShoppingCart.cpp | Đã làm, đã kiểm tra |
| Cung cấp phí giao thường 30.000 VND và thời gian giao 3 ngày để Lâm dùng khi tạo đơn | ShippingMethod.h | Đã làm, đã kiểm tra |

**Lưu ý về ProductFile.cpp:** Quốc Vĩ phụ trách phần **đọc sản phẩm**;
Lâm phụ trách phần **ghi sản phẩm mới của S05**. Hai phần dùng chung file source.

## Bích

| Chức năng/công việc | File chính | Trạng thái |
| --- | --- | --- |
| Lưu mã, tên và giá của sản phẩm; kiểm tra sản phẩm có dữ liệu hợp lệ | Product.h/.cpp | Đã làm, đã kiểm tra |
| Lưu tên, số điện thoại, địa chỉ khách hàng; kiểm tra thông tin hợp lệ | Customer.h/.cpp | Đã làm, đã kiểm tra |
| Kiểm tra và chuẩn bị dữ liệu sản phẩm mẫu | products.txt | Đã có; giữ nguyên các sản phẩm người dùng thêm |
| Lọc sản phẩm theo giá thấp nhất và cao nhất; nhập ngược thì đổi hai mốc | Product.cpp: filterByPriceRange | Đã làm, đã kiểm tra |
| So sánh hai sản phẩm theo mã để nhận biết cùng một mặt hàng | Product.cpp: operator== | Đã làm, được dùng khi thêm trùng vào giỏ |
| Kiểm tra việc tạo/đọc thông tin sản phẩm, khách hàng và kết quả lọc giá | Test cục bộ | 42 kiểm tra đạt; phần so sánh mã có trong bộ kiểm tra OOP |

**Bích phụ trách lọc giá; Lâm phụ trách thêm sản phẩm mới S05.**
Đây là hai chức năng khác nhau.

## S05 của Lâm gồm những gì?

| Phần việc | Cách hoạt động hiện tại |
| --- | --- |
| Nhập mã, tên và giá ở mục 8 | Nhập sai thì báo lỗi và cho nhập lại; mã 0 là hủy. |
| Kiểm tra mã trùng, tên rỗng/chứa dấu phân cách, giá không dương | Không cho lưu sản phẩm sai dữ liệu. |
| Lưu sản phẩm mới | Ghi vào bản sao tạm, kiểm tra xong mới thay file products.txt. |
| Giữ danh sách cũ khi lỗi lưu | Không thêm sản phẩm vào danh sách trên màn hình nếu lưu thất bại. |
| Dùng ngay sau khi thêm | Xem, tìm, lọc, thêm vào giỏ được ngay; mở lại chương trình vẫn còn. |

Đã chạy 16 kiểm tra ghi file và 18 kiểm tra S05 qua menu, đều đạt.
Dữ liệu products.txt thật được giữ nguyên khi kiểm thử.

## Ai cần giải thích phần kiến thức nào khi vấn đáp?

| Người | Đoạn code cần nắm | Cách giải thích ngắn |
| --- | --- | --- |
| **Lâm** | main.cpp, Order.h/.cpp, phần ghi S05 trong ProductFile.cpp | Chương trình đi từ menu đến đặt hàng/lưu file thế nào; vì sao hủy không mất giỏ và lưu lỗi không thêm sản phẩm. |
| **Quốc Vĩ** | CartItem, ShoppingCart, phần đọc trong ProductFile.cpp, ShippingMethod.h | Giỏ lưu và tính tiền thế nào; đọc file sai thì xử lý ra sao; phí/ngày giao được cung cấp cho Order bằng cách nào. |
| **Bích** | Product, Customer, filterByPriceRange, operator== | Mỗi sản phẩm/khách lưu gì, vì sao cần constructor/getter; lọc giá và nhận biết trùng mã ra sao. |

Bảng minh chứng đủ 7 chương và câu hỏi ôn tập nằm trong README.md và
[docs/ON_TAP_OOP.md](docs/ON_TAP_OOP.md). Phân công trên không có nghĩa mỗi người
chỉ cần biết phần mình; cả nhóm vẫn cần hiểu luồng mua hàng chung.

## Kết quả kiểm tra và việc còn lại

Các bộ kiểm tra hiện tại đều đạt: 42 kiểm tra thông tin/lọc giá, 23 kiểm tra OOP,
59 kiểm tra đọc file/giỏ/đơn hàng, 18 kiểm tra menu cũ, 16 kiểm tra ghi S05
và 18 kiểm tra S05 qua menu. Có phần kiểm tra trùng nhau, không cộng thành số chức năng.
Build C++17 không cảnh báo; toàn bộ 8 mục menu đã bật.

- [x] Các chức năng mua hàng, lọc giá và thêm sản phẩm mới đã hoạt động.
- [x] Các phần bổ sung để minh họa 7 chương đã có trong source.
- [x] Tên và phân công đã cập nhật: Lâm, Quốc Vĩ, Bích; S05 thuộc Lâm.
- [ ] Lâm, Quốc Vĩ và Bích tự chạy chương trình trên máy mình.
- [ ] Mỗi người tự giải thích được những hàm mình phụ trách.
- [ ] Cả nhóm chuẩn bị và thực hiện demo, thuyết trình, vấn đáp.

Thư mục tests/ chỉ dùng cục bộ và bị Git bỏ qua. Chưa kiểm thử mất điện/đĩa đầy;
chưa hỗ trợ nhiều chương trình cùng ghi products.txt.
