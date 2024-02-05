#include "fib_heap.hpp"

class Priority_Queue{
    
};

int main(){
    Fib_heap_max *myHeap;
    myHeap = myHeap->make_heap();

    // Add nodes to the heap
    myHeap->insert(myHeap, 55, 3);
    //myHeap->print(myHeap);
    myHeap->insert(myHeap, 45, 5);
    //myHeap->print(myHeap);
    myHeap->insert(myHeap, 32, 4);
    //myHeap->print(myHeap);
    myHeap->insert(myHeap, 7, 8);
    
    myHeap->insert(myHeap, 24, 7);
    
    myHeap->insert(myHeap, 5, 10);
    myHeap->print(myHeap);

    // Extract the max node
    node *maxNode = myHeap->extract_max(myHeap);
    myHeap->print(myHeap);
    // Increase the key of a node
    int valueToIncrease = 4;
    int newKey = 50;
    myHeap->increase_key(myHeap, valueToIncrease, newKey);
    myHeap->print(myHeap);
    // Delete a node
    int valueToDelete = 8;
    myHeap->dlt(myHeap, valueToDelete);
    myHeap->print(myHeap);

    // Find the max node
    node *maxNodeAfterDeletion = myHeap->find_max(myHeap);
    // Meld two heaps
    Fib_heap_max *secondHeap;
    secondHeap = secondHeap->make_heap();
    secondHeap->insert(secondHeap, 12, 15);
    secondHeap->insert(secondHeap, 30, 20);
    Fib_heap_max *mergedHeap = myHeap->meld(myHeap, secondHeap);
    node *maxNodeMergedHeap = mergedHeap->find_max(mergedHeap);
    myHeap->print(mergedHeap);
    return 0;
}