#include <iostream>
using namespace std;

#include "Media.cpp"
#include "Book.cpp"
#include "Magazine.cpp"
#include "Disk.cpp"

int main() {
    Book b("George Orwell", "1984", 1949, true, "Dystopian", 328);
    Magazine m("National Geographic", "Wildlife Special", 2023, true, 215, "October");
    Disk d("Audio-CD", "Metallica", "Nothing Else Matters", 1992, true, "MP3", 74.5);

    cout << b << endl;
    cout << m << endl;
    cout << d << endl;

    m.setAvailability(false);
    cout << "\nAfter lending the magazine:\n" << m << endl;

    return 0;
}
