#include <iostream>
#include <fstream>
#include <vector>
#include "py++.hpp"

using namespace std;

int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    vector<string> lines(split(input, "\n"));
    int maxY = 0;
    for (auto l: lines) {
        for (int i = 0; i < l.size(); ++i) {
            if (l[i] == ',') {
                string yStr = split(l.substr(i+1, l.size()-i-1), " ")[0];
                int y = stoi(yStr);
                if (y > maxY)
                    maxY = y;
            }
        }
    }
    lines.push_back("0," + to_string(maxY+2) + " -> 999," + to_string(maxY+2));

    int matrix_size = 1000;
    char matrix[matrix_size][matrix_size];
    for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
            matrix[i][j] = '.';
        }
    }

    for (auto l : lines) {
        vector<string> points = split(l, " -> ");
        for (int j = 0; j < points.size() - 1; ++j) {
            int startX = stoi(split(points[j], ",")[0]);
            int startY = stoi(split(points[j], ",")[1]);
            int endX = stoi(split(points[j+1], ",")[0]);
            int endY = stoi(split(points[j+1], ",")[1]);
            if (startX > endX) {
                int t = startX;
                startX = endX;
                endX = t;
            }
            if (startY > endY) {
                int t = startY;
                startY = endY;
                endY = t;
            }
            for (int x = startX; x <= endX; ++x) {
                for (int y = startY; y <= endY; ++y) {
                    matrix[x][y] = '#';
                }
            }
        }
    }

    int score = 0;
    bool blocked = false;
    bool dropped = false;
    while (matrix[500][0] == '.') {
        int x = 500, y = -1;
        while (!blocked) {
            if (matrix[x][y+1] == '.')
                y++;
            else if (matrix[x-1][y+1] == '.') {
                y++;
                x--;
            }
            else if (matrix[x+1][y+1] == '.') {
                y++;
                x++;
            }
            else {
                blocked = true;
            }
            if (!dropped && y > maxY) {
                dropped = true;
                cout << score << endl;
            }
        }
        blocked = false;
        matrix[x][y] = 'o';
        score++;
    }

    cout << score << endl;
}
