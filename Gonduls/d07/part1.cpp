#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <sstream>
#define INPUT "./Gonduls/d07/input.txt"
using namespace std;

int globalResult = 0;

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
            /* cout << "{";

            for(Dir d : subDirs)
                cout << ", " << d.name;
            
            cout << "}\n"; */

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

    //cout << root -> name << ", " << result << endl;
    
    if(result < 100000)
        globalResult += result;
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
            //cout << line << endl;
            string end = line.substr(5);
            
            if(end.compare("..") == 0){
                current = current -> getFather();
                //cout << "\t> " << current -> name << endl;
                continue;
            }
            current = current -> getDir(end);
            continue;
        }
        
        if(line.find("$ ls", 0) == 0){
            //cout << line << endl;
            alreadyAdded = current -> alreadyAdded();
            continue;
        }

        if(alreadyAdded){
            //cout << line << endl;
            continue;
        }
        
        if(line.find("dir ", 0) == 0){
            //cout << line << endl;
            current -> addDir(line.substr(4));
        } else {
            stringstream ss;
            string integer;
            ss << line;
            ss >> integer;
            // cout << integer << endl;
            // cout << stoi(integer) << endl;
            current -> addFile(stoi(integer));
        }
    }
    
    traverse(&root);
    cout << globalResult << endl;
}