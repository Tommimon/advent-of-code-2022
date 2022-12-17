#include <iostream>
#include <fstream>
#include <vector>
#include "py++.hpp"

using namespace std;
using namespace py;

#define ROCK_NUM 2022

const int h = ROCK_NUM*100+10;

bool collision(char grid[h][7], vector<string> rock, int x, int y) {
    for (int i = 0; i < rock.size(); ++i) {
        for (int j = 0; j < rock[i].length(); ++j) {
            if (x + j < 0 || x + j >= 7 || y + i < 0 || y + i >= h)
                return true;
            if (rock[i][j] == '#' && grid[y + i][x + j] == '#')
                return true;
        }
    }
    return false;
}

int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));
    input = replace(input, "\n", "");

    vector<vector<string>> rocks_list = {{"####"}, {".#.", "###", ".#."}, {"..#", "..#", "###"}, {"#", "#", "#", "#"}, {"##", "##"}};

    vector<string> history;

    char grid[h][7];
    for (auto & r : grid)
        for (char & e : r)
            e = '.';

    int top = h;
    int j = 0;
    long int target = 1000000000000;
    long int bias = 0;
    int streak = 0;
    int streak_offset = -1;
    for (int i = 0; i < ROCK_NUM || i < target; ++i) {
        vector<string> rock = rocks_list[i % rocks_list.size()];

        bool falling = true;
        int x = 2;
        int y = top - 3 - rock.size();
        if (y < 0) {
            printf("Grid overflow");
            return 0;
        }
        while (falling) {
            x += input[j] == '>' ? 1 : -1;
            if (collision(grid, rock, x, y))
                x -= input[j] == '>' ? 1 : -1;
            y++;
            if (collision(grid, rock, x, y)) {
                y--;

                if (bias == 0) {
                    string record =
                            "i" + to_string(i % rocks_list.size()) + "j" + to_string(j) + "x" + to_string(x) + "y" +
                            to_string(top - y) + "t" +
                            to_string(top);
                    for (int k = 0; k < history.size(); ++k) {
                        if (split(history[k], "t")[0] == split(record, "t")[0]) {
                            bool inStreak = true;
                            for (int l = 1; l < 10; ++l) {
                                if (split(history[k-l], "t")[0] != split(history[i-l], "t")[0]) {
                                    inStreak = false;
                                    break;
                                }
                            }
                            if (inStreak) {
                                int deltaI = i - k;
                                int deltaT = stoi(split(history[k], "t")[1]) - top;
                                long int q = (target - i) / deltaI - 1;
                                target = target - (deltaI * q);
                                bias = deltaT * q;
                            }
                        }
                    }
                    history.push_back(record);
                }

                if (y < top)
                    top = y;
                falling = false;
                for (int k = 0; k < rock.size(); ++k)
                    for (int l = 0; l < rock[k].length(); ++l)
                        if (rock[k][l] == '#')
                            grid[y + k][x + l] = '#';
            }
            j = (j+1) % input.length();
        }
        if  (i == ROCK_NUM-1)
            cout << h-top << endl;
        if (i == target-1)
            cout << bias+h-top << endl;
    }
}
