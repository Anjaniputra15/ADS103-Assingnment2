CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

all: task1_app task2_app

task1_app: src/task1/main.cpp src/task1/SortBenchmark.cpp src/task1/SortBenchmark.h
	$(CXX) $(CXXFLAGS) src/task1/main.cpp src/task1/SortBenchmark.cpp -o task1_app

task2_app: src/task2/main.cpp src/task2/LibrarySystem.cpp src/task2/LibrarySystem.h
	$(CXX) $(CXXFLAGS) src/task2/main.cpp src/task2/LibrarySystem.cpp -o task2_app

clean:
	rm -f task1_app task2_app
