#include <stdio.h>
#include <stdlib.h>

#define POLY_SIZE 3
#define MAX_SIZE 9
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))

typedef struct {
	int coef; //coefficient, 계수
	int exp; //exponential, 지수
} polynomial; //구조체 정의와 동시에 polynomial 변수로 선언

void printpoly(polynomial* [], int);

int main(){

	int A_coef[3] = { 2,2,3 }; int A_exp[3] = { 3,2,4 }; // A(x) = 2x^3 + 2x^2 + 3x^4
        polynomial* A[POLY_SIZE]; //구조체형 포인터형 배열 A[] 선언

	for (int i = 0; i < POLY_SIZE; i++) { //Assign values into polynomial
		A[i] = malloc(sizeof(polynomial)); //각 포인터형 배열에 구조체 크기만큼 메모리 할당
		A[i]->coef = A_coef[i]; //만들어진 메모리 공간(구조체)에 기존값 할당
		A[i]->exp = A_exp[i];
		printf("for i to POLY_SIZE: %d\n",i);
	}
	printpoly(A, POLY_SIZE);

return 0;
}

void printpoly(polynomial *list[], int n) 
{ 
	printf("printpoly: on\n");
	for(int i = 0; i < n ; i++){ 
		printf("%dx^%d ", (list[i]->coef), list[i]->exp);
		printf("+ ");
	} 
	printf("\n"); 
}
