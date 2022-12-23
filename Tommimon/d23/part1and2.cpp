#include <iostream>
#include <fstream>
#include <vector>
#include "py++.hpp"

using namespace std;
using namespace py;

#define SIZE 200
int shift;

#define BLOCKED (-4)
#define CHOSEN (-3)
#define EMPTY (-2)
#define ELF (-1)
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3


int calcScore(vector<vector<int>>& grid) {
    int minX = SIZE, maxX = -1, minY = SIZE, maxY = -1;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (grid[i][j] == ELF) {
                if (i > maxY) maxY = i;
                if (i < minY) minY = i;
                if (j > maxX) maxX = j;
                if (j < minX) minX = j;
            }
        }
    }

    int score = 0;
    for (int i = minY; i <= maxY; ++i) {
        for (int j = minX; j <= maxX; ++j) {
            if (grid[i][j] == EMPTY)
                score++;
        }
    }
    return score;
}


int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    vector<string> lines(split(input, "\n"));
    shift = (SIZE - lines.size()) / 2;
    vector<vector<int>> grid (SIZE, vector<int>(SIZE));

    for (auto& r: grid) {
        for (auto& e: r) {
            e = EMPTY;
        }
    }

    for (int i = 0; i < lines.size(); ++i) {
        for (int j = 0; j < lines[i].size(); ++j) {
            if (lines[i][j] == '#')
                grid[i+shift][j+shift] = ELF;
        }
    }

    vector<vector<pair<int, int>>> neighbours = {
            {{-1, -1}, {-1, 0}, {-1, 1}},
            {{1, -1}, {1, 0}, {1, 1}},
            {{-1, -1}, {0, -1}, {1, -1}},
            {{-1, 1}, {0, 1}, {1, 1}}
    };

    int firstDir = UP;
    bool run = true;
    int round = 0;
    while (run) {
        run = false;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (grid[i][j] == ELF) {
                    bool move = false;
                    for (const auto& v: neighbours)
                        for (auto p: v)
                            if (grid[i+p.first][j+p.second] > EMPTY) {
                                move = true;
                                run = true;
                            }
                    if (move) {
                        int k = firstDir;
                        while (true) {
                            for (auto p: neighbours[k])
                                if (grid[i+p.first][j+p.second] > EMPTY)
                                    move = false;
                            if (move) {
                                grid[i][j] = k;
                                pair<int, int> p = neighbours[k][1];
                                if (grid[i+p.first][j+p.second] == EMPTY)
                                    grid[i + p.first][j + p.second] = CHOSEN;
                                else if (grid[i+p.first][j+p.second] == CHOSEN)
                                    grid[i+p.first][j+p.second] = BLOCKED;
                                break;
                            }
                            k = (k+1)%4;
                            if (k == firstDir)
                                break;
                            move = true;
                        }
                    }
                }
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (grid[i][j] >= UP) {
                    pair<int, int> p = neighbours[grid[i][j]][1];
                    if (grid[i+p.first][j+p.second] == CHOSEN) {
                        grid[i][j] = EMPTY;
                        grid[i+p.first][j+p.second] = ELF;
                    }
                }
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (grid[i][j] == BLOCKED)
                    grid[i][j] = EMPTY;
                if (grid[i][j] >= UP)
                    grid[i][j] = ELF;
                if (i == 0 || i == SIZE-1 || j == 0 || j == SIZE-1)
                    if (grid[i][j] == ELF)
                        cout << "Elf too close to border, please increase grid size and retry" << endl;
            }
        }
        firstDir = (firstDir+1)%4;
        round++;
        if (round == 10)
            cout << calcScore(grid) << endl;
    }

    cout << round << endl;
}
