#ifndef MAGAZINE_H
#define MAGAZINE_H
#include <string>
#include <fstream>
#include "Resource.h"
// 派生类：杂志
class Magazine : public Resource {
private:
    std::string issn;    // 期刊号
    std::string period;  // 发行周期
public:
    Magazine(const std::string& code, const std::string& n, int c,
             const std::string& i, const std::string& p);
    void display() const;   // 多态：重写基类纯虚函数
    void saveToFile(std::ofstream& out) const;  // 实验六：写文件
};

#endif
