#ifndef FIB_HEAP_HPP
#define FIB_HEAP_HPP


#include <bits/stdc++.h>
using namespace std;
#define pos_max 100000
#define neg_max -100000

// Node Class
struct node
{
    int key;
    int value;
    int degree;
    node *parent;
    node *child;
    node *left;
    node *right;
    bool mark;
    bool visited;
};

// Fibonacci Heap Class
class Fib_heap_max
{
public:
    // elements
    int no_of_nodes;
    node *H;                       // max node
    node *valueArray[pos_max + 1]; // array to store the nodes


    // Helper Functions
    void Consolidate_helper(node *H1, node *y, node *z)
    {
        // pull the node from the root list
        y->left->right = y->right;
        y->right->left = y->left;
        y->left = y;
        y->right = y;
        y->parent = z;
        // if z has no child
        if (z->child == NULL)
        {
            z->child = y;
        }
        // add y to the child list of z
        y->right = z->child;
        y->left = z->child->left;
        z->child->left->right = y;
        z->child->left = y;
        if (y->key > z->child->key)
        {
            z->child = y;
        }
        if (z->right == z)
        {
            H1 = z;
        }
        z->degree++;
    }
    // Function to consolidate the heap
    void Consolidate(node *H1)
    {
        int D = 1 + log2(no_of_nodes);
        node *A[D];
        for (int i = 0; i < D; i++)
        {
            A[i] = NULL;
        }
        node *x = H1;
        node *y;
        node *z;
        node *temp;
        int d;
        do
        {
            d = x->degree;
            //if there is a node with the same degree
            while (A[d] != NULL)
            {
                y = A[d];
                // if the joining node is larger just swap the values
                if (y->key > x->key)
                {
                    temp = x;
                    x = y;
                    y = temp;
                }
                // if y is root it's automatically largest
                if (y == H1)
                {
                    H1 = x;
                }
                Consolidate_helper(H1, y, x);
                A[d] = NULL;
                d++;
            }
            // store the node in the array if/if not there is no node with the same degree
            A[d] = x;
            x = x->right;
        } while (x != H1);
        // find the new max
        H = H1;
        node *temp1 = H1;
        node *temp2 = H1;
        do
        {
            if (temp1->key > H->key)
            {
                H = temp1;
            }
            temp1 = temp1->right;
        } while (temp1 != temp2);
    }
    // Function to cut the increased node from its parent
    void cut(node *H1, node *node_to_be_decreased, node *parent)
    {
        // only child of the parent
        if (node_to_be_decreased == node_to_be_decreased->right)
        {
            parent->child = NULL;
        }
        // more than one child
        else
        {
            // rmv node
            node_to_be_decreased->right->left = node_to_be_decreased->left;
            node_to_be_decreased->left->right = node_to_be_decreased->right;
            // right heavy input so the right node is largest
            parent->child = node_to_be_decreased->right;
        }
        parent->degree--;
        // add the node to the root list
        node_to_be_decreased->left = node_to_be_decreased;
        node_to_be_decreased->right = node_to_be_decreased;
        (H1->left)->right = node_to_be_decreased;
        node_to_be_decreased->right = H1;
        node_to_be_decreased->left = H1->left;
        H1->left = node_to_be_decreased;
        node_to_be_decreased->parent = NULL;
        node_to_be_decreased->mark = false;
    }
    // Function to cascade cut the increased node from its parent
    void cascading_cut(node *H1, node *parent)
    {
        node *y = parent->parent; // y is grandparent
        if (y != NULL)
        {
            // if parent is unmarked just mark it
            if (parent->mark == false)
            {
                parent->mark = true;
            }
            // if parent is marked cut it from its parent and check for cascading cuts
            else
            {
                cut(H1, parent, y);
                cascading_cut(H1, y);
            }
        }
    }
    // Search Function
    node *Find(node *H1, int value)
    {
        node *found = valueArray[value];
        if (found == NULL)
        {
            return NULL;
        }
        return found;
    }

    // Initializes an empty Fib-Heap
    Fib_heap_max *make_heap()
    {
        Fib_heap_max *H1 = new Fib_heap_max;
        H1->H = NULL;
        H1->no_of_nodes = 0;
        fill(H1->valueArray, H1->valueArray + pos_max + 1, nullptr);
        return H1;
    }

    // Checks if the heap is empty
    bool is_empty(Fib_heap_max *H1)
    {
        return H1->H == NULL;
    }

    // Inserts a node into the heap
    void insert(Fib_heap_max *H1, int key, int value)
    {
        node *_new = new node;
        _new->visited = false;
        _new->key = key;
        _new->value = value;
        _new->degree = 0;
        _new->child = NULL;
        _new->parent = NULL;
        _new->left = _new;
        _new->right = _new;
        _new->mark = false;
        // Update valueArray
        H1->valueArray[value] = _new;
        if (H1->H == NULL)
        {
            H1->H = _new;
        }
        else
        {
            H1->H->left->right = _new;
            _new->right = H1->H;
            _new->left = H1->H->left;
            H1->H->left = _new;
            if (_new->key > H1->H->key)
            {
                H1->H = _new;
            }
        }
        H1->no_of_nodes++;
        cout << _new->key << " added" << endl;
    }

    // Extract min
    node *extract_max(Fib_heap_max *H1)
    {

        if (H1->H == NULL)
        {
            cerr << "The heap is empty" << endl;
            return H1->H;
        }
        else
        {
            node *temp = H1->H; // temp has max node
            node *x = NULL;     // flag
            node *ptr = temp;//store max in ptr
            if (temp->child != NULL)
            {
                x = temp->child; // x has the child of H1
            }
            if (x != NULL)//if there is a child
            {
                ptr = x; // ptr has the child of H1
                // loop the list of children
                node *np;
                do
                {
                    np = x->right;
                    // pulling the child of H1 to the root list
                    (H1->H->left)->right = x;
                    x->right = H1->H;
                    x->left = H1->H->left;
                    H1->H->left = x;
                    if (x->key > H1->H->key)
                    {
                        H1->H = x;
                    }
                    x->parent = NULL;
                    x = np;
                } while (np != ptr);
            }
            // remove the max node from the root list
            //regardless of child or not
            (temp->left)->right = temp->right;
            (temp->right)->left = temp->left;
            H1->H = temp->right;
            // fixing H1 pointer after removing the max node
            if (temp == temp->right)
            {
                H1->H = NULL;
            }
            else
            {
                H1->H = temp->right;
                Consolidate(H1->H);
            }
            no_of_nodes--;
            // Update valueArray after deletion
            H1->valueArray[temp->value] = nullptr;
            cout << temp->key << " removed" << endl;
            return temp;
        }
    }

    // Increase Key Operation
    void increase_key(Fib_heap_max *H1, int value, int n_k)
    {
        if (H1->H == NULL)
        {
            cerr << "The heap is empty" << endl;
            return;
        }
        node *node_to_be_increased = Find(H1->H, value);
        if (node_to_be_increased == NULL)
        {
            cerr << "The node is not in the heap" << endl;
            return;
        }
        if (n_k < node_to_be_increased->key)
        {
            cerr << "The new key is smaller than the current key" << endl;
            return;
        }
        node_to_be_increased->key = n_k;
        node *y = node_to_be_increased->parent;
        if (y != NULL && node_to_be_increased->key > y->key)
        {
            cut(H1->H, node_to_be_increased, y);
            cascading_cut(H1->H, y);
        }
        if (node_to_be_increased->key > H1->H->key)
        {
            H1->H = node_to_be_increased;
        }
        H1->valueArray[value] = node_to_be_increased;
        cout << value << " increased to " << n_k << endl;
    }

    // Dlt function
    void dlt(Fib_heap_max *H1, int value)
    {
        if (H1->H == NULL)
        {
            cerr << "The heap is empty" << endl;
            return;
        }
        node *node_to_be_deleted = Find(H1->H, value);
        if (node_to_be_deleted == NULL)
        {
            cerr << "The node is not in the heap" << endl;
            return;
        }
        increase_key(H1, value, pos_max);
        extract_max(H1);
        cout << value << " deleted" << endl;
    }

    Fib_heap_max *meld(Fib_heap_max *H1, Fib_heap_max *H2)
    {
        Fib_heap_max *H3 = make_heap();
        H3->H = H1->H; // make the max of new heap the max of first heap
        // place the entire root list of second heap in the root list of the new heap
        (H3->H->left)->right = H2->H->right;
        (H2->H->right)->left = H3->H->left;
        (H3->H->left) = H2->H;
        (H2->H->right) = H3->H;
        if (H1->H == NULL || (H2->H != NULL && H2->H->key > H1->H->key))
        {
            H3->H = H2->H;
        }
        H3->no_of_nodes = H1->no_of_nodes + H2->no_of_nodes;
        return H3;
        cout << "Heaps Merged" << endl;
    }

    // find max
    node *find_max(Fib_heap_max *H1)
    {
        return H1->H;
    }

    // print helpers and function

    // print the gen queue
    void print_queue(std::queue<node *> q)
    {
        while (!q.empty())
        {
            node *current = q.front();
            q.pop();
            print_node(current);
            std::cout << " ";
        }
        std::cout << std::endl;
    }
 
    void print_node(node *n)
    {
        cout << "( " << n->key << ", " << n->value << " )";
    }
    // print the heap

    void print_sub_tree(node *temp){

    }

    void print_tree(node *temp){
        queue<node *> q;
        if(temp->parent == NULL && temp->child == NULL){
            print_node(temp);
            cout<<endl;
            return;
        }
        //cout<<"1"<<endl;
        print_node(temp);
            cout<<"->";
            
            q = store_child_with_grandchild(temp->child);
            print_sibling(temp->child);
            cout<<endl;
            //cout<<"1"<<endl;
        while(!q.empty()){
            //cout<<q.front()->key<<endl;
            node *temp1 = q.front();
            q.pop();
            print_tree(temp1);
        }
        
    }
    queue<node *> store_child_with_grandchild(node *n){
        queue<node *> q;
        node *temp = n;
        do{
            if(temp->child != NULL){//jodi baccchq thake tahole queue te push korbe
                q.push(temp);
            }
            temp = temp->right;
        }while (temp != n);
        return q;
    }
    void print(Fib_heap_max *H1)
    {
        if(H1->H == NULL){
            cerr << "The heap is empty" << endl;
        }
        else{
            node *temp = H1->H;
            int i = 0;
            do
            {
                ++i;
                cout<<"Tree "<<i<<" : ";
                print_tree(temp);
                temp = temp->right;
            } while (temp != H1->H);
        }
    }
    
    
    

    // print all the sibling including node
    void print_sibling(node *n)
    {
        node *temp = n;
        do
        {
            print_node(temp);
            temp = temp->right;
        } while (temp != n);
    }
    //test
    
    
};

#endif