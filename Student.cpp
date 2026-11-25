#include "Student.h"
#include <iostream>

Student::Student(const std::string& n) : name(n) {}

// 依赖关系：参数为基类 Resource 引用，可接收 Book/Magazine/ElectronicResource（类型兼容规则）
bool Student::borrowBook(Resource& res) {
    if (res.getCount() <= 0) {
        std::cout << "  → 失败：《" << res.getName() << "》无可借数量\n";
        return false;
    }
   res.borrow();                               // 数量-1
    borrowedCodes.push_back(res.getBarcode());
    records.push_back(BorrowRecord(res.getBarcode(), res.getName(), "2026-10-10")); // 组合
    std::cout << "  → 成功借阅《" << res.getName() << "》！\n";
    return true;
}

bool Student::returnBook(Resource& res) {
    size_t idx = borrowedCodes.size();
    for (size_t i = 0; i < borrowedCodes.size(); ++i) {
        if (borrowedCodes[i] == res.getBarcode()) { idx = i; break; }
    }
    if (idx == borrowedCodes.size()) {
        std::cout << "  → 失败：未借过《" << res.getName() << "》\n";
        return false;
    }
    borrowedCodes.erase(borrowedCodes.begin() + idx);
    res.returnItem();                           // 数量+1
    std::cout << "  → 归还《" << res.getName() << "》成功！\n";
    return true;
}

void Student::showRecords() const {
    std::cout << name << " 的借阅记录：\n";
    for (const auto& r : records) {
        r.show();
    }
}

// 实验六：第一行姓名，其后每行一个已借条码
void Student::saveToFile(std::ofstream& out) const {
    out << name << "\n";
    for (size_t i = 0; i < borrowedCodes.size(); ++i) {
        out << borrowedCodes[i] << "\n";
    }
}

// 实验六：从文件恢复姓名与已借条码（重启后可继续归还）
void Student::loadFromFile(std::ifstream& in) {
    std::string line;
    if (!std::getline(in, line) || line.empty()) return;
    name = line;
    borrowedCodes.clear();
    while (std::getline(in, line)) {
        if (!line.empty()) borrowedCodes.push_back(line);
    }
}
