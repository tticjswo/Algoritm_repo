# Algoritm_repo
2021_2학기 알고리즘 과목에서 사용한 모든 알고리즘

1. .binary_search
   - 이진탐색 알고리즘을 반복문과 재귀문으로 나누어서 2가지 방법으로 구현.
2. .Sorting_Algo_Time_test  
   - 정렬알고리즘을 구현하고 시간 측정
   - 보고서 참고.
3. .floid_Algo
   - 플로이드 알고리즘, 그 결과를 이용한 최단 경로 출력 알고리즘
4. .TSP_Program
   - Traveling Salesperson Problem을 주어진 수도 코드와 가중치 포함 그래프를 이용해서 구현하고 풀어본다
   - 보고서 참고.
  
               int g1[NUM][NUM] = {
                  {0,4,INF,INF,INF,10,INF},
                  {3,0,INF,18,INF,INF,INF},
                  {INF,6,0,INF,INF,INF,INF},
                  {INF,5,15,0,2,19,5},
                  {INF,INF,12,1,0,INF,INF},
                  {INF,INF,INF,INF,INF,0,10},
                  {INF,INF,INF,8,INF,INF,8}
               };
              
               int g2[NUM][NUM] = {
                  {0,INF,INF,INF,INF,INF,10},
                  {INF,0,1,12,INF,INF,INF},
                  {19,2,0,15,5,INF,5},
                  {INF,INF,INF,0,6,INF,INF},
                  {INF,INF,18,INF,0,3,INF},
                  {10,INF,INF,INF,4,0,INF},
                  {INF,INF,8,INF,INF,INF,0}
               };
