#include <iostream>
#include <string>
using namespace std;

class Disk : public Media {
private:
    string format;
    double duration; // in minutes

public:
    Disk() : Media(), format(""), duration(0.0) {}

    Disk(const string& type, const string& author, const string& title,
         int year, bool available, const string& format, double duration)
        : Media(type, author, title, year, available),
          format(format), duration(duration) {}

    string getFormat() const { return format; }
    void setFormat(const string& f) { format = f; }

    double getDuration() const { return duration; }
    void setDuration(double d) { duration = d; }

    friend ostream& operator<<(ostream& os, const Disk& d) {
        os << static_cast<const Media&>(d)
           << "Format: " << d.format << "\n"
           << "Duration: " << d.duration << " min\n";
        return os;
    }
};
