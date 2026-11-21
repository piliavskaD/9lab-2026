#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Book {
public:
    Book(std::string title, std::string author)
        : title_(std::move(title)), author_(std::move(author)) {
    }

    const std::string& title()  const { return title_; }   
    const std::string& author() const { return author_; }

private:
    std::string title_;
    std::string author_;
};

class IBookRepository {
public:
    virtual void save(const Book& book) = 0;
    virtual ~IBookRepository() = default;
};

class INotifier {
public:
    virtual void notifyBookAdded(const Book& book) = 0;
    virtual ~INotifier() = default;
};

class DatabaseBookRepository : public IBookRepository {
public:
    void save(const Book&) override {
        std::cout << "Saving book to database..." << std::endl;
    }
};

class EmailNotifier : public INotifier {
public:
    void notifyBookAdded(const Book&) override {
        std::cout << "Sending email notification about the new book..." << std::endl;
    }
};

class SmsNotifier : public INotifier {
public:
    void notifyBookAdded(const Book& book) override {
        std::cout << "Sending SMS about: " << book.title() << std::endl;
    }
};

class BookPrinter {
public:
    static void print(const Book& book) {
        std::cout << "Title: " << book.title()
            << ", Author: " << book.author() << std::endl;
    }
};

class Library {
public:
    Library(IBookRepository& repository, INotifier& notifier)
        : repository_(repository), notifier_(notifier) {
    }

    void addBook(const Book& book) {
        books_.push_back(book);
        repository_.save(book);
        notifier_.notifyBookAdded(book);
    }

    const std::vector<Book>& books() const { return books_; }

private:
    std::vector<Book> books_;
    IBookRepository& repository_;
    INotifier& notifier_;
};

int main() {
    DatabaseBookRepository repo;
    EmailNotifier notifier;              
    Library library(repo, notifier);

    library.addBook(Book("The Catcher in the Rye", "J.D. Salinger"));
    library.addBook(Book("To Kill a Mockingbird", "Harper Lee"));

    for (const auto& book : library.books())
        BookPrinter::print(book);
}