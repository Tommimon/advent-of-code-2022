#include <iostream>
#include <fstream>
#include <vector>
#include "py++.hpp"

using namespace std;

int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    vector<string> lines(split(input, "\n"));
    int score1 = 0;
    int score2 = 0;
    for(auto l: lines) {
        vector<int> nums = map<std::string, int>([](string s) { return stoi(s); }, split(replace(l, ",", "-"), "-"));
        score1 += ((nums[2] >= nums[0] && nums[3] <= nums[1]) || (nums[2] <= nums[0] && nums[3] >= nums[1]));
        score2 += ((nums[2] >= nums[0] && nums[2] <= nums[1]) || (nums[0] >= nums[2] && nums[0] <= nums[3]));
    }
    cout << score1 << endl;
    cout << score2 << endl;
}
