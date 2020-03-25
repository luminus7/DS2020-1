/*
* 
* Chung-Ang UNIV. school of CSE
* Data Structure lecture 2020-1
* 20162191 SangJin Lee (CSE undergraduate student)
* Fundamentals of Data Structures in C 2nd edit. chap.1 program 1.4
* <Selection sort>
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_SIZE 101
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))

void sort(int [], int); /*selection sort*/

int main()
{
    int i, n;
    int list[MAX_SIZE];
    printf("Enter the number of numbers to generate: ");
    scanf("%d",&n);

//예외처리
    if( n < 1 || n > MAX_SIZE ){
       fprintf(stderr, "Improper value of n/n");
       exit(EXIT_FAILURE);
    }

    for( i = 0 ; i < n ; i++){
        /*randomly generate numbers*/
        list[i] = rand() % 1000;
        printf("%d  ",list[i]);
    }
    sort(list,n);
    printf("\n Sorted array: \n");

    for(i = 0 ; i < n ; i++)
        printf("%d  ",list[i]);
    printf("\n");   

return 0;
}

void sort (int list[], int n)
{
    int i, j, max, temp;
    for (i = 0 ; i < n-1 ; i++){
        max = i;
        for(j = i+1; j < n ; j++){
            if(list[max] < list[j])
            max = j;
	}
        SWAP(list[i], list[max], temp);
    }
}
