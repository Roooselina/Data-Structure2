#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VERTICLES 50

typedef struct {
    int n;
    int adj_mat[MAX_VERTICLES][MAX_VERTICLES];
} GraphType;

int visited[MAX_VERTICLES];

typedef struct {
    int fir, sec;
} arrNum;

typedef struct {
    int num;
    arrNum* arrNum;
} chosenNumArray;

void init(GraphType* g, chosenNumArray * a) {
    g->n = 0;
    a->num = 0;
    for (int r = 0; r < MAX_VERTICLES; r++) {
        for (int c = 0; c < MAX_VERTICLES; c++)
            g->adj_mat[r][c] = 0;
        visited[r] = 0;
    }
}

void insert_vertex(GraphType* g, int v) {
    if ((g->n) + 1 > MAX_VERTICLES) {
        printf(stderr, "그래프: 정점 개수 초과");
        return;
    }
    g->n++;
}

void insert_edge(GraphType* g, int start, int end) {
    if (start >= g->n || end >= g->n) {
        printf(stderr, "그래프: 정점 번호 오류");
        return;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}

void dfs_mat(GraphType* g, int v) {
    visited[v] = 1;
    printf("%c ", v+65);
    for (int w = 0; w < g->n; w++) {
        if (g->adj_mat[v][w] && !visited[w])
            dfs_mat(g, w);
    }
}

void printGraph(GraphType* g) {
    for (int i = 0; i < g->n; i++) {
        printf("%c ", i + 65);
        for (int j = 0; j < g->n; j++)
            printf("%d ", g->adj_mat[i][j]);
        printf("\n");
    }
}

int main() {
    int node, edge;
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    chosenNumArray* a = (chosenNumArray*)malloc(sizeof(chosenNumArray));
    init(g, a);

    printf("정점의 개수는? ");
    scanf("%d", &node);

    for (int i = 0; i < node; i++) {
        insert_vertex(g, i);
    }

    printf("랜덤 연결 그래프 생성\n");

    printf("간선 수는? ");
    scanf("%d", &edge);
    a->arrNum = (arrNum*)malloc(sizeof(arrNum) * edge);

    srand(time(NULL));

    // 랜덤 간선 입력
    do {
        int num1 = rand() % node;
        int num2 = rand() % node;

        // 중복 간선 검사

        int retry = 0;
        for (int j = 0; j < a->num; j++) {
            if ((num1 == a->arrNum[j].fir && num2 == a->arrNum[j].sec) ||
                (num1 == a->arrNum[j].sec && num2 == a->arrNum[j].fir) ||
                (num1 == num2)) {
                retry = 1;
                break;
            }
        }
        if (retry == 1) 
            continue;

        
        a->arrNum[a->num].fir = num1;
        a->arrNum[a->num].sec = num2;
        insert_edge(g, num1, num2);
        a->num++;
    } while (a->num < edge);

    printGraph(g);

    printf("DFS: ");
    dfs_mat(g, 0);

    // 메모리 해제
    free(a->arrNum);
    free(a);
    free(g);
    return 0;
}