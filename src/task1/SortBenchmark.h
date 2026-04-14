#ifndef SORT_BENCHMARK_H
#define SORT_BENCHMARK_H

#include <string>

class SortBenchmark {
public:
    void run() const;

private:
    bool processFile(const std::string& fileName) const;
    bool loadData(const std::string& fileName, int*& data, int& size) const;
    int* copyArray(const int* source, int size) const;
    void insertionSort(int data[], int size) const;
    void quickSort(int data[], int low, int high) const;
    int partition(int data[], int low, int high) const;
    bool isSorted(const int data[], int size) const;
};

#endif
