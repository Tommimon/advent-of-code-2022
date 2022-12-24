#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include "py++.hpp"

using namespace std;
using namespace py;

int fSize = INT32_MAX;

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

void rotateFace(const vector<vector<int>>& division, vector<vector<pair<int, int>>>& contacts, int f, int tar, int finalDir) {
    int currDir;
    for (int i = 0; i < contacts[f].size(); i++) {
        if (contacts[f][i].first == tar)
            currDir = i;
    }

    while (currDir != finalDir) {
        currDir = (currDir+1)%4;
        pair<int, int> t = contacts[f][3];
        contacts[f][3] = contacts[f][2];
        contacts[f][2] = contacts[f][1];
        contacts[f][1] = contacts[f][0];
        contacts[f][0] = t;
        for (int i = 0; i < contacts.size(); ++i) {
            for (int j = 0; j < contacts[i].size(); ++j) {
                if (contacts[i][j].first == f)
                    contacts[i][j].second = (contacts[i][j].second+1) % 4;
            }
        }
    }
    return;
}

int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    string mapInput = split(input, "\n\n")[0];
    string directions = split(input, "\n\n")[1];
    vector<string> lines(split(mapInput, "\n"));

    vector<vector<pair<int, int>>> contacts { // contacts for the standard cross unfolded cube
            {{3, 1}, {2, 1}, {1, 1}, {5, 3}},
            {{2, 0}, {4, 0}, {5, 0}, {0, 0}},
            {{3, 0}, {4, 1}, {1, 2}, {0, 3}},
            {{5, 2}, {4, 2}, {2, 2}, {0, 2}},
            {{3, 3}, {5, 1}, {1, 3}, {2, 3}},
            {{3, 2}, {0, 1}, {1, 0}, {4, 3}}
    };

    vector<pair<string, int>> board = py::map<string, pair<string, int>>([](const string& s){
        int spaces = 0;
        for (auto i : s) {
            if (i != ' ')
                break;
            spaces++;
        }
        return make_pair(s.substr(spaces, s.size()-spaces), spaces);
    }, lines);

    int width = 0;
    for (const auto& r: board) {
        if (r.first.size() < fSize)
            fSize = r.first.size();
        if (r.first.size() + r.second > width)
            width = r.first.size() + r.second;
    }

    vector<vector<int>> division;
    int faceCounter = 0;
    for (int i = 0; i < board.size() / fSize; ++i) {
        division.emplace_back();
        for (int j = 0; j < width / fSize; ++j) {
            if (j * fSize < board[i*fSize].second || j * fSize >= board[i*fSize].first.size() + board[i*fSize].second)
                division[i].push_back(-1);
            else {
                division[i].push_back(faceCounter);
                faceCounter++;
            }
        }
    }

    vector<int> faceMapping = {0, -1, -1, -1, -1, -1};
    bool modified = true;
    while (modified) {
        modified = false;
        for (int k = 0; k < faceMapping.size(); ++k) {
            int f = faceMapping[k];
            if (f == -1)
                continue;
            for (int i = 0; i < division.size(); ++i) {
                for (int j = 0; j < division[i].size(); ++j) {
                    if (division[i][j] == f) {
                        if (j < division[i].size()-1 && division[i][j+1] != -1)
                            if (faceMapping[contacts[k][0].first] == -1) {
                                faceMapping[contacts[k][0].first] = division[i][j + 1];
                                modified = true;
                                rotateFace(division, contacts, contacts[k][0].first, k, 2);
                            }
                        if (i < division.size()-1 && division[i+1][j] != -1)
                            if (faceMapping[contacts[k][1].first] == -1) {
                                faceMapping[contacts[k][1].first] = division[i+1][j];
                                modified = true;
                                rotateFace(division, contacts, contacts[k][1].first, k, 3);
                            }
                        if (j > 0 && division[i][j-1] != -1)
                            if (faceMapping[contacts[k][2].first] == -1) {
                                faceMapping[contacts[k][2].first] = division[i][j-1];
                                modified = true;
                                rotateFace(division, contacts, contacts[k][2].first, k, 0);
                            }
                        if (i > 0 && division[i-1][j] != -1)
                            if (faceMapping[contacts[k][3].first] == -1) {
                                faceMapping[contacts[k][3].first] = division[i-1][j];
                                modified = true;
                                rotateFace(division, contacts, contacts[k][3].first, k, 1);
                            }
                    }
                }
            }
        }
    }

    for (auto & r : contacts)
        for (auto & e : r)
            e.first = faceMapping[e.first];

    vector<vector<pair<int, int>>> temp = contacts;
    for (int i = 0; i < contacts.size(); ++i)
        temp[faceMapping[i]] = contacts[i];
    contacts = temp;

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
