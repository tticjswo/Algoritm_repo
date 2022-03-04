#define _CRT_SECURE_NO_WARNINGS
#include  <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(x,y,temp) ((temp) =(x),(x)=(y),(y)=(temp)) // 위치를 바꾸는 함수
#define MAXSIZE 8        // 정렬하는 입력값의 개수를 변경 하는 상수.
float sorted[MAXSIZE];// 병합정렬을 위한 임시 배열
void selection_sort(float input[], int n);
void bubble_sort(float input[], int n);
void insertion_sort(float input[], int n);
void merge_sort(float input[], int left, int right);
void merge(float input[], int left, int mid, int right);
void build_heap(float input[], int n);
void heapify(float input[], int n, int start);
void heap_sort(float input[], int n);
void quick_sort(float input[], int start, int end);
int count = 0;
float temp;
int main(void) {
	int n = MAXSIZE;
	int a;
	int num;
	clock_t finish, start;
	double duration;
	float input[MAXSIZE];
	float array[8];
	printf("input을 통한 8개의 숫자 정렬하기 (1) 난수발생을 통한 숫자 정렬 시간 구하기 (2) : "); 
	scanf("%d", &num);
	switch (num)
	{
	case 1:
		printf("input 8 numbers : ");
		for (int i = 0; i < 8; i++) {
			scanf("%f", &array[i]);
		}
		printf("1. 선택정렬 \n2. 버블정렬 \n3. 삽입 정렬 \n4. 병합 정렬 \n5. 퀵 정렬\n6. 힙 정렬\n 숫자로 입력하세요 :");
		scanf_s("%d", &a);
		if (a == 1) {
			selection_sort(array, 8);
		}
		else if (a == 2) {
			bubble_sort(array, 8);
		}
		else if (a == 3) {
			insertion_sort(array, 8);
		}
		else if (a == 4) {
			merge_sort(array, 0, 7);
		}
		else if (a == 5) {
			quick_sort(array, 0, 7); // 첫번째 값을 key로 가질수 있게 설정한다.
		}
		else if (a == 6) {
			heap_sort(array, 8);
		}
		else {
			printf("1~6까지의 수만 입력해주세요");
			break;
		}

		for (int i = 0; i < 8; i++)
			printf("%d  ",(int)array[i]);

		break;
	case 2: 
		for (int i = 0; i < n; i++) {  //난수 생성 (seed)값이 같기 때문에 항상 같은 값이 나올 것이다.
			input[i] = rand() / (float)RAND_MAX - rand() / (float)RAND_MAX;//0~1까지의 실수를 뽑아내고 그걸 다시 0~1까지 실수로 빼준다면 -1~1까지의 실수의 랜덤 값이 될 것이다.
		}
		printf("1. 선택정렬 \n2. 버블정렬 \n3. 삽입 정렬 \n4. 병합 정렬 \n5. 퀵 정렬\n6. 힙 정렬\n 숫자로 입력하세요 :");
		scanf_s("%d", &a);
		if (a == 1) {
			start = clock(); // 함수 시작 시간 저장
			selection_sort(input, n);
			finish = clock();// 함수 종료 시간 저장
			//printf("----------------------선택 정렬로 나열합니다.-----------------------\n");
		}
		else if (a == 2) {
			start = clock();
			bubble_sort(input, n);
			finish = clock();
			//printf("----------------------버블 정렬로 나열합니다.-----------------------\n");
		}
		else if (a == 3) {
			start = clock();
			insertion_sort(input, n);
			finish = clock();
			//printf("----------------------삽입 정렬로 나열합니다.-----------------------\n");
		}
		else if (a == 4) {
			start = clock();
			merge_sort(input, 0, n - 1);
			finish = clock();
			//printf("----------------------병합 정렬로 나열합니다.-----------------------\n");
		}
		else if (a == 5) {
			start = clock();
			quick_sort(input, 0, n - 1); // 첫번째 값을 key로 가질수 있게 설정한다.
			finish = clock();
			//printf("----------------------퀵 정렬로 나열합니다.-----------------------\n");
		}
		else if (a == 6) {
			start = clock();
			heap_sort(input, n);
			finish = clock();
			//printf("----------------------힙 정렬로 나열합니다.-----------------------\n");
		}
		else
			printf("1~6까지의 수만 입력해주세요");
		duration = (float)(finish - start) / CLOCKS_PER_SEC; // 종료시간에서 시작시간을 뺸후 초단위로 바꿔준다.
		// msec 기준으로 하려면 뒤에 CLOCKS_PER_SEC를 나누지 않으면 된다.
		printf(" 걸린 시간 : %lf\n", duration);

		for (int i = 0; i < n; i++)
			printf("%.3f  ", input[i]);

		break;
	default:
		break;
	}
	
	return 0;
}
void selection_sort(float input[], int n) {
	int i, j,k, maxindex = 0;
	int count = 0;
	float max = -2;				// -1~1 까지의 난수이기때문에 최소값보다 작아야함
	for (i = n - 1; i >= 0; i--) {
		for (j = 0; j <= i; j++) {
			if (input[j] > max) {
				max = input[j];
				maxindex = j;
			}
		}
		max = -2;
		if (i != maxindex)
			SWAP(input[i], input[maxindex], temp);
		if (count++ < 5) {
			printf("%d 회전 : ", count);
			for (k = 0; k < n; k++) {
				printf("%.3f  ", input[k]);
			}
			printf("\n");
		}
	}
}
void bubble_sort(float input[], int n) {
	int i, j,k;
	int count = 0;
	for (i = n - 1; i >= 0; i--) {
		for (j = 0; j <= i - 1; j++) {
			if (input[j] > input[j + 1])
				SWAP(input[j], input[j + 1], temp);
		}
		if (count++ < 5) {
			printf("%d 회전 : ", count);
			for (k = 0; k < n; k++) {
				printf("%.3f  ", input[k]);
			}
			printf("\n");
		}
	}
}
void insertion_sort(float input[], int n) {
	int i, j,k;
	float key;
	int count = 0;
	for (i = 1; i < n; i++) {
		key = input[i];//key 설정
		for (j = i - 1; j >= 0 && input[j] > key; j--) {
			input[j + 1] = input[j];
		}
		input[j + 1] = key;
		if (count++ < 5) {
			printf("%d 회전 key = %f : ", count,key);
			for (k = 0; k < n; k++) {
				printf("%.3f  ", input[k]);
			}
			printf("\n");
		}
	}
}
void merge_sort(float input[], int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2; //중앙 값을 잡는다.
		merge_sort(input, left, mid); // 왼쪽기준으로 재귀
		merge_sort(input, mid + 1, right); //종료후 오른쪽기준으로 재귀
		merge(input, left, mid, right);
	}
}
void merge(float input[], int left, int mid, int right) {
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;
	while (i <= mid && j <= right) { // 분할 정렬된 input 배열의 합병
		if (input[i] <= input[j])
			sorted[k++] = input[i++];
		else
			sorted[k++] = input[j++];
	}
	if (i > mid) {
		for (l = j; l <= right; l++) //  남아 있는 값들을 일괄 복사
			sorted[k++] = input[l];
	}
	else {
		for (l = i; l <= mid; l++)	// 남아 있는 값들을 일괄 복사
			sorted[k++] = input[l];
	}
	for (l = left; l <= right; l++) { // sorted[](임시 배열)의 리스트를  input 배열로 재복사
		input[l] = sorted[l];
	}
	if (count++ < 5) {
		printf("%d 회전 : ", count);
		for (k = 0; k < 8; k++) {
			printf("%.3f  ", input[k]);
		}
		printf("\n");
	}
}
void build_heap(float input[], int n) {
	int start = n / 2 - 1;// 자식노드가 존재하는 노드는 전체 수 n/2번째 노드에 존재할 수있다. -1은 배열의 인덱스가 0으로 시작함을 감안하였다.
	for (start; start >= 0; start--) // n/2-1번째 index 부터 위의 index에만 자식노드가 존재한다.
		heapify(input, n, start);
}
void heapify(float input[], int n, int start) {
	int root_index = start;
	int left_index = root_index * 2 + 1; // 왼쪽 자식 노드
	int right_index = root_index * 2 + 2; // 오른쪽 자식 노드
	int largest_index = start;
	if (left_index <n && input[left_index]>input[largest_index]) {
		//left_index는 배열 안에 존재해야한다. n보다 작아야함
		largest_index = left_index;
	}
	if (right_index<n && input[right_index]>input[largest_index]) {
		//right_index는 배열 안에 존재해야한다. n보다 작아야함
		largest_index = right_index;
	}
	if (root_index != largest_index) {
		SWAP(input[largest_index], input[root_index], temp); // 위치를 바꾸고
		heapify(input, n, largest_index); // 다시 힙 화 해준다.
	}
}
void heap_sort(float input[], int n) {
	build_heap(input, n); // 초기 배열 힙 상태로 설정
	while (n > 1) {
		SWAP(input[0], input[n - 1], temp);
		n--; //힙상태 되어있는 배열의 첫번째 값과 마지막값을 교체 후 다시 heapify 할 배열의 사이즈를 임의로 줄인다.
		heapify(input, n, 0);
	}

}
void quick_sort(float input[], int start, int end) {
	if (start >= end) {
		return;
	}
	int key = start; // key= pivot,  코드로 구현한 피벗은 제일 첫번째 값으로 한다
	int i = start + 1;
	int j = end;
	int k;
	while (i <= j) { //교차되기 전까지
		while (i <= end && input[i] <= input[key]) {
			i++;
		}
		while (input[j] >= input[key] && j > start) {
			j--;
		}
		if (i > j) { // 교차되는 순간 피벗의 위치를 고정 한다. 위의 반복문도 탈출
			SWAP(input[j], input[key], temp); // 
		}
		else {
			SWAP(input[i], input[j], temp);
		}
		if (count++ < 5) {
			printf("%d 회전 : ", count);
			for (k = 0; k < 8; k++) {
				printf("%.3f  ", input[k]);
			}
			printf("\n");
		}
	}
	quick_sort(input, start, j - 1); // 피벗 기준 왼쪽
	quick_sort(input, j + 1, end); // 피벗 기준 오른쪽
}

