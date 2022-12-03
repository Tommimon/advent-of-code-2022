#include <iostream>
#include <fstream>
#include <string>
#define INPUT "./Gonduls/d03/input.txt"
using namespace std;

int index(char letter){
    if (letter <= 'z' && letter >= 'a')
        return letter - 'a';
    
    return letter - 'A' + 26;
}

int main(){
    ifstream file(INPUT);
    string str;
    int result = 0;
    int line = 0;
    while (getline(file, str)){
        int letters[3][56];

        for (int i = 0; i < 56; i++)
            letters[line][i] = 0;

        for (int i = 0; i < str.size(); i++)
            letters[line][index(str[i])]++;
        
        if(line == 2){
            for (int i = 0; i < 56; i++){
                int a = letters[0][i];
                int b = letters[1][i];
                int c = letters[2][i];
                if (a*b*c!= 0){
                    result += i + 1;
                    break;
                }
            }
            line = -1;
        }
        line ++;
    }
    cout << "Result part2 = " << result << endl;
}