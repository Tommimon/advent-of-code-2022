#include <iostream>
#include <fstream>
#include <vector>
#include "py++.hpp"

using namespace std;

int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    vector<string> lines(split(input, "\n"));

    int width = lines[0].size();
    int height = lines.size();
    int distance[height][width];

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (lines[i][j] == 'E') {
                distance[i][j] = 0;
                lines[i][j] = 'Z';
            }
            else
                distance[i][j] = -1;

            if (lines[i][j] == 'S')
                lines[i][j] = 'A';
        }
    }


    int result1 = -1;
    int result2 = -1;
    int step = 0;
    while (result1 == -1) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (distance[i][j] == step) {
                    if (lines[i][j] == 'A')
                        result1 = step;
                    if (tolower(lines[i][j]) == 'a' && result2 == -1)
                        result2 = step;
                    if (i > 0 && distance[i-1][j] == -1 && tolower(lines[i-1][j]) >= tolower(lines[i][j]-1))
                        distance[i-1][j] = step+1;
                    if (j > 0 && distance[i][j-1] == -1 && tolower(lines[i][j-1]) >= tolower(lines[i][j]-1))
                        distance[i][j-1] = step+1;
                    if (i < height - 1 && distance[i + 1][j] == -1 && tolower(lines[i+1][j]) >= tolower(lines[i][j]-1))
                        distance[i+1][j] = step+1;
                    if (j < width - 1 && distance[i][j + 1] == -1 && tolower(lines[i][j+1]) >= tolower(lines[i][j]-1))
                        distance[i][j+1] = step+1;
                }
            }
        }
        step++;
    }

    cout << result1 << endl;
    cout << result2 << endl;
}
