#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define N 7
#define M 128
//#define N 4   
////1번,2번 문제 정점의 수 
//#define M 16 
//부분집합의 수 '2의 N승'
#define VS 1   //시작경로
#define VSP (int)pow(2,VS-1)
#define INF 1000


int D[N][M]; //최단경로 저장배열
int P[N][M]; //P[Vi][A] = D[Vi][A]의 최단경로로 갈때 처음가는 원소
int set[M];  //각 부분집합이며, 원소갯수를 저장한다.

int W[N][N] = {
	{0,4,INF,INF,INF,10,INF},
	{3,0,INF,18,INF,INF,INF},
	{INF,6,0,INF,INF,INF,INF},
	{INF,5,15,0,2,19,5},
	{INF,INF,12,1,0,INF,INF},
	{INF,INF,INF,INF,INF,0,10},
	{INF,INF,INF,8,INF,INF,0}
};
//int W[N][N] = { // 1,2번 문제 인접행렬
//	{0,2,9,INF},
//	{1,0,6,4},
//	{INF,7,0,8},
//	{6,3,INF,0}
//}; 
//인접행렬 입력값


void setCount();
int travel();
void path(int, int);
void min(int, int);


int main(int argc, char* argv[])
{
	printf("최소 비용 %d \n\n", travel()); //최소비용 출력
	printf("최소 비용 경로\n");               //경로출력
	path(VS - 1, M - 1 - VSP);
	return 0;
}

int travel() {
	//외판원 경로구하기
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
	// 노드의 index 는 0 부터 시작이지만 노드의 번호는 1부터 시작이기에 - 1을 해주는 것을 잊지말자
	minlength = D[VS - 1][M - 1 - VSP];
	return minlength; //최소비용 리턴
}

void setCount() {
	//각 부분집합들의 원소 갯수를 세는 함수
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
		set[A] = K;	//set[A]에 원소의 갯수를 넣어줌
	}
}

void min(int i, int A) {
	int j, s;
	D[i][A] = INF;	// ∞(INF)로 초기화
	for (j = 0; j < N; j++) {
		s = (int)pow(2, j);
		if ((A & s) != 0) {
			if (D[i][A] > W[i][j] + D[j][A - s]) {
				D[i][A] = W[i][j] + D[j][A - s];
				P[i][A] = j; //j의 최소값 저장
			}
		}
	}
}

void path(int i, int A) {
	int j = P[i][A];
	printf("V%d -> ", i + 1);
	if (A - pow(2, j) != 0)
		path(j, (int)A - pow(2, j));		//다음 가야할 경로 호출 
	else
		printf("V%d -> V%d\n", j + 1, VS);	//도착
}