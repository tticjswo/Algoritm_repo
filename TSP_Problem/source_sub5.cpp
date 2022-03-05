#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define N 7
#define M 128
//#define N 4   
////1��,2�� ���� ������ �� 
//#define M 16 
//�κ������� �� '2�� N��'
#define VS 1   //���۰��
#define VSP (int)pow(2,VS-1)
#define INF 1000


int D[N][M]; //�ִܰ�� ����迭
int P[N][M]; //P[Vi][A] = D[Vi][A]�� �ִܰ�η� ���� ó������ ����
int set[M];  //�� �κ������̸�, ���Ұ����� �����Ѵ�.

int W[N][N] = {
	{0,4,INF,INF,INF,10,INF},
	{3,0,INF,18,INF,INF,INF},
	{INF,6,0,INF,INF,INF,INF},
	{INF,5,15,0,2,19,5},
	{INF,INF,12,1,0,INF,INF},
	{INF,INF,INF,INF,INF,0,10},
	{INF,INF,INF,8,INF,INF,0}
};
//int W[N][N] = { // 1,2�� ���� �������
//	{0,2,9,INF},
//	{1,0,6,4},
//	{INF,7,0,8},
//	{6,3,INF,0}
//}; 
//������� �Է°�


void setCount();
int travel();
void path(int, int);
void min(int, int);


int main(int argc, char* argv[])
{
	printf("�ּ� ��� %d \n\n", travel()); //�ּҺ�� ���
	printf("�ּ� ��� ���\n");               //������
	path(VS - 1, M - 1 - VSP);
	return 0;
}

int travel() {
	//���ǿ� ��α��ϱ�
	int i, k, A;
	setCount();

	printf("\n");
	int minlength;

	for (i = 0; i < N; i++)
		D[i][0] = W[i][VS - 1];

	for (k = 1; k <= N - 2; k++) {
		for (A = 0; A < M; A++) {
			if (set[A] == k && (A & VSP) == 0) {
				for (i = 0; i < N; i++) {
					if (A & (int)pow(2, i))
						continue;
					min(i, A); //min(W[i][j]+D[j][A-j]
				}
			}
		}
	}
	min(VS - 1, M - 1 - VSP); 
	// ����� index �� 0 ���� ���������� ����� ��ȣ�� 1���� �����̱⿡ - 1�� ���ִ� ���� ��������
	minlength = D[VS - 1][M - 1 - VSP];
	return minlength; //�ּҺ�� ����
}

void setCount() {
	//�� �κ����յ��� ���� ������ ���� �Լ�
	int A, I, J, K;
	for (A = 0; A < M; A++) {
		J = A;
		I = M / 2;
		K = 0;
		while (J > 0) {
			if (J - I >= 0) {
				J = J - I;
				K++;
			}
			I /= 2;
		}
		set[A] = K;	//set[A]�� ������ ������ �־���
	}
}

void min(int i, int A) {
	int j, s;
	D[i][A] = INF;	// ��(INF)�� �ʱ�ȭ
	for (j = 0; j < N; j++) {
		s = (int)pow(2, j);
		if ((A & s) != 0) {
			if (D[i][A] > W[i][j] + D[j][A - s]) {
				D[i][A] = W[i][j] + D[j][A - s];
				P[i][A] = j; //j�� �ּҰ� ����
			}
		}
	}
}

void path(int i, int A) {
	int j = P[i][A];
	printf("V%d -> ", i + 1);
	if (A - pow(2, j) != 0)
		path(j, (int)A - pow(2, j));		//���� ������ ��� ȣ�� 
	else
		printf("V%d -> V%d\n", j + 1, VS);	//����
}