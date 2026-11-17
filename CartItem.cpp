#include "CartItem.h"
#include <limits>
#include <stdexcept>

using namespace std;

CartItem::CartItem(const Product& product, int quantity)
    : product(product), quantity(quantity) {
    if (quantity <= 0) {
        throw invalid_argument("So luong phai lon hon 0.");
    }
    getTotalPrice(); // Kiem tra phep nhan ngay khi tao dong gio hang.
}

const Product& CartItem::getProduct() const {
    return product;
}

int CartItem::getQuantity() const {
    return quantity;
}

void CartItem::increaseQuantity() {
    if (quantity == numeric_limits<int>::max()) {
        throw overflow_error("So luong vuot gioi han int.");
    }
    const long long nextQuantity = static_cast<long long>(quantity) + 1;
    const long long price = product.getPrice();
    // Product da dam bao gia > 0, nen co the chia de kiem tra tran.
    if (nextQuantity > numeric_limits<long long>::max() / price) {
        throw overflow_error("Thanh tien vuot gioi han long long.");
    }
    ++quantity; // Chi thay doi sau khi da kiem tra xong.
}

void CartItem::decreaseQuantity() {
    if (quantity == 0) {
        throw underflow_error("So luong khong duoc am.");
    }
    --quantity;
}

long long CartItem::getTotalPrice() const {
    const long long price = product.getPrice();
    if (quantity > numeric_limits<long long>::max() / price) {
        throw overflow_error("Thanh tien vuot gioi han long long.");
    }
    return price * quantity;
}
