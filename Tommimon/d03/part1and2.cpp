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

    for (auto l : lines) {
        string part1 = l.substr(0, l.size()/2);
        string part2 = l.substr(l.size()/2, l.size()/2);
        char both = -1;
        for (auto c : part1) {
            if (part2.contains(c))
                both = c;
        }
        if (both >= 'A' && both <= 'Z')
            score1 += both-'A'+27;
        else
            score1 += both-'a'+1;
    }

    int score2 = 0;
    for (int i = 0; i < lines.size(); i += 3) {
        string part1 = lines[i];
        string part2 = lines[i+1];
        string part3 = lines[i+2];
        char all = -1;
        for (auto c : part1) {
            if (part2.contains(c) && part3.contains(c))
                all = c;
        }
        if (all >= 'A' && all <= 'Z')
            score2 += all - 'A' + 27;
        else
            score2 += all - 'a' + 1;
    }

    cout << score1 << endl;
    cout << score2 << endl;
}
