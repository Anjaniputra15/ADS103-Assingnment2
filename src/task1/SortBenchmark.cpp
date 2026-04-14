#include "SortBenchmark.h"

#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

void SortBenchmark::run() const {
    const std::string inputFiles[] = {
        "a2_task1_input1.txt",
        "a2_task1_input2.txt"
    };

    std::cout << "========================================\n";
    std::cout << "Task 1: Sorting Algorithm Comparison\n";
    std::cout << "Algorithms used: Insertion Sort and Quick Sort\n";
    std::cout << "========================================\n\n";

    for (const std::string& fileName : inputFiles) {
        processFile(fileName);
    }
}

bool SortBenchmark::processFile(const std::string& fileName) const {
    int* originalData = nullptr;
    int size = 0;

    if (!loadData(fileName, originalData, size)) {
        std::cout << "Could not read input file: " << fileName << "\n\n";
        return false;
    }

    // Create two fresh copies so each algorithm sorts the same original data.
    int* insertionData = copyArray(originalData, size);
    int* quickData = copyArray(originalData, size);

    delete[] originalData;

    if (insertionData == nullptr || quickData == nullptr) {
        delete[] insertionData;
        delete[] quickData;
        std::cout << "Memory allocation failed while copying data for "
                  << fileName << ".\n\n";
        return false;
    }

    // Measure only the sorting work, not the file reading or copying steps.
    const auto insertionStart = std::chrono::high_resolution_clock::now();
    insertionSort(insertionData, size);
    const auto insertionEnd = std::chrono::high_resolution_clock::now();

    const auto quickStart = std::chrono::high_resolution_clock::now();
    quickSort(quickData, 0, size - 1);
    const auto quickEnd = std::chrono::high_resolution_clock::now();

    const double insertionTimeMs =
        std::chrono::duration<double, std::milli>(insertionEnd - insertionStart).count();
    const double quickTimeMs =
        std::chrono::duration<double, std::milli>(quickEnd - quickStart).count();
    const double displayedInsertionTime = std::round(insertionTimeMs * 1000.0) / 1000.0;
    const double displayedQuickTime = std::round(quickTimeMs * 1000.0) / 1000.0;

    std::cout << "File: " << fileName << "\n";
    std::cout << "Number of elements: " << size << "\n";
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Insertion sort time: " << displayedInsertionTime << " ms\n";
    std::cout << "Quick sort time:     " << displayedQuickTime << " ms\n";

    if (!isSorted(insertionData, size) || !isSorted(quickData, size)) {
        std::cout << "Result check: Sorting verification failed.\n";
    } else if (displayedInsertionTime == displayedQuickTime) {
        std::cout << "Faster algorithm: Both took the same time\n";
    } else if (displayedInsertionTime < displayedQuickTime) {
        std::cout << "Faster algorithm: Insertion sort\n";
    } else {
        std::cout << "Faster algorithm: Quick sort\n";
    }

    std::cout << "\n";

    delete[] insertionData;
    delete[] quickData;
    return true;
}

bool SortBenchmark::loadData(const std::string& fileName, int*& data, int& size) const {
    std::ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        return false;
    }

    if (!(inputFile >> size) || size <= 0) {
        return false;
    }

    data = new int[size];

    for (int index = 0; index < size; ++index) {
        if (!(inputFile >> data[index])) {
            delete[] data;
            data = nullptr;
            size = 0;
            return false;
        }
    }

    return true;
}

int* SortBenchmark::copyArray(const int* source, int size) const {
    int* copy = new int[size];

    for (int index = 0; index < size; ++index) {
        copy[index] = source[index];
    }

    return copy;
}

void SortBenchmark::insertionSort(int data[], int size) const {
    for (int index = 1; index < size; ++index) {
        const int currentValue = data[index];
        int position = index - 1;

        while (position >= 0 && data[position] > currentValue) {
            data[position + 1] = data[position];
            --position;
        }

        data[position + 1] = currentValue;
    }
}

void SortBenchmark::quickSort(int data[], int low, int high) const {
    // Recursively sort the values smaller and larger than the pivot.
    if (low < high) {
        const int pivotIndex = partition(data, low, high);
        quickSort(data, low, pivotIndex - 1);
        quickSort(data, pivotIndex + 1, high);
    }
}

int SortBenchmark::partition(int data[], int low, int high) const {
    const int pivot = data[high];
    int smallerIndex = low - 1;

    for (int index = low; index < high; ++index) {
        if (data[index] <= pivot) {
            ++smallerIndex;
            const int temp = data[smallerIndex];
            data[smallerIndex] = data[index];
            data[index] = temp;
        }
    }

    const int temp = data[smallerIndex + 1];
    data[smallerIndex + 1] = data[high];
    data[high] = temp;

    return smallerIndex + 1;
}

bool SortBenchmark::isSorted(const int data[], int size) const {
    for (int index = 1; index < size; ++index) {
        if (data[index] < data[index - 1]) {
            return false;
        }
    }

    return true;
}
