#include "Student.h"
#include <iostream>

Student::Student(const std::string& n) : name(n) {}

// 依赖关系：Student 依赖 Book，通过引用传递修改 Book 状态
bool Student::borrowBook(Book& book) {
    if (!book.isAvailable()) {
        std::cout << "  → 失败：书已借出\n";
        return false;
    }
    book.borrow();                              // 修改 Book 状态
    borrowedCodes.push_back(book.getBarcode());
    records.push_back(BorrowRecord(book.getBarcode(), "2026-10-05")); // 组合
    std::cout << "  → 成功借书！\n";
    return true;
}

bool Student::returnBook(Book& book) {
    if (book.isAvailable()) {
        std::cout << "  → 失败：书本来就在馆\n";
        return false;
    }
    book.returnBook();
    std::cout << "  → 归还成功！\n";
    return true;
}

void Student::showRecords() const {
    std::cout << name << " 的借阅记录：\n";
    for (const auto& r : records) {
        r.show();
    }
}
