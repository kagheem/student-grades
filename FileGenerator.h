#ifndef FILEGENERATOR_H
#define FILEGENERATOR_H

#include <string>

class FileGenerator {
public:
    static void generateFile(const std::string& filename, int numRecords, int numHomework);
};

#endif