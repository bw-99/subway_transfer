#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_SIZE 1000


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
	int tag = 0;


	for (i = 0; i < MAX_SIZE; i++) {
		random = rand() % 20;
		j1 = rand() % (MAX_SIZE-1) + 1;
		j1 = j1 == i ? rand() % (MAX_SIZE-1) + 1 : j1;
		j2 = rand() % (j1) + 3;
		j2 = j2 == i ? j2 + 3 : j2;
		printf("\n%d %d %d",i, j1, j2);
		tag = 0;
		if (random < 16) {	// 일반
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
		else {		//환승
			for (j = 0; j < MAX_SIZE; j++) {
				if (matrix[i][j] == -1) {

					if (j == j1 || j == j2) {
						matrix[i][j] = 1;
						matrix[j][i] = 1;
						tag++;
					}
					else {
						random = rand() % 19 + 1;
						random = i == j ? 0 : random > 5 ? 1000 : 1;
						if (random == 1)
							tag++;
						
						if (tag > 8 && random == 1)
							random = 1000;

						matrix[i][j] = random;
						matrix[j][i] = random;
					}
					
				}
			}
		}
		
	}


	for (i = 0; i < MAX_SIZE; i++) {
		for (j = 0; j < MAX_SIZE; j++) {
			fprintf(fp, "%d  ", matrix[i][j]);
			//printf("%d  ", matrix[i][j]);
		}
		fprintf(fp, "\n\n");
		//printf("\n");
	}
	fclose(fp);
	//printf("\n");
	
}