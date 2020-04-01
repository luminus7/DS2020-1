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
    int i, n, f;
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
    scanf_s("%d", &f);

    int temp = binsearch(list, f, 0, n - 1);
    printlist(i, n, list);

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
    int middle, shifter;
    int L = left;
    int R = right;

    while (left <= right) {
        middle = (left + right) / 2;
        switch (COMPARE(list[middle], searchnum)) {
            case -1: left = middle + 1;
                break;
            case 0: return middle;
            case 1: right = middle - 1;
        }
    }

    if ( (COMPARE(list[middle], searchnum)) != 1) { //mid보다 searchnum이 크면 mid 오른쪽 시작, 나머지 부분들은 오른쪽으로 쭉쭉 밀어야겠네
        for (shifter = middle + 1; shifter < R; shifter++) {
            list[shifter] = list[shifter + 1];//다시방..ㅈ
        }
        printf("matching number does NOT exist\n");
        printf("number inserted right side of middle\n");
        list[middle + 1] = searchnum;
    }
    else {

    }
    return -1;
}

int printlist(int i, int n, int list[]) {
    for (i = 0; i < n; i++)
        printf("%d  ", list[i]);
    printf("\n");
}
