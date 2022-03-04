#define _CRT_SECURE_NO_WARNINGS
#include  <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(x,y,temp) ((temp) =(x),(x)=(y),(y)=(temp)) // ��ġ�� �ٲٴ� �Լ�
#define MAXSIZE 8        // �����ϴ� �Է°��� ������ ���� �ϴ� ���.
float sorted[MAXSIZE];// ���������� ���� �ӽ� �迭
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
	printf("input�� ���� 8���� ���� �����ϱ� (1) �����߻��� ���� ���� ���� �ð� ���ϱ� (2) : "); 
	scanf("%d", &num);
	switch (num)
	{
	case 1:
		printf("input 8 numbers : ");
		for (int i = 0; i < 8; i++) {
			scanf("%f", &array[i]);
		}
		printf("1. �������� \n2. �������� \n3. ���� ���� \n4. ���� ���� \n5. �� ����\n6. �� ����\n ���ڷ� �Է��ϼ��� :");
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
			quick_sort(array, 0, 7); // ù��° ���� key�� ������ �ְ� �����Ѵ�.
		}
		else if (a == 6) {
			heap_sort(array, 8);
		}
		else {
			printf("1~6������ ���� �Է����ּ���");
			break;
		}

		for (int i = 0; i < 8; i++)
			printf("%d  ",(int)array[i]);

		break;
	case 2: 
		for (int i = 0; i < n; i++) {  //���� ���� (seed)���� ���� ������ �׻� ���� ���� ���� ���̴�.
			input[i] = rand() / (float)RAND_MAX - rand() / (float)RAND_MAX;//0~1������ �Ǽ��� �̾Ƴ��� �װ� �ٽ� 0~1���� �Ǽ��� ���شٸ� -1~1������ �Ǽ��� ���� ���� �� ���̴�.
		}
		printf("1. �������� \n2. �������� \n3. ���� ���� \n4. ���� ���� \n5. �� ����\n6. �� ����\n ���ڷ� �Է��ϼ��� :");
		scanf_s("%d", &a);
		if (a == 1) {
			start = clock(); // �Լ� ���� �ð� ����
			selection_sort(input, n);
			finish = clock();// �Լ� ���� �ð� ����
			//printf("----------------------���� ���ķ� �����մϴ�.-----------------------\n");
		}
		else if (a == 2) {
			start = clock();
			bubble_sort(input, n);
			finish = clock();
			//printf("----------------------���� ���ķ� �����մϴ�.-----------------------\n");
		}
		else if (a == 3) {
			start = clock();
			insertion_sort(input, n);
			finish = clock();
			//printf("----------------------���� ���ķ� �����մϴ�.-----------------------\n");
		}
		else if (a == 4) {
			start = clock();
			merge_sort(input, 0, n - 1);
			finish = clock();
			//printf("----------------------���� ���ķ� �����մϴ�.-----------------------\n");
		}
		else if (a == 5) {
			start = clock();
			quick_sort(input, 0, n - 1); // ù��° ���� key�� ������ �ְ� �����Ѵ�.
			finish = clock();
			//printf("----------------------�� ���ķ� �����մϴ�.-----------------------\n");
		}
		else if (a == 6) {
			start = clock();
			heap_sort(input, n);
			finish = clock();
			//printf("----------------------�� ���ķ� �����մϴ�.-----------------------\n");
		}
		else
			printf("1~6������ ���� �Է����ּ���");
		duration = (float)(finish - start) / CLOCKS_PER_SEC; // ����ð����� ���۽ð��� �A�� �ʴ����� �ٲ��ش�.
		// msec �������� �Ϸ��� �ڿ� CLOCKS_PER_SEC�� ������ ������ �ȴ�.
		printf(" �ɸ� �ð� : %lf\n", duration);

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
	float max = -2;				// -1~1 ������ �����̱⶧���� �ּҰ����� �۾ƾ���
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
			printf("%d ȸ�� : ", count);
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
			printf("%d ȸ�� : ", count);
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
		key = input[i];//key ����
		for (j = i - 1; j >= 0 && input[j] > key; j--) {
			input[j + 1] = input[j];
		}
		input[j + 1] = key;
		if (count++ < 5) {
			printf("%d ȸ�� key = %f : ", count,key);
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
		mid = (left + right) / 2; //�߾� ���� ��´�.
		merge_sort(input, left, mid); // ���ʱ������� ���
		merge_sort(input, mid + 1, right); //������ �����ʱ������� ���
		merge(input, left, mid, right);
	}
}
void merge(float input[], int left, int mid, int right) {
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;
	while (i <= mid && j <= right) { // ���� ���ĵ� input �迭�� �պ�
		if (input[i] <= input[j])
			sorted[k++] = input[i++];
		else
			sorted[k++] = input[j++];
	}
	if (i > mid) {
		for (l = j; l <= right; l++) //  ���� �ִ� ������ �ϰ� ����
			sorted[k++] = input[l];
	}
	else {
		for (l = i; l <= mid; l++)	// ���� �ִ� ������ �ϰ� ����
			sorted[k++] = input[l];
	}
	for (l = left; l <= right; l++) { // sorted[](�ӽ� �迭)�� ����Ʈ��  input �迭�� �纹��
		input[l] = sorted[l];
	}
	if (count++ < 5) {
		printf("%d ȸ�� : ", count);
		for (k = 0; k < 8; k++) {
			printf("%.3f  ", input[k]);
		}
		printf("\n");
	}
}
void build_heap(float input[], int n) {
	int start = n / 2 - 1;// �ڽĳ�尡 �����ϴ� ���� ��ü �� n/2��° ��忡 ������ ���ִ�. -1�� �迭�� �ε����� 0���� �������� �����Ͽ���.
	for (start; start >= 0; start--) // n/2-1��° index ���� ���� index���� �ڽĳ�尡 �����Ѵ�.
		heapify(input, n, start);
}
void heapify(float input[], int n, int start) {
	int root_index = start;
	int left_index = root_index * 2 + 1; // ���� �ڽ� ���
	int right_index = root_index * 2 + 2; // ������ �ڽ� ���
	int largest_index = start;
	if (left_index <n && input[left_index]>input[largest_index]) {
		//left_index�� �迭 �ȿ� �����ؾ��Ѵ�. n���� �۾ƾ���
		largest_index = left_index;
	}
	if (right_index<n && input[right_index]>input[largest_index]) {
		//right_index�� �迭 �ȿ� �����ؾ��Ѵ�. n���� �۾ƾ���
		largest_index = right_index;
	}
	if (root_index != largest_index) {
		SWAP(input[largest_index], input[root_index], temp); // ��ġ�� �ٲٰ�
		heapify(input, n, largest_index); // �ٽ� �� ȭ ���ش�.
	}
}
void heap_sort(float input[], int n) {
	build_heap(input, n); // �ʱ� �迭 �� ���·� ����
	while (n > 1) {
		SWAP(input[0], input[n - 1], temp);
		n--; //������ �Ǿ��ִ� �迭�� ù��° ���� ���������� ��ü �� �ٽ� heapify �� �迭�� ����� ���Ƿ� ���δ�.
		heapify(input, n, 0);
	}

}
void quick_sort(float input[], int start, int end) {
	if (start >= end) {
		return;
	}
	int key = start; // key= pivot,  �ڵ�� ������ �ǹ��� ���� ù��° ������ �Ѵ�
	int i = start + 1;
	int j = end;
	int k;
	while (i <= j) { //�����Ǳ� ������
		while (i <= end && input[i] <= input[key]) {
			i++;
		}
		while (input[j] >= input[key] && j > start) {
			j--;
		}
		if (i > j) { // �����Ǵ� ���� �ǹ��� ��ġ�� ���� �Ѵ�. ���� �ݺ����� Ż��
			SWAP(input[j], input[key], temp); // 
		}
		else {
			SWAP(input[i], input[j], temp);
		}
		if (count++ < 5) {
			printf("%d ȸ�� : ", count);
			for (k = 0; k < 8; k++) {
				printf("%.3f  ", input[k]);
			}
			printf("\n");
		}
	}
	quick_sort(input, start, j - 1); // �ǹ� ���� ����
	quick_sort(input, j + 1, end); // �ǹ� ���� ������
}

