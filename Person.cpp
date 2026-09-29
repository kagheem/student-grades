#include "Person.h"
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>

Person::Person() {
    name = "";
    surname = "";
    exam = 0.0;
    finalGrade = 0.0;
    finalGradeAvg = 0.0;
    finalGradeMed = 0.0;
}

Person::Person(const Person& other) {
    finalGradeAvg = other.finalGradeAvg;
    finalGradeMed = other.finalGradeMed;
    name = other.name;
    surname = other.surname;
    homework = other.homework;
    exam = other.exam;
    finalGrade = other.finalGrade;
}


Person& Person::operator=(const Person& other) {
    finalGradeAvg = other.finalGradeAvg;
    finalGradeMed = other.finalGradeMed;
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
void Person::generateRandomScores(int numHomework) {
    homework.clear();
    for (int i = 0; i < numHomework; i++) {
        homework.push_back(rand() % 11); // random score 0–10
    }
    exam = rand() % 11;
}
void Person::setNameSurname(const std::string& n, const std::string& s) {
    name = n;
    surname = s;
}

bool Person::readFromLine(std::istream& in, int numHomework) {
    if (!(in >> name >> surname)) {
        return false; // end of file or bad read
    }

    homework.clear();
    for (int i = 0; i < numHomework; i++) {
        double score;
        in >> score;
        homework.push_back(score);
    }

    in >> exam;
    return true;
}
void Person::calculateBothGrades() {
    double sum = 0.0;
    for (double score : homework) {
        sum += score;
    }
    double average = sum / homework.size();

    std::vector<double> sorted = homework;
    std::sort(sorted.begin(), sorted.end());
    size_t mid = sorted.size() / 2;
    double median;
    if (sorted.size() % 2 == 0) {
        median = (sorted[mid - 1] + sorted[mid]) / 2.0;
    } else {
        median = sorted[mid];
    }

    finalGradeAvg = 0.4 * average + 0.6 * exam;
    finalGradeMed = 0.4 * median + 0.6 * exam;
}

double Person::getFinalGradeAvg() const {
    return finalGradeAvg;
}

double Person::getFinalGradeMed() const {
    return finalGradeMed;
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