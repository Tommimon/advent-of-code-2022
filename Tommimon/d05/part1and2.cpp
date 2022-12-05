#include <iostream>
#include <fstream>
#include <vector>
#include "py++.hpp"

using namespace std;

int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    vector<string> lines(split(input, "\n"));
    auto separator = std::find_if(lines.begin(), lines.end(), [&](const auto &item) {
        return item == "";
    });

    vector<string> nums = split(*(separator-1), "   ");
    vector<vector<char>> stacks1, stacks2;
    stacks1.resize(nums.size());
    stacks2.resize(nums.size());
    for (auto i = separator-2; i >= lines.begin(); i--) {
        for (int j = 0; j < stacks1.size(); ++j) {
            if ((*i).length() > j*4) {
                char c = (*i).substr(j * 4 + 1, 1)[0];
                if (c != ' ') {
                    stacks1[j].push_back(c);
                    stacks2[j].push_back(c);
                }
            }
        }
    }

    for (auto i = separator+1; i < lines.end(); i++) {
        int count = stoi(split(split(*i, " from ")[0], "move ")[1]);
        int from = stoi(split(split(*i, " from ")[1], " to ")[0])-1;
        int to = stoi(split(split(*i, " from ")[1], " to ")[1])-1;
        for (int j = 0; j < count; ++j) {
            stacks1[to].push_back(stacks1[from][stacks1[from].size() - 1]);
            stacks1[from].erase(stacks1[from].end() - 1);
        }
    }

    for (auto s: stacks1)
        cout << s[s.size()-1];
    cout << endl;

    for (auto i = separator+1; i < lines.end(); i++) {
        int count = stoi(split(split(*i, " from ")[0], "move ")[1]);
        int from = stoi(split(split(*i, " from ")[1], " to ")[0])-1;
        int to = stoi(split(split(*i, " from ")[1], " to ")[1])-1;
        for (int j = 0; j < count; ++j) {
            stacks2[to].push_back(stacks2[from][stacks2[from].size() - (count-j)]);
            stacks2[from].erase(stacks2[from].end() - (count - j));
        }
    }

    for (auto s: stacks2)
        cout << s[s.size()-1];
    cout << endl;
}
