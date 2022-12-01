#include <iostream>
#include <fstream>
#include <string.h>
#define INPUT "./Gonduls/d01/input.txt"

using namespace std;

int main(){
	char letter;
	ifstream input(INPUT);
	bool groupEnd = false;
	int maxG[3] = {0,0,0}, currentG = 0, currentInt = 0;
	while (input.get(letter)){
		if (letter == '\n'){
			if (groupEnd){

				// swap elements if greater, continue to keep consistent sort
				for(int i = 0; i< 3; i++){
					if(currentG > maxG[i])
						swap(currentG, maxG[i]);
				}
				currentG = 0;
			}
			else
				currentG += currentInt;

			groupEnd = !groupEnd;
			currentInt = 0;
			continue;
		}

		groupEnd = false;
		currentInt = currentInt * 10 + letter - '0';

	}
	currentG += currentInt;
	for(int i = 0; i< 3; i++)
		if(currentG > maxG[i])
			swap(currentG, maxG[i]);
	cout << "result part 1: " << maxG[0] << endl;
	cout << "result part 2: " << maxG[0] + maxG[1] + maxG[2] << endl;
}