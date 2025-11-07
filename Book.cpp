#include <iostream>
#include <string>
using namespace std;

class Book : public Media {
private:
    string genre;
    int pages;

public:
    Book() : Media(), genre(""), pages(0) {}

    Book(const string& author, const string& title, int year, bool available,
         const string& genre, int pages)
        : Media("Book", author, title, year, available), genre(genre), pages(pages) {}

    string getGenre() const { return genre; }
    void setGenre(const string& g) { genre = g; }

    int getPages() const { return pages; }
    void setPages(int p) { pages = p; }

    friend ostream& operator<<(ostream& os, const Book& b) {
        os << static_cast<const Media&>(b)
           << "Genre: " << b.genre << "\n"
           << "Pages: " << b.pages << "\n";
        return os;
    }
};
