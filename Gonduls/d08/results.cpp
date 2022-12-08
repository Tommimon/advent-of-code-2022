#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#define INPUT "./Gonduls/d08/input.txt"
using namespace std;

int calculateScenic(int size, int x, int y, const string* strings);

int main(){
    ifstream file(INPUT);
    string line;

    getline(file, line);
    int size = line.size();
    string strings[size];
    bool matrix[size][size];

    for(int j = 0; j < size; j++)
        matrix[0][j] = false;
    
    strings[0] = line;
    int i = 1;
    while (getline(file, line)){
        strings[i] = line;

        for(int j = 0; j < size; j++)
            matrix[i][j] = false;
        
        i++;
    }

    for(int direction = 0; direction < 2; direction ++){
        
        for(i = 0; i < size; i++){
            char directMax = '0' -1, reverseMax = '0' -1;
            for(int j = 0; j < size; j++){
                int dx = j, rx = size - 1 -j;
                int dy = i, ry = size - 1 -i;

                if(direction){
                    swap(dx, dy);
                    swap(rx, ry);
                }

                if(strings[dy][dx] > directMax){
                    matrix[dy][dx] = true;
                    directMax = strings[dy][dx];
                }

                if(strings[ry][rx] > reverseMax){
                    matrix[ry][rx] = true;
                    reverseMax = strings[ry][rx];
                }

                if(directMax == '9' && reverseMax == '9')
                    break;
            }
        }
    }

    int result1 = 0;
    int result2 = 0;
    for(i = 0; i < size; i++)
        for(int j = 0; j < size; j++){
            if(matrix[i][j])
                result1 ++;

            int scenic = calculateScenic(size, i, j, strings);
            result2 = scenic > result2? scenic : result2;
        }

    cout << "Result part 1 = " << result1 << endl;
    cout << "Result part 2 = " << result2 << endl;


}

int calculateScenic(int size, int x, int y, const string* strings){
    int result = 1;
    int partial = 0;
    int i;
    char letter = strings[y][x];
    partial = 0;
    for(i = x + 1; i < size; i++){
        partial ++;
        if(strings[y][i] >= letter){
            break;
        }
    }
    result *= partial;
    partial = 0;
    for(i = x -1; i >= 0; i--){
        partial ++;
        if(strings[y][i] >= letter){
            break;
        }
    }
    result *= partial;
    partial = 0;
    for(i = y + 1; i < size; i++){
        partial ++;
        if(strings[i][x] >= letter){
            break;
        }
    }
    result *= partial;
    partial = 0;
    for(i = y - 1; i >= 0; i--){
        partial ++;
        if(strings[i][x] >= letter){
            break;
        }
    }
    result *= partial;
    return result;
}