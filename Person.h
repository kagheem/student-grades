#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

const int NUM_HW = 3; // fixed number of homework scores for now

class Person {
private:
    std::string name;
    std::string surname;
    double homework[NUM_HW];
    double exam;
    double finalGrade;

public:
    // Constructors, rule of three
    Person();                          // default constructor
    Person(const Person& other);       // copy constructor
    Person& operator=(const Person& other); // copy assignment
    ~Person();                         // destructor

    // Input/output
    friend std::istream& operator>>(std::istream& in, Person& p);
    friend std::ostream& operator<<(std::ostream& out, const Person& p);

    // Calculation
    void calculateFinalGrade(); // uses average of homework for now

    // Getters (needed to print/sort later)
    std::string getName() const;
    std::string getSurname() const;
    double getFinalGrade() const;
};

#endif