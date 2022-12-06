#include <iostream>
#include <fstream>
#include <string>
#define INPUT "./Gonduls/d06/input.txt"
using namespace std;


int main(){
    ifstream file(INPUT);
    string str;
    int result = 4;
    getline(file, str);
    for (int j = 0; j < size(str); j++){
        if (str[j] == str[j+1] || str[j] == str[j+2] || str[j] == str[j+3]  || str[j+1] == str[j+2] || str[j+1] == str[j+3] || str[j+2] == str[j+3]){
            result ++;
        } else break;
    }
    cout << "Result part1 = " << result << endl;
}