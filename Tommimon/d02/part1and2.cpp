#include <iostream>
#include <fstream>
#include <vector>
#include "py++.hpp"

using namespace std;

int game_score(int opponent, int me) {
    int partial = (me) + 1;
    if (opponent == me)
        partial += 3;
    else if (me == (opponent+1)%3)
        partial += 6;
    return partial;
}

int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    vector<string> lines(split(input, "\n"));
    int score1 = 0;
    int score2 = 0;
    for (auto l : lines) {
        char opponent = l[0] - 'A';
        char me1 = l[2] - 'X';
        char me2 = (l[0] + l[2] - 1) % 3;
        if (me2 == -1) me2 = 2;
        score1 += game_score(opponent, me1);
        score2 += game_score(opponent, me2);
    }
    cout << score1 << endl;
    cout << score2 << endl;
}
