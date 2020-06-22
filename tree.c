#define _CRT_SECURE_NO_WARNINGS
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

typedef struct station* link;
typedef struct station {
	int vertex;
	link next[8];
	int way;
	int k;			//next[k]ºÎÅÍ ´Ù½Ã ½ÃÀÛ
	int prev;
};

link stack[5 * MAX_SIZE];

int pushtop = -1;
link stack2[5 * MAX_SIZE];

void push(link a) {
	stack2[++pushtop] = a;
	return;
}

link pop() {
	return stack2[pushtop--];
}
void init() {
	int i = 0;
	for (i; i < MAX_SIZE; i++) {
		stack[i] = (link)malloc(sizeof(*stack[i]));
		stack[i]->vertex = i;
	}
}
void connect(int i) {
	//printf("\nconnect start\n");
	int j;
	link a = (link)malloc(sizeof(*a));


	//printf("\n");
	a = stack[i];
	a->k = -1;
	//printf("%d-\n", a->vertex);
	int k = 0;
	for (j = 0; j < MAX_SIZE; j++) {

		if (matrix[i][j] == 1) {
			//printf("\n\t%d\t\t%d\n", k,j);
			if(k>=8)
				continue;
			stack[j]->k = -1;
			//printf("%d-", stack[j]->vertex);
			a->next[k++] = stack[j];
			a->way = k;
			a->prev = -1;
			stack[j]->prev = -1;
	
			//printf("\tk : %d\t way : %d\n", stack[j]->k, a->way);
		}
		//
	}

	//printf("\n");
}


void dfs(int p, int q) {
	link a = (link)malloc(sizeof(*a));
	a = stack[p];
	push(a);
	int index;
	int k = 0;
	int tmp;
	while (a != stack[q]) {
		while (a->way <= a->k + 2) {
			//printf("\npop\n");
			a = pop();
		}

		//printf("\nindex : %d \t way : %d\n", a->k, a->way);
		a->k++;
		tmp = a->vertex;

		//tmp = a->vertex;
		//printf("\n%d %d\n", a->next[a->k]->vertex, a->prev);
		if (a->next[a->k]->vertex == a->prev) {
			if (a->k < 7)
				a->k++;
			else {
				a = pop();
				//printf("\npop\n");
			}

		}

		//printf("\nfind %d \t next search is %d\n", a->vertex, a->next[a->k]->vertex);
		push(a);
		a = a->next[a->k];
		a->prev = tmp;
	}
	push(a);
}
int overlap(int k, int list[], int len) {
	int sum = 0;
	int i = 0;
	for (i; i < len; i++) {
		if (list[i] == k)
			sum++;
	}
	if (sum == 1)
		return 0;
	else
		return 1;

}

int* find(int list[], int k, int len) {
	int sum = 0;
	int i = 0;
	int j = 0;
	int l = 0;
	int* most = (int*)malloc(sizeof(int) * 2);
	for (i; i < len; i++) {

		if (list[i] == k && sum == 0) {
			l = i;
			sum++;

		}
		else if (list[i] == k && sum > 0) {
			j = i;
			sum++;

		}

	}
	most[0] = l;
	most[1] = j;
	return most;

}

void leftshift(int list[], int* most, int len) {
	int buffer[5 * MAX_SIZE] = { 0, };
	int i = 0;
	for (i; i < len; i++) {
		buffer[i] = list[i];
	}
	for (i = 0; i < most[0]; i++) {
		buffer[i] = list[i];
	}
	int j = i;
	for (i = most[1]; i < len; i++) {
		buffer[j++] = list[i];
	}
	for (i = 0; i < j; i++) {
		list[i] = buffer[i];
	}
	list[i] = -1;
}
void printarray(int list[]) {
	int i = 0;
	while (list[i] != -1) {
		printf("%d ", list[i++]);
	}
	printf("\n%d stations\n", i);
}
void rearrange(int list[], int len) {
	int list2[5 * MAX_SIZE] = { 0, };
	int i = 0;
	for (i; i < len; i++) {
		list2[i] = list[i];
	}
	for (i = 0; i < len; i++) {
		list[i] = list2[len - i - 1];
	}
	int tmp;
	int* most = (int*)malloc(sizeof(int) * 2);
	for (i = 0; i < len; i++) {
		tmp = overlap(list[i], list, len);
		if (tmp) {
			most = find(list, list[i], len);
			leftshift(list, most, len);

		}
	}
	printarray(list);



}
main() {
	FILE* fp;
	int list[5 * MAX_SIZE] = { 0, };
	fp = fopen("input.txt", "r");
	if (fp == NULL) {
		printf("error");
		return;
	}
	else {
		printf("success\n");
	}
	int i = 0;
	int j = 0;
	int n1, n2;
	for (i = 0; i < MAX_SIZE; i++) {
		for (j = 0; j < MAX_SIZE; j++) {
			fscanf(fp, "%d", &matrix[i][j]);
		}
	}

	init();
	for (i = 0; i < MAX_SIZE; i++) {
		connect(i);
	}
	link a;
	a = (link)malloc(sizeof(*a));

	int n3, n4;
	printf("\nwhere to where\n");
	scanf("%d %d", &n3, &n4);
	getchar();

	dfs(n3, n4);
	int k = 0;


	a = pop();
	int lm = 0;
	while (a) {
		list[lm] = a->vertex;
		lm++;
		a = pop();
	}


	rearrange(list, lm);


	return;

}

