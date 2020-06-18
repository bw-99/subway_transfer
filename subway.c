#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100


int matrix[12][12] = {
	{0,1,1000,1000,1000,1000,1000,1000,4,3,1000,1000},	//미남
	{1,0,1,1000,1000,1000,1000,1000,1000,1000,1000,1000},//동래
	{1000,1,0,6,1000,1000,1000,1000,1000,1,1000,1},		//교대
	{1000,1000,6,0,3,1000,1000,1000,1000,1000,1000,1000},//백스코
	{1000,1000,1000,3,0,11,1000,1000,1000,1000,1000,4},	//수영
	{1000,1000,1000,1000,11,0,8,1000,1000,1000,1,1000},//서면
	{1000,1000,1000,1000,1000,8,0,6,6,1000,1000,1000},//사상
	{1000,1000,1000,1000,1000,1000,6,0,4,1000,1000,1000},//대저
	{4,1000,1000,1000,1000,1000,6,4,0,1000,1000,1000},//덕천
	{3,1000,1,1000,1000,1000,1000,1000,1000,0,2,1},//거제
	{1000,1000,1000,1000,1000,1,1000,1000,1000,2,0,3},//부천
	{1000,1000,1,1000,4,1000,1000,1000,1000,1,3,0}	//연산
};

int distance[12];
int found[12];
int n = 12;

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

void shortestPath(int v){
	int i, u, w;
	for (i = 0; i < n; i++) {
		found[i] = 0;
		distance[i] = matrix[v][i];
	}
	found[v] = 1;
	distance[v] = 0;
	for (i = 0; i < n - 2; i++) {
		u = choose();
		found[u] = 1;
		for (w = 0; w < n; w++)
			if (!found[w])
				if (distance[u] + matrix[u][w] < distance[w])
					distance[w] = distance[u] + matrix[u][w];
	}
	printf("%d번째 환승역\t\t", v+1);
	for (i = 0; i < n; i++) {
		printf("%d\t", distance[i]);
	}
	printf("\n\n");
	/* for i */
}





typedef struct transfer* pointer;

pointer stack[MAX_SIZE];

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
typedef struct transfer {
	int name;
	pointer line[3];
};

int top = -1;

void push(pointer a) {
	if (top == MAX_SIZE) {
		return;
	}
	stack[++top] = a;

}


main() {
	int i = 0;
	for (i; i < 12; i++) {
		shortestPath(i);
	}
}