#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>

// Hàm l?y th?i gian d?a phuong an toàn tuong thích MinGW / GCC
std::tm localDateTime(std::time_t time) {
    std::tm* result = std::localtime(&time);
    if (result) {
        return *result;
    }
    std::tm empty = {};
    return empty;
}

// Hàm d?nh d?ng ngày gi? (Dùng std::strftime tuong thích m?i b?n Dev-C++)
std::string formatDateTime(std::time_t time, const char* format) {
    std::tm date = localDateTime(time);
    char buffer[100];
    if (std::strftime(buffer, sizeof(buffer), format, &date)) {
        return std::string(buffer);
    }
    return "";
}

// Hàm c?ng s? ngày vào th?i gian
std::time_t addCalendarDays(std::time_t time, int days) {
    std::tm date = localDateTime(time);
    date.tm_mday += days;
    date.tm_isdst = -1; // Ð? thu vi?n t? xác d?nh gi? mùa hè n?u có
    return std::mktime(&date);
}
