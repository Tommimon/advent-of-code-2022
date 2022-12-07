#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <sstream>
#define INPUT "./Gonduls/d07/input.txt"
using namespace std;

int result1 = 0;
int result2;
int threshold = 0;

class Dir{
    list<Dir> subDirs;
    int filesSize;
    Dir* father;
    bool added = false;

    public: 
        string name;
        Dir(string name, Dir* father){
            this -> father = father;
            this -> name = name;
            subDirs = {};
            filesSize = 0;
        }

        void addFile(int size){
            added = true;
            this -> filesSize += size;
        }

        void addDir(string name){
            added = true;
            subDirs.push_back(Dir(name, this));
        }

        Dir * getDir(string name){
            list<Dir>::iterator it = subDirs.begin();
            while(true){
                advance(it, 1);
                if (it -> name.compare(name) == 0){
                    return &(*it);
                }
            }
            throw invalid_argument("No such dir present");
        }

        Dir * getFather(){
            return father;
        }

        bool alreadyAdded(){
            return added;
        }

        list<Dir> getSubDirs(){
            return subDirs;
        }

        int getSize(){
            return filesSize;
        }

};

int traverse(Dir * root){
    int result = root -> getSize();
    for (Dir d : root -> getSubDirs())
        result += traverse(&d);

    if(result < 100000)
        result1 += result;
    
    if(result > threshold && result  < result2)
        result2 = result;
    
    return result;
}

int main(){
    ifstream file(INPUT);
    string line;
    Dir root = Dir("/", NULL);
    Dir* current = &root;
    bool alreadyAdded = false;
    getline(file, line);
    
    // populate
    while(getline(file, line)){
        if(line.find("$ cd ", 0) == 0){
            string end = line.substr(5);
            
            if(end.compare("..") == 0){
                current = current -> getFather();
                continue;
            }
            current = current -> getDir(end);
            continue;
        }
        
        if(line.find("$ ls", 0) == 0){
            alreadyAdded = current -> alreadyAdded();
            continue;
        }

        if(alreadyAdded){
            continue;
        }
        
        if(line.find("dir ", 0) == 0){
            current -> addDir(line.substr(4));
        } else {
            stringstream ss;
            string integer;
            ss << line;
            ss >> integer;
            current -> addFile(stoi(integer));
        }
    }
    
    int total = traverse(&root);
    cout << "Result part 1= " << result1 << endl;
    threshold = 30000000 - (70000000 - total);
    result2 = total;
    traverse(&root);
    cout << "Result part 2= " << result2 << endl;
}