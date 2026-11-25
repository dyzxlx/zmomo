#include "Magazine.h"
#include <iostream>

Magazine::Magazine(const std::string& code, const std::string& n, int c,
                   const std::string& i, const std::string& p)
    : Resource(code, n, c, 2), issn(i), period(p) {}

void Magazine::display() const {
    std::cout << "[杂志]";
    printCommon();
    std::cout << " - ISSN:" << issn << " / " << period << std::endl;
}

// 实验六：类型标记 M
void Magazine::saveToFile(std::ofstream& out) const {
    out << "M|" << barcode << "|" << name << "|" << count << "|"
        << issn << "|" << period << "\n";
}
