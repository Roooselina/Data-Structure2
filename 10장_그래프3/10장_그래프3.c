#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50

typedef struct GraphNode {
    int vertex;
    struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
    int n;
    GraphNode* adj_list[MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES];
int adj_matrix[MAX_VERTICES][MAX_VERTICES] = { 0 };

typedef struct {
    int front, rear;
    int data[MAX_VERTICES];
} QueueType;

void init(GraphType* g) {
    g->n = 0;
    for (int r = 0; r < MAX_VERTICES; r++) {
        g->adj_list[r] = NULL;
        visited[r] = 0;
    }
}

void initQueue(QueueType* q) {
    q->front = -1;
    q->rear = -1;
}

int is_empty(QueueType* q) {
    return q->front == q->rear;
}

int is_full(QueueType* q) {
    return q->rear == MAX_VERTICES - 1;
}

void enqueue(QueueType* q, int v) {
    if (!is_full(q)) {
        q->data[++q->rear] = v;
    }
}

int dequeue(QueueType* q) {
    if (!is_empty(q)) {
        return q->data[++q->front];
    }
    return -1;
}

void insert_vertex(GraphType* g) {
    if (g->n >= MAX_VERTICES) {
        fprintf(stderr, "그래프: 정점 개수 오류\n");
        return;
    }
    g->n++;
}

void insert_edge_matrix(int start, int end) {
    if (start < MAX_VERTICES && end < MAX_VERTICES) {
        adj_matrix[start][end] = 1;
        adj_matrix[end][start] = 1;
    }
    else {
        fprintf(stderr, "그래프: 정점 번호 초과\n");
    }
}

void insert_edge(GraphType* g, int start, int end) {
    if (start >= g->n || end >= g->n) {
        fprintf(stderr, "그래프: 정점 번호 초과\n");
        return;
    }

    GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = end;
    node->link = g->adj_list[start];
    g->adj_list[start] = node;
}

void print_adj_matrix(GraphType* g) {
    printf("인접 행렬:\n");
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            printf("%d ", adj_matrix[i][j]);
        }
        printf("\n");
    }
}

void convert_matrix_to_list(GraphType* g) {
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            if (adj_matrix[i][j] == 1) {
                insert_edge(g, i, j);
            }
        }
    }
}

void dfs_matrix(int v, int n) {
    visited[v] = 1;
    printf("%d ", v + 1);

    for (int i = 0; i < n; i++) {
        if (adj_matrix[v][i] == 1 && !visited[i]) {
            dfs_matrix(i, n);
        }
    }
}

void dfs_list(GraphType* g, int v) {
    visited[v] = 1;
    printf("%d ", v + 1); 

    for (GraphNode* w = g->adj_list[v]; w != NULL; w = w->link) {
        if (!visited[w->vertex]) {
            dfs_list(g, w->vertex);
        }
    }
}

void bfs_matrix(GraphType* g, int v) {
    QueueType q;
    initQueue(&q);

    visited[v] = 1;
    printf("%d ", v + 1);
    enqueue(&q, v);
    while (!is_empty(&q)) {
        v = dequeue(&q);
        for (int w = 0; w < g->n; w++) {
            if (adj_matrix[v][w] == 1 && !visited[w]) {
                visited[w] = 1;
                printf("%d ", w + 1);
                enqueue(&q, w);
            }
        }
    }
}

void bfs_list(GraphType* g, int v) {
    QueueType q;
    initQueue(&q);

    visited[v] = 1;
    printf("%d ", v + 1);
    enqueue(&q, v);
    while (!is_empty(&q)) {
        v = dequeue(&q);
        for (GraphNode* w = g->adj_list[v]; w != NULL; w = w->link) {
            if (!visited[w->vertex]) {
                visited[w->vertex] = 1;
                printf("%d ", w->vertex + 1);
                enqueue(&q, w->vertex);
            }
        }
    }
}

void print_adj_list(GraphType* g) {
    printf("인접 리스트:\n");
    for (int i = 0; i < g->n; i++) {
        printf("%d: ", i + 1); 
        for (GraphNode* node = g->adj_list[i]; node != NULL; node = node->link) {
            printf("%d ", node->vertex + 1); 
        }
        printf("\n");
    }
}

void reset_visited(int n) {
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }
}

int main() {
    int node = 8;
    GraphType g;

    init(&g);

    printf("정점의 수: 8\n");
    for (int i = 0; i < node; i++) {
        insert_vertex(&g);
    }

    printf("간선 입력:\n");
    insert_edge_matrix(0, 1);
    insert_edge_matrix(0, 2);
    insert_edge_matrix(1, 7);

    insert_edge_matrix(2, 3);
    insert_edge_matrix(2, 4);
    insert_edge_matrix(3, 4);

    insert_edge_matrix(5, 6);
    insert_edge_matrix(5, 7);
    insert_edge_matrix(6, 7);

    printf("인접 행렬을 사용한 DFS: ");
    dfs_matrix(0, node);
    printf("\n");

    print_adj_matrix(&g);

    convert_matrix_to_list(&g);

    print_adj_list(&g);

    reset_visited(node);
    printf("인접 리스트를 사용한 DFS: ");
    dfs_list(&g, 0);
    printf("\n");

    reset_visited(node);
    printf("인접 행렬을 사용한 BFS: ");
    bfs_matrix(&g, 0);
    printf("\n");

    reset_visited(node);
    printf("인접 리스트를 사용한 BFS: ");
    bfs_list(&g, 0);
    printf("\n");

    return 0;
}