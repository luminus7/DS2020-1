#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define numRow 10
#define numCol 10
#define MAX_STACK_SIZE 100

#define EXIT_ROW numRow-1
#define EXIT_COL numCol-1

int maze[numRow][numCol] = {
	{ 0,0,1,0,1,1,1,0,1,0 },
	{ 1,0,0,1,1,1,0,1,0,1 },
	{ 1,1,0,1,1,0,1,0,1,1 },
	{ 0,0,1,0,1,1,1,0,0,0 },
	{ 0,1,1,0,1,0,1,0,1,0 },
	{ 1,0,1,1,1,1,0,0,1,0 },
	{ 1,1,0,1,0,1,0,0,1,0 },
	{ 1,0,0,0,1,0,1,0,0,0 },
	{ 0,1,0,1,1,1,0,1,1,0 },
	{ 1,0,0,1,1,1,0,0,0,0 }
};

typedef struct {
	short int row;
	short int col;
}element;


element stack[MAX_STACK_SIZE];
int top = -1;

typedef struct {
	short int vert;
	short int horiz;
}offsets;

/*move maze using 8 directions*/
offsets move[8] = {
	{-1, 0},
	{-1, 1},
	{ 0, 1},
	{ 1, 1},
	{ 1, 0},
	{ 1,-1},
	{ 0,-1},
	{-1,-1},
};


void push(element item) {
	if (top >= MAX_STACK_SIZE)
		fprintf(stderr, "stack overflow");
	top = top + 1;
	stack[top] = item;
}

element pop() {
	if (top < 0)
		fprintf(stderr, "stack underflow");
	element X = stack[top];
	top = top - 1;
	return X;
}
void path();

int main() {
	path();
	return 0;
}


void path() {
	int i, row, col, nextRow, nextCol, direct = 0, found = FALSE;	//dir초기화 하는게 88번 줄에도 있는데 시작할때 예외처리해주기 위해 dir을 0으로 둔 것임. 82번 줄을 아래 else문 안에도 넣을 수 있지만 if(dir == 8)... while문 돌때 항상 조사해주는게 overhead가 크다고 생각했음. 근거는...?
	element position;
	printf("pathfinding...\n");
	top = 0;
	stack[0].row = 0;
	stack[0].col = 0;
	while (top > -1 && !found) {		//stack에 backtrack할게 남아있고 아직 덜찾았으면 계속 실행, 스택에 더 남아있는게 없으면 종료 아니면 스택과 무관하게 경로 찾았으면 종료...우왕... 논리소자네
		if (direct >= 8) {
			printf("valid move없으니 현위치 바리케이드 치기\n");
			maze[row][col] = 1;
		}							/*****내 scheme: pop이 필요해질 때 (blocked상태일때, dir은 8일테니까) 블록된 위치를 1로 바꾸어버림(막아버림)*****/
		printf("***pop!...\n");
		position = pop(&top);
		row = position.row;
		col = position.col;
		direct = 0;

		while (direct < 8 && !found) {		// 시도할 방향있고 아직 덜찾았으면 계속 실행, 시도할 방향이 없어지면 while2 탈출 or 찾았으면 while2 탈출
			printf("-> dir: %d\n", direct);
			printf("-> %2d%5d\n\n", row, col);
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;

			if (row == EXIT_ROW && col == EXIT_COL) {		//maze 탈출지점 도착
				printf("***PATH FOUND...\n");
				found = TRUE;
			}
			else if (!maze[nextRow][nextCol] && (nextRow > -1) && (nextCol > -1) && (nextRow < numRow) && (nextCol < numCol)) {	//시도할 valid move가 남아있다면 ... 길이 열려있다면만 조사해주면 되넹, 내 scheme에서는...
				printf("***valid move...\n");
				position.row = row;
				position.col = col;
				printf("***push!...\n");
				push(position);					//valid move실행하기 전 현 위치를 stack에 push (위치정보만)
				maze[row][col] = 1;				/********내 scheme, 다음 위치로 이동할 때, 방금 전 방향으로 돌아오는 경우를 제외하기 위함********/

				row = nextRow;
				col = nextCol;
				dir = 0;
			}
			else {
				printf("***check different path...\n");
				dir++;
			}
		}
	}
	if (found) {
		printf("The path is: \n");
		printf("row   col\n");
		for (i = 0; i <= top; i++)
			printf("%2d%5d%5d\n", stack[i].row, stack[i].col, i);
		printf("%2d%5d\n", row, col);
	}
}
