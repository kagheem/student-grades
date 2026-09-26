#include "Person.h"
#include <iomanip>
Person::Person() {
    name = "";
    surname = "";
    for (int i = 0; i < NUM_HW; i++) {
        homework[i] = 0.0;
    }
    exam = 0.0;
    finalGrade = 0.0;
}

Person::Person(const Person& other) {
    name = other.name;
    surname = other.surname;
    for (int i = 0; i < NUM_HW; i++) {
        homework[i] = other.homework[i];
    }
    exam = other.exam;
    finalGrade = other.finalGrade;
}

Person& Person::operator=(const Person& other) {
    if (this == &other) {
        return *this; // guard against "p = p;"
    }
    name = other.name;
    surname = other.surname;
    for (int i = 0; i < NUM_HW; i++) {
        homework[i] = other.homework[i];
    }
    exam = other.exam;
    finalGrade = other.finalGrade;
    return *this;
}

Person::~Person() {
    // nothing to manually free — no raw pointers used
}

std::istream& operator>>(std::istream& in, Person& p) {
    std::cout << "Enter first name: ";
    in >> p.name;
    std::cout << "Enter surname: ";
    in >> p.surname;
    for (int i = 0; i < NUM_HW; i++) {
        std::cout << "Enter homework " << (i + 1) << " score: ";
        in >> p.homework[i];
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
void Person::calculateFinalGrade() {
    double sum = 0.0;
    for (int i = 0; i < NUM_HW; i++) {
        sum += homework[i];
    }
    double average = sum / NUM_HW;
    finalGrade = 0.4 * average + 0.6 * exam;
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