#include <iostream>
#include <fstream>
#include <string>
#define INPUT "./Gonduls/d02/input.txt"
using namespace std;

int main() { 
    ifstream file(INPUT);
    string str; 
    int result1 = 0, result2 = 0;
    while (getline(file, str)){
        int sec = str[2] - 'X' + 1;     // x=1, y=2, z=3
        int first = str[0] - 'A' + 1;   // a=1, b=2, c=3

        // part 1
        result1 += sec;
        if (first == sec)
            result1 += 3;
        else if (sec == first +1 or sec == first -2)
            result1 += 6;

        // part 2
        result2 += (sec - 1) * 3;
        int toAdd = 0;
        switch (sec){
        case 1: //lost
            toAdd = first - 1;
            toAdd = toAdd > 0 ? toAdd : toAdd +3;
            break;
        case 2: //tied
            toAdd = first;
            break;
        case 3: //won
            toAdd = first + 1;
            toAdd = toAdd < 4 ? toAdd : toAdd  -3;
            break;
        }
        result2 += toAdd;
    }
    cout << "Result part1 = " << result1 << endl;
    cout << "Result part2 = " << result2 << endl;
}