#include "ElectronicResource.h"
#include <iostream>

ElectronicResource::ElectronicResource(const std::string& code, const std::string& n, int c,
                                       const std::string& f, const std::string& u)
    : Resource(code, n, c, 3), format(f), url(u) {}

void ElectronicResource::display() const {
    std::cout << "[电子]";
    printCommon();
    std::cout << " - " << format << " / " << url << std::endl;
}

// 实验六：类型标记 E
void ElectronicResource::saveToFile(std::ofstream& out) const {
    out << "E|" << barcode << "|" << name << "|" << count << "|"
        << format << "|" << url << "\n";
}
