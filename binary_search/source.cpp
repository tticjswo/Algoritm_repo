#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>

int BSearchRecursive(int[], int, int, int);
int BSearch(int[], int, int);
int input_num;
int main(void) {
	clock_t start, end;
	int array[10];
	for (int i = 0; i < 10; i++) {
		array[i] = i;
	}
	scanf("%d", &input_num);
	//int array[100000]; // 실행시간 확인용 추가 code
	int i = 0;
	for (int i = 0; i < input_num; i++) {
		//array[i] = i; // 실행시간 확인용 추가 code
		scanf("%d", &array[i]);
	}
	/*for (int i = 0; i < input_num; i++) {
		printf("%d ", array[i]);
	}*/
	int fn;
	printf("finding num : ");
	scanf("%d", &fn);
	
	int select_num = 0;
	printf("1. 반복문을 사용한 이진 탐색\n");
	printf("2. 재귀를 사용한 이진 탐색 \n");
	printf("input 1/2 : "); scanf("%d", &select_num);
	int answer;
	switch (select_num) {
		case 1:
			start = clock(); //함수 시작 시간을 ms 로 기록 
			answer = BSearch(array, fn, input_num) + 1;
			if (answer == 0)
				printf("실패\n");
			else
				printf("Answer : %d\n", answer);

			end = clock(); // 함수 끝 시간을 ms 로 기록
			break;
			
		case 2:
			start = clock();
			answer = BSearchRecursive(array, fn, 0, input_num) + 1;
			if (answer == 0)
				printf("실패\n");
			else
				printf("Answer : %d\n", answer);
			end = clock();
			break;
		default: printf("choose 1 or 2\n"); break;
	}
	double duration = (double)(end - start) / CLOCKS_PER_SEC; // 각 변수간의 차를 저장하여 흘러간 시간을 구한다.
	printf("%f clock 가 걸렸음\n", duration);
	return 0;
}
int BSearch(int arr[], int target, int length) {
	int low = 0; // low , high , mid 선언
	int high = length;
	int mid;
	while (low <= high) { //low가 high 가 되는 상황은 더이상의 반복이 있을 수 없다.
		mid = (low + high) / 2; //각 루프 마다 mid 를 새로 초기화 한다.
		if (arr[mid] == target)
			return mid; // 찾는 값과 같은 index를 리턴 return 
		else if (arr[mid] > target)
			high = mid - 1; // 찾는 값보다 arr 의 mid index 값이 더 클 때,
		else
			low = mid + 1; // 찾는 값보다 arr 의 mid index 값이 더 작을 때,
	}
	return -1;

}

int BSearchRecursive(int arr[], int target, int low, int high) {
	if (low > high) // 반복문과 마찬가지로 low 와 high가 반대로 되는 상황은 재귀호출이 일어나지 않게 한다.
		return -1;
	int mid = (low + high) / 2; // mid 초기화
	if (arr[mid] == target)
		return mid;
	else if (arr[mid] > target) {
		return BSearchRecursive(arr, target, low, mid - 1);
	}
	else
		return BSearchRecursive(arr, target, mid + 1, high);
}
