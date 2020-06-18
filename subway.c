#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100



int matrix2[MAX_SIZE][MAX_SIZE];
int matrix[MAX_SIZE][MAX_SIZE];
int link[100][30] = { 0, };
int top2 = 0;
int distance[MAX_SIZE];
int found[MAX_SIZE];
int n = MAX_SIZE;

int top = 0;
typedef struct transfer* pointer;

pointer stack[MAX_SIZE];
pointer stack2[MAX_SIZE];

typedef struct transfer {
	int name;
	pointer next;
};

void init() {
	for (int i = 0; i < MAX_SIZE; i++) {
		stack[i] = (pointer)malloc(sizeof(*stack[0]));
	}
}

void transpate() {
	for (int i = 0; i < MAX_SIZE; i++) {
		stack2[i] = (pointer)malloc(sizeof(*stack2[0]));
		stack2[i] = stack[i];
	}
}


//push 함수 손보기
void push(int a, int b) {
	/* showing a,b connected */
	pointer k_next = (pointer)malloc(sizeof(*k_next));
	stack[a]->name = a;
	k_next = stack[a]->next;
	k_next->name = b;
	
	stack[a] = stack[a]->next;

}
int choose() { 
	/* find smallest distance not yet checked */ 
	int i, min, minpos; 
	min = INT_MAX; 
	minpos = -1; 
	for (i = 0; i < n; i++) 
		if (distance[i] < min && !found[i]) { 
			min = distance[i]; 
			minpos = i; 
		} 
	return minpos; 
}

void shortestPath(int v,int n2){
	init();
	transpate();

	int i, u, w;
	for (i = 0; i < n; i++) {
		found[i] = 0;
		distance[i] = matrix[v][i];
	}
	int tag = 0;
	found[v] = 1;
	distance[v] = 0;
	for (i = 0; i < n - 2; i++) {
		u = choose();
		found[u] = 1;
		for (w = 0; w < n; w++)
			if (!found[w])
				if (distance[u] + matrix[u][w] < distance[w]) {
					push(u, w);
					distance[w] = distance[u] + matrix[u][w];
					matrix[v][w] = distance[w];
					matrix[w][v] = matrix[v][w];
				}
	}
}







// 1호선	25 서면 26 부전 29 연산 30 교대 31 동래 (1~40 : 1호선)
// 2호선	45 백스코 48 수영 59 서면 67 사상 73 덕천 (41~83 : 2호선)
// 3호선	84 수영 88 연산 89 거제 92 미남 96 덕천 100 대저 (84~100 : 3호선)
// 4호선	101 미남 102 동래 (101~114 : 4호선)
// 5호선	115 사상 121 대저 (109~135 : 부산김해(5호선))
// 6호선	136 부전 138 거제 139 교대 146 백스코 (136~151 : 동해선(6호선))



//1호선		서면 동래
//2호선		백스코 덕진
//3호선		수영 대저
//4호선		미남 안평
//5호선		


int speculate(int p) {
	int sum = 0;
	int i = 0;
	for (i; i < MAX_SIZE; i++) {
		if (matrix2[p][i] == 1)
			sum++;
	}
	if (sum == 2)
		return 1;
	else
		return 0;

}

main() {
	int i = 0;
	int j = 0;
	int n1, n2;
	for (i=0; i < MAX_SIZE; i++) {
		for (j = 0; j < MAX_SIZE; j++) {
			scanf("%d", &matrix[i][j]);
			matrix2[i][j] = matrix[i][j];
			//printf("abcdffsfasdlkfjaldfkjaef");
		}
	}

	printf("\n출발지와 목적지 선택\n");
	scanf("%d %d", &n1, &n2);
	/*for (i=0; i < MAX_SIZE; i++) {
		for (j = 0; j < MAX_SIZE; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}*/


	for (i = 0; i < MAX_SIZE; i++) {
		if (i == n1) {
			shortestPath(i,n2);
		}
		else {
			shortestPath(i,0);
		}
		
	}
	i = 0;
	printf("%d정거장 지남\n", matrix[n1][n2]);

	while (link[i]) {
		printf("%d-\t", link[i]);
		if (speculate(i) == 1)
			printf("\t환승역 아님\n");
		else
			printf("\t환승역\n");
		
		i++;
	}

}