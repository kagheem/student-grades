#include "FileGenerator.h"
#include <fstream>
#include <stdexcept>
#include <cstdlib>

void FileGenerator::generateFile(const std::string& filename, int numRecords, int numHomework) {
    std::ofstream file(filename);
    if (!file) {
        throw std::runtime_error("Could not create file: " + filename);
    }

    file << "Name       Surname     ";
    for (int i = 1; i <= numHomework; i++) {
        file << "HW" << i << "  ";
    }
    file << "Exam" << std::endl;

    for (int i = 1; i <= numRecords; i++) {
        file << "Name" << i << " " << "Surname" << i << " ";
        for (int h = 0; h < numHomework; h++) {
            file << (rand() % 11) << " ";
        }
        file << (rand() % 11) << std::endl;
    }
}