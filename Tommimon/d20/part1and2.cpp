#include <iostream>
#include <fstream>
#include <vector>
#include "py++.hpp"

using namespace std;
using namespace py;

#define KEY 811589153L

long int list_size;

long int pos(long int n) {
    if (n >= 0)
        return (n-1) % (list_size-1) + 1;
    return (n-list_size+2) % (list_size-1) + list_size - 2;
}

void mix(vector<pair<long int, long int>>& list) {
    for (int i = 0; i < list.size(); ++i) {
        long int start = list[i].second;
        long int end = pos(list[i].second + list[i].first);
        for (auto& e: list) {
            if (start < e.second && e.second <= end)
                e.second = pos(e.second - 1);
            if (end <= e.second && e.second < start)
                e.second = pos(e.second + 1);
        }
        list[i].second = end;
    }
}

long int coordinates(const vector<pair<long int, long int>>  & list) {
    long int score = 0;
    long int zero;
    for (auto e: list)
        if (e.first == 0)
            zero = e.second;

    for (auto e: list)
        if (e.second == (zero + 1000)%list_size || e.second == (zero + 2000)%list_size || e.second == (zero + 3000)%list_size)
            score += e.first;

    return score;
}

int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    vector<string> lines(split(input, "\n"));
    list_size = lines.size();
    vector<pair<long int, long int>> list1;
    vector<pair<long int, long int>> list2;

    for (int i = 0; i < lines.size(); ++i) {
        list1.emplace_back(stoi(lines[i]), i);
        list2.emplace_back(KEY * stoi(lines[i]), i);
    }

    mix(list1);
    for (int i = 0; i < 10; ++i) {
        mix(list2);
    }

    cout << coordinates(list1) << endl;
    cout << coordinates(list2) << endl;
}
