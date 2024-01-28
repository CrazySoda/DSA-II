#include <bits/stdc++.h>
#include "color.hpp"
using namespace std;

struct Element {
    int key;
    string data;
    Element *parent;
    Element *left;
    Element *right;
    int color;
    //0 is black, 1 is red
};

typedef Element* ElementPtr;

class RedBlackTree {
    private:
    //elements:
    ElementPtr root;
    ElementPtr TNULL;
    //helper functions:
    void inOrderHelper(ElementPtr node) {
        if (node != TNULL) {
            inOrderHelper(node->left);
            if(node->color == 0){
            cout<<dye::black(node->key)<<" => "<<dye::black(node->data)<<endl;
            }else {
                cout<<dye::red(node->key)<<" => "<<dye::red(node->data)<<endl;
            }
            inOrderHelper(node->right);
        }
    }
    void leftRotate(ElementPtr x){
        ElementPtr y =x->right;
        //y's left subtree is assigned as x's right subtree
        x->right = y->left;
        //also fix the parent of y's left subtree
        if(y->left != TNULL){
            y->left -> parent = x;
        }
        //fix y's parent
        y->parent = x->parent;
        //fix the pointer of x's parent
        if(x->parent == nullptr){
            root = y;
        }
        else if(x== x->parent->left){
            x->parent->left = y;
        }else {
            x->parent->right = y;
        }
        y->left =x;
        x->parent = y;
    }
    void rightRotate(ElementPtr x){
        ElementPtr y = x->left;
        x->left = y->right;
        if(y->right !=TNULL){
            y->right->parent = x;
        }
        y->parent = x->parent;
        if(x->parent == nullptr){
            root = y;
        }else if(x == x->parent->right){
            x->parent->right = y;
        }else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }
void clear_helper(ElementPtr x){
        if(x != TNULL){
            clear_helper(x->left);
            clear_helper(x->right);
            delete x;
        }
        }
    ElementPtr searchTreeHelper(ElementPtr node, int key) {
        if (node == TNULL || key == node->key) {
            return node;
        }

        if (key < node->key) {
             return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key);
    }
    //Balancing the tree after insertion
    void insertFix(ElementPtr k){
        ElementPtr uncle;
        while (k->parent->color == 1){
             if(k->parent == k->parent->parent->left){
                //parent is left child
                //uncle is right child
                uncle = k->parent->parent->right;
                if(uncle->color == 1){
                    uncle->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color=1;
                    k = k->parent->parent;
                }else{
                    if(k == k->parent->right){
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }else{
            //parent is right child
            //uncle is left child
                uncle = k->parent->parent->left;
                if(uncle->color == 1){
                    uncle->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    //zig-zag to zag-zag
                    if(k == k->parent->left){
                        k = k->parent;
                        rightRotate(k);
                    }
                    //re-color and rotate
                    k->parent->color =0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            }
            if(k==root){
                break;
            }
        }
        root->color = 0;
    }
    ElementPtr minimum(ElementPtr elem){
        ElementPtr x = elem;
        while(x->left != TNULL){
            x = x->left;
        }
        return x;
    }
    ElementPtr successor(ElementPtr elem){
        if(elem->right !=TNULL){
            return minimum (elem->right);
        }
        ElementPtr y = elem->parent;
        while(y!=nullptr && elem == y->right){
            elem = y;
            y = y->parent;
        }
        return y;
    }
    //join u to v
    void red_black_transplant(ElementPtr u, ElementPtr v){
        if(u->parent == nullptr){
            root = v;
        } else if(u == u->parent->left){
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }
    //BST Delete 
    void eraseElemHelper(ElementPtr Elem, int key){
        ElementPtr toDlt = TNULL;
        ElementPtr x,successor;
        while(Elem != TNULL){
            
            if(Elem->key <= key){
                Elem = Elem->right;
            } else {
                Elem = Elem->left;
            }
            if(Elem->key == key){
                toDlt = Elem;
            }
        }
        if(toDlt == TNULL){
            cout<<key<<" not found"<<endl;
            return;
        }
        successor = toDlt;
        int successor_original_color = successor->color;
        if(toDlt->left == TNULL){
            x = toDlt->right;
            red_black_transplant(toDlt, toDlt->right);
        }else if(toDlt->right == TNULL){
            x = toDlt->left;
            red_black_transplant(toDlt, toDlt->left);
        }else {
            successor = minimum(toDlt->right);
            successor_original_color = successor->color;//flag to see black or not
            x = successor->right;
            if(successor->parent == toDlt){
                x->parent = successor;
            }else {
                red_black_transplant(successor,successor->right);
                successor->right = toDlt->right;
                successor->right->parent = successor;
            }
            red_black_transplant(toDlt,successor);
            successor->left = toDlt->left;
            successor->left->parent = successor;
            successor->color = toDlt->color;
        }
        delete toDlt;
        if(successor_original_color == 0){
            eraseFix(x);
        }
    }
    //Balancing the tree after deletion
    void eraseFix(ElementPtr elem){
        ElementPtr sibling;
        while(elem!=root && elem->color == 0){
            if(elem == elem->parent->right){
                //elem is right child
                sibling = elem->parent->left;
                //Sibling->Red
                //elem asks parent to calm sibling down
                if(sibling->color ==1){
                    sibling->color = 0;
                    elem->parent->color = 1 ;
                    rightRotate(elem->parent);
                }
                //Sibling->Black
                if(sibling->left->color == 0 && sibling->right->color == 0){
                    sibling->color =1;
                    elem = elem->parent;
                }else{
                    //near child is red
                    //make near child black 
                    //make sibling red
                    //rotate sibling to left
                    //now sibling is the far red child
                    if(sibling->left->color == 0){
                        sibling->right->color = 0;
                        sibling->color = 1;
                        leftRotate(sibling);
                        sibling = elem->parent->left;
                    }
                    //swap color and rotate
                    sibling->color = elem->parent->color;
                    elem->parent->color = 0;
                    sibling->left->color = 0;
                    rightRotate(elem->parent);
                    elem = root;
                }
            }else{
                //elem is right child
                sibling = elem->parent->right;
                //Sibling->Red
                if(sibling->color == 1){
                    sibling->color = 0;
                    elem->parent->color = 1;
                    leftRotate(elem->parent);
                    sibling = elem->parent->right;
                }
                //Sibling->Black
                if(sibling->left->color == 0 && sibling->right->color == 0){
                    sibling->color =1;
                    elem = elem->parent;
                    //back to loop
                }else {
                    //near child is red
                    //make near child black
                    //make sibling red
                    //rotate sibling to right
                    //now sibling is the far red child
                    if(sibling->right->color == 0){
                        sibling->left->color = 0;
                        sibling->color = 1;
                        rightRotate(sibling);
                        sibling=elem->parent->right;
                    }
                    //swap color of parent and sibling
                    sibling->color = elem->parent->color;
                    elem->parent->color = 0;
                    sibling->right->color = 0;
                    leftRotate(elem->parent);
                    elem = root;
                }
            }
        }

        elem->color = 0;
    }
    public:
    RedBlackTree() {
        TNULL = new Element;
        TNULL -> color = 0;
        TNULL -> left = nullptr;
        TNULL -> right = nullptr;
        root = TNULL;
    }
    ElementPtr getRoot(){
        return this->root;
    }
    void insert(int key, string data){
        //BSTinsert than fix the tree
        ElementPtr element = new Element;
        element ->parent = nullptr;
        element ->key = key;
        element->data = data;
        element -> left = TNULL;
        element -> right = TNULL;
        ElementPtr y = nullptr;
        ElementPtr x = root;

        while(x!=TNULL) {
            //x and y both sinks down but y is always x's parent
            y = x;
            if(element->key < x->key){
                x = x->left;
            }else if(element->key > x->key){
                x = x->right;
            }else {
                y = x;
                break;
            }
        }
        element->parent = y;
        if(y == nullptr){
            element -> color = 1;
            root = element;
        }else if(element->key < y->key){
            element -> color = 1;
            y->left = element;
        }else if(element->key > y->key){
            element -> color = 1;
            y->right = element;
        }else {
            y->data = element->data;
        }

        if(element->parent == nullptr){
            element->color = 0;
            return;
        }
        if(element->parent->parent == nullptr){
            return;
        }
        insertFix(element);
    }
    void eraseElement(int key){
        eraseElemHelper(this->root, key);
    }
    void printTree(ElementPtr root){
        if(root != TNULL ){
            if(root->color == 0){
            cout<<dye::black(root->key)<<dye::black("_")<<dye::black(root->data);
            }else {
                cout<<dye::red(root->key)<<dye::red("_")<<dye::red(root->data);
            }
            if(root->left != TNULL || root->right != TNULL){
            cout<<"(";
            printTree(root->left);
            cout<<", " ;
            printTree(root->right);
            cout<<")";
            }
        }else {
            return;
        }
    }
    void iteration(){
        inOrderHelper(this->root);
    }
    void find(int key){
        if(searchTreeHelper(this->root, key) == TNULL){
            cout<<key<<" not found"<<endl;
        }else{
            cout<<key<<" found"<<endl;
        }
    }
    void empty(){
        if(this->root == TNULL){
            cout<<"Yes"<<endl;
        }else {
            cout<<"No"<<endl;
        }
    }
    int size(ElementPtr root){
        if(root == TNULL){
            return 0;
        }else {
            return size(root->left) + size(root->right) + 1;
        }
    }
    void clear(ElementPtr root){
        if(root == TNULL){
            cout<<"Unsuccessful"<<endl;
            return;
        }else if(root!=TNULL){
            clear_helper(root);
            this->root = TNULL;
            cout<<"Successful"<<endl;
        }
    }
};

int main(){
    RedBlackTree rbt;
    string prompt;
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    while(getline(cin, prompt)){
        istringstream iss(prompt);
        string command;
        iss>>command;
         
        if(command == "I"){
            
            int key ;
            string data;
            iss>>key>>data;
            rbt.insert(key, data);
            rbt.printTree(rbt.getRoot());
            cout<<endl;
        }else if(command == "E"){
            int key;
            iss>>key;
            rbt.eraseElement(key);
            rbt.printTree(rbt.getRoot());
            cout<<endl;
        }else if(command == "Clr"){
            rbt.clear(rbt.getRoot());
        }else if(command == "F"){
            int key;
            iss>>key;
            rbt.find(key);
        }else if(command == "Em"){
            rbt.empty();
        }else if(command == "S"){
            cout<<rbt.size(rbt.getRoot())<<endl;
        }else if(command == "Itr"){
            rbt.iteration();
        }
    }
    return 0;
}