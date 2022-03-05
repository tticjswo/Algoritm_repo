#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VER 100 //여기서는 모든 간선을 정렬전에 넣어야함으로 간선의 최대 수보다 크게 정의한다
#define MAX_VERTICES_PRIM 10  // 신장트리의 정점 개수
#define INF 1000L // 경로가 없는 INFINITE를 표현하기 위해 정의된 상수 INF

int weight[MAX_VERTICES_PRIM][MAX_VERTICES_PRIM] = {// 신장트리의 거리와 모양을 배열로 표현, INF는 바로갈 수 있는 경로가 없음을 뜻한다.
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


int selected[MAX_VERTICES_PRIM]; // 선택된 정점의 정보를 담을 배열, 선택이 됐는지 안됐는지를 표시한다.
int dist[MAX_VERTICES_PRIM]; // 최소의 거리 정보만을 담는 배열, 새로운 최소거리가 나올 때마다 갱신된다.
int parent[MAX_VER]; // 각 정점 부모의 노드가 저장된다 , 음수 이면 그 원소가 최상위 부오라는 뜻이고 음수와 함께 표시된 숫자가 자식의 수다.
int num[MAX_VER]; // 각 정점들의 집합의 개수를 저장한다.

typedef struct {
    int src; //시작정점 번호
    int dest; //끝 정점 번호
    int weight; //가중치
}forSort;

forSort arr[MAX_VER] = {0}; // 간선 별로 시작 정점과 끝 정점 , 가중치를 저장하기 위한 구조체 배열

// 간선들을 구조체 내에 저장하기 위한 함수
int make_arr(int n); 
 // 최소 dist[v]값을 갖는 정점을 반환
int get_min_vertex(int n);
// Prim, s는 시작 정점 , n 은 정점의 수
void prim(int s, int n);
// 오름차순 qsort 에 쓰이는 비교함수
int compare(const void* a, const void* b); 
// 초기화 용 함수
void init_set(int n); 
//원소의 루트 노드를 찾아가서 사이클이 형성되는지 확인하기위한 함수
int find_set(int vertex); 
//사이클이 형성되지 않는 두개의 트리집합을 연결, 단 숫자가 더 작은 쪽이 큰 쪽의 자식으로 들어가는 것이 좋다.
void union_set(int r1, int r2); 
//가중치를 가지고 해당 가중치를 가지는 정점 2개를 찾아서 프린트하는 함수
void print_set(int); 
//크루스칼알고리즘 전 가중치를 기준으로 오름차순으로 정렬을 위한 함수
int sort_for_krusal(int n);
void kruskal(int n);



// ----------------------------------------------------------함수 및 전역 변수 및 구조체 선언 끝

//---------------------------------------------------------
int get_min_vertex(int n)
{
    int v, i; // 정점의 정보를 저장할 변수 v, 반복문을 위한 변수 i

    for (i = 0; i < n; i++)
    {
        if (selected[i] == FALSE) {
            v = i;  // 아직 선택되지 않은 정점의 번호를 v에 저장, 각 함수 실행별 0부터 n - 1까지 차례대로 저장된다.
            break;
        }
    }

    // 위에서 선택된 정점이 과연 최소거리를 지니고 있는 정점인지를 확인한다.
    for (i = 0; i < n; i++)
    {
        // 선택되지 않은 정점들을 순회하면서 최소거리를 가진 정점을 찾아낸다.
        if (selected[i] == FALSE && (dist[i] < dist[v]))
            v = i;  // 더 적은 거리가 존재한다면 해당 정점을 저장한다.
    }

    return(v);  // 최소의 거리를 갖는 정점이 선택됐으므로 정점 번호를 리턴한다.
}
void prim(int s, int n){
    make_arr(n);
    int i, u, v;
    for (u = 0; u < n; u++){  // dist배열과 selected배열의 정보를 초기화
        dist[u] = INF;
        selected[u] = FALSE;
    }
    dist[s] = 0;  // 시작정점과 시작정점간의 거리는 0이다. 자기자신을 순환하는 경로는 없다고 가정한다.
    int min = 0;
    for (i = 0; i < n; i++){
        // 리턴된 정점 번호를 u에 저장한다. u는 최소거리를 가지는 정점. 
        u = get_min_vertex(n);
        selected[u] = TRUE; //  해당 정점을 선택했다고 표시.
  
        for (v = 0; v < n; v++) { // 새로운 정점에서 얻은 이어진 가중치 정보 dist배열 업데이트
            // 선택된 u 정점을 기준으로 정점(u)과 연결되어 있는 정점까지의 거리를 각각 비교.
            if (weight[u][v] != INF) {  // 정점 u와 연결이 되어있고
                // 아직 선택되지 않았으며 해당 변(weight[u][v])의 길이가 기존의 dist[v] 값보다 작다면
                if (selected[v] == FALSE && weight[u][v] < dist[v])
                    dist[v] = weight[u][v]; // dist[v]의 값을 갱신.
            }  
        }
        min += dist[u]; // 최소거리 산출
        print_set(dist[u]);
        printf("선택한 가중치: %d\t-->", dist[u]);
        printf("현재 최소값 : %d\n", min);  
    }
    printf("\n최소값 : %d\n", min);
}
//----------------------------------------------------------프림알고리즘 사용 함수 끝
int compare(const void* a, const void* b) {

    const forSort* m1 = (const forSort*)a;

    const forSort* m2 = (const forSort*)b;

    return m1->weight - m2->weight;
}
void init_set(int n) {
    int i;
    for (i = 0; i < n; i++) {
        //- : 정점, 음수의 숫자 : 집합의 갯수, 양수의 수 : 원소의 부모
        parent[i] = -1;
        // 각 정점들의 집합의 갯수
        num[i] = 1;
    }
}
int find_set(int vertex) {
    int parent_value, p, i = -1;
    for (i = vertex; (parent_value = parent[i]) >= 0; i = parent_value)
        ;    // 원소의 parent를 찾아감
    p = i; //parent를 발견해냄.
    for (i = vertex; (parent_value = parent[i]) >= 0; i = parent_value)
        parent[i] = p;  // 원소의 parent
    return p;
}
void union_set(int r1, int r2) {
    if (num[r1] < num[r2]) {
        parent[r1] = r2;   //r2 = 부모노드가 될것  r1  = 자식
        num[r2] += num[r1]; // r2의 갯수가 r1의 집합의 갯수만큼 들어남.
    }
    else {
        parent[r2] = r1;
        num[r1] += num[r2];
    }
}
void print_set(int weight) {
    //printf("print_set에 인자로 들어온 weight : %d\n", weight);
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
                arr[index].src = i;     // 해당 가중치의 정점 2개를 기억하기위한 배열
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
    qsort(arr, index, sizeof(forSort), compare);  //-->arr배열에 저장된 가중치가 오름차순으로 정리
    printf("간선들의 가중치에 따른 정렬 :\n");
    for (int i = 0; i < index; i++) {     // --> qsort확인
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
    int uset, vset; //정점 u와 정점 v의 집합 번호


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
                printf("선택한 가중치: %d\t-->", min);
                printf("현재 최소값 : %d\n", mincost);
            }
            i++;
        }
    }
    printf("\n최소값 : %d \n", mincost);
}
//----------------------------------------------------------크루스칼 알고리즘 사용 함 수 끝
void main()
{
    int input;
    printf("1. 프림 알고리즘 2. 크루스칼 알고리즘 : "); scanf("%d", &input);
    printf("\n----------------------------------------------------------\n");

    switch (input)
    {
    case 1:  
        printf("프림 알고리즘을 이용한 최소 신장 트리 찾기\n");
        //prim(0, 10);  // 정점 개수가 7개인 그래프에서 0번 정점을 출발하여 얻을 수 있는 최소비용신장트리를 찾아라.
        prim(8,10);
        break;
    case 2 :   
        printf("크루스칼 알고리즘을 이용한 최소 신장 트리 찾기\n");
        kruskal(10);
        break;
    default: printf("1 혹은 2 의 숫자만 입력해주세요 \n");
        break;
    }
   
    
  
}

/*************************************************
 ** End Line
*************************************************/


