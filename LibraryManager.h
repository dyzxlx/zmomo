#ifndef LIBRARY_MANAGER_H
#define LIBRARY_MANAGER_H
#include <vector>
#include <string>
#include "Resource.h"
#include "Book.h"
#include "Magazine.h"
#include "ElectronicResource.h"
#include "Student.h"
// 管理类：封装资源货架与学生借阅业务，对外只暴露菜单主循环 run()
class LibraryManager {
    private:
    std::vector<Resource*> shelf; // 基类指针容器：统一管理三种派生类对象
    Student stu; // 组合：借阅业务由 Student 承担
    std::vector<Resource*>::iterator findResource(const std::string& code); // 实验五：迭代器按条码查找
    void showOne(Resource* r) const;
    void addResource(); // 1.增加新资源
    void changeCount(bool add); // 2/3.增加或减少数量
    void removeResource(); // 4.删除资源
    void showOneRes(); // 5.显示某资源
    void showAll() const; // 6.显示全部资源
    void borrowOrReturn(bool isBorrow); // 7/8.借阅或归还
    void loadData(); // 实验六：启动时从文件恢复资源与学生借阅状态
    void saveData() const; // 实验六：关闭时把对象数据写入文件
    public:
      LibraryManager();
    ~LibraryManager(); // 析构：释放所有 new 出来的资源对象
    void run(); // 菜单主循环
    };
     #endif
