#include <stdio.h>
#include <stdlib.h>

#define POLY_SIZE 3
#define MAX_SIZE 9
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))

typedef struct {
	int coef; //coefficient
	int exp; //exponential
} polynomial; //구조체 정의와 동시에 polynomial 변수로 선언

polynomial* A[POLY_SIZE];							 //구조체형 포인터형 전역배열 A[] 선언
polynomial* B[POLY_SIZE];
polynomial* C[MAX_SIZE];

void sort(polynomial* [], int);
void printpoly(polynomial* [], int);
int multiplypoly(polynomial* [], polynomial* [], int);


int main() {
	int A_coef[3] = { 2,2,3 }; int A_exp[3] = { 3,2,4 }; // A(x) = 2x^3 + 2x^2 + 3x^4
	int B_coef[3] = { 7,3,4 }; int B_exp[3] = { 0,1,2 }; // B(x) = 7x^0 + 3x^1 + 4x^2


	for (int i = 0; i < POLY_SIZE; i++) {	//Assign values into polynomial A and B
		A[i] = malloc(sizeof(polynomial));	//각 포인터형 배열에 구조체 크기만큼 메모리 할당
		B[i] = malloc(sizeof(polynomial));

		A[i]->coef = A_coef[i];				//만들어진 메모리 공간(구조체)에 기존값 할당
		B[i]->coef = B_coef[i];
		A[i]->exp = A_exp[i];
		B[i]->exp = B_exp[i];
	}
	for (int i = 0; i < MAX_SIZE; i++) {	//Assign values into polynomial C
		C[i] = malloc(sizeof(polynomial));
	}

	printf("--original polynomial A and B--\n");
	printpoly(A, POLY_SIZE);
	printpoly(B, POLY_SIZE);

	//use selection sort(non-incr) to sort polynomial A and B
	for (int i = 0; i < POLY_SIZE; i++) {
		sort(A, POLY_SIZE);
		sort(B, POLY_SIZE);
	}
	printf("\n--sorted polynomial A and B--\n");
	printpoly(A, POLY_SIZE);
	printpoly(B, POLY_SIZE); 

	int count = multiplypoly(A, B, POLY_SIZE);

	printf("\n--after sorting polynomial C--\n");
	printpoly(C, POLY_SIZE + count);
	return 0;
}


void sort(polynomial* list[], int n) { //Sangjin Lee 헤더파일로 빼버리자
	int max, temp;
	for (int i = 0; i < n - 1; i++) {
		max = i;
		for (int j = i + 1; j < n; j++) {
			if ((list[max]->exp) < (list[j]->exp))
				max = j;
		}
		SWAP(list[i], list[max], temp);
	}
}

void printpoly(polynomial* list[], int n) {
	printf("polynomial: "); //while문으로 돌아서 poly->exp 가 0보다 작으면 print안되는 걸로 짜자
	for (int i = 0; i < n; i++) {
		printf("%dx^%d ", list[i]->coef, list[i]->exp);
		if (i != n - 1)
			printf("+ ");
	}
	printf("\n");
}

/*
 *'multiply' polynomial A and B
 * then 'sort' C (the result of multiplication A and B)
 * 'search' to find if there is any same exp value in C
 * if there is same exp value in C, then add coefs to make one polynomial in one term
 */
int multiplypoly(polynomial* A_parr[], polynomial* B_parr[], int n) { 
	int count = 0;
	polynomial* new = malloc(sizeof(polynomial));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != 0) {
				new->coef = (A_parr[i]->coef) * (B_parr[j]->coef);
				new->exp = (A_parr[i]->exp) + (B_parr[j]->exp);

				printf("\ni: %d,j: %d\n\n", i, j);
				printf("A_parr[i]->coef: %d\n", A_parr[i]->coef);
				printf("         *\n");
				printf("B_parr[i]->coef: %d\n\n", B_parr[j]->coef);
				printf("A_parr[i]->exp: %d\n", A_parr[i]->exp);
				printf("         +\n");
				printf("B_parr[i]->exp: %d\n\n", B_parr[j]->exp);

				int x = binsearch(C, new, 0, 2 + count); //use binarysearch to find matching exponential value in C[]
				if(x == -1) // count++ if there was existing exponential value
					count++;
			}
			else {
				C[3 * i + j]->coef = (A_parr[i]->coef) * (B_parr[j]->coef);
				C[3 * i + j]->exp = (A_parr[i]->exp) + (B_parr[j]->exp);
			}
		}
	}

	sort(C, MAX_SIZE);
	return count;
}

#define COMPARE(x,y) ( ((x)<(y))? -1 : ((x)==(y))? 0 : 1 )

int binsearch(polynomial* list[], polynomial* new, int left, int right) {
	int middle = 0;
	int R = right;

	while (left <= right) {
		middle = (left + right) / 2;
		switch (COMPARE(list[middle]->exp, new->exp)) {
		case -1: right = middle - 1;
			break;
		case 0:	list[middle]->coef = (list[middle]->coef) + (new->coef);
			return 0;
		case 1: left = middle + 1;
		}
	}

	int i = 0;
	while ((list[i]->exp > new->exp) && (list[i]->exp > -1))
		i++;   //search proper dest to insert 'searchnum'

	int dest = i - 1;

	while ((R + 1) != i) {  //shift array elements to the right, until get free space to insert 'searchnum'
		list[R + 1] = list[R];
		R--;
	}
	list[dest + 1]->exp = new->exp;
	list[dest + 1]->coef = new->coef;

	return -1;
}
