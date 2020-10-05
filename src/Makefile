############################################
# @file Makefile
# @author Cameron Anundson (1216724132)
# @brief Makefile for CSE 310 Assignment4
############################################

EXEC = assignment4
CPP = g++
CFLAGS = -c -Wall

$(EXEC) : Assignment4.o MaxHeap.o
	$(CPP) -o $(EXEC) Assignment4.o MaxHeap.o

Assignment4.o : Assignment4.cpp
	$(CPP) $(CFLAGS) Assignment4.cpp

MaxHeap.o : MaxHeap.h MaxHeap.cpp
	$(CPP) $(CFLAGS) MaxHeap.cpp


clean :
	rm *.o
