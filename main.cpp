#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <string>
#include "Media.cpp"
#include "Book.cpp"
#include "Magazine.cpp"
#include "Disk.cpp"

using namespace std;

// --- Helper methods ---

bool equalsIgnoreCase(const string& a, const string& b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (size_t i = 0; i < a.size(); ++i) {
        if (tolower(a[i]) != tolower(b[i])) {
            return false;
        }
    }
    return true;
}

enum MediaType { BOOK, MAGAZINE, DISK, UNKNOWN };

MediaType getMediaType(const string& type) {
    if (equalsIgnoreCase(type, "book")) {
        return BOOK;
    }
    if (equalsIgnoreCase(type, "magazine")) {
        return MAGAZINE;
    }
    if (equalsIgnoreCase(type, "disk")) {
        return DISK;
    }
    return UNKNOWN;
}

int getValidatedInt(const string& prompt, int minValue, int maxValue) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value >= minValue && value <= maxValue) {
                return value;
            } 
            else {
                cout << "Please enter a value between " << minValue << " and " << maxValue << "." << endl;
            }
        } 
        else {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

bool getValidatedBool(const string& prompt) {
    int input;
    while (true) {
        cout << prompt << " (1 - Yes, 0 - No): ";
        if (cin >> input) {
            if (input == 0 || input == 1) {
                return input == 1;
            } 
            else {
                cout << "Please enter 1 or 0." << endl;
            }
        } 
        else {
            cout << "Invalid input. Please enter 1 or 0." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

string getValidatedString(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (!input.empty()) {
            return input;
        } 
        else {
            cout << "Input cannot be empty. Please try again." << endl;
        }
    }
}

// --- Main program ---

int main() {
    cout << "Welcome to your Virtual Library!" << endl;

    int itemCount = getValidatedInt("How many items would you like to add? ", 1, 1000);
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear leftover newline once

    vector<shared_ptr<Media>> library;

    for (int i = 0; i < itemCount; i++) {
        cout << "\n--- Item " << i + 1 << " ---" << endl;

        string type;
        cout << "Enter media type (Book / Magazine / Disk): ";
        getline(cin, type);

        string author = getValidatedString("Author: ");
        string title = getValidatedString("Title: ");
        int year = getValidatedInt("Year of release: ", 0, 2100);
        bool available = getValidatedBool("Is it available?");
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline after bool

        switch (getMediaType(type)) {
            case BOOK: {
                string genre = getValidatedString("Genre: ");
                int pages = getValidatedInt("Page count: ", 1, 10000);
                library.push_back(make_shared<Book>(author, title, year, available, genre, pages));
                break;
            }

            case MAGAZINE: {
                int issueNumber = getValidatedInt("Issue number: ", 1, 10000);
                int month = getValidatedInt("Month (1-12): ", 1, 12);
                library.push_back(make_shared<Magazine>(author, title, year, available, issueNumber, month));
                break;
            }

            case DISK: {
                string format = getValidatedString("Format (Audio-CD / CD-ROM / Cassette / Video): ");
                int duration = getValidatedInt("Duration (in minutes): ", 1, 10000);
                library.push_back(make_shared<Disk>(author, title, year, available, format, duration));
                break;
            }

            default:
                cout << "Invalid type. Skipping this item." << endl;
                break;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // prepare for next item
    }

    cout << "\nLibrary contents:\n";
    for (const auto& item : library) {
        cout << *item << endl;
    }

    bool filterAvailable = getValidatedBool("\nWould you like to view only available items?");
    if (filterAvailable) {
        cout << "\nAvailable items:\n";
        for (const auto& item : library) {
            if (item->getAvailability()) {
                cout << *item << endl;
            }
        }
    }

    return 0;
}
