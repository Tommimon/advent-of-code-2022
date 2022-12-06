#include <iostream>
#include <fstream>
#include <string>
#define INPUT "./Gonduls/d06/input.txt"
using namespace std;

bool check(int* array){
    for(int i = 0; i < 26; i++){
        if (*(array + i) > 1)
            return false;
    }
    return true;
}

int main(){
    ifstream file(INPUT);
    string str;
    int result = 15;
    getline(file, str);
    int all14[26];
    for (int i = 0; i<26; i++){
        all14[i] = 0;
    }
    for (int i = 0; i<14; i++){
        all14[str[i] - 'a'] ++;
    }

    for(int i = 14; i< size(str); i++){
        all14[str[i - 14] - 'a'] --;
        all14[str[i] - 'a'] ++;
        if(check(all14))
            break;
        result ++;
    }
    cout << "Result part2 = " << result << endl;
}