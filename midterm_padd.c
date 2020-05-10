/*
* Chung-Ang UNIV. school of CSE
* Lecture: Data Structure 2020-1
* Author: 20162191 SangJin Lee (CSE undergraduate student)
* Textbook: Fundamentals of Data Structures in C 2nd edit.
* project: Midterm-1 | padd.c
* Add polynomial
*/

#include <stdio.h>

#define MAX_DEGREE 101	/* 다항식의 최대 차수 + 1 */
#define COMPARE(x,y) ( ((x)<(y))? -1 : ((x)==(y))? 0 : 1 )

/****************************** fix here ******************************/
#define A_nonzero_terms 3
#define B_nonzero_terms 4
float A_coef[A_nonzero_terms] = { 2.0, 2.0, 3.0 }; int A_exp[A_nonzero_terms] = { 7, 3, 2 };
float B_coef[B_nonzero_terms] = { 4.0, 3.0, 7.0, 7.0 }; int B_exp[B_nonzero_terms] = { 5, 3, 1, 0 };
/**********************************************************************/

typedef struct {
	int degree;
	float coef[MAX_DEGREE];
} polynomial;

polynomial padd(polynomial, polynomial);
void printpoly(polynomial*);

int main() {
	polynomial A, B, D;		//D will be the result of padd (A, B)
	A.degree = A_exp[0];
	B.degree = B_exp[0];
	
	for (int i = 0; i < A.degree + 1; ++i)		A.coef[i] = 0;
	for (int i = 0; i < B.degree + 1; ++i)		B.coef[i] = 0;

	for (int j = 0; j < A_nonzero_terms; ++j) {
		for (int i = 0; i < A.degree + 1; ++i) {
			if (i == A.degree - A_exp[j])
				A.coef[i] = A_coef[j];
		}
	}
	for (int j = 0; j < B_nonzero_terms; ++j) {
		for (int i = 0; i < B.degree + 1; ++i) {
			if (i == B.degree - B_exp[j])
				B.coef[i] = B_coef[j];
		}
	}

	printf("\npolynomial A: ");		printpoly(&A);
	printf("\npolynomial B: ");		printpoly(&B);

	D = padd(A, B);
	printf("\npolynomial D: ");		printpoly(&D);

	return 0;
}

polynomial padd(polynomial A, polynomial B) {
	int min_degree = 0;
	polynomial temp;
	polynomial* big = NULL;
	polynomial* small = NULL;

	switch (COMPARE(A.degree, B.degree)) {	//x-y
	case -1: big = &B; small = &A;
		break;
	case 0: big = &B; small = &A;
		break;
	case 1: big = &A; small = &B;
	}

	temp.degree = big->degree;
	min_degree = small->degree;

	int a = big->degree;
	int b = small->degree;
	int tmp = temp.degree;

	while (min_degree >= 0) {
		temp.coef[tmp] = big->coef[a] + small->coef[b];
		a--; b--; tmp--; min_degree--;
	}

	for (int i = 0; i < ((big->degree) - (small->degree)) ; ++i) {
		temp.coef[i] = big->coef[i];
	}

	return temp;
}

void printpoly(polynomial* list) {
	int degree = list->degree;
	if ((list->degree == 0) || list->coef[0] == 0) {
		fprintf(stderr, "empty polynomial or wrong expression of polynomial\n");
		fprintf(stderr, "please check your polynomial values");
	}

	int i = 0;
	while (i < degree + 1) {
		if (list->coef[i] != 0) {
			if (list->coef[i] != 0 && (i != 0))
				printf(" +");
			printf(" (%.1f)x^%d", list->coef[i], degree - i);
		}
		i++;
	}
}
