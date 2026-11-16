#pragma once

// Lop truu tuong: chi quy dinh giao tiep, khong tao truc tiep duoc.
class ShippingMethod {
protected:
    ShippingMethod() = default;

public:
    virtual ~ShippingMethod() = default;
    virtual long long getFee() const = 0;
    virtual int getDeliveryDays() const = 0;
};

// Giao thuong la mot phuong thuc giao hang (quan he is-a).
class StandardShipping : public ShippingMethod {
public:
    // Hang so dung chung cho moi doi tuong giao thuong.
    static constexpr long long FEE = 30000;
    static constexpr int DELIVERY_DAYS = 3;

    StandardShipping() = default;

    long long getFee() const override {
        return FEE;
    }

    int getDeliveryDays() const override {
        return DELIVERY_DAYS;
    }
};
