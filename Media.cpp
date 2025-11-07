#include <iostream>
#include <string>
#include <stdexcept>
#include <ctime>
using namespace std;

class Media {
private:
    string type;
    string author;
    string title;
    int year;
    bool available;

    static int getCurrentYear() {
        time_t t = time(nullptr);
        tm* now = localtime(&t); // convert to local time structure
        return 1900 + now->tm_year; // tm_year is years since 1900
    }

    void validateType(const string& t) {
        if (t.empty()) {
            throw invalid_argument("Type cannot be empty.");
        }
    }

    void validateAuthor(const string& a) {
        if (a.empty()) {
            throw invalid_argument("Author cannot be empty.");
        }
    }

    void validateTitle(const string& t) {
        if (t.empty()) {
            throw invalid_argument("Title cannot be empty.");
        }
    }

    void validateYear(int y) {
        int currentYear = getCurrentYear();
        if ((y < 0) || (y > currentYear)) {
            throw invalid_argument("Invalid year of publication.");
        }
    }

public:
    Media(string type = "Unknown", string author = "Unknown", string title = "Untitled", int year = 0, bool available = true) {
        if (year == 0) {
            year = getCurrentYear();
        }

        validateType(type);
        validateAuthor(author);
        validateTitle(title);
        validateYear(year);

        this->type = type;
        this->author = author;
        this->title = title;
        this->year = year;
        this->available = available;
    }

    string getType() const {
        return type;
    }

    void setType(const string& t) {
        validateType(t);
        type = t;
    }

    string getAuthor() const {
        return author;
    }

    void setAuthor(const string& a) {
        validateAuthor(a);
        author = a;
    }

    string getTitle() const {
        return title;
    }

    void setTitle(const string& t) {
        validateTitle(t);
        title = t;
    }

    int getYear() const {
        return year;
    }

    void setYear(int y) {
        validateYear(y);
        year = y;
    }

    bool getAvailability() const {
        return available;
    }

    void setAvailability(bool a) {
        available = a;
    }

    friend ostream& operator<<(ostream& os, const Media& m) {
        os << "Type: " << m.type
           << " | Author: " << m.author
           << " | Title: " << m.title
           << " | Year: " << m.year
           << " | Status: " << (m.available ? "Available" : "Borrowed");
        return os;
    }
};
