#include <iostream>
#include <fstream>
#include <string>
#include "class.h"
using namespace std;
int main() {
    DoublyLinkedList<int> scorelist;
    const string filename = "Scores.txt";

    ifstream ifs(filename);

    if (!ifs) {
        cout << "file not opened\n";
        return 0;
    }
    int score;
    string username;
    while (ifs >> score >> username) {
        scorelist.insert(scorelist.end(), score, username);
        cout << score << "  " << username << "\n";
    }
    cout << "Data size:\n" << scorelist.getSize() << "\n";
    ifs.close();
    return 0;
}
