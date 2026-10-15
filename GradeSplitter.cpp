#include "GradeSplitter.h"
#include "Person.h"
#include <fstream>
#include <vector>
#include <list>
#include <deque>
#include <stdexcept>
#include <chrono>
#include <iostream>

void GradeSplitter::processFile(const std::string& inputFilename, int numHomework) {
    auto startTotal = std::chrono::high_resolution_clock::now();

    auto startRead = std::chrono::high_resolution_clock::now();
    std::ifstream file(inputFilename);
    if (!file) {
        throw std::runtime_error("Could not open " + inputFilename);
    }
    std::string headerLine;
    std::getline(file, headerLine);

    std::vector<Person> students;
    Person temp;
    while (temp.readFromLine(file, numHomework)) {
        students.push_back(temp);
    }
    file.close();
    auto endRead = std::chrono::high_resolution_clock::now();

    auto startCalc = std::chrono::high_resolution_clock::now();
    for (Person& p : students) {
        p.calculateBothGrades();
    }
    auto endCalc = std::chrono::high_resolution_clock::now();

    auto startSplit = std::chrono::high_resolution_clock::now();
    std::vector<Person> passed;
    std::vector<Person> failed;
    for (const Person& p : students) {
        if (p.getFinalGradeAvg() >= 5.0) {
            passed.push_back(p);
        } else {
            failed.push_back(p);
        }
    }
    auto endSplit = std::chrono::high_resolution_clock::now();

    auto startWrite = std::chrono::high_resolution_clock::now();
    std::ofstream passFile("passed_" + inputFilename);
    std::ofstream failFile("failed_" + inputFilename);
    if (!passFile || !failFile) {
        throw std::runtime_error("Could not create output files for " + inputFilename);
    }
    for (const Person& p : passed) {
        passFile << p.getName() << " " << p.getSurname() << " " << p.getFinalGradeAvg() << std::endl;
    }
    for (const Person& p : failed) {
        failFile << p.getName() << " " << p.getSurname() << " " << p.getFinalGradeAvg() << std::endl;
    }
    auto endWrite = std::chrono::high_resolution_clock::now();
    auto endTotal = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> readTime = endRead - startRead;
    std::chrono::duration<double, std::milli> calcTime = endCalc - startCalc;
    std::chrono::duration<double, std::milli> splitTime = endSplit - startSplit;
    std::chrono::duration<double, std::milli> writeTime = endWrite - startWrite;
    std::chrono::duration<double, std::milli> totalTime = endTotal - startTotal;

    std::cout << "[std::vector] File: " << inputFilename << " (" << students.size() << " records)" << std::endl;
    std::cout << "  Read time:   " << readTime.count() << " ms" << std::endl;
    std::cout << "  Calc time:   " << calcTime.count() << " ms" << std::endl;
    std::cout << "  Split time:  " << splitTime.count() << " ms" << std::endl;
    std::cout << "  Write time:  " << writeTime.count() << " ms" << std::endl;
    std::cout << "  Total time:  " << totalTime.count() << " ms" << std::endl;
    std::cout << "  Passed: " << passed.size() << ", Failed: " << failed.size() << std::endl;
    std::cout << std::endl;
}

void GradeSplitter::processFileList(const std::string& inputFilename, int numHomework) {
    auto startTotal = std::chrono::high_resolution_clock::now();

    auto startRead = std::chrono::high_resolution_clock::now();
    std::ifstream file(inputFilename);
    if (!file) {
        throw std::runtime_error("Could not open " + inputFilename);
    }
    std::string headerLine;
    std::getline(file, headerLine);

    std::list<Person> students;
    Person temp;
    while (temp.readFromLine(file, numHomework)) {
        students.push_back(temp);
    }
    file.close();
    auto endRead = std::chrono::high_resolution_clock::now();

    auto startCalc = std::chrono::high_resolution_clock::now();
    for (Person& p : students) {
        p.calculateBothGrades();
    }
    auto endCalc = std::chrono::high_resolution_clock::now();

    auto startSplit = std::chrono::high_resolution_clock::now();
    std::list<Person> passed;
    std::list<Person> failed;
    for (const Person& p : students) {
        if (p.getFinalGradeAvg() >= 5.0) {
            passed.push_back(p);
        } else {
            failed.push_back(p);
        }
    }
    auto endSplit = std::chrono::high_resolution_clock::now();

    auto startWrite = std::chrono::high_resolution_clock::now();
    std::ofstream passFile("passed_list_" + inputFilename);
    std::ofstream failFile("failed_list_" + inputFilename);
    if (!passFile || !failFile) {
        throw std::runtime_error("Could not create output files for " + inputFilename);
    }
    for (const Person& p : passed) {
        passFile << p.getName() << " " << p.getSurname() << " " << p.getFinalGradeAvg() << std::endl;
    }
    for (const Person& p : failed) {
        failFile << p.getName() << " " << p.getSurname() << " " << p.getFinalGradeAvg() << std::endl;
    }
    auto endWrite = std::chrono::high_resolution_clock::now();
    auto endTotal = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> readTime = endRead - startRead;
    std::chrono::duration<double, std::milli> calcTime = endCalc - startCalc;
    std::chrono::duration<double, std::milli> splitTime = endSplit - startSplit;
    std::chrono::duration<double, std::milli> writeTime = endWrite - startWrite;
    std::chrono::duration<double, std::milli> totalTime = endTotal - startTotal;

    std::cout << "[std::list] File: " << inputFilename << " (" << students.size() << " records)" << std::endl;
    std::cout << "  Read time:   " << readTime.count() << " ms" << std::endl;
    std::cout << "  Calc time:   " << calcTime.count() << " ms" << std::endl;
    std::cout << "  Split time:  " << splitTime.count() << " ms" << std::endl;
    std::cout << "  Write time:  " << writeTime.count() << " ms" << std::endl;
    std::cout << "  Total time:  " << totalTime.count() << " ms" << std::endl;
    std::cout << "  Passed: " << passed.size() << ", Failed: " << failed.size() << std::endl;
    std::cout << std::endl;
}

void GradeSplitter::processFileDeque(const std::string& inputFilename, int numHomework) {
    auto startTotal = std::chrono::high_resolution_clock::now();

    auto startRead = std::chrono::high_resolution_clock::now();
    std::ifstream file(inputFilename);
    if (!file) {
        throw std::runtime_error("Could not open " + inputFilename);
    }
    std::string headerLine;
    std::getline(file, headerLine);

    std::deque<Person> students;
    Person temp;
    while (temp.readFromLine(file, numHomework)) {
        students.push_back(temp);
    }
    file.close();
    auto endRead = std::chrono::high_resolution_clock::now();

    auto startCalc = std::chrono::high_resolution_clock::now();
    for (Person& p : students) {
        p.calculateBothGrades();
    }
    auto endCalc = std::chrono::high_resolution_clock::now();

    auto startSplit = std::chrono::high_resolution_clock::now();
    std::deque<Person> passed;
    std::deque<Person> failed;
    for (const Person& p : students) {
        if (p.getFinalGradeAvg() >= 5.0) {
            passed.push_back(p);
        } else {
            failed.push_back(p);
        }
    }
    auto endSplit = std::chrono::high_resolution_clock::now();

    auto startWrite = std::chrono::high_resolution_clock::now();
    std::ofstream passFile("passed_deque_" + inputFilename);
    std::ofstream failFile("failed_deque_" + inputFilename);
    if (!passFile || !failFile) {
        throw std::runtime_error("Could not create output files for " + inputFilename);
    }
    for (const Person& p : passed) {
        passFile << p.getName() << " " << p.getSurname() << " " << p.getFinalGradeAvg() << std::endl;
    }
    for (const Person& p : failed) {
        failFile << p.getName() << " " << p.getSurname() << " " << p.getFinalGradeAvg() << std::endl;
    }
    auto endWrite = std::chrono::high_resolution_clock::now();
    auto endTotal = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> readTime = endRead - startRead;
    std::chrono::duration<double, std::milli> calcTime = endCalc - startCalc;
    std::chrono::duration<double, std::milli> splitTime = endSplit - startSplit;
    std::chrono::duration<double, std::milli> writeTime = endWrite - startWrite;
    std::chrono::duration<double, std::milli> totalTime = endTotal - startTotal;

    std::cout << "[std::deque] File: " << inputFilename << " (" << students.size() << " records)" << std::endl;
    std::cout << "  Read time:   " << readTime.count() << " ms" << std::endl;
    std::cout << "  Calc time:   " << calcTime.count() << " ms" << std::endl;
    std::cout << "  Split time:  " << splitTime.count() << " ms" << std::endl;
    std::cout << "  Write time:  " << writeTime.count() << " ms" << std::endl;
    std::cout << "  Total time:  " << totalTime.count() << " ms" << std::endl;
    std::cout << "  Passed: " << passed.size() << ", Failed: " << failed.size() << std::endl;
    std::cout << std::endl;
}