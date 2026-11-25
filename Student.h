#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <vector>
#include <fstream>
#include "Resource.h"
#include "BorrowRecord.h"

class Student {
private:
    std::string name;
    std::vector<std::string> borrowedCodes;     // 已借条码列表
    std::vector<BorrowRecord> records;           // 组合：has-a

public:
    Student(const std::string& n);
    bool borrowBook(Resource& res);              // 依赖：基类引用可接收任意派生类
    bool returnBook(Resource& res);
    void showRecords() const;
    void saveToFile(std::ofstream& out) const;   // 实验六：保存姓名与已借条码
    void loadFromFile(std::ifstream& in);        // 实验六：从文件恢复借阅状态
};

#endif
