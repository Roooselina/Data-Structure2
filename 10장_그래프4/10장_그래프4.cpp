#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX 100
#define INF 1000

int parent[MAX];
int selected_arr[MAX];
int distance_arr[MAX];

int set_find(int curr) {
    if (parent[curr] == -1)
        return curr;
    while (parent[curr] != -1) curr = parent[curr];
    return curr;
}

void set_union(int a, int b) {
    int root1 = set_find(a);
    int root2 = set_find(b);
    if (root1 != root2) parent[root1] = root2;
}

struct Edge {
    int start, end, weight;
};

typedef struct {
    int n;
    struct Edge edges[2 * MAX];
} GraphType;

typedef struct {
    int n;
    int weight[MAX][MAX];
} GraphType2;

void graph_init(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < 2 * MAX; i++) {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF;
    }
}

void insert_edge(GraphType* g, int start, int end, int w) {
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = w;
    g->n++;
}

int compare(const void* a, const void* b) {
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    return (x->weight - y->weight);
}

void kruskal(GraphType* g, int num_vertices) {
    int edge_accepted = 0;
    int uset, vset;
    struct Edge e;

    qsort(g->edges, g->n, sizeof(struct Edge), compare);

    printf("Kruskal MST: \n");
    int i = 0;
    while (edge_accepted < num_vertices - 1 && i < g->n) {
        e = g->edges[i];
        uset = set_find(e.start);
        vset = set_find(e.end);
        if (uset != vset) {
            printf("간선 (%d, %d) %d 선택\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);
        }
        i++;
    }
}

int get_min(int n) {
    int v = -1;
    for (int i = 0; i < n; i++) {
        if (!selected_arr[i]) {
            if (v == -1 || distance_arr[i] < distance_arr[v])
                v = i;
        }
    }
    return v;
}

void print_status(int n) {
    printf("distance: ");
    for (int i = 0; i < n; i++) {
        if (distance_arr[i] == INF)
            printf("INF ");
        else
            printf("%d ", distance_arr[i]);
    }

    printf("\nselected: ");
    for (int i = 0; i < n; i++) {
        printf("%s ", selected_arr[i] ? "TRUE" : "FALSE");
    }
    printf("\n\n");
}

void prim(GraphType2* g, int s) {
    int i, u, v;
    for (i = 0; i < g->n; i++) {
        selected_arr[i] = FALSE;
        distance_arr[i] = INF;
    }
    distance_arr[s] = 0;

    for (u = 0; u < g->n; u++) {
        int min_vertex = get_min(g->n);
        if (min_vertex == -1 || distance_arr[min_vertex] == INF)
            break;

        selected_arr[min_vertex] = TRUE;
        printf("정점 %c 추가\n", min_vertex+'A');
        print_status(g->n);

        for (v = 0; v < g->n; v++) {
            if (g->weight[min_vertex][v] != INF && !selected_arr[v] && g->weight[min_vertex][v] < distance_arr[v]) {
                distance_arr[v] = g->weight[min_vertex][v];
            }
        }
    }
}

int main(void) {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);
    for (int i = 0; i < MAX; i++)
        parent[i] = -1;

    /*
    서울: 0	인천: 1	전주: 2	광주: 3
    대전: 4	원주: 5	강릉: 6	대구: 7
    부산: 8
    */

    insert_edge(g, 0, 1, 35); insert_edge(g, 0, 4, 154);
    insert_edge(g, 1, 2, 245);
    insert_edge(g, 2, 4, 87); insert_edge(g, 2, 3, 98);
    insert_edge(g, 3, 4, 122);
    insert_edge(g, 4, 5, 165); insert_edge(g, 4, 7, 155);
    insert_edge(g, 5, 6, 117); insert_edge(g, 5, 7, 222);
    insert_edge(g, 7, 8, 164);

    kruskal(g, g->n);

    GraphType2 g2 = {
        7, // Number of vertices
        {
            {0, 7, INF, 5, INF, INF, INF},
            {7, 0, 8, 9, 7, INF, INF},
            {INF, 8, 0, INF, 5, INF, INF},
            {5, 9, INF, 0, 15, 6, INF},
            {INF, 7, 5, 15, 0, 8, 9},
            {INF, INF, INF, 6, 8, 0, 11},
            {INF, INF, INF, INF, 9, 11, 0}
        }
    };


    printf("\nPRIM:\n");
    prim(&g2, 0);

    free(g);
    return 0;
}