CXX = g++
CXXFLAGS = -std=c++17 -fopenmp
SRC = src/main.cpp \
      src/search/binarySearch.cpp \
      src/search/gallopingSearch.cpp \
      src/sort/quickSort.cpp \
      src/utils/array_utils.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o
