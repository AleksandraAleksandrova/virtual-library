#include <iostream>
#include <string>
using namespace std;

class Book : public Media {
private:
    string genre;
    int pages;

    void validateGenre(const string& g) {
        if (g.empty()) {
            throw invalid_argument("Genre cannot be empty.");
        }
    }

    void validatePages(int p) {
        if (p <= 0) {
            throw invalid_argument("Number of pages must be positive.");
        }
    }

public:
    Book(string author, string title, int year, bool available, string genre, int pages)
        : Media("Book", author, title, year, available), genre(genre), pages(pages) {
        validateGenre(genre);
        validatePages(pages);
    }

    string getGenre() const {
        return genre;
    }

    void setGenre(const string& g) {
        validateGenre(g);
        genre = g;
    }

    int getPages() const {
        return pages;
    }
    
    void setPages(int p) {
        validatePages(p);
        pages = p;
    }

    friend ostream& operator<<(ostream& os, const Book& b) {
        os << static_cast<const Media&>(b)
           << " | Genre: " << b.genre
           << " | Pages: " << b.pages;
        return os;
    }
};
