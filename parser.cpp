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

    ifstream file(filename);
    if(!file) {
        cerr << "Error: unable to open file " << filename << endl;
        exit(1);
    }
    
    string line;
    while (getline(file, line)){
        stringstream ss(line);
        string val, type;
        if(getline(ss, val, ',') && getline(ss, type)) {
            tokens.push_back({type, val});
        }
    }

    file.close();
}
SynTreeNode* termsParse() { // matches for the multiplcation and division
    SynTreeNode* node = factorParse();

    while (tIndex < tokens.size()) {
        const Token& token = tokens[tIndex];

        if(token.val == "*" || token.val == "/") {
            tIndex++;
            if(tIndex >= tokens.size()) {
                cerr << "Syntax error: Expected operand after " << token.val << endl;
                exit(1);
            }
            SynTreeNode* right = factorParse();
            SynTreeNode* newNode = new SynTreeNode(nodeType::OPERATOR, token.val);
            newNode->left = node;
            newNode->right = right;
            node = newNode;
        }
        else {
            break;
        }
    }
    return node;
}


SynTreeNode* expressionParse() { // matches for addition and subtraction
    SynTreeNode* node = termsParse(); 

    while(tIndex < tokens.size()) {
      const Token& token = tokens[tIndex];

        if(token.val == "+" || token.val == "-") {
            tIndex++;

            if(tIndex >= tokens.size()) {
                cerr << "Syntax error: Expected operand after " << token.val << endl;
                exit(1);
            }
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
    if(tIndex >= tokens.size()) {
        cerr << "Syntax error: Unexpected end of input" << endl;
        exit(1);
    }
    
    const Token& token = tokens[tIndex];

    if(token.type == "integer"){
        tIndex++;
        return new SynTreeNode(nodeType::NUMBER, token.val);

    }

    if (token.val == "(") {
        tIndex++;
        SynTreeNode* node = expressionParse();
        if (tIndex >= tokens.size() || tokens[tIndex].val != ")"){ // checks to make sure the paranthesis are correct
            cerr << "Syntax error: requires ')'" << endl; // 
            exit(1);
        }
        tIndex++;
        return node;
    }
    cerr << "Syntax error: unexpected token " << token.val << "'" << endl;
    exit(1);
}

void print(SynTreeNode* node, int depth = 0){ // prints the ast 
    if (!node) return;

    for (int i = 0; i < depth; i++){
        cout << " ";  
    }
    cout << node->val << endl;

    print(node->left, depth+ 1);
    print(node->right, depth+ 1);
}



int main() {

    fileInput("results.txt");
    SynTreeNode* rootNode = expressionParse();
    
    cout << "Abstract Syntax Tree (AST):" << endl;
    print(rootNode);

    delete rootNode; //free allocated memory
    return 0;
}
