#ifndef BORROW_RECORD_H
#define BORROW_RECORD_H
#include <string>

class BorrowRecord {
private:
    std::string barcode;     // 条码
    std::string date;        // 借书日期

public:
    BorrowRecord(const std::string& code, const std::string& d);
    void show() const;
};

#endif
