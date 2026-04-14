#include "LibrarySystem.h"

#include <iomanip>
#include <iostream>
#include <sstream>

LibrarySystem::LibrarySystem() : borrowedBookIds(nullptr), borrowedCount(0), borrowedCapacity(0) {
    loadSampleBooks();
    borrowedCapacity = static_cast<int>(libraryBooks.size());
    // The brief requires borrowed book IDs to be stored in a dynamic int array.
    borrowedBookIds = new int[borrowedCapacity];
}

LibrarySystem::~LibrarySystem() {
    delete[] borrowedBookIds;
}

void LibrarySystem::run() {
    bool isRunning = true;

    std::cout << "========================================\n";
    std::cout << "Task 2: Book Management System\n";
    std::cout << "========================================\n";

    while (isRunning) {
        showMenu();
        const int choice = readInteger("Choose an option: ");
        std::cout << "\n";

        switch (choice) {
            case 1:
                listBorrowedBooks();
                break;
            case 2:
                returnBook();
                break;
            case 3:
                listAllLibraryBooks();
                break;
            case 4:
                borrowBook();
                break;
            case 5:
                std::cout << "Exiting program. Goodbye.\n";
                isRunning = false;
                break;
            default:
                std::cout << "Invalid menu option. Please choose a number from 1 to 5.\n";
                break;
        }

        std::cout << "\n";
    }
}

void LibrarySystem::loadSampleBooks() {
    libraryBooks[101] = "Introduction to Algorithms";
    libraryBooks[102] = "Data Structures in C++";
    libraryBooks[103] = "Discrete Mathematics";
    libraryBooks[104] = "Computer Networks";
    libraryBooks[105] = "Operating Systems Concepts";
    libraryBooks[106] = "Clean Code";
    libraryBooks[107] = "Database System Basics";
    libraryBooks[108] = "Software Engineering";
    libraryBooks[109] = "Programming Principles";
    libraryBooks[110] = "Artificial Intelligence Foundations";
}

void LibrarySystem::showMenu() const {
    std::cout << "1) List all books you have on loan\n";
    std::cout << "2) Return a book\n";
    std::cout << "3) List all books in the library\n";
    std::cout << "4) Borrow a book\n";
    std::cout << "5) Exit\n";
}

void LibrarySystem::listBorrowedBooks() const {
    if (borrowedCount == 0) {
        std::cout << "You do not currently have any books on loan.\n";
        return;
    }

    std::cout << "Books currently on loan:\n";

    for (int index = 0; index < borrowedCount; ++index) {
        const int bookId = borrowedBookIds[index];
        std::cout << std::left << std::setw(6) << bookId
                  << libraryBooks.at(bookId) << "\n";
    }
}

void LibrarySystem::listAllLibraryBooks() const {
    std::cout << "Library catalogue:\n";

    for (const auto& book : libraryBooks) {
        std::cout << std::left << std::setw(6) << book.first
                  << std::setw(40) << book.second
                  << " | " << (isBorrowed(book.first) ? "On loan" : "Available") << "\n";
    }
}

void LibrarySystem::borrowBook() {
    const int bookId = readInteger("Enter the book ID to borrow: ");

    if (!isValidBookId(bookId)) {
        std::cout << "That book ID does not exist in the library.\n";
        return;
    }

    if (isBorrowed(bookId)) {
        std::cout << "That book is already on loan.\n";
        return;
    }

    if (borrowedCount >= borrowedCapacity) {
        std::cout << "No more books can be borrowed at this time.\n";
        return;
    }

    // Add the borrowed book ID to the next free position in the dynamic array.
    borrowedBookIds[borrowedCount] = bookId;
    ++borrowedCount;

    std::cout << "You borrowed: " << libraryBooks.at(bookId) << "\n";
}

void LibrarySystem::returnBook() {
    if (borrowedCount == 0) {
        std::cout << "You do not have any borrowed books to return.\n";
        return;
    }

    const int bookId = readInteger("Enter the book ID to return: ");
    const int borrowedIndex = findBorrowedIndex(bookId);

    if (borrowedIndex == -1) {
        std::cout << "That book is not currently in your borrowed list.\n";
        return;
    }

    const std::string returnedTitle = libraryBooks.at(bookId);

    // Shift later IDs left to keep the borrowed list compact after a return.
    for (int index = borrowedIndex; index < borrowedCount - 1; ++index) {
        borrowedBookIds[index] = borrowedBookIds[index + 1];
    }

    --borrowedCount;
    std::cout << "You returned: " << returnedTitle << "\n";
}

bool LibrarySystem::isValidBookId(int bookId) const {
    return libraryBooks.find(bookId) != libraryBooks.end();
}

bool LibrarySystem::isBorrowed(int bookId) const {
    return findBorrowedIndex(bookId) != -1;
}

int LibrarySystem::findBorrowedIndex(int bookId) const {
    for (int index = 0; index < borrowedCount; ++index) {
        if (borrowedBookIds[index] == bookId) {
            return index;
        }
    }

    return -1;
}

int LibrarySystem::readInteger(const std::string& prompt) const {
    while (true) {
        std::cout << prompt;

        std::string inputLine;
        std::getline(std::cin, inputLine);

        std::stringstream converter(inputLine);
        int value = 0;
        char extraCharacter = '\0';

        if (converter >> value && !(converter >> extraCharacter)) {
            return value;
        }

        std::cout << "Invalid input. Please enter a whole number.\n";
    }
}
