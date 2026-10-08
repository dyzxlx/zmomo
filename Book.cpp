#include "Book.h"
#include <iostream>

Book::Book(const std::string& code, const std::string& name)
    : barcode(code), title(name), available(true) {}

bool Book::borrow() {
    if (!available) return false;
    available = false;
    return true;
}

bool Book::returnBook() {
    if (available) return false;
    available = true;
    return true;
}

bool Book::isAvailable() const { return available; }

std::string Book::getBarcode() const { return barcode; }

void Book::display() const {
    std::cout << "[" << barcode << "] " << title
              << " - " << (available ? "在馆" : "已借出") << std::endl;
}
