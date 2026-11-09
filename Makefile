CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall
TARGET   = main
OBJS     = main.o Person.o FileGenerator.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

main.o: main.cpp Person.h FileGenerator.h GradeSplitter.h
Person.o: Person.cpp Person.h
FileGenerator.o: FileGenerator.cpp FileGenerator.h

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean