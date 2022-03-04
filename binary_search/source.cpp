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
	//int array[100000]; // ����ð� Ȯ�ο� �߰� code
	int i = 0;
	for (int i = 0; i < input_num; i++) {
		//array[i] = i; // ����ð� Ȯ�ο� �߰� code
		scanf("%d", &array[i]);
	}
	/*for (int i = 0; i < input_num; i++) {
		printf("%d ", array[i]);
	}*/
	int fn;
	printf("finding num : ");
	scanf("%d", &fn);
	
	int select_num = 0;
	printf("1. �ݺ����� ����� ���� Ž��\n");
	printf("2. ��͸� ����� ���� Ž�� \n");
	printf("input 1/2 : "); scanf("%d", &select_num);
	int answer;
	switch (select_num) {
		case 1:
			start = clock(); //�Լ� ���� �ð��� ms �� ��� 
			answer = BSearch(array, fn, input_num) + 1;
			if (answer == 0)
				printf("����\n");
			else
				printf("Answer : %d\n", answer);

			end = clock(); // �Լ� �� �ð��� ms �� ���
			break;
			
		case 2:
			start = clock();
			answer = BSearchRecursive(array, fn, 0, input_num) + 1;
			if (answer == 0)
				printf("����\n");
			else
				printf("Answer : %d\n", answer);
			end = clock();
			break;
		default: printf("choose 1 or 2\n"); break;
	}
	double duration = (double)(end - start) / CLOCKS_PER_SEC; // �� �������� ���� �����Ͽ� �귯�� �ð��� ���Ѵ�.
	printf("%f clock �� �ɷ���\n", duration);
	return 0;
}
int BSearch(int arr[], int target, int length) {
	int low = 0; // low , high , mid ����
	int high = length;
	int mid;
	while (low <= high) { //low�� high �� �Ǵ� ��Ȳ�� ���̻��� �ݺ��� ���� �� ����.
		mid = (low + high) / 2; //�� ���� ���� mid �� ���� �ʱ�ȭ �Ѵ�.
		if (arr[mid] == target)
			return mid; // ã�� ���� ���� index�� ���� return 
		else if (arr[mid] > target)
			high = mid - 1; // ã�� ������ arr �� mid index ���� �� Ŭ ��,
		else
			low = mid + 1; // ã�� ������ arr �� mid index ���� �� ���� ��,
	}
	return -1;

}

int BSearchRecursive(int arr[], int target, int low, int high) {
	if (low > high) // �ݺ����� ���������� low �� high�� �ݴ�� �Ǵ� ��Ȳ�� ���ȣ���� �Ͼ�� �ʰ� �Ѵ�.
		return -1;
	int mid = (low + high) / 2; // mid �ʱ�ȭ
	if (arr[mid] == target)
		return mid;
	else if (arr[mid] > target) {
		return BSearchRecursive(arr, target, low, mid - 1);
	}
	else
		return BSearchRecursive(arr, target, mid + 1, high);
}
