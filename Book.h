#ifndef BOOK_H
#define BOOK_H
#include <string>

class Book {
private:
    std::string barcode;
    std::string title;
    bool available;          // true=在馆 false=借出

public:
    Book(const std::string& code, const std::string& name);
    bool borrow();           // 借出
    bool returnBook();       // 归还
    bool isAvailable() const;
    std::string getBarcode() const;
    void display() const;
};

#endif
