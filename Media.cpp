#include <iostream>
#include <string>
using namespace std;

class Media {
private:
    string type;
    string author;
    string title;
    int year;
    bool available;

public:
    Media() : type(""), author(""), title(""), year(2025), available(true) {}

    Media(const string& type, const string& author, const string& title, int year, bool available)
        : type(type), author(author), title(title), year(year), available(available) {}

    string getType() const { return type; }
    void setType(const string& t) { type = t; }

    string getAuthor() const { return author; }
    void setAuthor(const string& a) { author = a; }

    string getTitle() const { return title; }
    void setTitle(const string& t) { title = t; }

    int getYear() const { return year; }
    void setYear(int y) { year = y; }

    bool getAvailability() const { return available; }
    void setAvailability(bool av) { available = av; }

    friend ostream& operator<<(ostream& os, const Media& m) {
        os << "Type: " << m.type << "\n"
           << "Author: " << m.author << "\n"
           << "Title: " << m.title << "\n"
           << "Year: " << m.year << "\n"
           << "Available: " << (m.available ? "Yes" : "No") << "\n";
        return os;
    }
};
