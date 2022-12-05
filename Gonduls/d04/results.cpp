#include <iostream>
#include <fstream>
#include <string>
#define INPUT "./Gonduls/d04/input.txt"
using namespace std;

int main(){
    ifstream file(INPUT);
    string str;
    int result1 = 0;
    int result2 = 0;
    while (file >> str){
        int numbers[4] = {0, 0, 0, 0};
        int index = 0;
        for (auto &ch : str) {
            if (ch == '-' || ch == ','){
                index ++;
                continue;
            }
            numbers[index] = numbers[index] * 10 + ch - '0';
        }

        // part 1
        if(numbers[0] <= numbers[2] && numbers[3] <= numbers[1])
            result1 ++;
        else if(numbers[0] >= numbers[2] && numbers[3] >= numbers[1])
            result1 ++;

        //part 2
        if(numbers[0] <= numbers[2] && numbers[2] <= numbers[1])
            result2 ++;
        else if(numbers[2] <= numbers[0] && numbers[0] <= numbers[3])
            result2 ++;
    }
    cout << "Result part1 = " << result1 << endl;
    cout << "Result part2 = " << result2 << endl;
}