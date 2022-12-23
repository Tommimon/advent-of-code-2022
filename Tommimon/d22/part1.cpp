#include <iostream>
#include <fstream>
#include <vector>
#include "py++.hpp"

using namespace std;
using namespace py;

int jump(vector<pair<string, int>> board, int i, int j, int dir) {
    while (j >= board[i].second && j < board[i].first.size() + board[i].second)
        i += dir;
    return i - dir;
}

int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    string mapInput = split(input, "\n\n")[0];
    string directions = split(input, "\n\n")[1];
    vector<string> lines(split(mapInput, "\n"));

    vector<pair<string, int>> board = py::map<string, pair<string, int>>([](const string& s){
        int spaces = 0;
        for (auto i : s) {
            if (i != ' ')
                break;
            spaces++;
        }
        return make_pair(s.substr(spaces, s.size()-spaces), spaces);
    }, lines);

    vector<string> instructions = {""};
    for (auto c: directions) {
        if (c == 'R' || c == 'L') {
            string s;
            s += c;
            instructions.push_back(s);
            instructions.emplace_back("");
        }
        else if (c != '\n')
            instructions[instructions.size()-1] += c;
    }

    int i = 0, j = board[i].second, dir = 0;
    for (const auto& s: instructions) {
        if (s == "R")
            dir = (dir + 1) % 4;
        else if (s == "L")
            dir = dir == 0 ? 3 : (dir - 1);
        else {
            int delta = stoi(s);
            for (int k = 0; k < delta; ++k) {
                if (dir % 2 == 0) {
                    int newJ = j + (dir >= 2 ? -1 : 1);
                    if (newJ == board[i].first.size() + board[i].second)
                        newJ = board[i].second;
                    if (newJ == board[i].second-1)
                        newJ = board[i].first.size() + board[i].second - 1;
                    if (board[i].first[newJ - board[i].second] == '.')
                        j = newJ;
                }
                else {
                    int newI = i + (dir >= 2 ? -1 : 1);
                    if (newI == -1)
                        newI = jump(board, i, j, 1);
                    if (newI == board.size())
                        newI = jump(board, i, j, -1);
                    if (j < board[newI].second || j >= board[newI].first.size() + board[newI].second)
                        newI = jump(board, i, j, (dir >= 2 ? 1 : -1));
                    if (board[newI].first[j - board[newI].second] == '.')
                        i = newI;
                }
            }
        }
    }

    cout << (i+1) * 1000 + (j+1) * 4 + dir << endl;
}
