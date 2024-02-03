#include <bits/stdc++.h>
//constants
#define POSINF 100000
#define NEGINF -100000
//all the values are unique in the heap
using namespace std;

typedef Node* NodePtr;

class Node{
    public:
    int key;
    int value;
    int rank;
    NodePtr parent;
    NodePtr child;
    NodePtr left;
    NodePtr right;
    bool mark;
    //constructor
    Node(int key,int value){
        this->key = key;
        this->value = value;
        this->rank = 0;
        this->parent = NULL;
        this->child = NULL;
        this->left = this;
        this->right = this;
        this->mark = mark;
    }
    //destructor
    ~Node(){
        delete this;
    }
};



int main(){
    
    return 0;
}