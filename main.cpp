#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include "FileGenerator.h"
#include "GradeSplitter.h"

bool fileExists(const std::string& name) {
    std::ifstream f(name);
    return f.good();
}

void runStrategy(int container, const std::string& filename, int strategy) {
    if (container == 1 || container == 4) {
        GradeSplitter::run<std::vector<Person>>("vector", filename, 5, strategy);
    }
    if (container == 2 || container == 4) {
        GradeSplitter::run<std::list<Person>>("list", filename, 5, strategy);
    }
    if (container == 3 || container == 4) {
        GradeSplitter::run<std::deque<Person>>("deque", filename, 5, strategy);
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    const int sizes[] = {1000, 10000, 100000, 1000000, 10000000};

    while (true) {
        try {
            int sizeChoice;
            std::cout << "=== Student grades ===" << std::endl;
            std::cout << "File size: 1) 1000  2) 10000  3) 100000  4) 1000000  5) 10000000  0) exit" << std::endl;
            std::cout << "Choose: ";
            if (!(std::cin >> sizeChoice) || sizeChoice == 0) {
                break;
            }
            if (sizeChoice < 1 || sizeChoice > 5) {
                std::cout << "Unknown size." << std::endl << std::endl;
                continue;
            }

            int container;
            std::cout << "Container: 1) vector  2) list  3) deque  4) all three: ";
            std::cin >> container;

            int strategy;
            std::cout << "Strategy: 1) two new containers  2) one new container (manual loop)  "
                      << "3) one new container (algorithms)  4) all: ";
            std::cin >> strategy;
            std::cout << std::endl;

            int n = sizes[sizeChoice - 1];
            std::string filename = "students_" + std::to_string(n) + ".txt";
            if (!fileExists(filename)) {
                std::cout << "Generating " << filename << " ..." << std::endl;
                FileGenerator::generateFile(filename, n, 5);
            }

            for (int s = 1; s <= 3; s++) {
                if (strategy == s || strategy == 4) {
                    runStrategy(container, filename, s);
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}