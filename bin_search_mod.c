/*
*
*- Chung-Ang UNIV. school of CSE
*- Data Structure lecture 2020-1
*- 20162191 SangJin Lee (CSE undergraduate student)
* Fundamentals of Data Structures in C 2nd edit.
* chap.1 program 1.4
* chap.1 program 1.7
*
* <selection sort and binary search>
* sorted in non-decreasing order
*
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_SIZE 101
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))
#define COMPARE(x,y) ( ((x)<(y))? -1 : ((x)==(y))? 0 : 1 )

void sort(int[], int); /*selection sort*/
int binsearch(int list[], int searchnum, int left, int right); /*binary search*/
int printlist(int i, int n, int list[]); /*print list*/

int main()
{
    int i, n, find;
    int list[MAX_SIZE];
    printf("Enter the number of numbers to generate: ");
    scanf_s("%d", &n);

    //예외처리
    if (n < 1 || n > MAX_SIZE) {
        fprintf(stderr, "Improper value of n\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < n; i++) {
        /*randomly generate numbers*/
        list[i] = rand() % 1000;
        printf("%d  ", list[i]);
    }
    sort(list, n);
    printf("\n Sorted array: \n");

    printlist(i, n, list);

    printf("Enter the number to find: ");
    scanf_s("%d", &find);

    int temp = binsearch(list, find, 0, n - 1);
    printlist(i, n+1, list);

    return 0;
}

void sort(int list[], int n)
{
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (list[j] < list[min])
                min = j;
        }
        SWAP(list[i], list[min], temp);
    }
}

int binsearch(int list[], int searchnum, int left, int right) {
    int middle = 0;
    int R = right;

    while (left <= right) {
        middle = (left + right) / 2;
        switch (COMPARE(list[middle], searchnum)) {
            case -1: left = middle + 1;
                break;
            case 0: printf("middle: %d\n", middle); return middle;
            case 1: right = middle - 1;
        }
    }
    printf("value does not exist\n");

    printf("shift list to right to make emptied memory dest\n");

    int i = 0;
    while ( (list[i] < searchnum) && (list[i] > 0) ) i++;   //search proper dest to insert 'searchnum'
    int dest = i - 1;

    while ((R + 1) != i) {  //shift array elements to the right, until get free space to insert 'searchnum'
        list[R + 1] = list[R];
        R--;
    }
    list[dest + 1] = searchnum; //insert 'searchnum'
    
    return -1;
}

int printlist(int i, int n, int list[]) {
    for (i = 0; i < n; i++)
           if(list[i] > 0)
               printf("%d  ", list[i]);
    printf("\n");
}
