#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>
#include <fstream>   // 实验六：文件流持久化
// 基类：抽取三类资源的公共属性与操作
class Resource {
protected:
    std::string barcode;    // 条码号
    std::string name;       // 资源名称
    int count;              // 馆藏数量（>0 才可借）
    int type;               // 类型码：1图书 2杂志 3电子（供 main 区分派生类型）
    void printCommon() const;  // 输出公共信息（不换行，供各子类 display 复用）

public:
    Resource(const std::string& code, const std::string& n, int c, int t);
    virtual ~Resource();    // 虚析构：delete 基类指针时能正确析构派生类对象
    std::string getBarcode() const;
    std::string getName() const;
    int getCount() const;
    int getType() const;
    bool addCount(int n);   // 增加数量
    bool reduceCount(int n); // 减少数量
    bool borrow();          // 借出：数量-1
    bool returnItem();      // 归还：数量+1
    // 实验四：纯虚函数统一接口，Resource 成为抽象类，由各派生类给出差异化实现
    virtual void display() const = 0;
    // 实验六：由各派生类把自己的类型标记与成员数据写入文件
    virtual void saveToFile(std::ofstream& out) const = 0;
};

#endif
