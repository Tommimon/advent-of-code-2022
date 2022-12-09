#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#define INPUT "./Gonduls/d09/input.txt"
using namespace std;

void adjust(int *H, int *T);

int main(){
    ifstream file(INPUT);
    char direction;
    int steps;
    int H[2], T[2];
    H[0] = 0; H[1] = 0; T[0] = 0; T[1] = 0;

    set<int> positions;

    while(file >> direction >> steps){
        
        int x = 0, y = 0;
        switch (direction){
            case 'U':
                y++;
                break;    
            case 'D':
                y--;
                break;    
            case 'L':
                x--;
                break;    
            case 'R':
                x++;
                break;
        }
        
        for(int i = 0; i < steps; i++){
            H[0] += x;
            H[1] += y;

            adjust(H, T);

            // 10000 * x + y is enough of a hash function for this problem
            positions.insert(10000*T[0] + T[1]);
        }
    }
    cout << "Result part 1: " << positions.size() << endl;
}

void adjust(int *H, int *T){
    // x and y = how many steps away from H is T in a direction
    int x = T[0] - H[0];
    int y = T[1] - H[1];

    // missing edge case where H is diagonally 2 steps away from T

    // if T is horizontally two steps away from H:
    // T ends vertically alligned with H 
    if (x > 1 || x < -1){
        y = 0;
    } 
    // like before, swap horizontally with vertically
    if (y > 1 || y < -1){
        x = 0;
    }

    // at the end only values -1, 0, 1 allowed for x and y
    x = (x > 1 || x < -1) ? x/2 : x;
    y = (y > 1 || y < -1) ? y/2 : y;

    T[0] = H[0] + x;
    T[1] = H[1] + y;
}