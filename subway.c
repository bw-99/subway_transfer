
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10000
#define INT_MAX 999999999


int matrix2[MAX_SIZE][MAX_SIZE];
int matrix[MAX_SIZE][MAX_SIZE];
int top2 = 0;
int distance[MAX_SIZE];
int found[MAX_SIZE];
int n = MAX_SIZE;

int top = 0;


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
	int tag = 0;
	found[v] = 1;
	distance[v] = 0;
	for (i = 0; i < n - 2; i++) {
		u = choose();
		found[u] = 1;
		for (w = 0; w < n; w++)
			if (!found[w])
				if (distance[u] + matrix[u][w] < distance[w]) {
					distance[w] = distance[u] + matrix[u][w];
					matrix[v][w] = distance[w];
					matrix[w][v] = matrix[v][w];
				}
	}
}

main() {
	FILE* fp;
	fp = fopen("./input.txt","r");
	int i = 0;
	int j = 0;
	int n1, n2;
	for (i=0; i < MAX_SIZE; i++) {
		for (j = 0; j < MAX_SIZE; j++) {
			fscanf(fp,"%d", &matrix[i][j]);
			matrix2[i][j] = matrix[i][j];
			//printf("abcdffsfasdlkfjaldfkjaef");
		}
	}


	printf("\npress first and final station\n");
	scanf("%d %d", &n1, &n2);
	getchar();
	shortestPath(n1);



	
	printf("%d subway\n", matrix[n1][n2]);

	printf("press c to continue\nor anything to finish\n");
	char a;
	//rewind(stdin);
	//rewind(fp);
	while (1) {
		scanf("%c", &a);
		if (a == 'c') {
			printf("\npress first and final station\n");
			scanf("%d %d", &n1, &n2);
			shortestPath(n1);
			printf("%d subway\n", matrix[n1][n2]);
			getchar();
			printf("press c to continue\nor anything to finish\n");
		}
		else {
			break;
		}
		
	}
	return;

}
