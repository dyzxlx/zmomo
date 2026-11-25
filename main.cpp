#include "LibraryManager.h"
int main() {
     LibraryManager mgr;   // 构造时初始化资源货架与学生
    mgr.run();            // 菜单主循环，退出时析构自动释放全部资源
    return 0;
}