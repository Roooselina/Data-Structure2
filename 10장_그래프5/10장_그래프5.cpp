#include <stdio.h>

#define INF 99999
#define MAX_VERTICES 100

#define TRUE 1
#define FALSE 0

int distance[6];
int found[6];
int pathArray[6];

typedef struct {
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

void printMatrix(int dist[MAX_VERTICES][MAX_VERTICES], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void floyd(GraphType* g) {
    int A[MAX_VERTICES][MAX_VERTICES];
    int i, j, k;

    for (i = 0; i < g->n; i++)
        for (j = 0; j < g->n; j++)
            A[i][j] = g->weight[i][j];

    for (k = 0; k < g->n; k++) {
        for (i = 0; i < g->n; i++) {
            for (j = 0; j < g->n; j++) {
                if (A[i][k] != INF && A[k][j] != INF && (A[i][k] + A[k][j] < A[i][j])) {
                    A[i][j] = A[i][k] + A[k][j];
                }
            }
        }
        printf("{A%d}\n", k - 1);
        printMatrix(A, g->n);
    }
}

int choose(int distance[], int n, int found[]) {
    int i, min, minpos;
    min = INF;
    minpos = -1;
    for (i = 0; i < n; i++) {
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

void dikstra(GraphType* g, int start) {
    int i, u, j;

    for (int i = 0; i < g->n; i++) {
        distance[i] = INF;
        found[i] = FALSE;
        pathArray[i] = INF;
    }
    distance[start] = 0;

    for (i = 0; i <= g->n - 1; i++) {
        u = choose(distance, g->n, found);

        if (u == -1) break;
        found[u] = TRUE;
        pathArray[i] = u;

        for (int j = 0; j < g->n; j++) {
            if (!found[j]) {
                if (distance[u] + g->weight[u][j] < distance[j]) {
                    distance[j] = distance[u] + g->weight[u][j];
                }
            }
        }
        printf("path: ");
        for (int j = 0; j <= i; j++) {
            printf("%d ", pathArray[j]+1);
            if (j <= i - 1) printf(" -> ");

        }
        printf("\n{%d}\n", i + 1);
        for (int j = 0; j < 6; j++) {
            if (distance[j] == INF)
                printf("INF ");
            else  printf("%d ", distance[j]);
        }
        printf("\n\n");
    }
}


int main() {
    GraphType graph = { 6,
        {{0,    10,   INF,   30,   100, INF},
        {INF,  0,    50,   INF,   INF, INF},
        {INF,  INF,  0,    INF,  10,  5},
        {INF,   INF,  20,  0,    INF,  15},
        {INF,  INF,   INF,   60,  0,   INF},
        {INF,  INF,  INF,  INF,  INF,   0}}
    };

    printf("=================  DIJKSTRA  =================\n");
    dikstra(&graph, 0);


    printf("=================  FLOYD  =================\n");
    floyd(&graph);

    return 0;
}