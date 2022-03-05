#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#define N 6 //���� 5�� ���� ����ϴ� ��� ��

#define NUM 7 // ��� ��
#define INF 999 //���Ѵ�

//input W matrix ���� 1
int g1[NUM][NUM] = {
	{0,4,INF,INF,INF,10,INF},
	{3,0,INF,18,INF,INF,INF},
	{INF,6,0,INF,INF,INF,INF},
	{INF,5,15,0,2,19,5},
	{INF,INF,12,1,0,INF,INF},
	{INF,INF,INF,INF,INF,0,10},
	{INF,INF,INF,8,INF,INF,8}
};
//input W matrix ���� 3
int g2[NUM][NUM] = {
	{0,INF,INF,INF,INF,INF,10},
	{INF,0,1,12,INF,INF,INF},
	{19,2,0,15,5,INF,5},
	{INF,INF,INF,0,6,INF,INF},
	{INF,INF,18,INF,0,3,INF},
	{10,INF,INF,INF,4,0,INF},
	{INF,INF,8,INF,INF,INF,0}
};

int graph_D[NUM][NUM];
int graph_P[NUM][NUM];

typedef enum { 
	CASE = 1, ELSE, END, IF, OF, THEN 
} keytype;

const float percentage[] = {
	0, .05, .15, .05, .35, .05, .35 
};

typedef struct nodetype {
	keytype key;
	struct nodetype* left;
	struct nodetype* right;
}node;

typedef node* node_p;

float A[N + 2][N + 1]; // A[1~N+1][0~N]
int   R[N + 2][N + 1]; // R[1~N+1][0~N]

float sum(int start, int end) //���� Ȯ����
{
	float sum = 0;
	for (int i = start; i <= end; i++) {
		sum += percentage[i];
	}

	return sum;
}
void optsearchtree() // �����ڵ� ���� ���ڴ� ��� ���������� ó����
{
	int i, j, k, diagonal;
	float min;

	for (i = 1; i <= N; ++i){
		A[i][i - 1] = 0; A[i][i] = percentage[i];
		R[i][i - 1] = 0; R[i][i] = i;
	}
	A[N + 1][N] = 0; R[N + 1][N] = 0;
	for (diagonal = 1; diagonal <= N - 1; ++diagonal) {
		for (i = 1; i <= N - diagonal; ++i) {
			j = i + diagonal;

			A[i][j] = min = A[i][i - 1] + A[i + 1][j] + sum(i, j); 
			R[i][j] = i;
			for (k = i + 1; k <= j; ++k) {
				if (min > A[i][k - 1] + A[k + 1][j] + sum(i, j)) {
					A[i][j] = min = A[i][k - 1] + A[k + 1][j] + sum(i, j);
					R[i][j] = k;
				}
			}
		}
	}
}
keytype getKey(int key)
{
	if (key == 1)
		return CASE;
	if (key == 2)
		return ELSE;
	if (key == 3)
		return END;
	if (key == 4)
		return IF;
	if (key == 5)
		return OF;
	if (key == 6)
		return THEN;
}
node_p tree(int i, int j)
{
	int k;
	node_p p;
	k = R[i][j];
	if (k == 0)return NULL;
	else
	{
		p = (node_p)malloc(sizeof(node));
		p->key = getKey(k);
		p->left = tree(i, k - 1);
		p->right = tree(k + 1, j);
		return p;
	}
}
void floyd2(int W[][NUM]) {
	//matrix D �ʱ�ȭ
	for (int i = 0; i < NUM; i++) {
		for (int j = 0; j < NUM; j++) {
			graph_D[i][j] = W[i][j];
		}
	}
	//matrix P �ʱ�ȭ
	for (int i = 0; i < NUM; i++) {
		for (int j = 0; j < NUM; j++) {
			graph_P[i][j] = 0;
		}
	}
	//����� ���� ��� ���� ���� ����� ���� ������ ��� ������ ����� ��(?) �� ��ü�Ѵ�.
	for (int k = 0; k < NUM; k++) {
		for (int i = 0; i < NUM; i++) {
			for (int j = 0; j < NUM; j++) {
				if (graph_D[i][k] + graph_D[k][j] < graph_D[i][j]) {
					graph_P[i][j] = k; 
					graph_D[i][j] = graph_D[i][k] + graph_D[k][j];
				}
			}
		}
		printf("MATRIX D (%d):\n\n",k);
		for (int i = 0; i < NUM; i++) {
			for (int j = 0; j < NUM; j++) {
				printf("%3d ", graph_D[i][j]);

			}
			printf("\n");
		}
		printf("\n");
		printf("MATRIX P (%d):\n\n", k);
		for (int i = 0; i < NUM; i++) {
			for (int j = 0; j < NUM; j++) {
				printf("%3d ", graph_P[i][j]);

			}
			printf("\n");
		}
		printf("\n");
	}
	printf("MATRIX D :\n");
	for (int i = 0; i < NUM; i++) {
		for (int j = 0; j < NUM; j++) {
			printf("%3d ", graph_D[i][j]);

		}
		printf("\n");
	}
	printf("MATRIX P :\n");
	for (int i = 0; i < NUM; i++) {
		for (int j = 0; j < NUM; j++) {
			printf("%3d ", graph_P[i][j]);

		}
		printf("\n");
	}
}
void print_shortest_path(int a,int b ) {
	printf("print_shortest_path(%d, %d) : %d\n", a, b, graph_P[a][b]);

	if (graph_P[a][b] != 0) { // 0�� ���´ٴ� ���� �ش� ��带 �������ٴ� ��
		print_shortest_path(a, graph_P[a][b]);
		printf("node index : %d  \n", graph_P[a][b]); 
		print_shortest_path(graph_P[a][b], b);
	}

}

int main()
{
	floyd2(g2);// 1�� 2�� ������ ���ڸ� g1 ���� 3�� 4�� ������ ���ڸ� g2�� ������ �ȴ�.
	print_shortest_path(6, 3);
	//���� index �� 0~6 ���� ������ ���������� v1~v7�̱� ������ 7���� 3������ �ִܰ�δ�
	//index 6 ~ index 2������ �ִ� ����̴�.


	printf("\n------------------------------------------\n");

	optsearchtree();
	printf("A-----------\n");
	for (int i = 1; i < N + 1; i++)
	{
		for (int j = 0; j <= N; j++)
			printf("%f ", A[i][j]);
		printf("\n");
	}
	printf("R-----------\n");
	for (int i = 1; i <= N + 1; i++)
	{
		for (int j = 0; j <= N; j++)
			printf("%d ", R[i][j]);
		printf("\n");
	}
	node_p head = tree(1, 6);


	return 0;
}
