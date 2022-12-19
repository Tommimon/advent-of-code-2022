#include <iostream>
#include <fstream>
#include <vector>
#include "py++.hpp"

using namespace std;
using namespace py;

#define SIZE 4
#define GEODE 3

int mostGeodes(const vector<vector<int>>& costs, vector<int> robots, const vector<int>& res, int timeLeft, vector<bool>& needs) {
    int max = 0, geodes;
    for (int choice = SIZE-1; choice >= -1; --choice) {
        geodes = robots[GEODE] * timeLeft;
        if (choice >= 0) {
            if (!needs[choice]) continue;
            int timeNeeded = 1;
            int missing = -1;
            for (int i = 0; i < SIZE; ++i) {
                int wait = robots[i] == 0 ? timeLeft * costs[choice][i] : (costs[choice][i] - res[i] + (robots[i]-1)) / robots[i] + 1;
                if (wait > timeNeeded) {
                    timeNeeded = wait;
                    missing = i;
                }
            }
            if (missing != -1) needs[missing] = true;
            if (timeNeeded >= timeLeft) continue;
            vector<int> newRes;
            for (int i = 0; i < SIZE; ++i)
                newRes.push_back(res[i] + robots[i] * timeNeeded - costs[choice][i]);
            geodes = newRes[GEODE] - res[GEODE];
            vector<bool> childNeeds = {false, false, false, true};
            robots[choice]++;
            geodes += mostGeodes(costs, robots, newRes, timeLeft-timeNeeded, childNeeds);
            robots[choice]--;
            for (int i = 0; i < SIZE; ++i)
                if (childNeeds[i]) needs[i] = true;
        }
        if (geodes > max) max = geodes;
    }
    return max;
}

int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    vector<vector<vector<int>>> costs;
    vector<string> lines(split(input, "\n"));
    int score1 = 0;
    int score2 = 1;

    for (int i = 0; i < lines.size(); ++i) {
        string l = lines[i];
        costs.emplace_back();
        costs[i].push_back({stoi(split(split(l, "costs ")[1], " ")[0]), 0, 0, 0});
        costs[i].push_back({stoi(split(split(l, "costs ")[2], " ")[0]), 0, 0, 0});
        costs[i].push_back({stoi(split(split(l, "costs ")[3], " ")[0]), stoi(split(split(l, "and ")[1], " ")[0]), 0, 0});
        costs[i].push_back({stoi(split(split(l, "costs ")[4], " ")[0]), 0, stoi(split(split(l, "and ")[2], " ")[0]), 0});
    }

    for (int i = 0; i < costs.size(); ++i) {
        vector<int> robots = {1, 0, 0, 0};
        vector<int> res = {0, 0, 0, 0};
        vector<bool> needs = {false, false, false, true};
        score1 += (i+1) * mostGeodes(costs[i], robots, res, 24, needs);
    }

    for (int i = 0; i < 3; ++i) {
        vector<int> robots = {1, 0, 0, 0};
        vector<int> res = {0, 0, 0, 0};
        vector<bool> needs = {false, false, false, true};
        score2 *= mostGeodes(costs[i], robots, res, 32, needs);
    }

    cout << score1 << endl;
    cout << score2 << endl;
}
