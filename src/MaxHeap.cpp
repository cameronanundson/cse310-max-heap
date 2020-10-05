/**
 * @file MaxHeap.cpp
 * @author Cameron Anundson (1216724132)
 * @brief Contains all implementation for MaxHeap
 * @note All arrays are indexed starting at 1.
 * @note Order of functions is same as listed in MaxHeap.h
 */

#include <iostream>
#include <iomanip>
#include <string>
#include "MaxHeap.h"

using namespace std;

/**
 * @brief Prints heap.
 * 
 * Sample output:
 * Max Size: 15
 * Current Size: 10
 * ProjD  
 * 250    
 * ProjS ProjT  
 * 32       49     
 * Proj5   ProjY  ProjPP  ProjOK 
 * 13         10          11           17     
 * ProjX   ProjK   ProjC  
 * 8             4             2
 */
void MaxHeap::printMaxHeap() 
  {
    if (projectList == NULL) 
    {
        cout << "The heap is empty" << endl;
    }
    else 
    {
        cout << "Max Size: " << maxSize << endl;
        cout << "Current Size: " << currentSize << endl;
        int nextline = 1;
        if (projectList != NULL && currentSize > 0) 
        {
            for (int i = 1; i <= currentSize; i = i*2) 
            {
                int k = i;
                while (k < i+nextline && k <= currentSize)
                {
                      cout << std::left << setw(8) << projectList[k].projName;
                      k++;
                }
                cout << endl; 
                k = i;
                while (k < i+nextline && k <= currentSize)
                {
                      cout << std::left << setw(8) << projectList[k].cost;
                      k++;
                }
              cout << endl; 
              nextline *= 2;
            }
        }
        cout << endl;
    }
}

/**
 * @brief Allocates memory for projectList and assigns values to maxSize and currentSize.
 * 
 * @param   n   the size of the array to be created (heap size is n-1)
 */
void MaxHeap::create(int n) {
  maxSize = n - 1; // Since the max heap is indexed from 1, this accounts for index 0 being empty.
  currentSize = 0;
  delete []projectList; // Frees memory from old array.
  projectList = new Project[n];
}

/**
 * @brief Builds max heap in projectList from otherList in O(n) runtime.
 * 
 * @param otherList         an array of Projects with no specific order
 * @param sizeOfOtherList   the length of otherList
 */
void MaxHeap::buildMaxHeap(Project* otherList, int sizeOfOtherList) {
  if (sizeOfOtherList > maxSize || currentSize == maxSize) {
    int sizeOfNewList = getNextPowerOfTwo(sizeOfOtherList) + 1;
    create(sizeOfNewList);
  } else { // If a larger heap doesn't need to be created, the heap should be reinstantiated with the same size.
    create(maxSize + 1);
  }

  // Copies data from otherList to projectList. 
  for(int i = 1; i <= sizeOfOtherList; i++) {
    projectList[i] = otherList[i];
    currentSize++;
  }
  
  maxHeapifyFullTree();
}

/**
 * @brief Inserts new node into heap.
 * 
 * The new node is inserted at the end of the heap, then it is percolated up until the heap order
 * is no longer in violation. Also, prints heap before and after change if print=="yes".
 * 
 * @note No specification was made that disallows negative project cost, so negative project cost is
 * allowed in this implementation.
 * 
 * @param newProjectName  string to fill projName field of new Project node
 * @param newCost         int to fill cost field of new Project node
 * @param print           if print=="yes", print heap before and after insertion. if print=="no", do not print 
 */
void MaxHeap::maxHeapInsert(string newProjectName, int newCost, string print) {
  // If print contains "yes", expected behavior is to print heap before and after modification.
  if (print == "yes") {
    cout << "Before insert operation:" << endl;
    printMaxHeap();
  }
  
  /**
   * If heap is full, store data in current heap, then create new heap of size n where n is the next
   * lowest power of 2 such that n > maxSize.
   */
  if (currentSize == maxSize) {
    Project* copyOfProjectList = new Project[currentSize + 1];
    for (int i = 1; i <= currentSize; i++) {
      copyOfProjectList[i].projName = projectList[i].projName;
      copyOfProjectList[i].cost = projectList[i].cost;
    }
    buildMaxHeap(copyOfProjectList, currentSize);
  }
  // At this point, it is guaranteed that there is space in the heap for the new project.

  // Create new project and add to end of heap.
  Project newProject = { newCost, newProjectName };
  int newProjectIndex = currentSize + 1; // Need to add 1 because heap is indexed from 1.
  projectList[newProjectIndex] = newProject;
  currentSize += 1;
  
  // Percolate newProject up in maxHeap until heap order property is no longer in violation.
  percolateUp(newProjectIndex);

  if (print == "yes") {
    cout << "After insert operation:" << endl;
    printMaxHeap();
  }
}

/**
 * @brief Removes node with max value of cost field (root node) from heap, moves node at lost position to root,
 * then restores heap-order-property.
 * 
 * @param print   if print=="yes", print heap before and after insertion. if print=="no", do not print 
 * @return int    cost field of node with max value in heap
 */
int MaxHeap::extractMax(string print) {
  // If print contains "yes", expected behavior is to print heap before and after modification.
  if (print == "yes") {
    cout << "Before extract max operation:" << endl;
    printMaxHeap();
  }

  // Get value from max node (root node) then replace max node (root node) with last node in heap and decrement size.
  int max = projectList[1].cost;
  projectList[1] = projectList[currentSize];
  currentSize --;

  // Enforces heap-order-property.
  maxHeapifyFullTree();

  if (print == "yes") {
    cout << "After extract max operation:" << endl;
    printMaxHeap();
  }

  return max;
}

/**
 * @brief Increases the key value of node then reorganizes heap to maintain heap-order-property if needed.
 * 
 * @param index     index of node to have key value increased
 * @param newCost   value to replace cost field of node
 * @param print   if print=="yes", print heap before and after insertion. if print=="no", do not print
 */
void MaxHeap::increaseKey(int index, int newCost, string print) {
  // Guard block for case where new key < current key, which is not allowed.
  if (newCost < projectList[index].cost) {
    cout << "Error: new cost is smaller than current cost" << endl;
    return;
  }
  // Guard block for case where new key = current key, which is not allowed.
  if (newCost == projectList[index].cost) {
    cout << "Error: new cost is equal to current cost" << endl;
    return;
  }

  // If print contains "yes", expected behavior is to print heap before and after modification.
  if (print == "yes") {
    cout << "Before increase operation:" << endl;
    printMaxHeap();
  }

  // Sets new cost and reorganizes heap (if necessary) to maintain heap-order-property.
  projectList[index].cost = newCost;
  maxHeapifyFullTree();

  if (print == "yes") {
    cout << "After increase operation:" << endl;
    printMaxHeap();
  }
}

/**
 * @brief Percolates the node at index i upwards in the max heap until heap-order-property is restored.
 * 
 * @param i   index of node to be percolated upwards
 */
void MaxHeap::percolateUp(int i) {
  int parentNodeIndex = getParentNode(i);

  if ( (i != 1) && (projectList[i].cost > projectList[parentNodeIndex].cost)) {
    exchange(i, parentNodeIndex);
    percolateUp(parentNodeIndex);
  } 
}

/**
 * @brief Percolates the node at index i downwards in the max heap until heap order property is restored.
 * 
 * Essentially the same as maxHeapifyFullTree() that starts at the node specified by index i and traverses
 * downwards instead of starting at end and traversing upwards.
 * 
 * @param i   index of node to be percolated downwards
 */
void MaxHeap::percolateDown(int i) {
  for ( ; i < currentSize; i++) {
    maxHeapify(i);
  }
}

/**
 * @brief Given a node at index i, ensures node at index i has a greater key value than both children. If this
 * is not true, rearranges nodes until it is.
 * 
 * @param i   index of node to apply maxHeapify to
 */
void MaxHeap::maxHeapify(int i) {
  int largest;
  int l = getLeftNode(i); // Left child node.
  int r = getRightNode(i); // Right child node.

  // Check if left node is larger than root.
  if ( (l <= currentSize) && (projectList[l].cost > projectList[i].cost) ) {
    largest = l;
  } else {
    largest = i;
  }

  // Check if right node is largest of nodes at i, l, and r.
  if ( (r <= currentSize) && (projectList[r].cost > projectList[largest].cost) ) {
    largest = r;
  }

  if (largest != i) {
    exchange(i, largest);
    maxHeapify(largest);
  }
}

/**
 * @brief Applies maxHeapify to every non-leaf node in tree
 */
void MaxHeap::maxHeapifyFullTree() {
  for (int i = getLastParentNode(currentSize); i >= 1; i--) {
    maxHeapify(i);
  }
}

// Exchanges Projects at indexes i and j in projectList
void MaxHeap::exchange(int i, int j) {
  Project temp = projectList[i];
  projectList[i] = projectList[j];
  projectList[j] = temp;
}

// Returns index of left child node relative to to i. Does not check if return index is within heap bounds.
int MaxHeap::getLeftNode(int i) {
  return 2 * i;
}

// Returns index of right child node relative to to i. Does not check if return index is within heap bounds.
int MaxHeap::getRightNode(int i) {
  return 2 * i + 1;
}

// Returns index of parent node relative to to i. Does not check if return index is within heap bounds.
int MaxHeap::getParentNode(int i) {
  return i / 2; // Would normally floor i/2, but not needed because integer division truncates.
}

// Returns the index of the last parent node in a heap with n nodes where n==size (parameter).
int MaxHeap::getLastParentNode(int size) {
  return size / 2;
}

/**
 * @brief Returns integer of least power of 2 greater than i.
 * 
 * Sample input 1: 5
 * Sample output 1: 8
 * 
 * Sample input 2: 16
 * Sample output 2: 32
 * 
 * @param i     value that return must be greater than
 * @return int  least power of 2 greater than i.
 */
int MaxHeap::getNextPowerOfTwo(int i) {
  // i += 1; // Add 1 to i because the heap implementation here begins at index 1, 0 is empty.
  int power = 1;
  while (power <= i) {
    power *= 2;
  }
  return power;
}
