ADS103 Algorithms and Data Structures Assignment Submission

Project structure
- README.txt
- Makefile
- a2_task1_input1.txt
- a2_task1_input2.txt
- src/task1/main.cpp
- src/task1/SortBenchmark.h
- src/task1/SortBenchmark.cpp
- src/task2/main.cpp
- src/task2/LibrarySystem.h
- src/task2/LibrarySystem.cpp

How to compile
Option 1:
make

Option 2:
g++ -std=c++17 -Wall -Wextra -pedantic src/task1/main.cpp src/task1/SortBenchmark.cpp -o task1_app
g++ -std=c++17 -Wall -Wextra -pedantic src/task2/main.cpp src/task2/LibrarySystem.cpp -o task2_app

How to run
./task1_app
./task2_app

Run both commands from the project root so Task 1 can find the required input files.

Expected input file format for Task 1
- First line: number of integers
- Second line: integers separated by spaces

Example:
5
9 2 7 1 4

Task 1 notes
- The program automatically reads both required files:
  a2_task1_input1.txt
  a2_task1_input2.txt
- It stores the values in dynamically allocated arrays.
- It sorts one copy with insertion sort and one copy with recursive quick sort.
- Sorting time is measured in milliseconds using std::chrono.

Task 2 notes
- The library database is stored in a std::map<int, std::string>.
- Borrowed book IDs are stored in a dynamically allocated int array.
- Input validation is included for menu choices and book IDs.

Example output for Task 1
========================================
Task 1: Sorting Algorithm Comparison
Algorithms used: Insertion Sort and Quick Sort
========================================

File: a2_task1_input1.txt
Number of elements: 1000
Insertion sort time: 0.941 ms
Quick sort time:     0.155 ms
Faster algorithm: Quick sort

File: a2_task1_input2.txt
Number of elements: 3000
Insertion sort time: 7.133 ms
Quick sort time:     0.784 ms
Faster algorithm: Quick sort

Note: timing values will vary slightly on different computers.

Example output for Task 2
========================================
Task 2: Book Management System
========================================
1) List all books you have on loan
2) Return a book
3) List all books in the library
4) Borrow a book
5) Exit
Choose an option: 4

Enter the book ID to borrow: 106
You borrowed: Clean Code

1) List all books you have on loan
2) Return a book
3) List all books in the library
4) Borrow a book
5) Exit
Choose an option: 1

Books currently on loan:
106   Clean Code

Brief explanation of rubric alignment
- Task 1 reads files, uses dynamic arrays, applies insertion sort and recursive quick sort, measures time in milliseconds, and compares which algorithm is faster.
- Task 2 uses a repeated menu, a map for book storage, a dynamic int array for borrowed books, and functions and a class to keep the code organised.
- Both tasks use meaningful names, comments only where needed, and basic input validation.
