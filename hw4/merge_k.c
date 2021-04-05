#include <stdlib.h>
#include <stdio.h>


#include "merge_k.h"  // includes list.h


/*  Sorts linked list L in pace using insertion sort. 
*/
nodePT sort_list(nodePT L){
	// implement insertion sort for linked list
}

/* It is recommended to implement a sinkDown function in this file. 
You can declare its header at the top of this file (after include) 
write the implementation anywhere in this file. 
(You cannot modify any of the list.h or merge_k.h files) 
*/



/* Turns the given array (named heap) into an actual Min-Heap
   using the bottom-up method to build the heap. 
   (See buidMaxHeap pseudocode in slides)
*/
void make_heap(int k, nodePT heap[k]){
	// write your code in here
}



/*  heap is a Min-Heap of linked lists
	remove_min will remove AND RETURN the first node of the list at index 0.
	k (size of heap) will only change when that removal leaves that list empty.
*/
nodePT remove_min(int* k, nodePT heap[(*k)]){
	// Replace the place holder code with the correct code
   return NULL;  // place holder code. 
}


/*
   heap is a Min-Heap array of SORTED single linked lists. 
   Merging process: 
	- use the heap to identify and remove the node, np, with the smallest data out 
      of the k lists.
	- insert np at the end of result list.

   Returns: a sorted single linked list built by merging the k lists.
*/
nodePT merge_k(int k, nodePT heap[k]){
	// Replace the place holder code with the correct code
   return NULL;   // place holder code
}

