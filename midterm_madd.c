/*
* Chung-Ang UNIV. school of CSE
* Lecture: Data Structure 2020-1
* Author: 20162191 SangJin Lee (CSE undergraduate student)
* Textbook: Fundamentals of Data Structures in C 2nd edit.
* project: Midterm-2 | madd.c
* Add sparse matrix
*/

#include <stdio.h>
#include <math.h>

/****************************** fix here ******************************/
#define Row 4
#define Col 4
#define A_nonzero_elements 3	//A matrix의 nonzero element의 수
int AP[(Row * Col) / 8] = { 129, 8 }; int AV[A_nonzero_elements] = { 11, 7, -1 };
#define B_nonzero_elements 4	//B matrix의 nonzero element의 수
int BP[(Row * Col) / 8] = { 65, 136 }; int BV[B_nonzero_elements] = { 5, 2, 4, 1 };
/**********************************************************************/

#define COMPARE(x,y) ( ((x)<(y))? -1 :((x)==(y))? 0 : 1 )
#define len (Row * Col) / 8
typedef unsigned char __u_char;

__u_char flag = 0;
__u_char mask = 128;

__u_char checkbit(__u_char);
__u_char* madd(__u_char[], __u_char[], __u_char[]);


int main() {
	
	__u_char posA[len] ,posB[len], posD[len];

	for (int i = 0; i < len; ++i) {
		posA[i] = (__u_char)AP[i];		//1000 0001	| 0000 1000
		posB[i] = (__u_char)BP[i];		//0100 0001 | 1000 1000
		posD[i] = posA[i] | posB[i];	//1100 0001 | (1)000 1000		(bitwise or)
	}

	__u_char* DV;
	DV = madd(posA, posB, &posD);
	return 0;
}

__u_char checkbit(__u_char pos) {
	__u_char temp;
	temp = flag & pos;
	return temp;
}

__u_char* madd(__u_char posA[], __u_char posB[], __u_char posD[]) {
	int countA = 0;
	int countB = 0;
	int countD = 0;
	int temp;

	__u_char x, y;
	__u_char value[100];

	printf("==========================%d \n",__LINE__);
	printf("==========================%d \n", __LINE__);

	for (int i = 0; i < len; ++i) {
		printf("posA[%d]: %d\n", i, posA[i]);
		printf("posB[%d]: %d\n", i, posB[i]);
		printf("==========================\n");
		printf("==========================\n");
		flag |= mask;

		for (int j = 0; j < 8; ++j) {
			x = checkbit(posA[i]); y = checkbit(posB[i]);
			printf("x: %d  y: %d\n", x, y);
			printf("COMPARE(x,y) result: %d\n", COMPARE(x, y));

			switch (COMPARE(x,y)) {
			case -1:					//value in only B position 
				printf("A bit: 0, B bit: 1\n");
				temp = BV[countB];
				value[countD] = temp;
				printf("temp: %d\n", temp);
				countB++;
				countD++;
				break;
			case 0:						//value in A and B position (or) no value in both A and B
				if (x == 0 && y == 0) {			//no value in both Aand B
					printf("A bit: 0, B bit: 0\n");
					break;
				}
				printf("A bit: 1, B bit: 1 and...");
				temp = AV[countA] + BV[countB];
				printf("temp::: %d\n", temp);
				if (temp) {				//value in A and B position, sum is NOT Zero
					printf("sum is NOT zero.\n");
					value[countD] = temp;
					countA++;
					countB++;
					countD++;
				} else {				//value in A and B position, sum is ZERO
					printf("sum is zero.\n");
					__u_char dtemp = posD[i];
					printf("dtemp: %d  ", dtemp);
					printf("j: %d  ", j);
					int exp = 7 - j;
					int subtr = 0;
					subtr = subtr << exp;
					printf("(__u_char) 2^%d: %d  ", 7-j, (__u_char)subtr);

					dtemp = dtemp - (__u_char)subtr;
					printf("(aft calc)dtemp: %d\n", dtemp);
				}
				break;
			case 1:						//value in only A position 
				printf("A bit: 1, B bit: 0\n");
				temp = AV[countA];
				value[countD] = temp;
				printf("temp: %d\n", temp);
				countA++;
				countD++;
			}
			flag = flag >> 1;
			printf("==========================\n");
		}
	}
	printf("(non-zero of D) countD: %d", countD);
	for (int i = 0; i < countD ;++i) {
		printf("\nvalue[%d]: %d", i, value[i]);
	}

//	malloc(sizeof());
	return value;
}
