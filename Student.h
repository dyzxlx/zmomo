#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <vector>
#include "Book.h"
#include "BorrowRecord.h"

class Student {
private:
    std::string name;
    std::vector<std::string> borrowedCodes;     // 已借条码列表
    std::vector<BorrowRecord> records;           // 组合：has-a

public:
    Student(const std::string& n);
    bool borrowBook(Book& book);                // 依赖：use-a（参数为引用）
    bool returnBook(Book& book);
    void showRecords() const;
};

#endif
