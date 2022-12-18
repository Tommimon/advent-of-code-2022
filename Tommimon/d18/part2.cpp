#include <iostream>
#include <fstream>
#include <vector>
#include "py++.hpp"

using namespace std;
using namespace py;

#define GRID_SIZE 25

#define AIR 1
#define ROCK 2
#define SHIFT 1

int countExtern (int startX, int startY, int startZ, int grid[GRID_SIZE][GRID_SIZE][GRID_SIZE]) {
    vector<vector<int>> close = {
            {0, 0, 1},
            {0, 0, -1},
            {0, 1, 0},
            {0, -1, 0},
            {1, 0, 0},
            {-1, 0, 0},
    };
    int count = 0;

    for (auto c: close) {
        int x = startX + c[0];
        int y = startY + c[1];
        int z = startZ + c[2];

        if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE && z >= 0 && z < GRID_SIZE) {
            if (grid[x][y][z] > 0) {
                if (grid[x][y][z] == ROCK) {
                    count++;
                } else {
                    grid[x][y][z] *= -1;
                    count += countExtern(x, y, z, grid);
                }
            }
        }
    }

    return count;
}


int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));
    int grid[GRID_SIZE][GRID_SIZE][GRID_SIZE];

    for (auto & i : grid)
        for (auto & j : i)
            for (int & k : j)
                k = AIR;

    vector<string> lines(split(input, "\n"));

    for (const auto& l: lines) {
        vector<string> coords = split(l, ",");
        grid[stoi(coords[0])+SHIFT][stoi(coords[1])+SHIFT][stoi(coords[2])+SHIFT] = ROCK;
    }

    int res = countExtern(0, 0, 0, grid);

    cout << res << endl;
}
