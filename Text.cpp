#include "Text.h"

int textLength(const char text[]) {
    int length = 0;
    while (text[length] != '\0') {
        length++;
    }
    return length;
}

bool copyText(char destination[], int capacity, const char source[]) {
    int length = textLength(source);
    if (length >= capacity) {
        destination[0] = '\0';
        return false;
    }
    for (int i = 0; i <= length; i++) {
        destination[i] = source[i];
    }
    return true;
}

bool hasText(const char text[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] != ' ' && text[i] != '\t' && text[i] != '\r'
            && text[i] != '\n' && text[i] != '\f' && text[i] != '\v') {
            return true;
        }
    }
    return false;
}

char lowercase(char letter) {
    if (letter >= 'A' && letter <= 'Z') {
        return letter + ('a' - 'A');
    }
    return letter;
}

bool containsText(const char text[], const char keyword[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        int j = 0;
        while (text[i + j] != '\0' && keyword[j] != '\0'
               && lowercase(text[i + j]) == lowercase(keyword[j])) {
            j++;
        }
        if (keyword[j] == '\0') {
            return true;
        }
    }
    return keyword[0] == '\0';
}
