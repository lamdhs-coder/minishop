#pragma once

// Lop truu tuong: chi quy dinh giao tiep, khong tao truc tiep duoc.
class ShippingMethod {
protected:
    ShippingMethod() {}

public:
    virtual ~ShippingMethod() {}
    virtual long long getFee() const = 0;
    virtual int getDeliveryDays() const = 0;
};

// Giao thuong la mot phuong thuc giao hang (quan he is-a).
class StandardShipping : public ShippingMethod {
public:
    // Hang so dung chung cho moi doi tuong giao thuong.
    static const int FEE = 30000;
    static const int DELIVERY_DAYS = 3;

    StandardShipping() {}

    long long getFee() const {
        return FEE;
    }

    int getDeliveryDays() const {
        return DELIVERY_DAYS;
    }
};
