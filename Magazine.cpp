#include <iostream>
#include <string>
using namespace std;

class Magazine : public Media {
private:
    int issueNumber;
    string publicationMonth;

public:
    Magazine() : Media(), issueNumber(0), publicationMonth("") {}

    Magazine(const string& author, const string& title, int year, bool available,
             int issueNumber, const string& publicationMonth)
        : Media("Magazine", author, title, year, available),
          issueNumber(issueNumber), publicationMonth(publicationMonth) {}

    int getIssueNumber() const { return issueNumber; }
    void setIssueNumber(int num) { issueNumber = num; }

    string getPublicationMonth() const { return publicationMonth; }
    void setPublicationMonth(const string& month) { publicationMonth = month; }

    friend ostream& operator<<(ostream& os, const Magazine& m) {
        os << static_cast<const Media&>(m)
           << "Issue: " << m.issueNumber << "\n"
           << "Month: " << m.publicationMonth << "\n";
        return os;
    }
};
