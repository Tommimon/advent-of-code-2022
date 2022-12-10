#include <iostream>
#include <fstream>
#include <vector>
#include "py++.hpp"

using namespace std;

int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    vector<string> lines(split(input, "\n"));
    int score1 = 0;

    int cycles = 1;
    int x = 1;
    int subCycles = 0;
    for (int i = 0; i < lines.size(); ++i) {
        string l = lines[i];
        int col = (cycles-1) % 40;
        if ((cycles - 20) % 40 == 0)
            score1 += cycles * x;
        if (col >= x-1 && col <= x+1)
            cout << '#';
        else
            cout << '.';
        if (col == 39)
            cout << endl;
        if (l[0] == 'a') {
            if (subCycles == 1) {
                x += stoi(split(l, "addx ")[1]);
                subCycles = 0;
            }
            else {
                i--;
                subCycles++;
            }
            cycles ++;
        }
        else  if (l[0] == 'n'){
            cycles ++;
        }
    }

    cout << score1 << endl;
}
