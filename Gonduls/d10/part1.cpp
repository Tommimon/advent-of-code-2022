#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#define INPUT "./Gonduls/d10/input.txt"
using namespace std;

bool checkCycle(int cycle){
    return ((cycle - 20)%40 == 0);
}

int main(){
    ifstream file(INPUT);
    int reg = 1, result = 0, cycle = 0;
    bool check;
    string word;

    while(file >> word){
        check = false;

        if(word == "addx"){
            cycle += 2;
            check = checkCycle((cycle / 2) * 2);
        }
        else if(word == "noop"){
            cycle += 1;
            check = checkCycle(cycle);
        }
        else
            reg += stoi(word);
        

        if(check)
            result += reg * (cycle / 2) * 2;
    }
    cout << "Result part 1: " << result << endl;
    return 0;
}