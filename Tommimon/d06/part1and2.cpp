#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    int score1 = -1;
    int score2 = -1;
    string prev;
    for(int i = 0; i < input.size(); i++) {
        if (score1 == -1 && prev.size() == 4) {
            score1 = i;
        }
        if (score2 == -1 && prev.size() == 14) {
            score2 = i;
        }
        if (prev.contains(input[i])) {
            auto start = prev.find(input[i]) + 1;
            prev = prev.substr(start, prev.size() - start);
        }
        prev += input[i];
    }
    cout << score1 << endl;
    cout << score2 << endl;
}
