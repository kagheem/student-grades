#include "Person.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include "FileGenerator.h"
#include "GradeSplitter.h"

int main() {
    try {
        srand(static_cast<unsigned int>(time(nullptr)));

        FileGenerator::generateFile("students_1000.txt", 1000, 5);
        FileGenerator::generateFile("students_10000.txt", 10000, 5);
        FileGenerator::generateFile("students_100000.txt", 100000, 5);
        FileGenerator::generateFile("students_1000000.txt", 1000000, 5);
        FileGenerator::generateFile("students_10000000.txt", 10000000, 5);

        GradeSplitter::processFile("students_1000.txt", 5);
        GradeSplitter::processFile("students_10000.txt", 5);
        GradeSplitter::processFile("students_100000.txt", 5);
        GradeSplitter::processFile("students_1000000.txt", 5);
        GradeSplitter::processFile("students_10000000.txt", 5);

        GradeSplitter::processFileList("students_1000.txt", 5);
        GradeSplitter::processFileList("students_10000.txt", 5);
        GradeSplitter::processFileList("students_100000.txt", 5);
        GradeSplitter::processFileList("students_1000000.txt", 5);
        GradeSplitter::processFileList("students_10000000.txt", 5);

        GradeSplitter::processFileDeque("students_1000.txt", 5);
        GradeSplitter::processFileDeque("students_10000.txt", 5);
        GradeSplitter::processFileDeque("students_100000.txt", 5);
        GradeSplitter::processFileDeque("students_1000000.txt", 5);
        GradeSplitter::processFileDeque("students_10000000.txt", 5);

        std::ifstream file("Students.txt");
        if (!file) {
            throw std::runtime_error("Could not open Students.txt");
        }

        std::string headerLine;
        std::getline(file, headerLine);

        const int NUM_HOMEWORK = 5;

        std::vector<Person> students;
        Person temp;
        while (temp.readFromLine(file, NUM_HOMEWORK)) {
            temp.calculateBothGrades();
            students.push_back(temp);
        }

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

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}