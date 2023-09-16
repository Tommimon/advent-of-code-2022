#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#define INPUT "./Gonduls/d10/input.txt"
using namespace std;

bool checkPosition(int cycle, int x){
    return (cycle == x || cycle == x-1 || cycle == x+1);
}

int main(){
    ifstream file(INPUT);
    int reg = 1, cycle = 0, row, col;
    string word;
    char matrix[6][40];

    while(file >> word){

        row = cycle / 40;
        col = cycle % 40;

        if(word == "addx"){
            matrix[row][col] = checkPosition(cycle % 40, reg) ? '#' : ' ';
            cycle ++;
            row = cycle / 40;
            col = cycle % 40;
            matrix[row][col] = checkPosition(cycle % 40, reg) ? '#' : ' ';
            cycle ++;
        }
        else if(word == "noop"){
            matrix[row][col] = checkPosition(cycle % 40, reg) ? '#' : ' ';
            cycle ++;
        }
        else
            reg += stoi(word);
    }

    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 40; j++){
            cout << matrix[i][j];
        }
        cout << endl;
    }
    return 0;
}