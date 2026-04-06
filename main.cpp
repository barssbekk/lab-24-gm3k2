#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include <ctime>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20, MIN_AGE = 1;

int select_goat(set<Goat> trip);
void delete_goat(set<Goat> &trip);
void add_goat(set<Goat> &trip, string [], string [], int, int);
void display_trip(set<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again = true;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int nameCount = 0;
    while (nameCount < SZ_NAMES && fin >> names[nameCount]) {
        ++nameCount;
    }

    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    int colorCount = 0;
    while (colorCount < SZ_COLORS && fin1 >> colors[colorCount]) {
        ++colorCount;
    }

    fin1.close();
    set<Goat> trip;
    while (again) {
        int choice = main_menu();

        switch (choice) {
            case 1:
                add_goat(trip, names, colors, nameCount, colorCount);
                break;
            case 2:
                delete_goat(trip);
                break;
            case 3:
                display_trip(trip);
                break;
            case 4:
                again = false;
                break;
        }
    }

    return 0;
}

void add_goat(set<Goat>& trip, string names[], string colors[],
              int nameCount, int colorCount) {
    string rndName = names[rand() % nameCount];
    string rndColors = colors[rand() % colorCount];
    int rndAge = rand() % (MAX_AGE - MIN_AGE + 1) + MIN_AGE;
    trip.insert(Goat(rndName, rndAge, rndColors));
}

int select_goat(set<Goat> trip) {
    int index = 1;

    for (Goat goat : trip) {
        cout << "[" << index++ << "] "
             << goat.get_name()
             << " (" << goat.get_age()
             << ", " << goat.get_color()
             << ")\n";
    }

    int choice;
    cout << "Choice --> ";
    cin >> choice;

    while (choice < 1 || choice >= index) {
        cin.clear();
        cin.ignore();
        cout << "Choice --> ";
        cin >> choice;
    }
    return choice;
}

// TODO: delete goat
void delete_goat(set<Goat>& trip) {
    if (trip.empty()) return;
    int choice = select_goat(trip);

    auto it = trip.begin();
    advance(it, choice - 1);
    trip.erase(it);
}

// TODO: print goat
void display_trip(set<Goat> trip) {
    int index = 1;
    for (Goat g : trip) {
        cout << "[" << index++ << "] "
             << g.get_name()
             << " (" << g.get_age()
             << ", " << g.get_color()
             << ")\n";
    }
}

int main_menu() {
    int choice = 0;
    cout << "*** GOAT MANAGER 3001 ***\n"
         << "[1] Add a goat\n"
         << "[2] Delete a goat\n"
         << "[3] List goats\n"
         << "[4] Quit\n"
         << "Choice --> ";
    cin >> choice;
    while (choice < 1 || choice > 4) {
        cerr << "Invalid input. Try again: ";
        cin >> choice;
    }
    return choice;
}

