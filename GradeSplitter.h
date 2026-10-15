#ifndef GRADESPLITTER_H
#define GRADESPLITTER_H

#include <string>

class GradeSplitter {
public:
    static void processFile(const std::string& inputFilename, int numHomework);
};

#endif