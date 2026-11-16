#include "CartItem.h"
#include <limits>
#include <stdexcept>

using namespace std;

CartItem::CartItem(const Product &product, int quantity)
    : product(product), quantity(quantity) {
    if (quantity <= 0) throw invalid_argument("Quantity must be positive");
    (void) getTotalPrice();
}

const Product &CartItem::getProduct() const { return product; }
int CartItem::getQuantity() const { return quantity; }

void CartItem::increaseQuantity() {
    if (quantity == numeric_limits<int>::max()) throw overflow_error("Quantity overflow");
    const long long price = product.getPrice();
    if (price < 0) throw invalid_argument("Negative product price");
    if (price != 0 && static_cast<long long>(quantity + 1) > numeric_limits<long long>::max() / price)
        throw overflow_error("Item total overflow");
    ++quantity;
}

void CartItem::decreaseQuantity() {
    if (quantity == 0) throw underflow_error("Quantity cannot be negative");
    --quantity;
}

long long CartItem::getTotalPrice() const {
    const long long price = product.getPrice();
    if (price < 0) throw invalid_argument("Negative product price");
    if (price != 0 && quantity > numeric_limits<long long>::max() / price)
        throw overflow_error("Item total overflow");
    return price * quantity;
}
