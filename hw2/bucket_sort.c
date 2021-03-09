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
nodePT insert_sorted(nodePT L, nodePT newP);

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
	for(j=0; j<N; j++)
	{
		printf("%5d,", arr[j]);
	}
	printf("\n");
}

void bucket_sort(int arr[], int N)
{
    int k, j, h, min, max;
    int* idx = malloc(N * sizeof(int));
    // Finding the Maximum and Minimum of the array
    max = arr[0];
    min = arr[0];
    for (j=1; j<N; j++)
    {
        if (arr[j] > max)
        {
            max = arr[j];
        }
        if (arr[j] < min)
        {
            min = arr[j];
        }
    }
    printf("\nBucketsort: min = %d, max = %d, N = %d buckets\n", min, max, N);
    // Finding the indexes
    for (h=0; h<N; h++)
        idx[h] = floor(((arr[h]-1)/(max-min+1))*N);
    for (k=0; k<N; k++)
        printf("arr[%d]=    %d, idx = %d\n", k, arr[k], idx[k]);
        
    free(idx);
    //print_array(arr, N);    
}

//-------------------------------------------------------------


void run1(){
  // Fill in your code here. You should not write everything in this function.  
  // Write some helper functions to separate the work.	
    char fname[100];
	int mx_size, i;
	int* arr = malloc(mx_size * sizeof(int));
	FILE *fp;

	printf("Enter the filename: ");
	scanf("%s", fname);
	fp =fopen(fname, "r");
	if (fp == NULL)
	{
		printf("File could not be opened.\n");
		return;
	}
	else
	{

        fscanf(fp, "%d", &mx_size);
	    for (i=0; i<mx_size; i++)
        {
            fscanf(fp, "%d", &arr[i]);
	    }
	
	    fclose(fp);
	    print_array(arr, mx_size);
	    bucket_sort(arr, mx_size);
	    free(arr);
	    return;
    }
}

int main()
{
	printf("This program will read a file name, load data for an array from there and print the sorted array.\n");
	printf("The array is sorted using bucket sort.\n");
	printf("This will be repeated as long as the user wants.\n");
	int option;
	do 
	{
		run1();
		printf("\nDo you want to repeat? Enter 1 to repeat, or 0 to stop) ");
		scanf("%d",&option);
	} while (option == 1);

   return 0;
}
