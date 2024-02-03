#include <bits/stdc++.h>
//constants
#define POSINF 100000
#define NEGINF -100000
//all the values are unique in the heap
using namespace std;



class Node{
    public:
    int key;
    int value;
    int rank;
    Node* parent;
    Node* child;
    Node* left;
    Node* right;
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
class FibMaxHeap{
    public:
    Node* max;
    int n;
    //constructor
    FibMaxHeap(){
        this->max = NULL;
        this->n = 0;
    }
    //destructor
    ~FibMaxHeap(){
        delete this;
    }
    //insert a node
    void insert (int key , int value){
        Node* node = new Node(key,value);
        //if the heap is empty
        if(this->max == NULL){
            this->max = node;
        }else{
            //insert the node to the right of thr max node
            node ->left = max;
            node->right = max->right;
            max->right->left = node;
            max->right = node;
            //if the key of the node is greater than the max node
            if(node->key>max->key){
                max = node;
            }
        }
        this->n++;
    }
    //get the max node
    Node* getMax(){
        return this->max;
    }
    //print the heap
    void print() {
    if (this->max == NULL) {
        cout << "The heap is empty" << endl;
    } else {
        Node* temp = this->max;
        int count = 1;
        do {
            cout << "Tree " << count << " :";
            cout << "( " << temp->key << " , " << temp->value << ")";

            Node* children = temp->child;
            while(children != NULL) {
                Node* temp2 = children;
                do {
                    cout << "( " << temp2->key << " , " << temp2->value << ")";
                    temp2 = temp2->right;
                } while (temp2 != children);
                children = children->child;
            }
            count++;
            temp = temp->right;
            cout << endl;
        } while (temp != this->max);
    }
}

};

int main(){
    FibMaxHeap fmx;
    fmx.insert(55,13);
    fmx.insert(24,13);
    fmx.insert(33,13);
    fmx.insert(79,13);
    fmx.print();
    return 0;
}