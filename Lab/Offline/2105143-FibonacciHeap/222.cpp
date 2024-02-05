#include "fib_heap.hpp"

// Wrapper class
class Priority_Queue {
public:
    Fib_heap_max* myHeap;
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

    ///////////////10/////////////////////
    void test() {
        // Add your test cases here
        // ...
    }
};

int main() {
    Priority_Queue myQueue;
    Priority_Queue myQueue2;
    myQueue.make_heap();
    myQueue2.make_heap();
    myQueue.insert(myQueue.myHeap, 2, 2);
    myQueue.insert(myQueue.myHeap, 3, 3);
    myQueue.insert(myQueue.myHeap, 4, 4);
    myQueue.insert(myQueue.myHeap, 5, 5);
    myQueue.insert(myQueue.myHeap, 6, 6);
    myQueue.insert(myQueue.myHeap, 7, 7);
    myQueue.print(myQueue.myHeap);
    myQueue2.insert(myQueue2.myHeap, 8, 8);
    myQueue2.insert(myQueue2.myHeap, 9, 9);
    myQueue2.insert(myQueue2.myHeap, 10, 10);
    myQueue2.insert(myQueue2.myHeap, 11, 11);
    myQueue2.insert(myQueue2.myHeap, 12, 12);
    Priority_Queue myQueue3;
    myQueue3.make_heap();
    /* Fib_heap_max* heap = myQueue.myHeap->meld(myQueue.myHeap, myQueue2.myHeap);
    heap->print(heap); */
    myQueue3.myHeap=myQueue3.myHeap->meld(myQueue.myHeap, myQueue2.myHeap) ;
    myQueue3.print(myQueue3.myHeap);
    myQueue3.insert(myQueue3.myHeap, 13, 13);
    myQueue3.is_empty(myQueue3.myHeap);
    myQueue3.insert(myQueue3.myHeap, 14, 14);
    myQueue3.extract_max(myQueue3.myHeap);
    myQueue3.print(myQueue3.myHeap);
    

    return 0;
}


//////////!!!!!LESSSSS GOOOOOOOOOOOOOOOOO!!!!!!!!!!!//////////