/**
 * @file Assignment4.cpp
 * @author Cameron Anundson (1216724132)
 * @brief Runner class for assignment.
 * @note All arrays are indexed starting at 1.
 */

#include <iostream>
#include <fstream>
#include <string>
#include "MaxHeap.h"

using namespace std;

// Method to get next command and store parameters into variables.
string nextCommand(int * n, int * index, int * newCost, string * printCommand, string * newProjName);

// Runner method that handles all operation of the program.
int main() {
    // Variables that contain parameters from input commands.
    int n, index, newCost;
    string command, newProjName, printCommand;

    // The MaxHeap used during program operation. No other MaxHeaps are used.
    MaxHeap *maxHeap = new MaxHeap();

    // Program runs in this loop. Handles input/output.
    while (true) {
        command = nextCommand(&n, &index, &newCost, &printCommand, &newProjName);

        // All potential inputs are handled in this if/else tree.
        if (command == "quit") {
            cout << "Next Command: " << command << endl;
            return 0;
        } else if (command == "fileread") {
            cout << "Next Command: " << command << endl;
            // Guard block against reading file if maxHeap projectList has not been instantiated.
            if (maxHeap->projectList == NULL) {
                cout << "Error: heap not created" << endl;
            } else {
                // Open file
                ifstream inputFile("heapInfo.txt");
                string inputString;
            
                // Read first line (number of projects) and convert to int.
                getline(inputFile, inputString);
                int numProj = std::stoi(inputString);

                // Guard block against reading file if maxHeap does not have capacity for all data.
                if (numProj > maxHeap->maxSize) {
                    cout << "Error: array size exceeds heap capacity" << endl;
                } else {
                    // Read rest of lines and store into Project array.
                    Project *projArray = new Project[numProj+1];
                    int index = 1; // Heap is indexed from 1
                    string projName;
                    int projCost;
                    while (getline(inputFile, inputString)) {
                        // Parse input line to retrieve project name and project cost.
                        projName = inputString.substr(0, inputString.find(" "));
                        projCost = std::stoi(inputString.substr(inputString.find(" ")+1));

                        // Create new project from parsed data and add to Project array. 
                        Project newProject = {projCost, projName};
                        projArray[index] = newProject;
                        index++;
                    }
                    // Build heap from Project array.
                    maxHeap->buildMaxHeap(projArray, numProj);
                }
            }
        } else if (command == "print") { 
            // Note: No guard block against empty heap needed -- handled in print function.
            cout << "Next Command: " << command << endl;
            maxHeap->printMaxHeap();
        } else if (command == "insert") {
            cout << "Next Command: " << command << " " << newProjName << " " << newCost << " " << printCommand << endl;
            // Guard blocks for null heap and invalid print command.
            if (maxHeap->projectList == NULL) {
                cout << "Error: heap not created" << endl;
            } else if ( !(printCommand == "yes" || printCommand == "no") ) {
                cout << "Error: invalid print command" << endl;
            } else {
                maxHeap->maxHeapInsert(newProjName, newCost, printCommand);
            }
        } else if (command == "create") {
            cout << "Next Command: " << command << " " << n << endl;
            // Guard block for heap capacity, as negative heap capacity isn't allowed.
            if (n < 0) {
                cout << "Error: invalid heap capacity" << endl;
            } else {
                maxHeap->create(n + 1); // Heap is indexed from 1, so size of array must be 1 greater than size of heap.
            }
        } else if (command == "extractmax") {
            cout << "Next Command: " << command << " " << printCommand << endl;
            // Guard blocks for null heap, empty heap, and invalid print command.
            if (maxHeap->projectList == NULL) {
                cout << "Error: heap not created" << endl;
            } else if (maxHeap->currentSize == 0) {
                cout << "Error: heap empty" << endl;
            } else if ( !(printCommand == "yes" || printCommand == "no") ) {
                cout << "Error: invalid print command" << endl;
            } else {
                int max = maxHeap->extractMax(printCommand);
                cout << "Extract Max = " << max << endl;
            }
        } else if (command == "increase") {
            cout << "Next Command: " << command << " " << index << " " << newCost << " " << printCommand << endl;
            // Guard blocks against null heap, invalid print command, and invalid heap index.
            if (maxHeap->projectList == NULL) {
                cout << "Error: heap not created" << endl;
            } else if ( !(printCommand == "yes" || printCommand == "no") ) {
                cout << "Error: invalid print command" << endl;
            } else if (index <= 0 || index > maxHeap->currentSize) {
                cout << "Error: invalid index" << endl;
            } else {
                maxHeap->increaseKey(index, newCost, printCommand);
            }
        } else {
            break;
        }
    }
    return 0;
}

// Parses command and accompanying variables into pointers used by main function.
string nextCommand(int * n, int * index, int * newCost, string * printCommand, string * newProjName) 
{
    string command = "?";

    while(true) {
        cin >> command;
        
        //empty space, tab, return
        if (command == " " || command == "\t" || command == "\n") {
            continue;
        }

        if (command == "quit" || command == "fileread" || command == "print") {
            break;
        }
        // Command for inserting new node into heap.
        if (command == "insert") {
            cin >> *newProjName;
            cin >> *newCost;
            cin >> *printCommand;
            break;
        }
        // Command for creating heap of size n.
        if (command == "create") {
            cin >> *n;
            break;
        }
        // Command for extracting the max from the heap.
        if (command == "extractmax") {
            cin >> *printCommand;
            break;
        }
        // Command for increasing the value of a node in the heap.
        if (command == "increase") {                
            cin >> *index;
            cin >> *newCost;
            cin >> *printCommand;
            break;
        }

        cout << "Invalid command" << endl;
    }
    return command;
}