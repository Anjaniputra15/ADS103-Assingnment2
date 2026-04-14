#ifndef LIBRARY_SYSTEM_H
#define LIBRARY_SYSTEM_H

#include <map>
#include <string>

class LibrarySystem {
public:
    LibrarySystem();
    ~LibrarySystem();

    void run();

private:
    std::map<int, std::string> libraryBooks;
    int* borrowedBookIds;
    int borrowedCount;
    int borrowedCapacity;

    void loadSampleBooks();
    void showMenu() const;
    void listBorrowedBooks() const;
    void listAllLibraryBooks() const;
    void borrowBook();
    void returnBook();
    bool isValidBookId(int bookId) const;
    bool isBorrowed(int bookId) const;
    int findBorrowedIndex(int bookId) const;
    int readInteger(const std::string& prompt) const;
};

#endif
