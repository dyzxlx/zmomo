#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <fstream>
#include "Resource.h"
// 派生类：一般图书 is-a Resource（公有继承）
class Book : public Resource {
private:
    std::string author;      // 图书特有：作者
    std::string publisher;   // 出版社
    std::string isbn;        // ISBN


public:
     Book(const std::string& code, const std::string& n, int c,
         const std::string& a, const std::string& pub, const std::string& i);
    void display() const;    // 多态：重写基类纯虚函数，差异化显示
    void saveToFile(std::ofstream& out) const;  // 实验六：写文件
};

#endif
