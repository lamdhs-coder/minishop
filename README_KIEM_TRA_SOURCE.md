# Báo cáo kiểm tra và đơn giản hóa source MiniShop

## Kết quả và phạm vi

Đã đối chiếu toàn bộ các file .h/.cpp của ứng dụng với các PDF môn học, đọc phần văn bản và xem các trang ví dụ code liên quan. Người dùng đã chốt **chỉ chương 1–6**, nên chương 7, LAB 7 và Capstone chỉ được dùng để nhận diện sự khác biệt về phạm vi, không làm căn cứ đưa STL hoặc chức năng ngoài phạm vi vào bản cuối.

README.md gốc, TASKS.md, docs/ON_TAP_OOP.md và products.txt được giữ nguyên trong lần sửa này. Các tài liệu cũ có thể mô tả source trước khi đơn giản hóa; báo cáo này mô tả bản hiện tại. Nội dung bài tập trong PDF là tài liệu tham khảo, không phải lệnh tự động thêm chức năng vào dự án.

**Bản hiện tại:** kiến thức chương 1–6, với ngoại lệ được người dùng cho phép là thư viện fstream để đọc products.txt. Dùng mảng cố định, chuỗi char[], hàm thường, vòng lặp có chỉ số và kiểm tra dữ liệu bằng bool. Chỉ include trực tiếp iostream và fstream; không dùng string, vector, sstream, ctime, filesystem, thuật toán STL hoặc ngoại lệ.

Các phép toán, kiểu số, hàm, if/for/while, mảng ký tự và nhập/xuất là kiến thức C++ nền tảng để triển khai ví dụ OOP. Không khẳng định các hàm tự viết có sẵn nguyên văn trong slide.

## Căn cứ trong chương học

| Kiến thức | Căn cứ PDF | Source hiện tại |
| --- | --- | --- |
| Đối tượng, đóng gói và tương tác qua phương thức | Chương 1, trang 19–28 | Product, Customer, CartItem, ShoppingCart, Order |
| Tách khai báo và định nghĩa, pragma once | Chương 2, trang 15–16 | Các cặp .h/.cpp; toàn bộ header dùng pragma once |
| Constructor và tham số mặc định | Chương 2, trang 18–30 | Product, Customer, CartItem, ShoppingCart, Order |
| Getter const, thành phần static/const, this | Chương 2, trang 35–51 | Getter các lớp; giới hạn dữ liệu; Customer::isValidPhone |
| Quá tải toán tử | Chương 3, trang 11–19 | Product::operator== so sánh mã, dùng khi thêm trùng vào giỏ |
| Kế thừa public và lớp cha/con | Chương 4, trang 8–11, 24, 29–31 | StandardShipping kế thừa ShippingMethod |
| Hàm ảo, destructor ảo và lớp trừu tượng | Chương 5, trang 9–13 | ShippingMethod; Order gọi getFee/getDeliveryDays qua tham chiếu lớp cha |
| Khuôn mẫu hàm và lớp | Chương 6, trang 7–16 | parsePositiveInteger<T> trong ProductFile.cpp dùng chung cho mã int và giá long long |

Không cần áp dụng tất cả kiến thức trong mỗi chương. Chỉ dùng một template nhỏ để tránh viết lặp phần đọc số cho int và long long. Các lớp nghiệp vụ vẫn giữ kiểu cụ thể. fstream là thư viện bổ trợ ngoài slide được người dùng cho phép, không xem là nội dung đã được dạy trong chương 1–6.

## Phát hiện ở source trước khi sửa

| Vị trí trước khi sửa | Kỹ thuật/hàm | Đánh giá |
| --- | --- | --- |
| ShoppingCart::addProduct | find_if, lambda, auto | Cách viết vượt các ví dụ chương 1–6; thay bằng vòng lặp |
| Các danh sách trong Product, ProductFile, ShoppingCart, Order, main | vector, iterator, erase, push_back | Thuộc chương 7; thay bằng mảng và biến đếm |
| ProductFile::loadProductsFromFile | fstream, unordered_set, emplace_back, try/catch | Không thuộc phạm vi 1–6 đã chốt |
| ProductFile::appendProductToFile | filesystem, copy_file, rename, error_code, file tạm | Quá phức tạp; chức năng thêm sản phẩm cũng đã được yêu cầu bỏ |
| parsePositiveInteger<T> | template kết hợp stringstream và throw | Template thuộc chương 6; stringstream/ngoại lệ không được giảng trong các chương này |
| Product/Customer/CartItem/ShoppingCart/Order/main | throw, try/catch, invalid_argument, overflow_error | Không có bài học xử lý ngoại lệ trong chương 1–6 |
| CartItem, ShoppingCart, Order | numeric_limits, kiểm tra tràn số nhiều tầng | Thay bằng giới hạn giá/số lượng rõ ràng và phép tính thường |
| main::addNewProduct | reserve, move | Tối ưu không cần thiết cho bài nhập môn; bỏ cùng chức năng 8 |
| Order | constructor ủy quyền | Không được trình bày trong chương 1–6; thay bằng constructor thông thường |
| ShippingMethod | constexpr, = default, override | Ý tưởng OOP phù hợp; cú pháp mới không được trình bày trong slide, đổi cách viết cơ bản |
| Order | time, localtime, mktime, put_time/định dạng ngày, lưu TXT | Thư viện bổ trợ ngoài phạm vi 1–6; bỏ theo lựa chọn người dùng |
| main/Order | stringstream, to_string, setw, xử lý string | Bỏ để tránh phụ thuộc API ngoài phần đã học; nhập/xuất và chuỗi dùng cách cơ bản |

`#pragma once`, constructor, getter const, this, operator==, kế thừa, hàm ảo và lớp trừu tượng đều được giữ. Không đánh đồng “có cú pháp giống template” với việc mọi lớp STL đều thuộc chương 6.

## Đã thay đổi những gì

| File | Thay đổi cụ thể |
| --- | --- |
| Product.h/.cpp | Tên dùng char[100]; thêm constructor mặc định cho ô mảng; isValid kiểm tra sản phẩm; print in một dòng; giữ operator==; bỏ filterByPriceRange |
| Customer.h/.cpp | Tên/điện thoại/địa chỉ dùng mảng char; kiểm tra dữ liệu bằng isValid; tách isValidPhone dùng chung cho menu và class, không còn kiểm tra điện thoại lặp lại |
| CartItem.h/.cpp | Constructor cho ô mảng; tăng số lượng trả bool; giảm có kiểm tra 0; giá × số lượng là phép tính thường; bỏ ngoại lệ và kiểm tra tràn nhiều tầng |
| ShoppingCart.h/.cpp | Thay vector bằng CartItem items[100] và itemCount; findProduct tìm vị trí; xóa bằng cách dồn mảng; tổng tiền/số lượng tính bằng for; thêm print |
| ShippingMethod.h | Giữ abstract class, kế thừa và hàm ảo; thay constexpr bằng static const, = default bằng thân hàm rỗng; bỏ từ khóa override nhưng vẫn ghi đè hàm ảo |
| Order.h/.cpp | Giữ bản sao Customer và ShoppingCart; một constructor thông thường; isValid kiểm tra trước khi dùng; tính tiền và print hóa đơn console; bỏ ngày giờ, định dạng tiền và lưu TXT |
| main.cpp | Đọc sản phẩm từ products.txt vào mảng 100 phần tử; menu chỉ có 1–6 và 0; nhập liệu bằng readText/readInt; tìm kiếm và sửa giỏ bằng vòng lặp; bỏ cờ ghép code, hàm dư và menu 7–8 |
| ProductFile.h/.cpp | Đã khôi phục theo yêu cầu giữ fstream: đọc id|name|price vào mảng, kiểm tra tên/mã/giá/trùng mã/sức chứa; trả bool và lý do lỗi qua char error[200]. Không có chức năng ghi/thêm sản phẩm |
| Text.h/.cpp | Thêm nhóm hàm thường dùng chung cho mảng char để tránh lặp sao chép/kiểm tra/tìm kiếm chuỗi trong nhiều class |

Không thêm Input.h/.cpp. Các hàm nhập liệu chỉ dùng trong menu nên nằm ở main.cpp. Text.h/.cpp có lý do tách riêng: được cả Product, Customer và main sử dụng.

### Cách đọc các hàm quan trọng

- readText: đọc hết một dòng bằng cin.get, ghi trong giới hạn mảng và bỏ phần vượt giới hạn. Chấp nhận dòng cuối chưa có Enter nếu vẫn có dữ liệu; hết dữ liệu thì trả false.
- readInt: duyệt ký tự, chỉ chấp nhận chữ số; kiểm tra giới hạn trước phép nhân 10 để không tràn khi nhập số dài. Không nhận dấu âm, dấu cộng hoặc khoảng trắng quanh số.
- copyText: chép cả ký tự kết thúc '\0'; chuỗi quá dài thì trả false và để chuỗi đích rỗng, không cắt tên âm thầm.
- containsText: tìm chuỗi con bằng hai vòng lặp; chữ hoa/thường ASCII được so sánh cùng dạng.
- ShoppingCart::removeProduct: tìm chỉ số rồi dời các phần tử sau sang trái một ô, giảm itemCount.
- Order: sao chép khách và giỏ; chỉ giữ giá trị phí/ngày lấy từ phương thức ảo, không giữ tham chiếu tới đối tượng giao hàng.

## Giới hạn dữ liệu

| Nội dung | Giới hạn |
| --- | --- |
| Sản phẩm trong shop | Tối đa 100 sản phẩm đọc từ products.txt |
| Loại mặt hàng trong giỏ | 100 |
| Số lượng mỗi loại | 999 |
| Đơn giá hợp lệ | 1 đến 1.000.000.000 VND |
| Tên sản phẩm/khách hàng | 99 byte và 1 ô kết thúc '\0' |
| Địa chỉ | 199 byte và 1 ô kết thúc '\0' |
| Điện thoại | 10 chữ số, bắt đầu bằng 0 |
| Phí/ngày giao của phương thức tùy chọn | Phí từ 0 đến 1 tỷ, số ngày từ 0 đến 30 |

Giá tối đa × số lượng tối đa × số mặt hàng tối đa = 99.900.000.000.000 VND. Cộng phí tối đa vẫn nằm trong long long, vì vậy không cần thuật toán kiểm tra tràn nhiều tầng trong từng phép tính. Tiền in dạng số nguyên VND.

Giới hạn chuỗi tính theo byte; chữ tiếng Việt UTF-8 có thể dùng nhiều byte. Tìm kiếm không phân biệt hoa/thường chỉ dành cho ASCII.

## Chức năng còn lại và khác biệt với Capstone

Menu giữ: xem sản phẩm, tìm theo tên, thêm vào giỏ, xem giỏ, tăng/giảm/xóa, nhập khách hàng và xem trước/hủy/xác nhận đơn. Xác nhận xóa giỏ; hủy giữ nguyên giỏ. Hóa đơn giữ bản sao nên xóa giỏ không làm mất dữ liệu hóa đơn đang in. Giao thường có phí 30.000 VND và dự kiến 3 ngày.

Đã khôi phục đọc products.txt. Không có lọc giá (7), thêm sản phẩm mới (8), lưu hóa đơn TXT, ngày đặt hệ thống hoặc ngày giao theo lịch. Chương trình chỉ đọc products.txt, không ghi/sửa file; các hóa đơn cũ được giữ nguyên.

### Định dạng products.txt và cách đọc

Đặt products.txt trong thư mục làm việc khi chạy chương trình (thường là thư mục project), mỗi dòng đúng ba trường:

```text
1|Chuot Logitech|250000
2|Ban phim AKKO|850000
```

- ifstream mở file, getline đọc từng dòng vào mảng char[256].
- Vòng lặp tìm đúng hai dấu |, rồi chia dòng thành mã, tên và giá bằng ký tự kết thúc chuỗi.
- parsePositiveInteger<T> kiểm tra chữ số và giới hạn trước khi nhân 10; dùng cho int và long long.
- Product::isValid kiểm tra dữ liệu; vòng lặp kiểm tra mã trùng; chỉ thêm khi mảng còn chỗ.
- Thành công trả true và số lượng sản phẩm qua count. Lỗi trả false, count = 0 và ghi lý do vào error (mảng phải có ít nhất 200 ô); main báo lỗi và thoát với mã 1. Các ô mảng có thể đã chứa một phần dữ liệu khi đọc lỗi, nên bên gọi chỉ sử dụng khi kết quả là true.
- File rỗng hợp lệ, hiển thị danh sách rỗng. Chấp nhận CRLF và dòng cuối không có ký tự xuống dòng. Dòng trắng, sai số trường, mã trùng, tên quá dài, giá không hợp lệ hoặc quá 100 sản phẩm bị từ chối.
- Mã và giá chỉ nhận chữ số, không dùng dấu hoặc khoảng trắng quanh số. Tên được phép có khoảng trắng, không được chứa dấu | hoặc xuống dòng.

**Bản này phục vụ yêu cầu học tập chỉ chương 1–6, chưa đáp ứng đầy đủ đề Capstone.** Bản này đã đọc danh sách từ file; còn thiếu lớp STL và ngày đặt thực tế trên hệ thống so với Capstone. Đây là sự khác biệt được ghi nhận, không tự đưa lại các kỹ thuật ngoài phạm vi người dùng đã chọn.

## Build và kiểm thử bản cuối

Lệnh build ứng dụng:

```powershell
g++ -std=c++17 -Wall -Wextra -Wconversion main.cpp Product.cpp Customer.cpp CartItem.cpp ShoppingCart.cpp Order.cpp Text.cpp ProductFile.cpp -o minishop_kiemtra.exe
.\minishop_kiemtra.exe
```

MinGW cần thư mục bin trong PATH khi build và chạy. Trên máy hiện tại:

```powershell
$env:PATH = "C:/Program Files/JetBrains/CLion 2026.2.3.1/bin/mingw/bin;" + $env:PATH
```

Kết quả sau khi cho phép thêm fstream:

- GCC 15.2.0: build không cảnh báo với -Wall -Wextra -Wconversion.
- 43 kiểm tra lớp đạt: dữ liệu sai, giới hạn, thêm trùng, đầy giỏ, giảm về 0, xóa/dồn mảng, bản sao Order, hàm ảo và các hàm chuỗi.
- 13 kịch bản menu đạt: xem/tìm, nhập sai, sửa giỏ, hủy/xác nhận, điện thoại sai, tên dài, EOF và từ chối 7/8.
- 18 trường hợp đọc file đạt: thiếu/rỗng, dòng cuối thiếu xuống dòng, CRLF, mã trùng, sai trường, số quá lớn, tên dài/trắng, dòng quá dài, 100 sản phẩm và vượt sức chứa.
- So sánh mã băm xác nhận README.md gốc và dữ liệu products.txt không thay đổi.

Các kết quả kiểm tra của phiên bản trước không thay cho kết quả bản có fstream ở trên.

Bộ test cục bộ trong tests/ bị gitignore. Test C++ các lớp dùng hàm thường, mảng và iostream; test đọc file được chạy qua ứng dụng bằng Python trong thư mục tạm. Test Python là công cụ bên ngoài để chạy ứng dụng trong thư mục tạm, không thuộc source ứng dụng. Các bộ test cũ không còn phù hợp giao diện được giữ ở dạng tham khảo .txt.

```powershell
g++ -std=c++17 -Wall -Wextra -Wconversion main.cpp Product.cpp Customer.cpp CartItem.cpp ShoppingCart.cpp Order.cpp Text.cpp ProductFile.cpp -o tests/minishop_review.exe
g++ -std=c++17 -Wall -Wextra -Wconversion tests/source_review_test.cpp Product.cpp Customer.cpp CartItem.cpp ShoppingCart.cpp Order.cpp Text.cpp ProductFile.cpp -o tests/source_review_test.exe
python tests/source_review_runner.py
```

## Tài liệu đã đọc

- [Chương 1 — Tổng quan](../../Chuong%201%20-%20Gioi%20thieu%20tong%20quan.pdf)
- [Chương 2 — Lớp và đối tượng](../../Chuong%202%20-%20Lop%20Va%20Doi%20Tuong.pdf)
- [Chương 3 — Quá tải toán tử](../../Chuong%203%20-%20Qua%20tai%20toan%20tu.pdf)
- [Chương 4 — Kế thừa](../../Chuong%204%20-%20Ke%20thua.pdf)
- [Chương 5 — Đa hình](../../Chuong%205%20-%20Da%20hinh.pdf)
- [Chương 6 — Khuôn mẫu](../../Chuong%206%20-%20Khuon%20mau.pdf)

Đã đọc thêm chương 7, LAB 7 và Capstone để xác định phần bị loại khỏi phạm vi và những yêu cầu đề bài chưa được đáp ứng; không triển khai thêm bài tập từ các tài liệu đó.
