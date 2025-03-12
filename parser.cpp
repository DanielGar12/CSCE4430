#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

enum class nodeType {NUMBER, OPERATOR};

class SynTreeNode {

    public:

    string val;
    nodeType type;
    SynTreeNode* left;
    SynTreeNode* right;

    SynTreeNode (nodeType t, string value){
        val = value;
        type = t;
        left = nullptr;
        right = nullptr;
    }

    ~SynTreeNode() {
        delete left;
        delete right;
    }

};

class Token {
    public:
    string type;
    string val; 
};

vector<Token> tokens;
int tIndex = 0;

void fileInput (const string &filename){

    string line;
    ifstream file(filename);

    while (getline(file, line)){
        stringstream ss(line);
        string val;
        string type;
        getline(ss, val, ','); // extracts value before the comma
        getline(ss, type); // does it after

        tokens.push_back({type, val});
    }

    file.close();
}


int main() {

    fileInput("results.txt");
    cout << "Hello" << endl; // test delete later

    return 0;
}