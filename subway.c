#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100


int matrix[12][12] = {
	{0,1,1000,1000,1000,1000,1000,1000,4,3,1000,1000},	//�̳�
	{1,0,1,1000,1000,1000,1000,1000,1000,1000,1000,1000},//����
	{1000,1,0,6,1000,1000,1000,1000,1000,1,1000,1},		//����
	{1000,1000,6,0,3,1000,1000,1000,1000,1000,1000,1000},//�齺��
	{1000,1000,1000,3,0,11,1000,1000,1000,1000,1000,4},	//����
	{1000,1000,1000,1000,11,0,8,1000,1000,1000,1,1000},//����
	{1000,1000,1000,1000,1000,8,0,6,6,1000,1000,1000},//���
	{1000,1000,1000,1000,1000,1000,6,0,4,1000,1000,1000},//����
	{4,1000,1000,1000,1000,1000,6,4,0,1000,1000,1000},//��õ
	{3,1000,1,1000,1000,1000,1000,1000,1000,0,2,1},//����
	{1000,1000,1000,1000,1000,1,1000,1000,1000,2,0,3},//��õ
	{1000,1000,1,1000,4,1000,1000,1000,1000,1,3,0}	//����
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
	printf("%d��° ȯ�¿�\t\t", v+1);
	for (i = 0; i < n; i++) {
		printf("%d\t", distance[i]);
	}
	printf("\n\n");
	/* for i */
}





typedef struct transfer* pointer;

pointer stack[MAX_SIZE];

// 1ȣ��	25 ���� 26 ���� 29 ���� 30 ���� 31 ���� (1~40 : 1ȣ��)
// 2ȣ��	45 �齺�� 48 ���� 59 ���� 67 ��� 73 ��õ (41~83 : 2ȣ��)
// 3ȣ��	84 ���� 88 ���� 89 ���� 92 �̳� 96 ��õ 100 ���� (84~100 : 3ȣ��)
// 4ȣ��	101 �̳� 102 ���� (101~114 : 4ȣ��)
// 5ȣ��	115 ��� 121 ���� (109~135 : �λ����(5ȣ��))
// 6ȣ��	136 ���� 138 ���� 139 ���� 146 �齺�� (136~151 : ���ؼ�(6ȣ��))



//1ȣ��		���� ����
//2ȣ��		�齺�� ����
//3ȣ��		���� ����
//4ȣ��		�̳� ����
//5ȣ��		
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