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
    int rope[10][2];

    for(int i = 0; i < 10; i++){
        rope[i][0] = 0;
        rope[i][1] = 0;
    }

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
            rope[0][0] += x;
            rope[0][1] += y;

            for(int j = 1; j < 10; j++)
                adjust(rope[j-1], rope[j]);

            // 10000 * x + y is enough of a hash function for this problem
            positions.insert(10000*rope[9][0] + rope[9][1]);
        }
    }
    cout << "Result part 2: " << positions.size() << endl;
}

void adjust(int *H, int *T){
    // x and y = how many steps away from H is T in a direction
    int x = T[0] - H[0];    // horizontally
    int y = T[1] - H[1];    // vertically

    if((x > 1 || x < -1) && (y > 1 || y < -1)){
        // edge case not present in part 1:
        // if a knot is diagonally 2 steps away: 
        // just move one step diagonally and end up diagonally adjacent.
        // taken care of by istructions after ifs
    }
    // if T is horizontally two steps away from H, but not also vertically:
    // T ends vertically alligned with H 
    else if (x > 1 || x < -1){
        y = 0;
    }
    // like before, swap horizontally with vertically
    else if (y > 1 || y < -1){
        x = 0;
    }

    // at the end only values -1, 0, 1 allowed for x and y
    x = (x > 1 || x < -1) ? x/2 : x;
    y = (y > 1 || y < -1) ? y/2 : y;

    T[0] = H[0] + x;
    T[1] = H[1] + y;
}