#include "Person.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

int main() {
    std::ifstream file("Students.txt");
    if (!file) {
        std::cout << "Could not open Students.txt" << std::endl;
        return 1;
    }

    // Skip the header line
    std::string headerLine;
    std::getline(file, headerLine);

    const int NUM_HOMEWORK = 5; // matches the 5 HW columns in Students.txt

    std::vector<Person> students;
    Person temp;
    while (temp.readFromLine(file, NUM_HOMEWORK)) {
        temp.calculateBothGrades();
        students.push_back(temp);
    }

    // Sort by surname (then name) alphabetically
    std::sort(students.begin(), students.end(), [](const Person& a, const Person& b) {
        if (a.getSurname() != b.getSurname()) {
            return a.getSurname() < b.getSurname();
        }
        return a.getName() < b.getName();
    });

    std::cout << std::left
               << std::setw(12) << "Name"
               << std::setw(12) << "Surname"
               << std::setw(14) << "Final (Avg.)"
               << "Final (Med.)" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;

    std::cout << std::fixed << std::setprecision(2);
    for (const Person& p : students) {
        std::cout << std::left
                   << std::setw(12) << p.getName()
                   << std::setw(12) << p.getSurname()
                   << std::setw(14) << p.getFinalGradeAvg()
                   << p.getFinalGradeMed() << std::endl;
    }

    return 0;
}