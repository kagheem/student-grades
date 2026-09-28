#include "Person.h"
#include <iostream>

int main() {
    Person p1;
    std::cin >> p1;

    char choice;
    std::cout << "Use median instead of average? (y/n): ";
    std::cin >> choice;
    bool useMedian = (choice == 'y' || choice == 'Y');

    p1.calculateFinalGrade(useMedian);
    std::cout << p1 << std::endl;

    return 0;
}