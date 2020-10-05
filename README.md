# README
CSE 310, Nakamura, M/W 3:05PM
Assignment 4

# README Organization
- Description
- How to run
- Files and descriptions

## Description
This project implements a max heap. It also contains a runner for interacting
with the max heap. It's highly commented for grading and clarity purposes.

## How to run 
To run the project, do the following commands:
make
./assignment4

The following describes the commands that are allowed:

COMMAND:     create n

CONSTRAINTS: n >= 0

DESCRIPTION: Creates a new max heap of size n.

---

COMMAND:     fileread

CONSTRAINTS: n/a

DESCRIPTION: Reads file "heapInfo.txt" and uses data from file to create max heap.

---

COMMAND:     print

CONSTRAINTS: n/a

DESCRIPTION: Prints max heap.

---

COMMAND:     insert projName projCost printCommand

CONSTRAINTS: projName is a string
	     projCost is an int
	     printCommand == "yes" or printCommand == "no"
	     
DESCRIPTION: Inserts new node to max heap with the fields projName and projCost.
	     If printCommand == "yes", will print heap before and after insertion.
	     If printCommand == "no", will NOT print heap before and after insertion.

---

COMMAND:     extractmax printCommand

CONSTRAINTS: printCommand == "yes" or printCommand == "no"

DESCRIPTION: Extracts max value from max heap and prints the max value.
	     If printCommand == "yes", will print heap before and after extraction.
	     If printCommand == "no", will NOT print heap before and after extraction.

---

COMMAND:     increase index newCost printCommand

CONSTRAINTS: index is an int
             newCost is an int and greater than cost of Project node at index
       	     printCommand == "yes" or printCommand == "no"
	     
DESCRIPTION: Increases value of key of node at index to newCost.
	     If printCommand == "yes", will print heap before and after extraction.
	     If printCommand == "no", will NOT print heap before and after extraction.

---

COMMAND:     quit

CONSTRAINTS: n/a

DESCRIPTION: program stops reading commands and exits

## Files and Descriptions
FILE:        Makefile

DESCRIPTION: Creates assignment4 executable, used to compile project in one easy command.

---

FILE:        Assignment4.cpp

DESCRIPTION: Contains runner and command parser for project.

---

FILE:        MaxHeap.h

DESCRIPTION: Header file for max heap implementation.

---

FILE:        MaxHeap.cpp

DESCRIPTION: CPP file that contains code that implements max heap functionality.
