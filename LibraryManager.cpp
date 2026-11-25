#include "LibraryManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

// 实验六：数据文件路径（相对项目根目录，编译任务的 cwd 即工作区根目录）
static const char* const RES_FILE = "data/resources.txt";
static const char* const STU_FILE = "data/student.txt";

// 多态：基类指针调用纯虚函数 display()，按对象实际类型差异化输出
void LibraryManager::showOne(Resource* r) const {
    r->display();
}

// 实验五：函数模板 + begin()/end() 迭代器遍历，返回首个满足条件的元素
template <typename T, typename Pred>
static typename std::vector<T*>::iterator findIf(std::vector<T*>& v, Pred pred) {
    for (auto it = v.begin(); it != v.end(); ++it)
        if (pred(*it)) return it;
    return v.end();
}

std::vector<Resource*>::iterator LibraryManager::findResource(const std::string& code) {
    return findIf(shelf, [&code](Resource* r) { return r->getBarcode() == code; });
}

LibraryManager::LibraryManager() : stu("张三") {
    loadData();   // 实验六：启动时先恢复上次运行时保存的数据
}

LibraryManager::~LibraryManager() {
    // 实验五：begin()/end() 迭代器遍历释放
    for (auto it = shelf.begin(); it != shelf.end(); ++it)
        delete *it;
    shelf.clear();   // 实验五：清空容器回收资源
}

// 实验六：按行读取，首字段是类型标记，据此 new 出对应派生类对象
void LibraryManager::loadData() {
    std::ifstream fin(RES_FILE);
    std::string line;
    while (std::getline(fin, line)) {
        if (line.empty()) continue;
        std::string field[7];
        int n = 0;
        std::stringstream ss(line);
        while (n < 7 && std::getline(ss, field[n], '|')) ++n;
        if (n < 4) continue;                       // 字段不足，跳过坏行
        int c = std::atoi(field[3].c_str());
        // 实验五：emplace_back 把新对象放入 vector 末尾
        if (field[0] == "B" && n == 7)
            shelf.emplace_back(new Book(field[1], field[2], c, field[4], field[5], field[6]));
        else if (field[0] == "M" && n == 6)
            shelf.emplace_back(new Magazine(field[1], field[2], c, field[4], field[5]));
        else if (field[0] == "E" && n == 6)
            shelf.emplace_back(new ElectronicResource(field[1], field[2], c, field[4], field[5]));
    }
    // 首次运行（数据文件尚未生成）：装载演示资源
    if (!fin.is_open()) {
        shelf.emplace_back(new Book("B001", "C++Primer", 3, "Lippman", "电子工业出版社", "9787121400001"));
        shelf.emplace_back(new Magazine("M001", "环球科学", 5, "ISSN-1673", "月刊"));
        shelf.emplace_back(new ElectronicResource("E001", "算法导论讲义", 2, "PDF", "http://lib.example.com/a.pdf"));
    }
    // 恢复学生信息与已借条码，保证重启后归还操作仍然有效
    std::ifstream sin(STU_FILE);
    if (sin.is_open()) stu.loadFromFile(sin);
}

// 实验六：把货架上每个对象（含派生类特有字段）与学生的借阅状态写入文件
void LibraryManager::saveData() const {
    std::ofstream fout(RES_FILE);
    if (!fout) {
        std::cout << "  → 警告：无法写入 " << RES_FILE << "（请确认 data 目录存在）\n";
        return;
    }
    for (size_t i = 0; i < shelf.size(); ++i)
        shelf[i]->saveToFile(fout);
    fout.close();

    std::ofstream sout(STU_FILE);
    if (sout) stu.saveToFile(sout);
    std::cout << "  → 数据已保存到 data/resources.txt 与 data/student.txt\n";
}

void LibraryManager::addResource() {
    int type = 0, c = 0;
    std::string code, name;
    std::cout << "类型(1图书 2杂志 3电子资源): ";
    std::cin >> type;
    std::cout << "条码 名称 数量: ";
    std::cin >> code >> name >> c;
    // 实验五：新增对象用 push_back 放入 vector 末尾
    if (type == 1) {
        std::string a, pub, isbn;
        std::cout << "作者 出版社 ISBN: ";
        std::cin >> a >> pub >> isbn;
        shelf.push_back(new Book(code, name, c, a, pub, isbn));
    }
    else if (type == 2) {
        std::string issn, per;
        std::cout << "期刊号 发行周期: ";
        std::cin >> issn >> per;
        shelf.push_back(new Magazine(code, name, c, issn, per));
    }
    else {
        std::string fmt, url;
        std::cout << "格式 下载链接: ";
        std::cin >> fmt >> url;
        shelf.push_back(new ElectronicResource(code, name, c, fmt, url));
    }
    std::cout << "  → 新增成功！当前资源数:" << shelf.size() << std::endl;
}

void LibraryManager::changeCount(bool add) {
    std::string code;
    int n = 0;
    std::cout << "条码 数量: ";
    std::cin >> code >> n;
    std::vector<Resource*>::iterator it = findResource(code);
    if (it == shelf.end()) { std::cout << "  → 未找到该条码\n";  return; }
    bool ok = add ? (*it)->addCount(n) : (*it)->reduceCount(n);
    std::cout << (ok ? "  → 操作成功，当前数量:" : "  → 操作失败，当前数量:")
              << (*it)->getCount() << std::endl;
}

void LibraryManager::removeResource() {
    std::string code;
    std::cout << "条码: ";
    std::cin >> code;
    std::vector<Resource*>::iterator it = findResource(code);
    if (it == shelf.end()) { std::cout << "  → 未找到该条码\n"; return; }
    delete *it;      // new/delete 配对释放
    shelf.erase(it); // 实验五：erase 删除迭代器指向的元素
    std::cout << "  → 删除成功\n";
}

void LibraryManager::showOneRes() {
    std::string code;
    std::cout << "条码: ";
    std::cin >> code;
    std::vector<Resource*>::iterator it = findResource(code);
    if (it == shelf.end()) { std::cout << "  → 未找到该条码\n"; return; }
    showOne(*it);
}

void LibraryManager::showAll() const {
    std::cout << "--- 全部资源 ---\n";
    // 实验五：迭代器遍历 vector
    for (auto it = shelf.begin(); it != shelf.end(); ++it)
        showOne(*it);
}

void LibraryManager::borrowOrReturn(bool isBorrow) {
    std::string code;
    std::cout << "条码: ";
    std::cin >> code;
    std::vector<Resource*>::iterator it = findResource(code);
    if (it == shelf.end()) { std::cout << "  → 未找到该条码\n"; return; }
    if (isBorrow) stu.borrowBook(**it);
    else stu.returnBook(**it);
}

void LibraryManager::run() {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n===== 图书资源借阅管理 =====\n" << " 1.增加新资源  2.增加数量  3.减少数量\n" << " 4.删除资源    5.显示某资源 6.显示全部资源\n" << " 7.学生借阅    8.学生归还   0.退出\n" << "请选择: ";
        std::cin >> choice; if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            std::cout << "  → 请输入数字选项\n"; continue;
        }
        switch (choice) {
            case 1: addResource(); break;
            case 2: changeCount(true); break;
            case 3: changeCount(false); break;
            case 4: removeResource(); break;
            case 5: showOneRes(); break;
            case 6: showAll(); break;
            case 7: borrowOrReturn(true); break;
            case 8: borrowOrReturn(false); break;
            case 0:
                saveData();   // 实验六：程序关闭前保存所有对象数据
                std::cout << "已退出，资源已全部释放\n";
                break;
            default: std::cout << "  → 无效选项\n";
        }
    }
}
