#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "py++.hpp"

using namespace std;

typedef struct {
    string operation;
    int test;
    int ifTrue;
    int ifFalse;
    queue<long int> items;
    int counter = 0;
} Monkey;

int main() {
    ifstream ifs("input");
    string input((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    vector<string> blocks(split(input, "\n\n"));

    vector<Monkey> monkeys;
    monkeys.resize(blocks.size());

    for (int i = 0; i < blocks.size(); ++i) {
        string b = blocks[i];
        vector<string> lines(split(b, "\n"));
        vector<string> itemsStrings = split(lines[1].substr(18, lines[1].size()-18), ", ");
        for (auto item: itemsStrings)
            monkeys[i].items.push(stoi(item));

        monkeys[i].operation = lines[2].substr(23, lines[2].size()-23);
        monkeys[i].test = stoi(lines[3].substr(21, lines[3].size()-21));
        monkeys[i].ifTrue = stoi(lines[4].substr(29, lines[4].size()-29));
        monkeys[i].ifFalse = stoi(lines[5].substr(30, lines[5].size()-30));
    }

    for (int i = 0; i < 20; ++i) {
        for (auto &m: monkeys) {
            while (!m.items.empty()) {
                long int level = m.items.front();
                m.items.pop();

                string secondString = split(m.operation, " ")[1];
                long int secondNum = level;
                if (secondString != "old")
                    secondNum = stoi(secondString);
                if (m.operation[0] == '*')
                    level *= secondNum;
                else
                    level += secondNum;

                level /= 3;
                m.counter++;

                if (level % m.test == 0)
                    monkeys[m.ifTrue].items.push(level);
                else
                    monkeys[m.ifFalse].items.push(level);
            }
        }
    }

    int max1 = -1;
    int max2 = -2;
    for (auto m: monkeys) {
        if (m.counter > max2) {
            if (m.counter > max1) {
                max2 = max1;
                max1 = m.counter;
            }
            else
                max2 = m.counter;
        }
    }

    cout << max1 * max2 << endl;
}
