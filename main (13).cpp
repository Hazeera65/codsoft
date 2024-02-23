/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Book class to store book information
class Book {
public:
    string title;
    string author;
    string isbn;
    bool isAvailable;

    Book(string t, string a, string i) : title(t), author(a), isbn(i), isAvailable(true) {}
};

// Library class to manage books
class Library {
private:
    vector<Book> books;

public:
    // Add a new book to the library
    void addBook(string title, string author, string isbn) {
        books.push_back(Book(title, author, isbn));
    }

    // Search for books by title, author, or ISBN
    vector<Book> searchBooks(string query) {
        vector<Book> results;
        for (const auto& book : books) {
            if (book.title.find(query) != string::npos ||
                book.author.find(query) != string::npos ||
                book.isbn.find(query) != string::npos) {
                results.push_back(book);
            }
        }
        return results;
    }

    // Check out a book
    void checkoutBook(string isbn) {
        auto it = find_if(books.begin(), books.end(), [&](const Book& b) { return b.isbn == isbn && b.isAvailable; });
        if (it != books.end()) {
            it->isAvailable = false;
            cout << "Book checked out successfully!" << endl;
        } else {
            cout << "Book not found or already checked out." << endl;
        }
    }

    // Return a book
    void returnBook(string isbn) {
        auto it = find_if(books.begin(), books.end(), [&](const Book& b) { return b.isbn == isbn && !b.isAvailable; });
        if (it != books.end()) {
            it->isAvailable = true;
            cout << "Book returned successfully!" << endl;
        } else {
            cout << "Book not found or already returned." << endl;
        }
    }

    // Calculate fine for overdue books
    float calculateFine(string isbn, int daysOverdue) {
        auto it = find_if(books.begin(), books.end(), [&](const Book& b) { return b.isbn == isbn && !b.isAvailable; });
        if (it != books.end()) {
            float fineRate = 0.50; // Example fine rate per day
            return fineRate * daysOverdue;
        } else {
            cout << "Book not found or not overdue." << endl;
            return 0.0;
        }
    }
};

int main() {
    Library library;

    // Add some books to the library
    library.addBook("The Catcher in the Rye", "J.D. Salinger", "9780316769488");
    library.addBook("To Kill a Mockingbird", "Harper Lee", "9780061120084");
    library.addBook("1984", "George Orwell", "9780451524935");

    // Search for books
    vector<Book> results = library.searchBooks("1984");
    for (const auto& book : results) {
        cout << "Title: " << book.title << ", Author: " << book.author << ", ISBN: " << book.isbn << endl;
    }

    // Check out a book
    library.checkoutBook("9780451524935");

    // Return a book
    library.returnBook("9780451524935");

    // Calculate fine for overdue book
    float fine = library.calculateFine("9780451524935", 5);
    cout << "Fine: $" << fine << endl;

    return 0;
}

