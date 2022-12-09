#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "py++.hpp"

using namespace std;

int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    vector<string> lines(split(input, "\n"));

    vector<int> knotsX, knotsY;
    set<int> history;
    int lengthArray[] = {2, 10};
    knotsX.resize(10);
    knotsY.resize(10);

    for (auto length: lengthArray) {
        history.clear();
        for (int i = 0; i < length; ++i) {
            knotsX[i] = 0;
            knotsY[i] = 0;
        }

        for (auto l: lines) {
            for (int j = 0; j < stoi(l.substr(2, l.size() - 2)); ++j) {
                if (l[0] == 'U') knotsY[0]++;
                if (l[0] == 'R') knotsX[0]++;
                if (l[0] == 'D') knotsY[0]--;
                if (l[0] == 'L') knotsX[0]--;

                for (int i = 1; i < length; ++i) {
                    int x = knotsX[i], y = knotsY[i], prevX = knotsX[i - 1], prevY = knotsY[i - 1];

                    if ((x - prevX) * (x - prevX) + (y - prevY) * (y - prevY) > 2) {
                        knotsX[i] = abs(prevX - x) <= 1 ? prevX : (prevX + x) / 2;
                        knotsY[i] = abs(prevY - y) <= 1 ? prevY : (prevY + y) / 2;
                    }
                }
                history.insert(knotsX[length - 1] * 10000 + knotsY[length - 1]);
            }
        }
        cout << history.size() << endl;
    }
}
