#include "Person.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // seed random generator once

    std::string name, surname;
    std::cout << "Enter first name: ";
    std::cin >> name;
    std::cout << "Enter surname: ";
    std::cin >> surname;

    int numHomework;
    std::cout << "How many homework scores? ";
    std::cin >> numHomework;

    Person p1;
    p1.setNameSurname(name, surname);
    p1.generateRandomScores(numHomework);

    char choice;
    std::cout << "Use median instead of average? (y/n): ";
    std::cin >> choice;
    bool useMedian = (choice == 'y' || choice == 'Y');

    p1.calculateFinalGrade(useMedian);
    std::cout << p1 << std::endl;

    return 0;
}