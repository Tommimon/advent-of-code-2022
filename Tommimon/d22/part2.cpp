#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include "py++.hpp"

using namespace std;
using namespace py;

int fSize;

vector<int> jump(const vector<pair<string, int>>& board, const vector<vector<int>>& division, const vector<vector<pair<int, int>>>& contacts, int i, int j, int dir) {
    int startFace = division[i / fSize][j / fSize];
    int onMyLeft;
    if (dir == 0)
        onMyLeft = i % fSize;
    else if (dir == 1)
        onMyLeft = fSize - 1 - (j % fSize);
    else if (dir == 2)
        onMyLeft = fSize - 1 - (i % fSize);
    else
        onMyLeft = j % fSize;

    int destinationFace = contacts[startFace][dir].first;
    int destinationDir = contacts[startFace][dir].second;
    int localI, localJ;
    if (destinationDir == 0) {
        localI = onMyLeft;
        localJ = 0;
    }
    else if (destinationDir == 1) {
        localI = 0;
        localJ = fSize - 1 - onMyLeft;
    }
    else if (destinationDir == 2) {
        localI = fSize - 1 - onMyLeft;
        localJ = fSize-1;
    }
    else {
        localI = fSize - 1;
        localJ = onMyLeft;
    }
    int globalI, globalJ;
    for (int k = 0; k < division.size(); ++k)
        for (int l = 0; l < division[k].size(); ++l)
            if (division[k][l] == destinationFace) {
                globalI = k * fSize + localI;
                globalJ = l * fSize + localJ;
            }

    return {globalI, globalJ, destinationDir};
}

int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    string mapInput = split(input, "\n\n")[0];
    string directions = split(input, "\n\n")[1];
    vector<string> lines(split(mapInput, "\n"));

    vector<vector<pair<int, int>>> contactsTest = {
            {{5, 2}, {3, 1}, {2, 1}, {1, 1}}, // first number is the target face and the second the arrival direction
            {{2, 0}, {4, 3}, {5, 3}, {0, 1}},
            {{3, 0}, {4, 0}, {1, 2}, {0, 0}},
            {{5, 1}, {4, 1}, {2, 2}, {0, 3}},
            {{5, 0}, {1, 3}, {2, 3}, {3, 3}},
            {{0, 2}, {1, 0}, {4, 2}, {3, 2}}
    };
    vector<vector<int>> divisionTest = {
            {-1, -1, 0, -1},
            {1, 2, 3, -1},
            {-1, -1, 4, 5}
    };
    vector<vector<pair<int, int>>> contactsInput{
            {{1, 0}, {2, 1}, {3, 0}, {5, 0}},
            {{4, 2}, {2, 2}, {0, 2}, {5, 3}},
            {{1, 3}, {4, 1}, {3, 1}, {0, 3}},
            {{4, 0}, {5, 1}, {0, 0}, {2, 0}},
            {{1, 2}, {5, 2}, {3, 2}, {2, 3}},
            {{4, 3}, {1, 1}, {0, 1}, {3, 3}}
    };
    vector<vector<int>> divisionInput = {
            {-1, 0, 1},
            {-1, 2, -1},
            {3, 4, -1},
            {5, -1, -1}
    };
    //vector<vector<pair<int, int>>>& contacts = contactsTest; vector<vector<int>>& division = divisionTest; fSize = 4;
    vector<vector<pair<int, int>>>& contacts = contactsInput; vector<vector<int>>& division = divisionInput; fSize = 50;

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
                int newI = i;
                int newJ = j;
                int newDir = dir;
                vector<int> newPos;
                if (dir % 2 == 0) {
                    newJ = j + (dir >= 2 ? -1 : 1);
                    if (newJ == board[i].first.size() + board[i].second || newJ == board[i].second-1) {
                        newPos = jump(board, division, contacts, i, j, dir);
                        newI = newPos[0];
                        newJ = newPos[1];
                        newDir = newPos[2];
                    }
                    if (board[newI].first[newJ - board[newI].second] == '.') {
                        i = newI;
                        j = newJ;
                        dir = newDir;
                    }
                }
                else {
                    newI = i + (dir >= 2 ? -1 : 1);
                    if (newI == -1 || newI == board.size() || j < board[newI].second || j >= board[newI].first.size() + board[newI].second) {
                        newPos = jump(board, division, contacts, i, j, dir);
                        newI = newPos[0];
                        newJ = newPos[1];
                        newDir = newPos[2];
                    }
                    if (board[newI].first[newJ - board[newI].second] == '.') {
                        i = newI;
                        j = newJ;
                        dir = newDir;
                    }
                }
            }
        }
    }

    cout << (i+1) * 1000 + (j+1) * 4 + dir << endl;
}
