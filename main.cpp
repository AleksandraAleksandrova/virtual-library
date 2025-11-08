#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <string>
#include <fstream>
#include <sstream>

#include "Media.cpp"
#include "Book.cpp"
#include "Magazine.cpp"
#include "Disk.cpp"

using namespace std;


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
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

void displayLibrary(const vector<shared_ptr<Media>>& library) {
    bool filterAvailable = getValidatedBool("\nWould you like to view only available items?");
    
    if (filterAvailable) {
        cout << "\nAvailable items:\n";
        for (const auto& item : library) {
            if (item->getAvailability()) {
                cout << *item << endl;
            }
        }
    } else {
        cout << "\nLibrary contents:\n";
        for (const auto& item : library) {
            cout << *item << endl;
        }
    }
}

void saveLibraryToFile(const vector<shared_ptr<Media>>& library, const string& filename, bool logInfo = true) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file for writing.\n";
        return;
    }

    for (const auto& item : library) {
        string type = item->getType();

        switch (getMediaType(type)) {
            case BOOK: {
                const Book* b = dynamic_cast<const Book*>(item.get());
                if (b) {
                    file << "Book|" << b->getAuthor() << "|" << b->getTitle() << "|" << b->getYear() << "|"
                         << b->getAvailability() << "|" << b->getGenre() << "|" << b->getPages() << "\n";
                }
                break;
            }

            case MAGAZINE: {
                const Magazine* m = dynamic_cast<const Magazine*>(item.get());
                if (m) {
                    file << "Magazine|" << m->getAuthor() << "|" << m->getTitle() << "|" << m->getYear() << "|"
                         << m->getAvailability() << "|" << m->getIssueNumber() << "|" << m->getMonth() << "\n";
                }
                break;
            }

            case DISK: {
                const Disk* d = dynamic_cast<const Disk*>(item.get());
                if (d) {
                    file << "Disk|" << d->getAuthor() << "|" << d->getTitle() << "|" << d->getYear() << "|"
                         << d->getAvailability() << "|" << d->getFormat() << "|" << d->getDuration() << "\n";
                }
                break;
            }

            default:
                cerr << "Warning: Unknown media type, skipping item.\n";
                break;
        }
    }

    file.close();
    if (logInfo) {
        cout << "\nLibrary successfully saved to file: " << filename << endl;
    }
}


vector<shared_ptr<Media>> loadLibraryFromFile(const string& filename) {
    vector<shared_ptr<Media>> library;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Warning: Could not open file for reading. Starting with an empty library.\n";
        return library;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string type, author, title, yearStr, availStr;

        getline(ss, type, '|');
        getline(ss, author, '|');
        getline(ss, title, '|');
        getline(ss, yearStr, '|');
        getline(ss, availStr, '|');

        int year = stoi(yearStr);
        bool available = (availStr == "1");

        switch (getMediaType(type)) {
            case BOOK: {
                string genre, pagesStr;
                getline(ss, genre, '|');
                getline(ss, pagesStr, '|');
                int pages = stoi(pagesStr);
                library.push_back(make_shared<Book>(author, title, year, available, genre, pages));
                break;
            }

            case MAGAZINE: {
                string issueStr, monthStr;
                getline(ss, issueStr, '|');
                getline(ss, monthStr, '|');
                int issue = stoi(issueStr);
                int month = stoi(monthStr);
                library.push_back(make_shared<Magazine>(author, title, year, available, issue, month));
                break;
            }

            case DISK: {
                string format, durationStr;
                getline(ss, format, '|');
                getline(ss, durationStr, '|');
                int duration = stoi(durationStr);
                library.push_back(make_shared<Disk>(author, title, year, available, format, duration));
                break;
            }

            default:
                cerr << "Warning: Unknown media type found in file, skipping line.\n";
                break;
        }
    }

    file.close();
    cout << "Library loaded successfully from file: " << filename << endl;
    return library;
}

int main() {
    cout << "Welcome to your Virtual Library!" << endl;

    ifstream defaultCheck("default.txt");
    if (!defaultCheck.is_open()) {
        vector<shared_ptr<Media>> defaultLibrary;
        defaultLibrary.push_back(make_shared<Book>("George Orwell", "1984", 1949, false, "Dystopian", 328));
        defaultLibrary.push_back(make_shared<Magazine>("National Geographic", "Wildlife Special", 2023, true, 215, 10)); // October = 10
        defaultLibrary.push_back(make_shared<Disk>("Metallica", "Nothing Else Matters", 1992, true, "MP3", 74));
        saveLibraryToFile(defaultLibrary, "default.txt", false);
    }
    defaultCheck.close();

    vector<shared_ptr<Media>> library;

    bool loadFromFile = getValidatedBool("Would you like to load the library from a file? ");

    if (loadFromFile) {
        string filename = getValidatedString("Enter filename to load (or use 'default.txt'): ");
        ifstream testFile(filename);
        if (!testFile.is_open()) {
            cerr << "Error: Could not open file for reading. Exiting program.\n";
            return 0;
        }
        testFile.close();

        library = loadLibraryFromFile(filename);
        displayLibrary(library);
    } else {
        int itemCount = getValidatedInt("How many items would you like to add? ", 1, 1000);

        for (int i = 0; i < itemCount; i++) {
            cout << "\n--- Item " << i + 1 << " ---" << endl;

            string type;
            cout << "Enter media type (Book / Magazine / Disk): ";
            getline(cin, type);

            string author = getValidatedString("Author: ");
            string title = getValidatedString("Title: ");
            int year = getValidatedInt("Year of release: ", 0, 2100);
            bool available = getValidatedBool("Is it available?");

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
        }

        cout << "\nLibrary contents:\n";
        for (const auto& item : library) {
            cout << *item << endl;
        }

        displayLibrary(library);

        bool saveToFile = getValidatedBool("\nWould you like to save the library to a file?");
        if (saveToFile) {
            string saveFilename = getValidatedString("Enter filename to save: ");
            saveLibraryToFile(library, saveFilename);
        }
    }

    return 0;
}
