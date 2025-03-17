#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

enum class nodeType {NUMBER, OPERATOR};

class SynTreeNode { // declares the ast

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

SynTreeNode* termsParse();
SynTreeNode* factorParse();
SynTreeNode* expressionParse();

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
SynTreeNode* termsParse() { // matches for the terms
    SynTreeNode* node = factorParse();

    while (tIndex < tokens.size()) {
        Token token = tokens[tIndex];

        if(token.val == "/" || token.val == "*") {
            tIndex++;
            SynTreeNode* right = factorParse();
            SynTreeNode* Node = new SynTreeNode(nodeType::OPERATOR, token.val);
            Node->left = node;
            Node->right = right;
            node = Node;
        }
        else {
            break;
        }
    }
    return node;
}


SynTreeNode* expressionParse() { // to match an expression
    SynTreeNode* node = termsParse(); 

    while(tIndex < tokens.size()) {
        Token token = tokens[tIndex];

        if(token.val == "+" || token.val == "-") {
            tIndex++;
            SynTreeNode* right = termsParse();
            SynTreeNode* Node = new SynTreeNode(nodeType::OPERATOR, token.val);
            Node->left = node;
            Node->right = right;
            node = Node;
        }
        else{
            break;
        }
    }
    return node;
}

SynTreeNode* factorParse() { // matches the factors like ( )
    Token token = tokens[tIndex];

    if(token.type == "integer"){
        tIndex++;
        return new SynTreeNode(nodeType::NUMBER, token.val);

    }

    else if (token.val == "(") {
        tIndex++;
        SynTreeNode* node = expressionParse();
        if (tokens[tIndex].val != ")"){
            cout << "Syntax error: requires ')'" << endl;
            exit(1);
        }
        tIndex++;
        return node;
    }
    cout << "Syntax error: unexpected value " << token.val << endl;
    exit(1);
}

void print(SynTreeNode* node, int height = 0){ // prints the ast 
    if (!node){
        return;
    }

    for (int i = 0; i < height; i++){
        cout << " ";  
    }
    cout << node->val << endl;

    print(node->left, height+ 1);
    print(node->right, height+ 1);
}



int main() {

    fileInput("results.txt");
    SynTreeNode* rootNode = expressionParse();
    cout << "AST: " << endl;
    print(rootNode);

    return 0;
}