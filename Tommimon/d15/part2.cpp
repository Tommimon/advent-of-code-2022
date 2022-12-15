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

    int maxX = 4000000;
    int maxY = 4000000;
    for (int y = 0; y <= maxY; ++y) {
        for (int x = 0; x <= maxX; x++) {
            bool can = true;
            for (auto s: sensors) {
                if (abs(x - s.sX) + abs(y - s.sY) <= s.dist) {
                    can = false;
                    x = s.sX + (s.dist - abs(y-s.sY));
                    break;
                }
            }
            if (can)
                cout << (long) x * 4000000 + y << endl;
        }
    }
}
