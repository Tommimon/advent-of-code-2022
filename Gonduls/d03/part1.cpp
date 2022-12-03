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
    while (getline(file, str)){
        int letters[56];
        for (int i = 0; i < 56; i++)
            letters[i] = 0;

        for (int i = 0; i < str.size() / 2; i++){
            char a = str[i];
            letters[index(a)]++;
        }
        
        for (int i = str.size() / 2; i < str.size(); i++)
            if (letters[index(str[i])] > 0){
                result += index(str[i]) + 1;
                break;
            }
    }
    cout << "Result part1 = " << result << endl;
}