#include "Person.h"

int main() {
    Person p1;
    std::cin >> p1;
    p1.calculateFinalGrade();
    std::cout << p1 << std::endl;

    return 0;
}