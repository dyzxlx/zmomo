#include "Resource.h"
#include <iostream>
Resource::Resource(const std::string& code, const std::string& n, int c, int t)
    : barcode(code), name(n), count(c), type(t) {}

Resource::~Resource() {}
std::string Resource::getBarcode() const { return barcode; }
std::string Resource::getName() const { return name; }
int Resource::getCount() const { return count; }
int Resource::getType() const { return type; }
bool Resource::addCount(int n) {
    if (n <= 0) return false;
    count += n;
    return true;
}
bool Resource::reduceCount(int n) {
    if (n <= 0 || n > count) return false;
    count -= n;
    return true;
}
bool Resource::borrow() {
    if (count <= 0) return false;
    --count;
    return true;
}
bool Resource::returnItem() {
    ++count;
    return true;
}
// 公共信息输出：子类 display() 先调用它，再追加各自特有字段（纯虚函数无法再被直接调用）
void Resource::printCommon() const {
    std::cout << "[" << barcode << "] " << name << " - 馆藏:" << count;
}
