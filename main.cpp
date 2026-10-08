#include <iostream>
#include "Book.h"
#include "Student.h"

int main() {
    Book b1("B001", "C++ Primer");
    Book b2("B002", "Effective C++");

    b1.display();
    b2.display();

    Student stu("张三");

    std::cout << "\n--- 借书测试 ---\n";
    stu.borrowBook(b1);        // 成功
    stu.borrowBook(b1);        // 失败：已借出
    stu.borrowBook(b2);        // 成功

    std::cout << "\n--- 当前状态 ---\n";
    b1.display();
    b2.display();
    stu.showRecords();

    std::cout << "\n--- 还书测试 ---\n";
    stu.returnBook(b1);        // 成功
    b1.display();

    return 0;
}
