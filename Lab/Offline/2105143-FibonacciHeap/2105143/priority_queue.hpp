#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include "fib_heap.hpp"

// Wrapper class
class Priority_Queue {
public:
    Fib_heap_max* myHeap;
    //tester helper
    
    //constructor
    Fib_heap_max*& getHeap() {
        return myHeap;
    }
    Priority_Queue() {
        myHeap = new Fib_heap_max();
    }
    /////////////////1///////////////////
    void make_heap() {
        myHeap = myHeap->make_heap();
    }

    ///////////////2/////////////////////
    bool is_empty(Fib_heap_max* heap) {
        return heap->is_empty(heap);
    }

    ///////////////3/////////////////////
    void insert(Fib_heap_max* heap, int key, int value) {
        heap->insert(heap, key, value);
    }

    ///////////////4/////////////////////
    node* extract_max(Fib_heap_max* heap) {
        return heap->extract_max(heap);
    }

    ///////////////5/////////////////////
    void increase_key(Fib_heap_max* heap, int value, int newKey) {
        heap->increase_key(heap, value, newKey);
    }

    ///////////////6/////////////////////
    void dlt(Fib_heap_max* heap, int value) {
        heap->dlt(heap, value);
    }

    ///////////////7/////////////////////
    //meld
    Fib_heap_max* meld(Fib_heap_max* heap1, Fib_heap_max* heap2) {
        return heap1->meld(heap1, heap2);
    }
    ///////////////8/////////////////////
    node* find_max(Fib_heap_max* heap) {
        return heap->find_max(heap);
    }
    ///////////////9/////////////////////
    void print(Fib_heap_max* heap) {
        heap->print(heap);
    }

    
    
};

///////////////10/////////////////////
/* void test(){
    if (compareFiles("output.txt", "expected_output.txt")) {
        cout<<"Test Passed"<<endl;
    } else {
        cout<<"Test Failed"<<endl;
    }
}
 */
void test(FILE *fp1, FILE *fp2) 
{ 
    char ch1 = getc(fp1); 
    char ch2 = getc(fp2);  
    int error = 0, pos = 0, line = 1; 
    while (ch1 != EOF && ch2 != EOF) 
    { 
        pos++; 
        if (ch1 == '\n' && ch2 == '\n') 
        { 
            line++; 
            pos = 0; 
        }  
        if (ch1 != ch2) 
        { 
            error++; 
            cout<<"Failed"<<endl;
            return; 
        } 
        ch1 = getc(fp1); 
        ch2 = getc(fp2); 
    } 
  
    cout<<"Passed"<<endl; 
} 

#endif