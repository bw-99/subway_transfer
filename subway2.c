#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000
#define INT_MAX 999999999


int matrix2[MAX_SIZE][MAX_SIZE];
int matrix[MAX_SIZE][MAX_SIZE];
int top2 = 0;
int distance[MAX_SIZE];
int found[MAX_SIZE];
int n = MAX_SIZE;

int transinfo[50];
int top = 0;

int top_push = -1;
int pur;

typedef struct station* link;
typedef struct station {
	int ver;
	link next;
};

link stack[MAX_SIZE*5];


typedef struct pos {
	int ver;
}pos;

pos stack2[MAX_SIZE*5];


void push(int k) {
	pos a;
	a.ver = k;
	//printf("%d ", k);
	stack2[++top_push] = a;
}

int pop() {
	return(stack2[top_push--].ver);
}


void init(int v) {
	int i = 0;
	for (i; i < MAX_SIZE; i++) {
		stack[i] = (link)malloc(sizeof(*stack[i]));
		stack[i]->ver = v;
	}
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

void show(int f) {
	int i = 0;
	link a = (link)malloc(sizeof(*a));
	link b = (link)malloc(sizeof(*b));
	for (i; i < top; i++) {
		a = stack[i];
		while (a) {
			//printf("%d-", a->ver);
			if (a->next) {
				a = a->next;
				b = a;
			}
			else {
				a = a->next;
			}
		}
		if (b->ver == f) {
			pur = i;
		}
	}
}

int* find(int f) {
	int i = 0;
	link a = (link)malloc(sizeof(*a));
	link b = (link)malloc(sizeof(*b));
	int* tmp = (int*)malloc(sizeof(int) * 2);
	for (i; i < top; i++) {
		a = stack[i]->next;
		while (a) {
			if (a->next) {
				tmp[0] = a->ver;
				a = a->next;
				tmp[1] = a->ver;
				b = a;
			}
			else {
				break;
			}
		}
		if (tmp[1] == f) {
			return(tmp);
		}
	}
	tmp[1] = -1;
	return tmp;
}
void makepath(int f) {
	int i = 0;
	link a = (link)malloc(sizeof(*a));
	link b = (link)malloc(sizeof(*b));
	int* tmp = (int*)malloc(sizeof(int) * 2);
	tmp = find(f);
	while (tmp[1]!=-1) {
		push(tmp[1]);
		tmp = find(tmp[0]);
	}
}
void shortestPath(int v,int f){
	init(v);
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
				if (distance[u] + matrix[u][w]+ 3< distance[w]) {
					link a = (link)malloc(sizeof(*a));
					link b = (link)malloc(sizeof(*b));
					a->ver = u;
					b->ver = w;
					a->next = b;
					stack[top++]->next = a;
					distance[w] = distance[u] + matrix[u][w];
					matrix[v][w] = distance[w];
					matrix[w][v] = matrix[v][w];
				}
	}
	show(f);
	makepath(f);
	push(v);
}

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


void printarray(int list[], int len) {
	int i = len-1;
	for (i; i >=0 ; i--) {
		printf("%d ", list[i]);
	}
	printf("\n%d stations\n", len);
}


void inverse(int list[], int len) {
	int* list2 = (int*)malloc(sizeof(int) * len);
	int i = 0;
	for (i; i < len; i++) {
		list2[i] = list[i];
	}
	for (i = 0; i < len; i++) {
		list[i] = list2[len - i - 1];
	}

	printarray(list,len);
}


main() {
	FILE* fp;
	fp = fopen("input.txt","r");
	int i = 0;
	int j = 0;
	int n1, n2;
	int list[100] = { 0, };
	for (i=0; i < MAX_SIZE; i++) {
		for (j = 0; j < MAX_SIZE; j++) {
			fscanf(fp,"%d", &matrix[i][j]);
			matrix2[i][j] = matrix[i][j];
			//printf("abcdffsfasdlkfjaldfkjaef");
		}
	}
	/*for (i = 0; i < MAX_SIZE; i++) {
		shortestPath(i);
	}*/

	printf("\npress first and final station\n");
	scanf("%d %d", &n1, &n2);
	getchar();
	shortestPath(n1,n2);

	int a = pop();
	int lm = 0;
	while (a) {
		list[lm] = a;
		lm++;
		a = pop();
	}
	inverse(list, lm);

	return;

}
