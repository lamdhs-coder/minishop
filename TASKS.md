# Phân công MiniShop

Phạm vi hiện tại: xem/tìm sản phẩm, thêm và sửa giỏ, đặt hàng, in/lưu hóa đơn.
Menu có mục 0–6. Phân công dưới đây giữ tên và phần việc đã thống nhất.

## Bảng phân công nhanh

| Người | Phần phụ trách |
| --- | --- |
| **Lâm** | Menu, hiển thị/tìm sản phẩm, nhập khách, tạo và xác nhận đơn, ngày giao/tổng thanh toán, in/lưu hóa đơn, ghép code và tài liệu. |
| **Quốc Vĩ** | Đọc sản phẩm từ file, thêm/sửa giỏ, tính tiền và số lượng, chặn số quá lớn, cung cấp phí và số ngày giao hàng. |
| **Bích** | Thông tin sản phẩm/khách, kiểm tra dữ liệu, so sánh sản phẩm theo mã và chuẩn bị dữ liệu mẫu. |

## Lâm

| Công việc | File chính |
| --- | --- |
| Làm menu, nhận lựa chọn và quay lại sau mỗi thao tác | main.cpp |
| Hiển thị sản phẩm và giỏ thành bảng | main.cpp, Order.cpp |
| Tìm sản phẩm theo một phần tên, không phân biệt hoa thường ASCII | main.cpp |
| Nhập tên, điện thoại, địa chỉ và báo khi nhập sai | main.cpp |
| Tạo đơn; lấy ngày đặt, tính ngày giao và tổng tiền phải trả | Order.h/.cpp |
| Xem trước; hủy thì giữ giỏ, xác nhận xong thì xóa giỏ | main.cpp |
| In hóa đơn, lưu TXT và báo lỗi khi không ghi được | Order.cpp, main.cpp |
| Ghép code, hướng dẫn build, kiểm tra và cập nhật tài liệu | Toàn project, README.md, docs/ON_TAP_OOP.md |

## Quốc Vĩ

| Công việc | File chính |
| --- | --- |
| Đọc mã, tên, giá từ products.txt vào danh sách | ProductFile.h/.cpp |
| Báo lỗi thiếu file, dòng sai và mã trùng | ProductFile.cpp |
| Lưu sản phẩm cùng số lượng trong một dòng giỏ | CartItem.h/.cpp |
| Thêm vào giỏ; cùng mã thì tăng số lượng | ShoppingCart.cpp |
| Tăng/giảm/xóa; giảm về 0 thì bỏ dòng giỏ | CartItem.cpp, ShoppingCart.cpp |
| Tính thành tiền, tổng tiền hàng và tổng số lượng | CartItem.cpp, ShoppingCart.cpp |
| Chặn số lượng âm hoặc tiền/số lượng vượt giới hạn | CartItem.cpp, ShoppingCart.cpp |
| Dùng phép so sánh mã của Bích để tìm sản phẩm trùng | ShoppingCart.cpp |
| Cung cấp phí giao thường 30.000 VND và thời gian 3 ngày | ShippingMethod.h |

## Bích

| Công việc | File chính |
| --- | --- |
| Lưu mã, tên, giá; từ chối mã/giá không dương và tên rỗng | Product.h/.cpp |
| Lưu tên, điện thoại, địa chỉ; kiểm tra thông tin khách hợp lệ | Customer.h/.cpp |
| So sánh hai sản phẩm theo mã bằng operator== | Product.h/.cpp |
| Chuẩn bị và kiểm tra dữ liệu sản phẩm mẫu | products.txt |
| Kiểm tra constructor, getter, bản sao và dữ liệu sai | Test cục bộ cho Product/Customer |

## Chuẩn bị demo và vấn đáp

Các phần trên đã có code và được kiểm tra sau khi làm gọn.
Cả nhóm vẫn cần tự chạy và giải thích phần mình phụ trách:

- **Lâm:** theo luồng menu → xem trước → xác nhận → Order → hóa đơn;
  giải thích vì sao hủy giữ giỏ, xác nhận xóa giỏ mà hóa đơn vẫn còn.
- **Quốc Vĩ:** giải thích đọc từng dòng, template đổi số, tìm sản phẩm trùng,
  tăng/giảm/xóa và kiểm tra tràn trước khi đổi giỏ.
- **Bích:** giải thích private/public, constructor, getter const, kiểm tra
  điện thoại và phép so sánh hai Product theo mã.
- **Cả nhóm:** hiểu kế thừa ShippingMethod → StandardShipping và cách Order
  gọi hàm ảo qua tham chiếu lớp cha. Đọc docs/ON_TAP_OOP.md để ôn đủ 7 chương.

Kiểm tra cục bộ hiện tại: Product/Customer 32, OOP 23, bộ đọc/giỏ/đơn 52,
các điều kiện menu và môi trường chạy 44; tất cả đạt. Không push thư mục tests/.
