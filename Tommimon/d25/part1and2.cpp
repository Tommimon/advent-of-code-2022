#include <iostream>
#include <fstream>
#include <vector>
#include "py++.hpp"

using namespace std;
using namespace py;

const string digits = "=-012";

int digitToNum (char d) {
    return digits.find(d)-2;
}

char numToDigit (int n) {
    return digits[n+2];
}

const int space = 25;

int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    vector<string> lines(split(input, "\n"));
    vector<vector<int>> nums = py::map<string, vector<int>>([](string s){
        vector<int> n(space, 0);
        for (int i = 1; i <= s.size(); ++i)
            n[space-i] = digitToNum(s[s.size()-i]);
        return n;
    }, lines);


    vector<int> total(space, 0);

    for (auto n: nums) {
        for (int i = 0; i < space; ++i)
            total[i] += n[i];
        for (int i = space-1; i >= 1; --i) {
            if (total[i] > 2) {
                total[i] -= 5;
                total[i-1]++;
            }
            else if (total[i] < -2) {
                total[i] += 5;
                total[i-1]--;
            }
        }
    }

    bool firstNotZero = false;
    for (auto n: total)
        if (firstNotZero || n != 0){
            firstNotZero = true;
            cout << numToDigit(n);
        }
    cout << endl;
}
