#include <iostream>
#include <fstream>
#include <vector>
#include "py++.hpp"

using namespace std;
using namespace py;

int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    vector<string> lines(split(input, "\n"));
    int score1 = 0;
    int score2 = 0;

    for (int i = 0; i < lines.size(); ++i) {
        string l = lines[i];

    }

    cout << score1 << endl;
    cout << score2 << endl;
}
