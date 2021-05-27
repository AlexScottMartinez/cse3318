#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "spell.h"

int min(int a, int b, int c);

/*  Suggestions
- When you work with 2D arrays, be careful. Either manage the memory yourself, or
work with local 2D arrays. Note C99 allows parameters as array sizes as long as 
they are declared before the array in the parameter list. See: 
https://www.geeksforgeeks.org/pass-2d-array-parameter-c/

Worst case time complexity to compute the edit distance from T test words
 to D dictionary words where all words have length MAX_LEN:
Student answer:  Theta(3^n)


Worst case to do an unsuccessful binary search in a dictionary with D words, when 
all dictionary words and the searched word have length MAX_LEN 
Student answer:  Theta(M*logN)
*/


/* You can write helper functions here */

int min(int a, int b, int c)
{
    if ((a <= b) && (a <= c))
    {
        return a;
    }
    if ((b <= c) && (b <= a))
    {
        return b;
    }
    return c;
}

/*
Parameters:
first_string - pointer to the first string (displayed vertical in the table)
second_string - pointer to the second string (displayed horizontal in the table)
print_table - If 1, the table with the calculations for the edit distance will be printed.
              If 0 (or any value other than 1)it will not print the table
(See sample run)
Return:  the value of the edit distance (e.g. 3)
*/
int edit_distance(char * first_string, char * second_string, int print_table)
{
    int f = strlen(first_string);
    int s = strlen(second_string);
    int i, j;
    int matrx[f + 1][s + 1];

    
    for (i = 0; i <= f; i++)
    {
        for (j = 0; j <= s; j++)
        {
            if (i == 0)
            {
                matrx[i][j] = j;
            }
            else if (j == 0) 
            {
                matrx[i][j] = i;
            }
            else if (first_string[i-1] == second_string[j-1])
            {
                matrx[i][j] = matrx[i-1][j-1];
            }
            else {
                matrx[i][j] = 1 + min(matrx[i][j-1], matrx[i-1][j], matrx[i-1][j-1]);
            }
        }
    }
    printf("\n");
        
    if (print_table == 1)
    {
        for (i = 0; i < f+1; i++)
        {
            for (j = 0; j < s+1; j++)
            {
                printf("  %d", matrx[i][j]);
                if (matrx[i][j] < 10)
                {
                    printf("|");
                }
                else {
                    printf("|");
                }
            }
            printf("\n");
            for (;j >= 0;--j)
            {
                printf("----");
            }
            printf("\n");
        }
        printf("\n");
    }
    return matrx[f][s];
}
	  

/*
Parameters:
testname - string containing the name of the file with the paragraph to spell check, includes .txt e.g. "text1.txt" 
dictname - name of file with dictionary words. Includes .txt, e.g. "dsmall.txt"
printOn - If 1 it will print EXTRA debugging/tracing information (in addition to what it prints when 0):
			 dictionary as read from the file	
			 dictionary AFTER sorting in lexicographical order
			 for every word searched in the dictionary using BINARY SEARCH shows all the "probe" words and their indices indices
			 See sample run.
	      If 0 (or anything other than 1) does not print the above information, but still prints the number of probes.
		     See sample run.
*/
void spell_check(char * testname, char * dictname, int printOn)
{
    FILE* fp1 = fopen(testname, "r");
    FILE* fp2 = fopen(dictname, "r");
    int dictSize, temp, length, i, j, k, count, distance;
    char *words[1000];
    int array[1000];
    char *dictionary[10000];
    if ((!fp1) || (!fp2))
    {
        printf("\nUnable to open files for reading");
        return;
    }
    fscanf(fp2, "%d", &dictSize);
    for (i= 0; i < dictSize; i++)
    {
        dictionary[i] = (char*) malloc(100*sizeof(char));
        fscanf(fp2, "%s", dictionary[i]);
    }
    fscanf(fp1, "%d", &length);
    for (i = 0; i < length; i++)
    {
        words[i] = (char*) malloc(100*sizeof(char));
        fscanf(fp1, "%s", words[i]);
    }
    for (i = 0; i < length; i++)
    {
        distance = edit_distance(words[i], dictionary[0], 0);
        printf("\n--------------------\n");
        count = 1;
        array[0] = 0;
        for (j = 1; j < dictSize; j++)
        {
            temp = edit_distance(words[j], dictionary[j], 0);
            array[j] = temp;
            if (temp < distance)
            {
                distance = temp;
                count = 1;
                array[0] = j;
            }
            else if (temp == distance)
            {
                array[count] = j;
                count++;
            }
        }
        printf("Current word = %s", words[i]);
        printf("\nmin. distance = %d\n", distance);
        for (k = 0; k < count; k++)
        {
            printf("%s\n", dictionary[array[k]]);
        }
    }  
}
