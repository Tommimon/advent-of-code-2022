#include <iostream>
#include <fstream>
#include <vector>
#include "py++.hpp"

using namespace std;

int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    vector<string> lines(split(input, "\n"));
    int l = lines[0].size();

    int maxScore = -1;
    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < l; ++j) {
            int sceneScore = 1;
            for (int k = 0; k < 4; ++k) {
                int lineScore = 0;
                int startTree = lines[i][j] - '0';
                for (int iter = 1; iter < l; ++iter) {
                    char letter;
                    int iterAlias;
                    if (k < 2)
                        iterAlias = iter;
                    else
                        iterAlias = -iter;
                    if (k%2 == 0)
                        if (j + iterAlias < 0 || j + iterAlias >= l)
                            break;
                        else
                            letter = lines[i][j + iterAlias];
                    else
                        if (i + iterAlias < 0 || i + iterAlias >= l)
                            break;
                        else
                            letter = lines[i + iterAlias][j];
                    int val = letter - '0';
                    lineScore++;
                    if (val >= startTree) {
                        break;
                    }
                }
                sceneScore *= lineScore;
            }

            if (sceneScore > maxScore) {
                maxScore = sceneScore;
            }
        }
    }

    cout << maxScore << endl;
}
