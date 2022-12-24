#include <iostream>
#include <fstream>
#include <vector>
#include "py++.hpp"

using namespace std;
using namespace py;

int sizeX, sizeY;
const string dirMap = ">v<^";
const vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {0, 0}};

int calcTime(vector<vector<vector<int>>>& blizzards, pair<int, int> entrance, pair<int, int> escape) {
    vector<vector<bool>> reachable(sizeY, vector<bool>(sizeX));
    int steps = 0;
    bool destination = false;
    while (!destination) {
        vector<vector<vector<int>>> tempB(sizeY, vector<vector<int>>(sizeX, vector<int>(0)));
        for (int i = 0; i < sizeY; ++i)
            for (int j = 0; j < sizeX; ++j)
                while (!blizzards[i][j].empty()) {
                    int b = blizzards[i][j][blizzards[i][j].size()-1];
                    int y = (i + directions[b].first) % sizeY;
                    int x = (j + directions[b].second) % sizeX;
                    if (y == -1) y = sizeY-1;
                    if (x == -1) x = sizeX-1;
                    tempB[y][x].push_back(b);
                    blizzards[i][j].pop_back();
                }
        blizzards = tempB;
        vector<vector<bool>> tempR(sizeY, vector<bool>(sizeX));
        if (blizzards[entrance.first][entrance.second].empty())
            tempR[entrance.first][entrance.second] = true;
        for (int i = 0; i < sizeY; ++i)
            for (int j = 0; j < sizeX; ++j)
                if (reachable[i][j])
                    for (auto d: directions) {
                        int y = i + d.first;
                        int x = j + d.second;
                        if (y >= 0 && y < sizeY && x >= 0 && x < sizeX && blizzards[y][x].empty())
                            tempR[y][x] = true;
                    }
        reachable = tempR;
        destination = reachable[escape.first][escape.second];
        steps++;
    }

    return steps;
}

int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    vector<string> lines(split(input, "\n"));
    sizeY = (int) lines.size()-2;
    sizeX = (int) lines[0].size()-2;

    vector<vector<vector<int>>> blizzards(sizeY, vector<vector<int>>(sizeX, vector<int>(0)));
    for (int i = 0; i < sizeY; ++i)
        for (int j = 0; j < sizeX; ++j)
            if (lines[i+1][j+1] != '.')
                blizzards[i][j].push_back((int) dirMap.find(lines[i + 1][j + 1]));

    int steps = calcTime(blizzards, {0, 0}, {sizeY-1, sizeX-1}) + 1;
    cout << steps << endl;
    steps += calcTime(blizzards, {sizeY-1, sizeX-1}, {0, 0});
    steps += calcTime(blizzards, {0, 0}, {sizeY-1, sizeX-1});
    cout << steps << endl;
}
