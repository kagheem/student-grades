#ifndef GRADESPLITTER_H
#define GRADESPLITTER_H

#include "Person.h"
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <stdexcept>

class GradeSplitter {
private:
    typedef std::chrono::high_resolution_clock Clock;

    static double elapsedMs(Clock::time_point a, Clock::time_point b) {
        return std::chrono::duration<double, std::milli>(b - a).count();
    }

    // "Resize to a smaller size". vector and deque can shrink; list has nothing to shrink.
    template <typename T>
    static void shrink(T&) {}

    template <typename T>
    static void shrink(std::vector<T>& c) { c.shrink_to_fit(); }

    template <typename T>
    static void shrink(std::deque<T>& c) { c.shrink_to_fit(); }

    template <typename Container>
    static void writeStudents(const std::string& filename, const Container& students) {
        std::ofstream out(filename);
        if (!out) {
            throw std::runtime_error("Could not create file: " + filename);
        }
        for (const Person& p : students) {
            out << p.getName() << " " << p.getSurname() << " " << p.getFinalGradeAvg() << "\n";
        }
    }

public:
    // containerName: only used for printing and output file names
    // strategy 1: copy students into two NEW containers (passed and failed)
    // strategy 2: copy only failed students into ONE new container and remove them from the original
    template <typename Container>
    static void run(const std::string& containerName, const std::string& filename,
                    int numHomework, int strategy) {
        auto startTotal = Clock::now();
        Container students;

        // ---- Read ----
        auto t0 = Clock::now();
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("Could not open " + filename);
        }
        std::string headerLine;
        std::getline(file, headerLine);
        Person temp;
        while (temp.readFromLine(file, numHomework)) {
            students.push_back(temp);
        }
        file.close();
        auto t1 = Clock::now();

        // ---- Calculate grades ----
        for (Person& p : students) {
            p.calculateBothGrades();
        }
        auto t2 = Clock::now();

        size_t total = students.size();

        // ---- Split ----
        Container passed;
        Container failed;
        if (strategy == 1) {
            for (const Person& p : students) {
                if (p.getFinalGradeAvg() >= 5.0) {
                    passed.push_back(p);
                } else {
                    failed.push_back(p);
                }
            }
        } else {
            for (auto it = students.begin(); it != students.end(); ) {
                if (it->getFinalGradeAvg() < 5.0) {
                    failed.push_back(*it);
                    it = students.erase(it);   // erase returns the next element
                } else {
                    ++it;
                }
            }
            shrink(students);
        }
        auto t3 = Clock::now();

        // ---- Write ----
        // Strategy 1: "passed" is its own container. Strategy 2: the original now holds only passed students.
        const Container& passedRef = (strategy == 1) ? passed : students;
        writeStudents("passed_s" + std::to_string(strategy) + "_" + containerName + "_" + filename, passedRef);
        writeStudents("failed_s" + std::to_string(strategy) + "_" + containerName + "_" + filename, failed);
        auto t4 = Clock::now();

        std::cout << "[" << containerName << " | Strategy " << strategy << "] "
                  << filename << " (" << total << " records)" << std::endl;
        std::cout << "  Read time:   " << elapsedMs(t0, t1) << " ms" << std::endl;
        std::cout << "  Calc time:   " << elapsedMs(t1, t2) << " ms" << std::endl;
        std::cout << "  Split time:  " << elapsedMs(t2, t3) << " ms" << std::endl;
        std::cout << "  Write time:  " << elapsedMs(t3, t4) << " ms" << std::endl;
        std::cout << "  Total time:  " << elapsedMs(startTotal, t4) << " ms" << std::endl;
        std::cout << "  Passed: " << passedRef.size() << ", Failed: " << failed.size() << std::endl;
        std::cout << std::endl;
    }
};

#endif