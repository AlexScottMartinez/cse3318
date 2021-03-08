/* 
 * Updated 2/25/2021 - Alexandra Stefan
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "list.h"


/* 
compile with -g to collect debugging info needed for Valgrind: 
gcc -g bucket_sort.c list.c

run with Valgrind:
valgrind --leak-check=full --show-leak-kinds=all ./a.out

run without Valgrind:
./a.out
*/

void print_array(int arr[], int N);
void run1();
void bucket_sort(int arr[], int N);
//nodePT insert_sorted(nodePT L, nodePT newP);

/* // recommended helper functions:
// function to insert a new node in a sorted list.
nodePT insert_sorted(nodePT L, nodePT newP);
//  function to sort an array sing bucket sort
void bucket_sort(int arr[], int N)
*/

void print_array(int arr[], int N)
{
	int j;
	printf("\n array: ");
	for(j=0; j<N; j++){
		printf("%5d,", arr[j]);
	}
	printf("\n");
}

void bucket_sort(int arr[], int N)
{
    int i, j;
    int count[N];
    for (i=0; i<N; i++)
        count[i] = 0;
        
    for (i=0; i<N;i++)
        (count[arr[i]])++;
        
    for (i=0, j=0; i<N; i++)
        for (; count[i]>0; (count[i])--)
            arr[j++] = i;

    //print_array(arr, N);    
}

//-------------------------------------------------------------


void run1(){
  // Fill in your code here. You should not write everything in this function.  
  // Write some helper functions to separate the work.	
    char fname[100];
	int mx_size, i;
	int arr[mx_size];
	FILE *fp;

	printf("Enter the filename: ");
	scanf("%s", fname);
	fp =fopen(fname, "r");
	if (fp == NULL){
		printf("File could not be opened.\n");
		return 1;
	}
	fscanf(fp, "%d", &mx_size);
	for (i=0; i<mx_size; i++)
	    fscanf(fp, "%d", &arr[i]);
	    
	    
	fclose(fp);
	print_array(arr, mx_size);
	//bucket_sort(arr, mx_size);



	return 1;
}

int main()
{
	printf("This program will read a file name, load data for an array from there and print the sorted array.\n");
	printf("The array is sorted using bucket sort.\n");
	printf("This will be repeated as long as the user wants.\n");
	int option;
	do {
		run1();
		printf("\nDo you want to repeat? Enter 1 to repeat, or 0 to stop) ");
		scanf("%d",&option);
	} while (option == 1);

   return 0;
}
