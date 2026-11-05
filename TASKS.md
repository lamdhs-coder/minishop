# Phân công MiniShop

“Đã viết source” chỉ nói về phần triển khai. Những mục phụ thuộc TODO của thành
viên khác chưa được kiểm thử tích hợp và chưa được đánh dấu hoàn thành toàn bộ.

## Leader

| Công việc | Trạng thái |
| --- | --- |
| L01: Cấu trúc, main, header/source, dữ liệu mẫu, hướng dẫn build | Đã tạo; build thành công |
| L02: Console, bảng, phân cách nghìn, thông báo, quay lại menu | Đã viết; menu/định dạng tiền đã kiểm tra; bảng có dữ liệu chờ tích hợp |
| L03: Menu theo hàm, nhập sai, EOF, chặn chức năng chưa sẵn sàng | Đã viết; kiểm tra menu và cả 6 chốt chặn đạt |
| Nhập và kiểm tra tên, điện thoại, địa chỉ | Đã viết; kiểm tra các hàm nhập đạt; checkout chờ tích hợp |
| Class Order, snapshot Customer và vector<CartItem> | Đã viết source; chờ kiểm thử với class thật |
| Tính ngày hệ thống và ngày giao +3 | Đã viết; helper cộng ngày đã kiểm tra; Order chờ tích hợp |
| Phí vận chuyển và tổng thanh toán long long | Đã viết source; chờ kiểm thử Order |
| L04: Xem trước, từ chối giữ giỏ, xác nhận đơn chính thức | Đã viết source; chờ kiểm thử luồng thật |
| L05: Tạo chuỗi hóa đơn, in và lưu TXT, báo lỗi ghi file | Đã viết source; chờ kiểm thử với Order thật |
| F07: Tìm tên ASCII không phân biệt hoa thường | Đã viết source; chờ chạy trên Product thật |
| L06: Ghép qua giao tiếp class, không lặp logic giỏ trong main | Đã nối source; tích hợp runtime chưa hoàn tất |
| Kiểm thử, README, hướng dẫn bàn giao | Đã kiểm tra phần độc lập; kiểm thử đầy đủ còn chờ |

## Thành viên 2

| Công việc / file | Trạng thái | Bắt đầu từ |
| --- | --- | --- |
| CartItem.cpp: constructor và getter | TODO | Đọc CartItem.h, dùng Product đã hoàn tất |
| CartItem.cpp: tăng/giảm số lượng | TODO | Không âm; chặn tràn số |
| CartItem.cpp: thành tiền dòng | TODO | long long, kiểm tra trước phép nhân |
| ShoppingCart.cpp: vector<CartItem> | TODO | Getter const, isEmpty, clear |
| ShoppingCart.cpp: thêm cùng sản phẩm nhiều lần | TODO | Duyệt theo getId, không tạo dòng trùng |
| ShoppingCart.cpp: tăng/giảm/xóa theo mã | TODO | false nếu không thấy; giảm về 0 thì erase |
| ShoppingCart.cpp: tổng tiền và tổng số lượng | TODO | Cộng getTotalPrice và getQuantity |
| ProductFile.cpp: đọc TXT, xử lý lỗi | TODO | ifstream, getline, tách ba trường |
| Hỗ trợ tìm kiếm theo phân công bổ sung | Không bắt buộc | Leader đã viết tìm kiếm trong main |
| Kiểm thử các class và tích hợp với Leader | Chưa chạy | Bắt đầu sau khi Product sẵn sàng |

Hợp đồng cần giữ: tăng/giảm mỗi lần một đơn vị; addProduct trả void,
các thao tác theo mã trả bool; getItems trả tham chiếu const; tổng số lượng
và tiền trả long long. Không tự in thông báo thành công ở lớp nghiệp vụ.
Lỗi dữ liệu/tràn số dùng exception; không trả kết quả giả để che lỗi.

## Thành viên 3

| Công việc / file | Trạng thái | Bắt đầu từ |
| --- | --- | --- |
| Product.cpp: constructor | TODO | Kiểm tra id > 0, tên không rỗng, giá > 0 |
| Product.cpp: getId, getName, getPrice | TODO | Trả các thuộc tính private tương ứng |
| Customer.cpp: constructor | TODO | Lưu tên, điện thoại, địa chỉ |
| Customer.cpp: ba getter | TODO | Trả tham chiếu const tới chuỗi |
| Rà soát, chuẩn bị dữ liệu sản phẩm | Chờ rà soát | Leader đã tạo sẵn 10 dòng mẫu theo đề |
| Kiểm thử Product, Customer | Chưa chạy | Tạo đối tượng, đối chiếu mọi getter |
| Hỗ trợ tài liệu và thuyết trình | Chưa thực hiện | Giải thích đóng gói, constructor, getter |

Constructor đã có danh sách khởi tạo tối thiểu để stub biên dịch; phải hoàn thiện
theo TODO rồi xóa lệnh ném logic_error. Không chỉ đổi cờ để xem như đã làm xong.

## Điều kiện ghép code

- [x] Header và stub liên kết được bằng lệnh G++ trong README.
- [x] Cờ mặc định false, sáu mục báo chưa sẵn sàng.
- [x] Kiểm tra độc lập menu, validator, định dạng tiền và helper cộng ngày.
- [ ] Thành viên 3 hoàn thiện Product và Customer.
- [ ] Thành viên 2 hoàn thiện CartItem, ShoppingCart và ProductFile.
- [ ] Kiểm tra từng class và xử lý lỗi bộ đọc file.
- [ ] Leader đổi MEMBER_LOGIC_READY thành true và build lại.
- [ ] Chạy đầy đủ checklist tích hợp trong README.
- [ ] Kiểm tra từ chối xác nhận, lưu file thất bại và bản sao Order.
- [ ] Chuẩn bị demo và vấn đáp chung.

Không đánh dấu các ô còn trống trước khi thực sự triển khai và chạy kiểm tra.
