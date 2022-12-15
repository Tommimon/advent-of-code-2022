#include <iostream>
#include <fstream>
#include <vector>
#include "py++.hpp"

using namespace std;

class Sensor {
public:
    int sX, sY, bX, bY, dist;
    explicit Sensor(string &line) {
        sX = stoi(split(split(line, "x=")[1], ",")[0]);
        sY = stoi(split(split(line, "y=")[1], ":")[0]);
        bX = stoi(split(split(line, "x=")[2], ",")[0]);
        bY = stoi(split(split(line, "y=")[2], " ")[0]);
        dist = abs(sX-bX) + abs(sY-bY);
    }
};

int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    int startY = 2000000;
    vector<string> lines(split(input, "\n"));
    vector<Sensor> sensors = map<string, Sensor>([](string s) {return Sensor(s);}, lines);

    int minX = 9999999;
    int maxX = 0;
    for (auto s: sensors) {
        int beginX = s.sX - (s.dist - abs(startY-s.sY)) - 1;
        int endX = s.sX + (s.dist - abs(startY-s.sY)) + 1;
        if (beginX < minX)
            minX = beginX;
        if (endX > maxX)
            maxX = endX;
    }

    int score1 = 0;
    int y = startY;
    for (int x = minX; x <= maxX; x++) {
        bool can = true;
        for (auto s: sensors) {
            if (x == s.bX && y == s.bY) {
                can = true;
                break;
            }
            if (abs(x-s.sX) + abs(y-s.sY) <= s.dist)
                can = false;
        }
        if (!can)
            score1++;
    }

    cout << score1 << endl;
}
