#include <iostream>
#include <fstream>
#include <cstdio>
#define INPUT "./Gonduls/d05/input.txt"
#define STACK_N 9
#define MAX_CRATES 50
using namespace std;

int indexMod(int index){
    return index >= 0 ? index >= MAX_CRATES ? index - MAX_CRATES : index : index + MAX_CRATES;
}

int main(){
	char letter;
	ifstream input(INPUT);
    int starts[STACK_N], ends[STACK_N];
    char stacks[STACK_N][MAX_CRATES];
    FILE * file = fopen(INPUT, "r");

    // initialization
    for(int i = 0; i < STACK_N; i++){
        starts[i] = 0;
        ends[i] = 0;
    }

    // input parse
    int letterNum = -1;
	while (fscanf(file, "%c", &letter)){
        letterNum ++;
		if (letter == ' ' || letter == '[' || letter == ']')
            continue;
        if (letter == '\n'){
            letterNum = -1;
            continue;
        }
        if (letterNum % 4 == 1){
            int stack = (int) (letterNum - 1) / 4;
            if(letter <= 'Z' && letter >= 'A'){
                stacks[stack][starts[stack]] = letter;
                starts[stack] = indexMod(starts[stack] - 1);
            }
            else if (letter == '0' + STACK_N)
                break;
        }
    }

    fscanf(file, "%c", &letter);
    fscanf(file, "%c", &letter);
    fscanf(file, "%c", &letter);

    int a, b, c;
    
    while(fscanf(file, "move %d from %d to %d\n", &a, &b, &c) != EOF){
        b--; c--;
        for(int i = 0; i < a; i++){
            letter = stacks[b][ends[b]];
            ends[b] = indexMod(ends[b] - 1);
            ends[c] = indexMod(ends[c] + 1);
            stacks[c][ends[c]] = letter;
        }
    }
    cout << "result part 1: ";
    for(int i  = 0; i< STACK_N; i++)
        cout << stacks[i][ends[i]];
    cout << endl;
}