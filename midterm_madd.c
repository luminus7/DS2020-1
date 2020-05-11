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
int madd(__u_char[], __u_char[], __u_char[]);
__u_char posD[len];
__u_char value[(A_nonzero_elements * B_nonzero_elements)];		//value를 전역으로 선언한거 맘에 안든다. 포인터로 받을 수 있게 바꾸자 or linkedlist같은거 쓰자

int main() {

	__u_char posA[len], posB[len];// posD[len];

	for (int i = 0; i < len; ++i) {
		posA[i] = (__u_char)AP[i];
		posB[i] = (__u_char)BP[i];
		posD[i] = posA[i] | posB[i];
	}
	int t = madd(posA, posB, posD);

	/* print matrix in given format */
	printf("\n\n");
	printf("row: %d\n", Row);
	printf("col: %d\n", Col);
	printf("t: %d\n", t);
	printf("DP[]: ");
	for (int i = 0; i < len; ++i)
		printf(" %d", posD[i]);
	printf("\nDV[]:");
	for (int i = 0; i < t; ++i)
		printf(" %d", value[i]);
	return 0;
}

__u_char checkbit(__u_char pos) {
	__u_char temp;
	temp = flag & pos;
	return temp;
}

int madd(__u_char posA[], __u_char posB[], __u_char posD[]) {
	int countA = 0;
	int countB = 0;
	int countD = 0;
	int sum;

	__u_char x, y;

	for (int i = 0; i < len; ++i) {
		flag |= mask;
		for (int j = 0; j < 8; ++j) {
			x = checkbit(posA[i]);
			y = checkbit(posB[i]);
			switch (COMPARE(x, y)) {
			case -1:								//value in only B position 
				sum = BV[countB];
				value[countD] = sum;
				countB++; countD++;
				break;
			case 0:									//value in A and B position (or) no value in both A and B
				if (x == 0 && y == 0) {				//no value in both Aand B
					break;
				}
				sum = AV[countA] + BV[countB];
				if (sum) {							//value in A and B position, sum is NOT Zero
					value[countD] = sum;
					countA++; countB++; countD++;
				}
				else {								//value in A and B position, sum is ZERO
					__u_char dtemp = posD[i];
					int exp = 7 - j;
					int subtr = 1;
					subtr = subtr << exp;
					dtemp = dtemp - (__u_char)subtr;
					posD[i] = dtemp;
				}
				break;
			case 1:						//value in only A position 
				sum = AV[countA];
				value[countD] = sum;
				countA++; countD++;
			}
			flag = flag >> 1;
		}
	}
	for (int i = 0; i < countD; ++i) {
	}
	return countD;
}