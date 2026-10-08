#include "BorrowRecord.h"
#include <iostream>

BorrowRecord::BorrowRecord(const std::string& code, const std::string& d)
    : barcode(code), date(d) {}

void BorrowRecord::show() const {
    std::cout << "  条码:" << barcode << " 借出日期:" << date << std::endl;
}
