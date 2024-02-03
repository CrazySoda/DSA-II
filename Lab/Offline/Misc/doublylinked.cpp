#include <bits/stdc++.h>
using namespace std;
class Node{
    public:
    int data;
    Node *next;
    Node *prev;
};
class DoublyLinkedList{
    Node *head;
    Node *tail;
    int size;
    public:
    DoublyLinkedList(){
        head = NULL;
        tail = NULL;
        size = 0;
    }
    void insert(int data){
        Node *newNode = new Node();
        newNode->data = data;
        newNode->next = NULL;
        newNode->prev = NULL;
        if(head == NULL){
            head = newNode;
            tail = newNode;
        }
        else{
            tail->next = newNode;
            newNode->prev = tail;//tail has the address of the previous node
            tail = newNode;
        }
        size++;
    }
    void reverseTraversal(){
        Node *temp = tail;
        while(temp != NULL){
            cout<<temp->data<<" ";
            temp = temp->prev;
        }
        cout<<endl;
    }
};

int main(){
    DoublyLinkedList dll;
    dll.insert(1);
    dll.insert(2);
    dll.insert(3);
    dll.insert(4);
    dll.insert(5);
    dll.reverseTraversal();
    return 0;
}