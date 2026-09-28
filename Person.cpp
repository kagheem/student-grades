#include "Person.h"
#include <iomanip>
#include <algorithm>

Person::Person() {
    name = "";
    surname = "";
    exam = 0.0;
    finalGrade = 0.0;
}

Person::Person(const Person& other) {
    name = other.name;
    surname = other.surname;
    homework = other.homework;
    exam = other.exam;
    finalGrade = other.finalGrade;
}

Person& Person::operator=(const Person& other) {
    if (this == &other) {
        return *this;
    }
    name = other.name;
    surname = other.surname;
    homework = other.homework;
    exam = other.exam;
    finalGrade = other.finalGrade;
    return *this;
}

Person::~Person() {
    // nothing to manually free — std::vector cleans up after itself
}

std::istream& operator>>(std::istream& in, Person& p) {
    std::cout << "Enter first name: ";
    in >> p.name;
    std::cout << "Enter surname: ";
    in >> p.surname;

    int n;
    std::cout << "How many homework scores? ";
    in >> n;

    p.homework.clear();
    for (int i = 0; i < n; i++) {
        double score;
        std::cout << "Enter homework " << (i + 1) << " score: ";
        in >> score;
        p.homework.push_back(score);
    }

    std::cout << "Enter exam score: ";
    in >> p.exam;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Person& p) {
    out << p.name << " " << p.surname << " -> Final grade: "
        << std::fixed << std::setprecision(2) << p.finalGrade;
    return out;
}

void Person::calculateFinalGrade(bool useMedian) {
    double homeworkScore = 0.0;

    if (!useMedian) {
        double sum = 0.0;
        for (double score : homework) {
            sum += score;
        }
        homeworkScore = sum / homework.size();
    } else {
        std::vector<double> sorted = homework;
        std::sort(sorted.begin(), sorted.end());
        size_t mid = sorted.size() / 2;
        if (sorted.size() % 2 == 0) {
            homeworkScore = (sorted[mid - 1] + sorted[mid]) / 2.0;
        } else {
            homeworkScore = sorted[mid];
        }
    }

    finalGrade = 0.4 * homeworkScore + 0.6 * exam;
}

std::string Person::getName() const {
    return name;
}

std::string Person::getSurname() const {
    return surname;
}

double Person::getFinalGrade() const {
    return finalGrade;
}