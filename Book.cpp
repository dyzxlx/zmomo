#include "Book.h"
#include <iostream>

// 构造顺序：先执行基类 Resource 构造函数，再初始化本类特有成员
Book::Book(const std::string& code, const std::string& n, int c,
           const std::string& a, const std::string& pub, const std::string& i)
    : Resource(code, n, c, 1), author(a), publisher(pub), isbn(i) {}

// 多态：重写基类纯虚函数，复用公共输出后追加图书特有信息

void Book::display() const {
     std::cout << "[图书]";
    printCommon();
    std::cout << " - " << author << " / " << publisher
              << " / ISBN:" << isbn << std::endl;
}

// 实验六：类型标记 B，字段用 | 分隔，一行一个对象
void Book::saveToFile(std::ofstream& out) const {
    out << "B|" << barcode << "|" << name << "|" << count << "|"
        << author << "|" << publisher << "|" << isbn << "\n";
}
