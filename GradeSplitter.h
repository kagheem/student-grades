#ifndef GRADESPLITTER_H
#define GRADESPLITTER_H

#include <string>

class GradeSplitter {
public:
    static void processFile(const std::string& inputFilename, int numHomework);
    static void processFileList(const std::string& inputFilename, int numHomework);
    static void processFileDeque(const std::string& inputFilename, int numHomework);
};

#endif