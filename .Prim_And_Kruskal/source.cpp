#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VER 100 //���⼭�� ��� ������ �������� �־�������� ������ �ִ� ������ ũ�� �����Ѵ�
#define MAX_VERTICES_PRIM 10  // ����Ʈ���� ���� ����
#define INF 1000L // ��ΰ� ���� INFINITE�� ǥ���ϱ� ���� ���ǵ� ��� INF

int weight[MAX_VERTICES_PRIM][MAX_VERTICES_PRIM] = {// ����Ʈ���� �Ÿ��� ����� �迭�� ǥ��, INF�� �ٷΰ� �� �ִ� ��ΰ� ������ ���Ѵ�.
 {0  ,32 ,INF,17 ,INF,INF,INF,INF,INF,INF},
 {32, 0, INF, INF, 45, INF, INF, INF, INF, INF},
{ INF,INF,0  ,18 ,INF,INF,5  ,INF,INF,INF },
{ 17 ,INF,18 ,0  ,10 ,INF,INF,3  ,INF,INF },
{ INF,45 ,INF,10 ,0  ,28 ,INF,INF,25 ,INF },
{ INF,INF,INF,INF,28 ,0  ,INF,INF,INF,6 },
{ INF,INF,5  ,INF,INF,INF,0  ,59 ,INF,INF },
{ INF,INF,INF,3  ,INF,INF,59 ,0  ,4  ,INF },
{ INF,INF,INF,INF,25 ,INF,INF,4  ,0  ,12 },
{ INF,INF,INF,INF,INF,6  ,INF,INF,12 ,0 }
};

int temp_weight[MAX_VERTICES_PRIM][MAX_VERTICES_PRIM];


int selected[MAX_VERTICES_PRIM]; // ���õ� ������ ������ ���� �迭, ������ �ƴ��� �ȵƴ����� ǥ���Ѵ�.
int dist[MAX_VERTICES_PRIM]; // �ּ��� �Ÿ� �������� ��� �迭, ���ο� �ּҰŸ��� ���� ������ ���ŵȴ�.
int parent[MAX_VER]; // �� ���� �θ��� ��尡 ����ȴ� , ���� �̸� �� ���Ұ� �ֻ��� �ο���� ���̰� ������ �Բ� ǥ�õ� ���ڰ� �ڽ��� ����.
int num[MAX_VER]; // �� �������� ������ ������ �����Ѵ�.

typedef struct {
    int src; //�������� ��ȣ
    int dest; //�� ���� ��ȣ
    int weight; //����ġ
}forSort;

forSort arr[MAX_VER] = {0}; // ���� ���� ���� ������ �� ���� , ����ġ�� �����ϱ� ���� ����ü �迭

// �������� ����ü ���� �����ϱ� ���� �Լ�
int make_arr(int n); 
 // �ּ� dist[v]���� ���� ������ ��ȯ
int get_min_vertex(int n);
// Prim, s�� ���� ���� , n �� ������ ��
void prim(int s, int n);
// �������� qsort �� ���̴� ���Լ�
int compare(const void* a, const void* b); 
// �ʱ�ȭ �� �Լ�
void init_set(int n); 
//������ ��Ʈ ��带 ã�ư��� ����Ŭ�� �����Ǵ��� Ȯ���ϱ����� �Լ�
int find_set(int vertex); 
//����Ŭ�� �������� �ʴ� �ΰ��� Ʈ�������� ����, �� ���ڰ� �� ���� ���� ū ���� �ڽ����� ���� ���� ����.
void union_set(int r1, int r2); 
//����ġ�� ������ �ش� ����ġ�� ������ ���� 2���� ã�Ƽ� ����Ʈ�ϴ� �Լ�
void print_set(int); 
//ũ�罺Į�˰��� �� ����ġ�� �������� ������������ ������ ���� �Լ�
int sort_for_krusal(int n);
void kruskal(int n);



// ----------------------------------------------------------�Լ� �� ���� ���� �� ����ü ���� ��

//---------------------------------------------------------
int get_min_vertex(int n)
{
    int v, i; // ������ ������ ������ ���� v, �ݺ����� ���� ���� i

    for (i = 0; i < n; i++)
    {
        if (selected[i] == FALSE) {
            v = i;  // ���� ���õ��� ���� ������ ��ȣ�� v�� ����, �� �Լ� ���ະ 0���� n - 1���� ���ʴ�� ����ȴ�.
            break;
        }
    }

    // ������ ���õ� ������ ���� �ּҰŸ��� ���ϰ� �ִ� ���������� Ȯ���Ѵ�.
    for (i = 0; i < n; i++)
    {
        // ���õ��� ���� �������� ��ȸ�ϸ鼭 �ּҰŸ��� ���� ������ ã�Ƴ���.
        if (selected[i] == FALSE && (dist[i] < dist[v]))
            v = i;  // �� ���� �Ÿ��� �����Ѵٸ� �ش� ������ �����Ѵ�.
    }

    return(v);  // �ּ��� �Ÿ��� ���� ������ ���õ����Ƿ� ���� ��ȣ�� �����Ѵ�.
}
void prim(int s, int n){
    make_arr(n);
    int i, u, v;
    for (u = 0; u < n; u++){  // dist�迭�� selected�迭�� ������ �ʱ�ȭ
        dist[u] = INF;
        selected[u] = FALSE;
    }
    dist[s] = 0;  // ���������� ������������ �Ÿ��� 0�̴�. �ڱ��ڽ��� ��ȯ�ϴ� ��δ� ���ٰ� �����Ѵ�.
    int min = 0;
    for (i = 0; i < n; i++){
        // ���ϵ� ���� ��ȣ�� u�� �����Ѵ�. u�� �ּҰŸ��� ������ ����. 
        u = get_min_vertex(n);
        selected[u] = TRUE; //  �ش� ������ �����ߴٰ� ǥ��.
  
        for (v = 0; v < n; v++) { // ���ο� �������� ���� �̾��� ����ġ ���� dist�迭 ������Ʈ
            // ���õ� u ������ �������� ����(u)�� ����Ǿ� �ִ� ���������� �Ÿ��� ���� ��.
            if (weight[u][v] != INF) {  // ���� u�� ������ �Ǿ��ְ�
                // ���� ���õ��� �ʾ����� �ش� ��(weight[u][v])�� ���̰� ������ dist[v] ������ �۴ٸ�
                if (selected[v] == FALSE && weight[u][v] < dist[v])
                    dist[v] = weight[u][v]; // dist[v]�� ���� ����.
            }  
        }
        min += dist[u]; // �ּҰŸ� ����
        print_set(dist[u]);
        printf("������ ����ġ: %d\t-->", dist[u]);
        printf("���� �ּҰ� : %d\n", min);  
    }
    printf("\n�ּҰ� : %d\n", min);
}
//----------------------------------------------------------�����˰��� ��� �Լ� ��
int compare(const void* a, const void* b) {

    const forSort* m1 = (const forSort*)a;

    const forSort* m2 = (const forSort*)b;

    return m1->weight - m2->weight;
}
void init_set(int n) {
    int i;
    for (i = 0; i < n; i++) {
        //- : ����, ������ ���� : ������ ����, ����� �� : ������ �θ�
        parent[i] = -1;
        // �� �������� ������ ����
        num[i] = 1;
    }
}
int find_set(int vertex) {
    int parent_value, p, i = -1;
    for (i = vertex; (parent_value = parent[i]) >= 0; i = parent_value)
        ;    // ������ parent�� ã�ư�
    p = i; //parent�� �߰��س�.
    for (i = vertex; (parent_value = parent[i]) >= 0; i = parent_value)
        parent[i] = p;  // ������ parent
    return p;
}
void union_set(int r1, int r2) {
    if (num[r1] < num[r2]) {
        parent[r1] = r2;   //r2 = �θ��尡 �ɰ�  r1  = �ڽ�
        num[r2] += num[r1]; // r2�� ������ r1�� ������ ������ŭ ��.
    }
    else {
        parent[r2] = r1;
        num[r1] += num[r2];
    }
}
void print_set(int weight) {
    //printf("print_set�� ���ڷ� ���� weight : %d\n", weight);
    if (weight == 0) {
        return;
    }
    for (int i = 0; i < MAX_VER; i++) {
        if (arr[i].weight == INF)
            break;
        if (arr[i].weight == weight) {
            printf("(%d , %d) : ", arr[i].src + 1, arr[i].dest + 1);
            break;
        }
    }
}

int make_arr(int n) {
    for (int i = 0; i < MAX_VERTICES_PRIM; i++) {
        for (int j = 0; j < MAX_VERTICES_PRIM; j++) {
            temp_weight[i][j] = weight[i][j];
        }
    }
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (temp_weight[i][j] != 0 && temp_weight[i][j] != INF) {
                arr[index].weight = weight[i][j];
                temp_weight[j][i] = 0;
                arr[index].src = i;     // �ش� ����ġ�� ���� 2���� ����ϱ����� �迭
                arr[index].dest = j;
                //printf("(%d , %d) : %d\n", arr[index].src+1, arr[index].dest+1, arr[index].weight);
                index++;
            } 
        }
    }
    return index;
}
int sort_for_krusal(int n) {
    
    int index = make_arr(n);
    qsort(arr, index, sizeof(forSort), compare);  //-->arr�迭�� ����� ����ġ�� ������������ ����
    printf("�������� ����ġ�� ���� ���� :\n");
    for (int i = 0; i < index; i++) {     // --> qsortȮ��
        if (arr[i].weight == INF)
            break;
        printf("(%d , %d) : %d\n", arr[i].src, arr[i].dest, arr[i].weight);
    }
    return index;
}
void kruskal(int n) {
    int i, j;
    //int index = 0;
    int edge_count = 0;
    int min, mincost = 0;
    int uset, vset; //���� u�� ���� v�� ���� ��ȣ


    int index = sort_for_krusal(n);

    init_set(n);
    i = 0;
    while (edge_count < (n - 1)) {
        if (i < index) {
            min = arr[i].weight;
            uset = find_set(arr[i].src);
            vset = find_set(arr[i].dest);
            if (uset != vset) {
                edge_count++;
                union_set(uset, vset);
                mincost += min;
                print_set(min);
                printf("������ ����ġ: %d\t-->", min);
                printf("���� �ּҰ� : %d\n", mincost);
            }
            i++;
        }
    }
    printf("\n�ּҰ� : %d \n", mincost);
}
//----------------------------------------------------------ũ�罺Į �˰��� ��� �� �� ��
void main()
{
    int input;
    printf("1. ���� �˰��� 2. ũ�罺Į �˰��� : "); scanf("%d", &input);
    printf("\n----------------------------------------------------------\n");

    switch (input)
    {
    case 1:  
        printf("���� �˰����� �̿��� �ּ� ���� Ʈ�� ã��\n");
        //prim(0, 10);  // ���� ������ 7���� �׷������� 0�� ������ ����Ͽ� ���� �� �ִ� �ּҺ�����Ʈ���� ã�ƶ�.
        prim(8,10);
        break;
    case 2 :   
        printf("ũ�罺Į �˰����� �̿��� �ּ� ���� Ʈ�� ã��\n");
        kruskal(10);
        break;
    default: printf("1 Ȥ�� 2 �� ���ڸ� �Է����ּ��� \n");
        break;
    }
   
    
  
}

/*************************************************
 ** End Line
*************************************************/


