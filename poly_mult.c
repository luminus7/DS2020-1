#include <stdio.h>
#include <stdlib.h>

#define POLY_SIZE 3
#define MAX_SIZE 9
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))

typedef struct {
	int coef; //coefficient, 계수
	int exp; //exponential, 지수
} polynomial; //구조체 정의와 동시에 polynomial 변수로 선언

void sort (int[], int);
void printpoly (polynomial* [], int);

int main() {
	int A_coef[3] = { 2,2,3 }; int A_exp[3] = { 3,2,4 }; // A(x) = 2x^3 + 2x^2 + 3x^4
	int B_coef[3] = { 7,3,4 }; int B_exp[3] = { 0,1,2 }; // B(x) = 7x^0 + 3x^1 + 4x^2

	polynomial* A[POLY_SIZE]; //구조체형 포인터형 배열 A[] 선언
	polynomial* B[POLY_SIZE];
	polynomial* C[MAX_SIZE];

for (int i = 0; i < POLY_SIZE; i++) { //Assign values into polynomial
	A[i] = malloc(sizeof(polynomial)); //각 포인터형 배열에 구조체 크기만큼 메모리 할당
	B[i] = malloc(sizeof(polynomial));
	C[i] = malloc(sizeof(polynomial));

	A[i]->coef = A_coef[i]; //만들어진 메모리 공간(구조체)에 기존값 할당
	B[i]->coef = B_coef[i];

	A[i]->exp = A_exp[i];
	B[i]->exp = B_exp[i];
}


printpoly(A, POLY_SIZE);
printpoly(B, POLY_SIZE);

//use selection sort(non-incr) to sort polynomial A and B
for (int i = 0; i < POLY_SIZE; i++) {
	sort(A[i]->exp, POLY_SIZE);
}
printpoly(A, POLY_SIZE);

for (int i = 0; i < 3; i++) { //multiply polynomial and assign result into C[]
	for (int j = 0; j < 3; j++) {

	}
}



return 0;
}


void sort(int list[], int n) //Sangjin Lee 헤더파일로 빼버리자
{
	int max, temp;
	for (int i = 0; i < n - 1; i++) {
		max = i;
		for (int j = i + 1; j < n; j++) {
			if (list[max] < list[j])
				max = j;
		}
	SWAP(list[i], list[max], temp);
	}
}

void printpoly(polynomial* list[], int n)
{
	for(int i = 0; i < n; i++){
		printf("%dx^%d ", list[i]->coef, list[i]->exp);
		if(i != 2)
			printf("+ ");	
	}
	printf("\n");
}
