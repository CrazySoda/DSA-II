
 #include "priority_queue.hpp" 
int main() {

    
    
    /* Fib_heap_max* heap = myQueue.myHeap->meld(myQueue.myHeap, myQueue2.myHeap);
    heap->print(heap); */
    
    
    freopen("output.txt", "w", stdout); 
    Priority_Queue myQueue;
    Priority_Queue myQueue2;

    // Test 1: Make heaps
    myQueue.make_heap();
    myQueue2.make_heap();
    std::cout << "Is empty: " << (myQueue.is_empty(myQueue.getHeap()) ? "true" : "false") << std::endl;
    // Test 2: Insert elements
    myQueue.insert(myQueue.getHeap(), 2, 2);
    myQueue.insert(myQueue.getHeap(), 45, 3);
    myQueue.insert(myQueue.getHeap(), -14, 42);
    myQueue.insert(myQueue.getHeap(), 78, 54);
    myQueue.insert(myQueue.getHeap(), -60, 6);
    
    myQueue2.insert(myQueue2.getHeap(), 84, 88);
    myQueue2.insert(myQueue2.getHeap(), -99, 9);
    myQueue2.insert(myQueue2.getHeap(), 110, 10);
    myQueue2.insert(myQueue2.getHeap(), -124, 15);
    myQueue2.print(myQueue2.myHeap);

    // Test 3: Meld heaps
    Priority_Queue myQueue3;
    myQueue3.make_heap();
    myQueue3.getHeap() = myQueue3.meld(myQueue.getHeap(), myQueue2.getHeap());
    myQueue3.print(myQueue3.getHeap());
    // Test 4: Extract max and print
    myQueue3.extract_max(myQueue3.getHeap());
    myQueue3.print(myQueue3.getHeap());

    // Test 5: Insert and print
    myQueue3.insert(myQueue3.getHeap(), 1344, 145);
    myQueue3.insert(myQueue3.getHeap(), 134, 1004);
    myQueue3.print(myQueue3.getHeap());

    // Test 6: Extract max and print
    myQueue3.extract_max(myQueue3.getHeap());
    myQueue3.print(myQueue3.getHeap());

    // Test 7: Compare output with expected_output.txt
    myQueue3.increase_key(myQueue3.getHeap(),42 , 3);
    myQueue3.increase_key(myQueue3.getHeap(),3 , 80);
    myQueue3.increase_key(myQueue3.getHeap(),2 , 81);
    myQueue3.print(myQueue3.getHeap());
    std::cout << "Is empty: " << (myQueue3.is_empty(myQueue3.getHeap()) ? "true" : "false") << std::endl;
    node* max3 = myQueue3.find_max(myQueue3.getHeap());
    std::cout << "Max from Queue 3: " << max3->value << std::endl;
    freopen("CON", "w", stdout);
    FILE *fp1 = fopen("output.txt", "r"); 
    FILE *fp2 = fopen("expected_output.txt", "r");
    test(fp1, fp2);  
    return 0;
}


//////////!!!!!LESSSSS GOOOOOOOOOOOOOOOOO!!!!!!!!!!!//////////