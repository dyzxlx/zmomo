#ifndef ELECTRONIC_RESOURCE_H
#define ELECTRONIC_RESOURCE_H
#include <string>
#include <fstream>
#include "Resource.h"
// 派生类：电子资源
class ElectronicResource : public Resource {
private:
    std::string format;  // 文件格式
    std::string url;     // 下载链接
public:
    ElectronicResource(const std::string& code, const std::string& n, int c,
                       const std::string& f, const std::string& u);
    void display() const;   // 多态：重写基类纯虚函数
    void saveToFile(std::ofstream& out) const;  // 实验六：写文件
};

#endif
