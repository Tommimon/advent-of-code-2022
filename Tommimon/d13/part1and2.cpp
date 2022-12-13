#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "py++.hpp"

using namespace std;

int compareArrays(char** string1, char** string2, int* counter) {
    int depth = 0;
    do {
        if (**string1 != **string2) {
            if (**string1 == ']')
                return 1;
            if (**string2 == ']')
                return -1;
            if (**string1 == '[') {
                char alias[strlen(*string2)+3];
                alias[0] = '[';
                alias[1] = **string2;
                alias[2] = ']';
                strcpy(alias+3, (*string2)+1);
                char* pAlias = alias;
                int subCounter = 0;
                int res = compareArrays(string1, &pAlias, &subCounter);
                if (res == 1)
                    return 1;
                if (res == -1)
                    return -1;
                subCounter -= 2;
                (*string2) += subCounter;
            }
            else if (**string2 == '[') {
                char alias[strlen(*string1)+3];
                alias[0] = '[';
                alias[1] = **string1;
                alias[2] = ']';
                strcpy(alias+3, (*string1)+1);
                char* pAlias = alias;
                int subCounter = 0;
                int res = compareArrays(&pAlias, string2, &subCounter);
                if (res == 1)
                    return 1;
                if (res == -1)
                    return -1;
                subCounter -= 2;
                (*string1) += subCounter;
            }
            else {
                return **string1 < **string2 ? 1 : -1;
            }
        }

        if (**string1 == '[' || **string2 == '[')
            depth++;
        if (**string1 == ']' || **string2 == ']')
            depth--;

        (*string1)++;
        (*string2)++;
        (*counter)++;
    } while (depth > 0);
    return 0;
}

bool compareStrings(const string& s1, const string& s2) {
    char buffer1[500], buffer2[500];
    strcpy(buffer1, s1.c_str());
    strcpy(buffer2, s2.c_str());
    char *p1 = buffer1, *p2 = buffer2;
    int counter = 0;
    return compareArrays(&p1, &p2, &counter) != -1;
}

int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));
    input = replace(input, "10", "A");

    vector<string> packets(split(input, "\n\n"));
    int score1 = 0;
    for (int i=0; i<packets.size(); ++i)
        if (compareStrings(split(packets[i], "\n")[0], split(packets[i], "\n")[1]))
            score1 += i+1;
    cout << score1 << endl;

    input = replace(input, "\n\n", "\n") + "[[2]]\n[[6]]";
    vector<string> lines(split(input,"\n"));
    std::sort(lines.begin(), lines.end(), [](const string &s1, const string &s2) {return compareStrings(s1, s2);});
    auto pos1 = std::find_if(lines.begin(), lines.end(), [&](const auto &item) {return item == "[[2]]";});
    auto pos2 = std::find_if(lines.begin(), lines.end(), [&](const auto &item) {return item == "[[6]]";});
    cout << (pos1 - lines.begin() + 1) * (pos2 - lines.begin() + 1) << endl;
}
