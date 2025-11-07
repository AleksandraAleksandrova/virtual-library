#include <iostream>
#include <string>
using namespace std;

class Magazine : public Media {
private:
    int issueNumber;
    int month;

    void validateIssueNumber(int i) {
        if (i <= 0) {
            throw invalid_argument("Issue number must be positive.");
        }
    }

    void validateMonth(int m) {
        if ((m < 1) || (m > 12)) {
            throw invalid_argument("Month must be between 1 and 12.");
        }
    }

public:
    Magazine(string author, string title, int year, bool available, int issueNumber, int month)
        : Media("Magazine", author, title, year, available), issueNumber(issueNumber), month(month) {
        validateIssueNumber(issueNumber);
        validateMonth(month);
    }

    int getIssueNumber() const {
        return issueNumber;
    }

    void setIssueNumber(int i) {
        validateIssueNumber(i);
        issueNumber = i;
    }

    int getMonth() const {
        return month;
    }

    void setMonth(int m) {
        validateMonth(m);
        month = m;
    }

    friend ostream& operator<<(ostream& os, const Magazine& mg) {
        os << static_cast<const Media&>(mg)
           << " | Issue: " << mg.issueNumber
           << " | Month: " << mg.month;
        return os;
    }
};
