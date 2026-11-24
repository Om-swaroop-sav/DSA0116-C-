#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

class Book {
    std::string title;
    std::string author;
    int copies;
public:
    Book() : Book("Untitled", "Unknown", 0) {}

    explicit Book(std::string bookTitle) : Book(std::move(bookTitle), "Unknown", 1) {}

    Book(std::string bookTitle, std::string bookAuthor, int numberOfCopies)
        : title(std::move(bookTitle)), author(std::move(bookAuthor)), copies(numberOfCopies) {
        if (copies < 0) throw std::invalid_argument("number of copies cannot be negative");
    }

    void print() const {
        std::cout << "Title: " << title << " | Author: " << author
                  << " | Copies: " << copies << '\n';
    }
};

int main() {
    try {
        Book emptyRecord;
        Book donatedBook("The Alchemist");
        Book fullRecord("Wings of Fire", "A. P. J. Abdul Kalam", 5);
        emptyRecord.print();
        donatedBook.print();
        fullRecord.print();

        Book invalidBook("Invalid record", "Unknown", -2);
        invalidBook.print();
    } catch (const std::invalid_argument& error) {
        std::cout << "Rejected invalid book: " << error.what() << '\n';
    }
}
