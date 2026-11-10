# MiniShop – Ứng dụng đặt hàng Console

Đồ án OOP nhập môn, dùng C++17 và `std::vector`. Tiền được lưu bằng
`long long` theo đơn vị VND. Không dùng Qt, CMake hoặc thư viện bên thứ ba.

**Trạng thái hiện tại:** phần Leader đã viết đầy đủ source; phần code của thành
viên 3 (Product, Customer) đã hoàn thiện và kiểm thử. Phần thành viên 2 vẫn là
khung TODO. Project biên dịch và chạy menu được, nhưng **chưa mua hàng được**.
Cả sáu mục chức năng đang được chặn bằng cờ
`MEMBER_LOGIC_READY = false` trong `main.cpp`. Khi chọn, chương trình báo:

> Chuc nang dang duoc thanh vien phat trien.

Không dùng dữ liệu giả, không gọi stub để giả lập đặt hàng thành công.

## Chức năng và tình trạng

| Mã | Yêu cầu | Tình trạng thực tế |
| --- | --- | --- |
| F01 | Đọc products.txt vào vector<Product>, xử lý thiếu file | TODO thành viên 2; main đã bắt lỗi tải file |
| F02 | Bảng mã, tên, đơn giá sản phẩm | Product đã hoàn thiện; giao diện chờ bộ đọc file |
| F03 | Thêm theo mã, trùng mã tăng số lượng | Leader đã nối menu; logic ShoppingCart chờ thành viên 2 |
| F04 | Xem giỏ, đơn giá, số lượng, thành tiền, tổng | Leader đã viết giao diện; chờ CartItem/ShoppingCart |
| F05 | Nhập khách hàng, kiểm tra giỏ rỗng | Customer đã hoàn thiện; luồng chờ ShoppingCart |
| F06 | Xem trước, xác nhận, ngày giao, phí và tổng tiền | Leader đã viết Order và checkout; chưa kiểm thử tích hợp |
| F07 | Tìm một phần tên, không phân biệt hoa thường ASCII | Leader đã viết; chờ dữ liệu sản phẩm thật |
| F08 | Tăng, giảm, xóa trong giỏ | Leader đã nối menu; logic chờ thành viên 2 |
| F09 | Lưu hóa đơn TXT sau xác nhận | Leader đã viết; chưa kiểm thử thực tế với đơn hàng |

## Cấu trúc

Các file nằm trực tiếp trong workspace `shop`, không lồng thêm thư mục:

```text
shop/
  main.cpp
  Product.h       Product.cpp
  Customer.h      Customer.cpp
  CartItem.h      CartItem.cpp
  ShoppingCart.h  ShoppingCart.cpp
  Order.h         Order.cpp
  ProductFile.h   ProductFile.cpp
  products.txt
  tests/member3_test.cpp
  README.md
  TASKS.md
  .gitignore
```

## Biên dịch và chạy

Mở terminal **tại thư mục chứa các source file** rồi chạy:

```bash
g++ -std=c++17 -Wall -Wextra main.cpp Product.cpp Customer.cpp CartItem.cpp ShoppingCart.cpp Order.cpp ProductFile.cpp -o minishop.exe
./minishop.exe
```

Dùng được trong Git Bash/MSYS2 và terminal VS Code. Trong PowerShell cũng có thể
chạy bằng `./minishop.exe` hoặc `.\minishop.exe`. G++ cần có trong PATH.

Không có bước cài thêm thư viện. Chạy tại thư mục source để đường dẫn tương đối
`products.txt` và đường dẫn lưu hóa đơn đúng nơi mong muốn.

## Vai trò của đúng 5 class

| Class | Thành viên | Dữ liệu và trách nhiệm |
| --- | --- | --- |
| Product | 3 | Mã, tên, giá của một sản phẩm |
| Customer | 3 | Tên, số điện thoại, địa chỉ người mua |
| CartItem | 2 | Bản sao Product, số lượng, thành tiền một dòng |
| ShoppingCart | 2 | vector<CartItem>, thêm/tăng/giảm/xóa, tổng giỏ |
| Order | Leader | Bản sao Customer và vector<CartItem>, thời gian, phí, hóa đơn |

`ProductFile` chỉ chứa hàm tự do `loadProductsFromFile`, không phải class thứ sáu.
`main.cpp` giữ một ShoppingCart, không quản lý một vector giỏ hàng khác.
Vector dùng khi tìm kiếm chỉ chứa kết quả sản phẩm.

Các thuộc tính đều private. Getter có `const` để việc đọc không làm đổi đối tượng.
Getter trả `const &` cho chuỗi/vector/đối tượng nhằm tránh sao chép không cần thiết;
không giữ tham chiếu đó lâu hơn vòng đời đối tượng gốc.

Luồng phối hợp: đọc file → vector<Product> → ShoppingCart chứa CartItem →
nhập Customer → xem trước Order → xác nhận tạo Order chính thức → lưu TXT.

## Phần Leader

- Các hàm riêng trong main: `showMainMenu`, `showProducts`, `searchProducts`,
  `addToCart`, `showCart`, `editCart`, `checkout`.
- Nhập hoàn toàn bằng getline; dùng istringstream kiểm tra số nguyên, khoảng
  hợp lệ và ký tự thừa. EOF kết thúc luồng nhập, không lặp vô hạn.
- Tên và địa chỉ phải có nội dung sau khi bỏ khoảng trắng đầu/cuối. Điện thoại
  phải đúng 10 ký tự số ASCII, bắt đầu bằng 0; giữ kiểu string.
- Xem trước không lưu file, không xóa giỏ. Từ chối hoặc EOF lúc xác nhận giữ giỏ.
- Sau đồng ý mới tạo Order chính thức bằng thời gian hệ thống tại thời điểm đó.
  Order giữ bản sao, nên việc xóa giỏ sau xác nhận không đổi hóa đơn.
- Phí cố định 30.000 VND. Thành tiền dòng lấy từ CartItem; Order cộng các dòng,
  kiểm tra tràn số rồi cộng phí. Không dùng float/double.
- Ngày giao dùng localtime, tăng tm_mday thêm 3, mktime chuẩn hóa cuối
  tháng/năm và năm nhuận. Ngày giờ theo múi giờ hệ điều hành, không ghi cứng ngày.
- Hai hàm tự do `formatMoney` và `writeItemsTable` trong Order dùng chung cho
  giỏ Console và hóa đơn; tên sản phẩm dài được xuống dòng trong hóa đơn.
- Hóa đơn do getReceiptText tạo thành string; Order không nhập bàn phím.
- Tên mặc định: `hoadon_YYYYMMDD_HHMMSS.txt`; nếu trùng thì thêm `_1`, `_2`…
  Tên truyền vào đã tồn tại sẽ bị từ chối ghi đè. Lỗi mở/ghi/đóng file được
  báo bằng exception, main hiện thông báo rõ. Lỗi lưu không hủy đơn đã xác nhận.

Giao diện dùng tiếng Việt không dấu, iomanip và ký tự ASCII, không cần màu,
không gọi system("cls") hoặc system("pause"). Dữ liệu mẫu cũng dùng tên ASCII
để căn cột ổn định. Với tên Unicode, độ rộng hiển thị có thể khác độ dài byte.

## Bắt đầu công việc và tích hợp

1. Product và Customer đã hoàn thiện constructor, getter và kiểm thử riêng.
   Thành viên 3 đọc phần giải thích dưới đây để nắm code khi vấn đáp.
2. Thành viên 2 hoàn thiện CartItem, ShoppingCart, ProductFile theo TODO.
   Có thể đọc các header trước để thống nhất giao tiếp với main và Order.
3. Giữ nguyên chữ ký hàm. ShoppingCart tăng/giảm/xóa trả false khi không có mã,
   true khi đã thay đổi. addProduct thêm một đơn vị; trùng mã tăng một đơn vị.
   Giảm từ 1 về 0 phải xóa dòng khỏi vector.
4. CartItem kiểm tra số lượng và tràn phép nhân; ShoppingCart kiểm tra tràn
   phép cộng. getSubtotal gọi getTotalPrice của từng dòng. Không nhập bàn phím
   hoặc in thông báo thành công trong các class dữ liệu.
5. ProductFile dùng ifstream và getline, tách đúng ba trường bằng dấu `|`.
   Thiếu file hoặc dòng không hợp lệ ném runtime_error với thông tin rõ ràng.
   Không biến lỗi đọc thành danh sách rỗng hoặc bỏ qua âm thầm dòng lỗi.
6. Chỉ sau khi tất cả TODO thành viên hoàn tất và kiểm tra riêng, đổi **một dòng**
   trong main.cpp thành `constexpr bool MEMBER_LOGIC_READY = true;`.
7. Build lại và kiểm thử toàn bộ luồng. Nếu bật quá sớm, stub còn sót sẽ ném
   lỗi TODO; đó là dấu hiệu chưa tích hợp xong, không phải chức năng đã chạy.

ShoppingCart dùng constructor mặc định do C++ tạo để khởi tạo vector rỗng;
các phương thức nghiệp vụ và CartItem vẫn là stub. Không bật cờ khi các TODO
của thành viên 2 chưa hoàn tất.

Dữ liệu mẫu đã được rà soát: 10 dòng đúng định dạng, ID dương không trùng,
giá dương; đã tạo được Product thật từ cả 10 dòng khi kiểm thử riêng.

## Phần thành viên 3 và gợi ý vấn đáp

- Product lưu id, name và price trong thuộc tính private. Constructor dùng
  danh sách khởi tạo để sao chép dữ liệu, sau đó từ chối id/giá không dương
  hoặc tên rỗng/chỉ gồm khoảng trắng bằng `std::invalid_argument`.
- Customer sao chép tên, điện thoại và địa chỉ; từ chối tên/địa chỉ rỗng hoặc
  chỉ gồm khoảng trắng. Điện thoại phải đúng 10 chữ số ASCII, bắt đầu bằng 0.
  Lưu bằng string nên không mất số 0 đầu. Constructor không tự cắt khoảng trắng;
  main đã xử lý đầu vào, còn dữ liệu truyền trực tiếp sai định dạng sẽ bị từ chối.
- Việc kiểm tra tại class bảo vệ dữ liệu cả khi tạo đối tượng ngoài menu;
  kiểm tra tại main giúp người dùng được nhập lại ngay khi gõ sai.
- Mỗi getter chỉ trả thuộc tính tương ứng. `const` sau tên hàm cho phép đọc
  trên đối tượng const; `const std::string&` tránh sao chép và không cho người
  gọi sửa chuỗi private qua getter. Hai class không nhập/xuất Console.
- Dữ liệu được lưu theo giá trị: đổi biến chuỗi nguồn sau khi khởi tạo không
  đổi đối tượng. Phép sao chép mặc định của C++ cũng sao chép các thuộc tính.

Thành viên 3 cần đọc, chạy và tự giải thích phần này để chuẩn bị thuyết trình;
việc thuyết trình thực tế chưa được đánh dấu hoàn thành.

## Tự chạy kiểm thử phần thành viên 3

Từ thư mục `shop`, chạy hai lệnh trong Git Bash hoặc PowerShell:

```bash
g++ -std=c++17 -Wall -Wextra tests/member3_test.cpp Product.cpp Customer.cpp -o test_member3.exe
./test_member3.exe
```

File kiểm thử có main riêng, vì vậy **không thêm main.cpp của ứng dụng** vào
lệnh trên. Không cần bật MEMBER_LOGIC_READY và không cần phần thành viên 2.
Chương trình tự chạy 32 kiểm tra, in từng dòng PASS/FAIL; kết quả đúng là
`Ket qua: 32 PASS, 0 FAIL`. Khi có lỗi, chương trình trả mã thoát 1.

Kiểm thử gồm constructor/getter, lưu trong vector, sao chép dữ liệu, giới hạn
ID/giá, tên/địa chỉ rỗng hoặc toàn khoảng trắng và điện thoại sai định dạng.
Đây là kiểm thử riêng hai class; luồng mua hàng trên menu vẫn chờ thành viên 2.

## Kiểm tra đã thực sự chạy

Đã kiểm tra bằng **G++ 16.2.0 (MSYS2 UCRT64)**:

| Kiểm tra | Kết quả và phạm vi |
| --- | --- |
| Lệnh build C++17 -Wall -Wextra ở trên | Thành công, không cảnh báo source project |
| Khởi động, hiển thị menu, chọn 0 | Chạy được, thoát bình thường |
| Menu nhập chữ, ngoài khoảng, âm, ký tự thừa | Báo lỗi và cho nhập lại |
| Lần lượt chọn cả 6 mục khi cờ false | Đều báo đang phát triển; không gọi stub, không báo đặt hàng thành công |
| EOF tại menu và hàm nhập số | Thoát được, không lặp vô hạn |
| Hàm kiểm tra tên/địa chỉ bắt buộc | Từ chối khoảng trắng/rỗng và cho nhập lại |
| Hàm kiểm tra điện thoại | Chấp nhận 0901234567; từ chối sai độ dài, đầu số, chữ, khoảng trắng bên trong |
| Hàm định dạng tiền | Đúng với 0, 999, 1000, 1380000, giới hạn long long |
| Hàm cộng ngày được Order sử dụng | Đúng qua cuối tháng/năm, tháng 2 năm nhuận và thường |
| Product: constructor, getter, sao chép, lưu trong vector | Đạt; kiểm tra giá 1 và giới hạn long long, ID giới hạn int, tên dài |
| Product: đầu vào không hợp lệ | Từ chối ID/giá 0 hoặc âm, tên rỗng hoặc chỉ khoảng trắng |
| Customer: constructor, getter, sao chép | Đạt; giữ số 0 đầu, lưu chuỗi tiếng Việt, độc lập với biến nguồn |
| Customer: đầu vào không hợp lệ | Từ chối tên/địa chỉ rỗng hoặc chỉ khoảng trắng; điện thoại sai độ dài, đầu số, chữ hoặc khoảng trắng |
| products.txt và Product thật | Đã tạo đủ 10 Product, đối chiếu mã và giá mẫu; không dùng bộ đọc file TODO |

Các kiểm tra menu, hàm nhập, ngày và tiền dùng bộ chạy kiểm tra tạm thời.
Kiểm thử Product/Customer có thể chạy lại bằng `tests/member3_test.cpp`,
không cần framework. **Kiểm tra hàm nhập không có nghĩa đã
chạy được checkout. Kiểm tra hàm cộng ngày không thay thế kiểm thử Order.**

**Chưa chạy thực tế do phụ thuộc TODO:** khởi tạo đơn với dữ liệu thật, bản sao
khách/giỏ, phí và tổng tiền của Order, nội dung đầy đủ của hóa đơn, ghi file thành
công/thất bại, từ chối xác nhận giữ giỏ, các chức năng F01–F09 từ menu sau tích hợp.
Các phần này mới được viết và rà soát source, không được coi là PASS.

## Kiểm thử sau tích hợp

- Đọc đủ 10 sản phẩm; thử thiếu products.txt và dòng dữ liệu sai.
- Thêm cùng mã hai lần: một dòng, SL 2; thử mã không tồn tại.
- Tìm "CHUOT": thấy các sản phẩm có "Chuot"; thử từ khóa không có kết quả.
- Tăng, giảm, xóa; giảm SL 1 thì mất dòng; không có số lượng âm.
- Giỏ rỗng không được đặt. Kiểm tra tổng số lượng và thành tiền.
- Tên/địa chỉ rỗng phải nhập lại; điện thoại sai phải nhập lại.
- Thử từ chối xác nhận: toàn bộ giỏ giữ nguyên, không có file mới.
- Xác nhận: ngày giờ là lúc xác nhận, giao sau 3 ngày, phí 30.000 VND.
- Với Chuot Logitech SL 2 và Ban phim AKKO SL 1: tạm tính 1.350.000,
  tổng 1.380.000 VND. Sau thành công giỏ rỗng, hóa đơn vẫn đủ dữ liệu.
- Chọn không lưu thì không có file. Chọn lưu thì nội dung đúng bản in.
- Gọi saveReceiptToFile với đường dẫn không hợp lệ: phải báo lỗi ghi.
  Lưu hai lần cùng giây phải có hai tên khác nhau.
- Thử tên sản phẩm dài và giá/số lượng lớn; không vỡ cột hoặc tràn số âm.

Xem [TASKS.md](TASKS.md) để theo dõi phân công và trạng thái bàn giao.
