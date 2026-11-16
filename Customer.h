#pragma once

class Customer {
private:
    char name[100];
    char phone[11];
    char address[200];

public:
    Customer(const char name[] = "", const char phone[] = "",
             const char address[] = "");
    const char* getName() const;
    const char* getPhone() const;
    const char* getAddress() const;
    static bool isValidPhone(const char phone[]);
    bool isValid() const;
};
