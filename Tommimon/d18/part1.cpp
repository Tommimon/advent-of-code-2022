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
    int res = lines.size() * 6;

    for (const auto& a: lines) {
        for (const auto& b: lines) {
            vector<string> coordsA = split(a, ",");
            vector<string> coordsB = split(b, ",");
            int equal = 0;
            int close = 0;
            for (int i = 0; i < 3; ++i) {
                if (coordsA[i] == coordsB[i])
                    equal++;
                if (abs(stoi(coordsA[i]) - stoi(coordsB[i])) == 1)
                    close++;
            }
            if (equal == 2 && close == 1)
                res--;
        }
    }

    cout << res << endl;
}
