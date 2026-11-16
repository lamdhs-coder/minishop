# MiniShop – Ứng dụng đặt hàng Console

Đồ án OOP nhập môn dùng C++17, G++ và STL std::vector. Có 5 class nghiệp vụ chính:
Product, Customer, CartItem, ShoppingCart và Order; thêm 2 class phụ giao hàng
ShippingMethod và StandardShipping để minh họa kế thừa/đa hình (tổng 7 class).
Không dùng Qt, CMake,
database, server hay thư viện bên thứ ba.

**Trạng thái:** đã ghép code Quốc Vĩ, Bích và bật
`MEMBER_LOGIC_READY = true` trong main.cpp. Toàn bộ menu đã chạy được với file
sản phẩm thật, giỏ hàng, đặt hàng và hóa đơn TXT. Source ứng dụng không còn stub TODO.
Dùng Console; toàn bộ tiền và hai mốc lọc giá là long long theo đơn vị VND.

## Chức năng và phân công

F01–F06 là chức năng bắt buộc; F07–F11 là chức năng sáng tạo.
Tình trạng dưới đây dựa trên kiểm thử sau tích hợp.

| Mã | Chức năng | Phụ trách | Kết quả |
| --- | --- | --- | --- |
| F01 | Đọc products.txt vào vector<Product>, xử lý lỗi file/dữ liệu | Quốc Vĩ | Đạt |
| F02 | Hiển thị mã, tên, giá theo bảng Console | Lâm | Đạt qua menu |
| F03 | Thêm sản phẩm vào giỏ; thêm lại cùng mã thì tăng số lượng | Quốc Vĩ xử lý giỏ; Lâm làm menu | Đạt qua menu |
| F04 | Xem giỏ, số lượng, đơn giá, thành tiền, tổng tiền | Quốc Vĩ tính tiền/số lượng; Lâm hiển thị | Đạt qua menu |
| F05 | Nhập tên, điện thoại, địa chỉ; kiểm tra trước khi đặt hàng | Lâm làm màn hình; Bích làm Customer | Đạt qua menu |
| F06 | Xem trước, hủy/xác nhận, ngày giao, phí, tổng thanh toán | Lâm | Đạt qua menu |
| F07 / S01 | Tìm một phần tên, không phân biệt hoa thường ASCII | Lâm | Đạt qua menu |
| F08 / S02 | Tăng/giảm/xóa sản phẩm trong giỏ | Quốc Vĩ xử lý giỏ; Lâm làm menu | Đạt qua menu |
| F09 / S03 | Lưu hóa đơn TXT sau xác nhận, báo lỗi ghi | Lâm | Menu lưu đạt; lỗi ghi đã thử riêng |
| F10 / S04 | Lọc sản phẩm theo khoảng giá | Bích lọc giá; Lâm gắn vào menu | Hàm và menu đạt |
| F11 / S05 | Thêm sản phẩm mới, lưu vào file và dùng ngay | Lâm | Hàm ghi và menu đạt |

## Cấu trúc và build

Các file được Git theo dõi nằm cùng cấp:

```text
shop/
  main.cpp
  Product.h       Product.cpp
  Customer.h      Customer.cpp
  CartItem.h      CartItem.cpp
  ShoppingCart.h  ShoppingCart.cpp
  Order.h         Order.cpp
  ShippingMethod.h
  ProductFile.h   ProductFile.cpp
  products.txt
  README.md
  TASKS.md
  .gitignore
```

Mở terminal tại thư mục chứa main.cpp và products.txt rồi chạy:

```bash
g++ -std=c++17 -Wall -Wextra main.cpp Product.cpp Customer.cpp CartItem.cpp ShoppingCart.cpp Order.cpp ProductFile.cpp -o minishop.exe
./minishop.exe
```

Đã kiểm tra bằng G++ 16.2.0, MSYS2 UCRT64. Dùng được trong Git Bash, PowerShell
và terminal VS Code khi G++ có trong PATH. PowerShell cũng chạy bằng .\minishop.exe.
Không cần cài thêm thư viện.

Thư mục tests/, file *.exe và hoadon_*.txt bị Git bỏ qua. File test chỉ có cục bộ,
không có sẵn khi clone repo. Chạy tại thư mục source để đọc đúng dữ liệu và lưu hóa đơn.

## Menu và cách thử

```text
1. Xem danh sach san pham
2. Tim kiem san pham
3. Them san pham vao gio
4. Xem gio hang
5. Chinh sua gio hang
6. Dat hang
7. Loc san pham theo khoang gia
8. Them san pham moi vao shop
0. Thoat
```

Nhấn Enter khi được nhắc để quay lại menu chính.

- Chọn 1: thấy toàn bộ sản phẩm hiện có trong products.txt, không cố định số lượng.
- Chọn 2, nhập CHUOT: thấy các tên chứa Chuot/chuot.
- Chọn 7, nhập 250000 rồi 750000: lọc giá trong khoảng, lấy cả hai đầu mút.
  Nhập 750000 rồi 250000 cũng cho cùng kết quả, kèm thông báo đổi hai mốc.
- Giá nhập là số nguyên không âm, không có dấu phân cách. Nhập 250000;
  không nhập 250.000, 250000.5 hoặc chữ.
- Chọn 3 thêm mã 1 hai lần và mã 2 một lần. Chọn 4: tổng số lượng 3,
  tiền hàng 1.350.000 VND.
- Chọn 5 để tăng/giảm từng đơn vị hoặc xóa theo mã; giảm từ 1 về 0 thì xóa dòng.
- Chọn 6, nhập khách và xem trước. Chọn 0 để hủy, giữ nguyên giỏ; chọn 1
  để xác nhận rồi chọn lưu hoặc không lưu TXT.
- Giỏ mẫu trên có phí 30.000 VND, tổng 1.380.000 VND. Sau xác nhận giỏ rỗng,
  Order vẫn giữ bản sao các mặt hàng.

## S05 – Thêm sản phẩm mới vào shop

Chọn mục 8, nhập ID chưa có, tên và giá nguyên dương VND.
Ví dụ dùng một ID còn trống, tên Chuot Razer, giá 650000.
ID 0 là hủy thao tác, không tạo sản phẩm; EOF ở bước nhập cũng không lưu.
ID âm/chữ/thập phân/tràn int, tên rỗng/toàn khoảng trắng hoặc chứa dấu |,
giá 0/âm/chữ/thập phân/tràn long long đều bị từ chối và được nhập lại.
Hàm ghi cũng từ chối tên chứa ký tự xuống dòng để tránh sai định dạng TXT.

Các hàm liên quan:

- main.cpp: addNewProduct nhận tham chiếu tới chính vector products đang dùng.
  Dùng lại readInt/readRequiredText/readPrice; readPrice có tham số allowZero,
  mặc định true cho bộ lọc, false khi thêm sản phẩm mới.
- ProductFile.h/.cpp: appendProductToFile kiểm tra file hiện có và ID trên đĩa,
  ghi bản sao tạm rồi thay file gốc. Không tạo class quản lý mới hoặc sửa Product.

Trình tự lưu:

1. Tạo Product bằng constructor để kiểm tra dữ liệu.
2. Reserve trước dung lượng vector, để lỗi cấp phát xảy ra trước khi ghi.
3. Đọc lại file thật, kiểm tra ID trùng và quyền đọc/ghi. Không tự tạo file
   products.txt nếu file hiện tại bị thiếu hoặc không đọc được.
4. Copy nguyên byte file gốc sang products.txt.tmp trong cùng thư mục.
   Chỉ thêm newline nếu cuối file gốc chưa có; nối sản phẩm mới vào file tạm.
5. Đóng/kiểm tra ghi và đọc kiểm tra lại file tạm, sau đó filesystem::rename
   thay file gốc. Nếu lỗi trước khi thay, file gốc không bị ghi dở.
6. Khi lưu thành công mới push_back sản phẩm vào cùng vector bằng std::move.
   Product hiện có move constructor không ném lỗi; sau reserve không cần
   cấp phát lại khi thêm phần tử. std::move chuyển chuỗi thay vì sao chép lại.

Khi lỗi lưu, vector không nhận thêm phần tử và không báo thành công.
File tạm đã có sẵn không bị ghi đè/xóa tự động; cần kiểm tra nguyên nhân trước
khi thử lại. Khi lỗi sau khi copy thành công, chương trình cố gắng dọn file tạm.
Sản phẩm lưu thành công xuất hiện ngay trong xem/tìm/lọc và thêm vào giỏ,
không cần khởi động lại; mở ứng dụng lần sau vẫn đọc được từ file.
Giỏ hiện có và các bản sao trong Order không bị thay đổi bởi S05.

### Kiến thức và vấn đáp S05

- Chương 1: Product đóng gói dữ liệu, getter dùng khi ghi file.
- Chương 2: addNewProduct tạo object bằng constructor có tham số.
- Chương 7: duyệt vector kiểm tra mã, reserve và push_back cập nhật danh sách.
- I/O: đọc/ghi bằng fstream, ghi tạm để không nối dở vào file gốc.
  Không thêm kế thừa, đa hình hoặc template mới chỉ để làm S05.

| Câu hỏi | Trả lời ngắn |
| --- | --- |
| Vì sao tạo Product trước khi lưu? | Constructor kiểm tra dữ liệu; getter cung cấp giá trị để ghi, không truy cập private trực tiếp. |
| Vector nào được cập nhật? | Chính vector products của main, được truyền bằng tham chiếu vào addNewProduct. |
| Vì sao không push_back trước khi ghi file? | Ghi có thể thất bại; cập nhật trước sẽ khiến màn hình có sản phẩm chưa được lưu. |
| Vì sao phải dùng file tạm? | Ghi hoặc thay file thất bại sẽ không để bản ghi dở trong file gốc. |
| Vì sao khởi động lại vẫn thấy sản phẩm? | Bản ghi id|name|price đã được lưu trong products.txt và được bộ đọc hiện có tải lại. |

## Vai trò class và hàm

| Thành phần | Vai trò |
| --- | --- |
| Product | Mã, tên, giá; constructor/getter; operator== nhận diện theo mã |
| Customer | Tên, điện thoại, địa chỉ; kiểm tra thông tin bắt buộc |
| CartItem | Bản sao Product, số lượng, thành tiền; kiểm tra số lượng và tràn phép nhân |
| ShoppingCart | vector<CartItem>, find_if để tìm sản phẩm trùng, thêm/tăng/giảm/xóa và tổng giỏ |
| Order | Bản sao khách/giỏ, thời gian, bản sao phí/ngày giao từ phương thức giao hàng và hóa đơn |
| ShippingMethod | Lớp trừu tượng, quy định giao tiếp lấy phí và số ngày giao |
| StandardShipping | Kế thừa public, override giao thường: 30.000 VND và 3 ngày |
| loadProductsFromFile | Hàm tự do trong ProductFile.cpp, không phải class thứ sáu |
| filterByPriceRange | Hàm tự do trong Product.cpp, khai báo ở Product.h |

Thuộc tính đều private; getter const chỉ đọc dữ liệu. Chuỗi/vector/đối tượng
được trả bằng tham chiếu const để tránh sao chép không cần thiết.
Main giữ một ShoppingCart; vector kết quả tìm/lọc không thay đổi giỏ hoặc danh sách gốc.

## Minh chứng kiến thức cả 7 chương

| Chương | Kiến thức được dùng thật | Mở code tại |
| --- | --- | --- |
| 1 – Tổng quan OOP | Đóng gói, trừu tượng hóa, các đối tượng tương tác qua phương thức | Product.h, ShoppingCart.h, Order.h, main.cpp |
| 2 – Class/Object | Constructor, getter const, đối tượng const, this, static constexpr, protected constructor và destructor mặc định/ảo | Các class; ShippingMethod.h; Order.cpp |
| 3 – Quá tải toán tử | Product::operator== so sánh theo ID, được gọi khi thêm sản phẩm trùng | Product.h/.cpp, ShoppingCart::addProduct |
| 4 – Kế thừa | StandardShipping public kế thừa ShippingMethod; khởi tạo lớp cha trước lớp con | ShippingMethod.h |
| 5 – Đa hình | Abstract class, pure virtual, override; Order gọi qua const ShippingMethod& | ShippingMethod.h, constructor Order có tham số shipping |
| 6 – Template | parsePositiveInteger<T> tự viết, dùng int cho ID và long long cho giá | ProductFile.cpp |
| 7 – STL | vector, unordered_set, iterator, erase/emplace_back và std::find_if với lambda | ShoppingCart.cpp, ProductFile.cpp, Product.cpp |

Đây là minh chứng trọng tâm từng chương, không ép mọi mục lý thuyết vào source.
Không thêm friend, setter tùy ý, đa kế thừa hoặc class template không có nhu cầu.
Copy constructor mặc định vẫn phù hợp với các thuộc tính số/string/vector.
Các lớp nghiệp vụ không sở hữu con trỏ động nên không cần tự viết destructor
để giải phóng bộ nhớ. ShippingMethod có destructor virtual cho giao diện đa hình.

### Toán tử và thuật toán STL

Product::operator== chỉ so sánh ID: hai sản phẩm cùng ID là cùng một mặt hàng,
kể cả khi tên/giá truyền vào khác nhau. Giỏ giữ thông tin của sản phẩm đã có.
ShoppingCart::addProduct dùng std::find_if với lambda gọi toán tử này.
Lambda trả true khi tìm thấy cùng sản phẩm; iterator trả về dùng để tăng SL.
Nếu bằng items.end() thì thêm dòng mới. Kiểm tra tràn tổng vẫn được thực hiện
trước thay đổi giỏ như trước.

### Kế thừa và đa hình trong đặt hàng

ShippingMethod có hai phương thức ảo thuần túy getFee/getDeliveryDays nên không
tạo đối tượng trực tiếp được. Constructor protected dành cho lớp con.
StandardShipping override cả hai, dùng hằng static constexpr FEE/DELIVERY_DAYS.
Các hằng này dùng chung cho mọi đối tượng giao thường.

Order có hai constructor:

- Hai tham số khách/giỏ: giữ cách gọi cũ, ủy quyền cho constructor bên dưới
  bằng một StandardShipping mặc định.
- Ba tham số, thêm const ShippingMethod&: gọi hai phương thức ảo để lấy
  đúng phí/ngày của lớp con, rồi lưu vào shippingFee/deliveryDays theo giá trị.

Đây là constructor delegation: constructor hai tham số nhờ constructor ba
tham số thực hiện phần khởi tạo/kiểm tra chung. Không lặp lại logic tạo đơn.
Đối tượng giao thường tạm thời tồn tại đủ lâu trong lời gọi constructor.
Order không giữ con trỏ/tham chiếu đến nó nên không có tham chiếu treo sau khi tạo.
Sửa/hủy đối tượng giao hàng sau đó không đổi đơn đã tạo.

Luồng menu vẫn dùng giao thường, phí 30.000 VND, giao sau 3 ngày; không thêm
giao nhanh hay mục menu mới. Ngày giao dùng deliveryDays đã lưu.

### Cách minh họa khi vấn đáp

1. Khởi động: bộ đọc thật dùng template với int và long long.
2. Thêm mã 1 hai lần: mở addProduct để chỉ find_if, lambda và operator==.
3. Đặt hàng: mở constructor Order hai/ba tham số, theo tới getFee/getDeliveryDays
   gọi qua lớp cha và override trong StandardShipping.
4. Chỉ vector, iterator/erase khi giảm mặt hàng về 0 hoặc xóa khỏi giỏ.
5. Chỉ private/public/const, this và các hằng static của lớp giao hàng.

Hàm lọc giá do Bích phụ trách có chữ ký:

```cpp
std::vector<Product> filterByPriceRange(
    const std::vector<Product>& products,
    long long minPrice,
    long long maxPrice);
```

Giữ logic được cung cấp: đổi chỗ nếu min > max, duyệt từng sản phẩm, đưa vào
vector kết quả nếu min <= price <= max. Giữ thứ tự ban đầu.
Dùng long long thay double để không làm tròn số tiền nguyên lớn.
Hàm không nhập/xuất Console; kiểm tra giá nhập không âm nằm trong main.

## Quy tắc dữ liệu và đặt hàng

Mỗi dòng products.txt có đúng dạng id|name|price, ví dụ 1|Chuot Logitech|250000.
Bộ đọc kiểm tra ID nguyên dương không trùng, tên có nội dung, giá nguyên dương
trong giới hạn long long. Dòng sai/dòng trống báo lỗi kèm số dòng; thiếu file báo
lỗi mở file. File rỗng trả danh sách rỗng; ứng dụng thông báo khi xem sản phẩm.
Main thoát mã 1 nếu tải file thất bại.

Nhập bàn phím dùng getline/istringstream, kiểm tra ký tự thừa và tràn số.
EOF kết thúc luồng nhập, không lặp vô hạn. Điện thoại là string gồm đúng
10 chữ số ASCII, bắt đầu bằng 0. Tên/địa chỉ không được rỗng hoặc toàn khoảng trắng.

ShoppingCart kiểm tra tổng trước khi thêm/tăng; thao tác vượt giới hạn bị từ chối
và giữ nguyên giỏ. Order kiểm tra riêng phép cộng phí trước khi xác nhận thành công.

Xem trước không ghi file/sửa giỏ. Hủy hoặc EOF ở xác nhận giữ giỏ.
Sau đồng ý mới tạo Order chính thức bằng thời gian hệ thống lúc xác nhận.
Giao thường cộng 3 ngày lịch bằng localtime/mktime, chuẩn hóa cuối tháng/năm và năm nhuận.
Phí và số ngày được lấy qua giao tiếp ShippingMethod rồi lưu vào Order;
giá trị âm bị từ chối và phép cộng số ngày có kiểm tra tràn.
Ngày giờ theo múi giờ hệ điều hành; tiền dùng long long, không float/double.

Hóa đơn chứa khách/điện thoại/địa chỉ, ngày giờ đặt, ngày giao dự kiến, danh sách
sản phẩm, số lượng, đơn giá, thành tiền, tiền hàng, phí và tổng thanh toán.
Tên mặc định hoadon_YYYYMMDD_HHMMSS.txt, thêm hậu tố khi trùng.
Tên truyền vào đã tồn tại bị từ chối ghi đè. Lỗi mở/ghi/đóng file được báo rõ;
lỗi lưu không hủy đơn đã xác nhận.

## Kiểm thử sau tích hợp

| Nhóm | Kết quả | Phạm vi |
| --- | --- | --- |
| Build C++17 -Wall -Wextra | Đạt, không cảnh báo | Đủ source thực tế |
| Product, Customer, bộ lọc | 42 PASS, 0 FAIL | Getter, bản sao, dữ liệu sai, giới hạn số và lọc giá |
| Bổ sung OOP 7 chương | 23 PASS, 0 FAIL | operator==, find_if, abstract/inheritance/static, virtual dispatch, destructor ảo và bản sao phí/ngày |
| Bộ đọc, giỏ, Order, hóa đơn | 59 PASS, 0 FAIL | File thật/thiếu/sai, mã trùng, tràn số, snapshot, ngày, tiền và ghi file |
| Chạy EXE qua menu | 18 PASS, 0 FAIL | Xem/tìm/lọc, giỏ, nhập khách, hủy/EOF, xác nhận, lưu/không lưu, lỗi tải file |
| S05 – Ghi file | 16 PASS, 0 FAIL | Lưu/đọc lại, giữ byte cũ, mã trùng, tên lỗi, file thiếu/sai/chỉ đọc, thiếu newline và file tạm có sẵn |
| S05 – Menu và tính nhất quán | 18 PASS, 0 FAIL | Nhập sai, hủy/EOF, xem/tìm/lọc/thêm giỏ ngay, restart; lỗi chỉ đọc/khóa thay file không cập nhật vector |

Các nhóm có thể trùng phạm vi, không cộng thành số chức năng.
Bộ kiểm thử tích hợp dùng thư mục tạm chứa bản sao products.txt và hóa đơn thử,
không sửa dữ liệu project và không thay bộ đọc thật bằng mock.

Nếu có tests/member3_test.cpp cục bộ, kiểm tra Product, Customer và lọc giá của Bích bằng:

```bash
g++ -std=c++17 -Wall -Wextra tests/member3_test.cpp Product.cpp Customer.cpp -o test_member3.exe
./test_member3.exe
```

Kết quả hiện tại: 42 PASS, 0 FAIL. Không thêm main.cpp của ứng dụng vào lệnh test
vì file test có main riêng.

Nếu có tests/s05_test.cpp cục bộ:

```bash
g++ -std=c++17 -Wall -Wextra tests/s05_test.cpp Product.cpp ProductFile.cpp -o test_s05.exe
./test_s05.exe
```

Bộ test ghi file tự tạo thư mục tạm ngoài repo rồi dọn sau kiểm tra.
Kết quả: 16 PASS, 0 FAIL. Kiểm thử S05 qua menu dùng bản sao dữ liệu hiện tại;
đã xác nhận hash products.txt thật không thay đổi.

Nếu có tests/oop_test.cpp cục bộ, chạy kiểm thử kiến thức OOP mới:

```bash
g++ -std=c++17 -Wall -Wextra tests/oop_test.cpp Product.cpp Customer.cpp CartItem.cpp ShoppingCart.cpp Order.cpp -o test_oop.exe
./test_oop.exe
```

Kết quả: 23 PASS, 0 FAIL. Test dùng thêm một lớp giao hàng chỉ trong test để
chứng minh Order thực thi override theo kiểu thực tế, không ghi cứng giá trị.
Lớp test này không được dùng trong ứng dụng hoặc bổ sung vào menu.

## Giới hạn và bàn giao

Console dùng tiếng Việt không dấu, cột cố định, không cần màu; không gọi
system("cls") hoặc system("pause"). Bảng hóa đơn rộng 96 ký tự; terminal nên rộng
110–120 cột. Tên Unicode hoặc số tiền cực dài có thể vượt độ rộng cột; đây là
giới hạn trình bày, không thay đổi số tiền lưu trong dữ liệu.

Trong các trường hợp đã kiểm thử, không còn chức năng bắt buộc bị chặn bởi TODO.
S05 dành cho một tiến trình Console; không có khóa để nhiều ứng dụng cùng sửa file.
Chưa mô phỏng đĩa đầy, mất điện hoặc tiến trình bị ngắt giữa chừng; không coi các
trường hợp này là PASS. File tạm có thể cần kiểm tra/dọn thủ công sau gián đoạn.
Cả nhóm vẫn cần chạy demo trên máy mình, đọc hiểu code và chuẩn bị vấn đáp.
Việc thuyết trình thực tế chưa được coi là hoàn thành.

Xem [TASKS.md](TASKS.md) để theo dõi phân công.
