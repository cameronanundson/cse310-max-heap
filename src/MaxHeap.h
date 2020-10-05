/**
 * @file MaxHeap.h
 * @author Cameron Anundson (1216724132)
 * @brief Header file for MaxHeap.cpp
 */

#ifndef MAXHEAP_H
#define MAXHEAP_H
#include <string>

using namespace std;

// struct Project
struct Project {
    int cost;
    string projName;
};

/**
 * The MaxHeap structure contains all necessary variables and functions to 
 * implement a max heap. MaxHeap.cpp contains implementation (methods are in
 * same order as listed here).
 */
struct MaxHeap {
    // Maximum number of nodes in max heap.
    int maxSize; 
    // Current number of nodes in max heap.
    int currentSize; 
    // Max heap of projects implemented as array. Indexed from 1, so length = maxSize + 1 because index 0 is unfilled.
    struct Project * projectList; 

    // Essential functions (from assignment).
    void printMaxHeap();
    void create(int n);
    void buildMaxHeap(Project* otherList, int sizeOfOtherList);
    void maxHeapInsert(string newProjectName, int newCost, string print);
    int extractMax(string print);
    void increaseKey(int index, int newCost, string print);

    // Helper functions used to maintain heap order rules. Detailed documentation in MaxHeap.cpp.
    void percolateUp(int i);
    void percolateDown(int i);
    void maxHeapify(int i);
    void maxHeapifyFullTree();
    void exchange(int i, int j);

    /**
     * Helper functions used to increase code readability in other heap functions by
     * abstracting node location and heap size calculations. Detailed documentation in MaxHeap.cpp.
     */
    int getLeftNode(int i);
    int getRightNode(int i);
    int getParentNode(int i);
    int getLastParentNode(int i);
    int getNextPowerOfTwo(int i);
};

#endif 
