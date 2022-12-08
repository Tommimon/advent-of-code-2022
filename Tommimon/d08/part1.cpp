#include <iostream>
#include <fstream>
#include <vector>
#include "py++.hpp"

using namespace std;

int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    vector<string> lines(split(input, "\n"));
    int res1 = 0;
    int l = lines[0].size();

    for (int k = 0; k < 4; ++k) {
        for (int i = 0; i < l; ++i) {
            int max = -1;
            for (int j = 0; j < l; ++j) {
                char *letter;
                int b;
                if (k < 2)
                    b = j;
                else
                    b = l-j-1;
                if (k%2 == 0)
                    letter = &lines[i][b];
                else
                    letter = &lines[b][i];
                int val;
                if (*letter >= '0' && *letter <= '9')
                    val = *letter - '0';
                else
                    val = *letter - 'A';
                if (val > max) {
                    max = val;
                    if (*letter >= '0' && *letter <= '9')
                        res1++;
                    *letter = val + 'A';
                }
            }
        }
    }

    cout << res1 << endl;
}
