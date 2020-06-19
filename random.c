#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_SIZE 10000


int matrix[MAX_SIZE][MAX_SIZE];


main() {
	FILE* fp;

	fp = fopen("../source/repos/project7/project7/input.txt", "wt");
	if (fp == NULL) {
		printf("실패 종료\n");
		return;
	}
	int i, j;
	int random;
	srand(time(NULL));
	int j1, j2;

	for (i = 0; i < MAX_SIZE; i++) {
		for (j = 0; j < MAX_SIZE; j++) {
			matrix[i][j] = -1;
		}

	}



	for (i = 0; i < MAX_SIZE; i++) {
		random = rand() % 20;
		if (random < 15) {
			j1 = rand() % MAX_SIZE -1;
			j2 = rand() % MAX_SIZE -1;

			j1 = j1 == i ? rand() % MAX_SIZE - 1 : j1;
			j2 = j2 == i ? rand() % MAX_SIZE - 1 : j2;

			j2 = j1 == j2 ? rand() % MAX_SIZE - 1 : j2;

			for (j = 0; j < MAX_SIZE; j++) {
				if (matrix[i][j] == -1) {
					

					if (j == j1 || j == j2) {
						matrix[i][j] = 1;
						matrix[j][i] = 1;
					}
					else {
						matrix[i][j] = i == j ? 0 : 1000;
						matrix[j][i] = matrix[i][j];
					}
					
				}
			}
		}
		else {
			for (j = 0; j < MAX_SIZE; j++) {
				if (matrix[i][j] == -1) {
					random = rand() % 19 + 1;
					random = random > 7 ? 1000 : random;
					random = i == j ? 0 : random;
					matrix[i][j] = random;
					matrix[j][i] = random;
				}
			}
		}
		
	}


	for (i = 0; i < MAX_SIZE; i++) {
		for (j = 0; j < MAX_SIZE; j++) {
			fprintf(fp, "%d  ", matrix[i][j]);
			//printf("%d  ", matrix[i][j]);
		}
		//fprintf(fp, "\n\n");
		//printf("\n");
	}
	fclose(fp);
	//printf("\n");
	
}