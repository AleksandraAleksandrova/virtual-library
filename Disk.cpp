#include <iostream>
#include <string>
using namespace std;

class Disk : public Media {
private:
    string format;
    int duration; // in minutes

    void validateFormat(const string& f) {
        if (f.empty()) {
            throw invalid_argument("Format cannot be empty.");
        }
    }

    void validateDuration(int d) {
        if (d <= 0) {
            throw invalid_argument("Duration must be a positive number.");
        }
    }

public:
    Disk(string type, string author, string title, int year, bool available, string format, int duration)
        : Media(type, author, title, year, available), format(format), duration(duration) {
        validateFormat(format);
        validateDuration(duration);
    }

    string getFormat() const {
        return format;
    }

    void setFormat(const string& f) {
        validateFormat(f);
        format = f;
    }

    int getDuration() const {
        return duration;
    }

    void setDuration(int d) {
        validateDuration(d);
        duration = d;
    }

    friend ostream& operator<<(ostream& os, const Disk& d) {
        os << static_cast<const Media&>(d)
           << " | Format: " << d.format
           << " | Duration: " << d.duration << " mins";
        return os;
    }
};
