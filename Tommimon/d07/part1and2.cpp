#include <iostream>
#include <fstream>
#include <vector>
#include "py++.hpp"

using namespace std;

int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    vector<string> lines(split(input, "\n"));
    int thisDir = 0;
    int res1 = 0;

    vector<string > dirs;
    vector<int> space;
    for(int j = lines.size()-1; j >= 0; j--) {
        string l= lines[j];
        if (l.size() > 2 && l.substr(0,3) == "dir") {
            for (int i = dirs.size()-1; i >= 0; --i) {
                if (dirs[i] == l.substr(4, l.size()-4)) {
                    thisDir += space[i];
                    break;
                }
            }
        }
        else if (l[0] == '$') {
            if (l[2] == 'c' && l[5] != '.') {
                bool found = false;
                for (int i = dirs.size()-1; i >= 0; --i) {
                    if (dirs[i] == split(l, "$ cd ")[1]) {
                        space[i] = thisDir;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    dirs.push_back(split(l, "$ cd ")[1]);
                    space.push_back(thisDir);
                }
                if (thisDir <= 100000)
                    res1 += thisDir;
                thisDir = 0;
            }
        } else {
            thisDir += stoi(split(l, " ")[0]);
        }
    }

    int toFree = space[space.size() - 1] - 40000000;
    int chosen = 70000000;
    for (int i = 0; i < dirs.size(); ++i) {
        if (space[i] >= toFree && space[i] < chosen)
            chosen = space[i];
    }

    cout << res1 << endl;
    cout << chosen << endl;
}
