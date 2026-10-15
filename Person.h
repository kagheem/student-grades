#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
#include <iostream>

class Person {
private:
    std::string name;
    std::string surname;
    std::vector<double> homework;
    double exam;
    double finalGrade;
    double finalGradeAvg;
    double finalGradeMed;

public:
    Person();
    Person(const Person& other);
    Person& operator=(const Person& other);
    ~Person();

    friend std::istream& operator>>(std::istream& in, Person& p);
    friend std::ostream& operator<<(std::ostream& out, const Person& p);

    void calculateFinalGrade(bool useMedian);
    void generateRandomScores(int numHomework);
    void setNameSurname(const std::string& n, const std::string& s);
    bool readFromLine(std::istream& in, int numHomework);
    void calculateBothGrades();

    std::string getName() const;
    std::string getSurname() const;
    double getFinalGrade() const;
    double getFinalGradeAvg() const;
    double getFinalGradeMed() const;
};

#endif