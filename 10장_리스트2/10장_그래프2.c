#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VERTICLES 50

typedef struct GraphNode {
    int vertex;
    struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
    int n;
    GraphNode* adj_list[MAX_VERTICLES];
} GraphType;

int visited[MAX_VERTICLES];
int adj_matrix[MAX_VERTICLES][MAX_VERTICLES] = { 0 };

typedef struct {
    int fir, sec;
} arrNum;

typedef struct {
    int num;
    arrNum* arrNum;
} chosenNumArray;

void init(GraphType* g, chosenNumArray* a) {
    g->n = 0;
    a->num = 0;
    for (int r = 0; r < MAX_VERTICLES; r++) {
        g->adj_list[r] = NULL;
        visited[r] = 0;
    }
}

void insert_vertex(GraphType* g) {
    if (g->n >= MAX_VERTICLES) {
        fprintf(stderr, "�׷���: ���� ���� ����\n");
        return;
    }
    g->n++;
}

void insert_edge_matrix(int start, int end) {
    adj_matrix[start][end] = 1;
    adj_matrix[end][start] = 1;
}

void insert_edge(GraphType* g, int start, int end) {
    if (start >= g->n || end >= g->n) {
        fprintf(stderr, "�׷���: ���� ��ȣ �ʰ�\n");
        return;
    }

    GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = end;
    node->link = g->adj_list[start];
    g->adj_list[start] = node;
}

void print_adj_matrix(GraphType* g) {
    printf("���� ���:\n");
    int limit = g->n;

    for (int i = 0; i < limit; i++) {
        for (int j = 0; j < limit; j++) {
            printf("%d ", adj_matrix[i][j]);
        }
        printf("\n");
    }
}

void dfs_matrix(int v, int n) {
    visited[v] = 1;
    printf("%c ", v + 65);

    for (int i = 0; i < n; i++) {
        if (adj_matrix[v][i] == 1 && !visited[i]) {
            dfs_matrix(i, n);
        }
    }
}

void dfs_list(GraphType* g, int v) {
    visited[v] = 1;
    printf("%c ", v + 65);

    for (GraphNode* w = g->adj_list[v]; w != NULL; w = w->link) {
        if (!visited[w->vertex]) {
            dfs_list(g, w->vertex);
        }
    }
}

void print_adj_list(GraphType* g) {
    printf("���� ����Ʈ:\n");
    for (int i = 0; i < g->n; i++) {
        printf("%c: ", 'A' + i);
        for (GraphNode* node = g->adj_list[i]; node != NULL; node = node->link) {
            printf("%c ", 'A' + node->vertex);
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
    int node, edge;
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    chosenNumArray* a = (chosenNumArray*)malloc(sizeof(chosenNumArray));

    init(g, a);

    printf("������ ��? ");
    scanf("%d", &node);

    for (int i = 0; i < node; i++) {
        insert_vertex(g);
    }

    printf("���� �׷��� ���� �Ϸ�\n");

    printf("������ ����? ");
    scanf("%d", &edge);

    a->arrNum = (arrNum*)malloc(sizeof(arrNum) * edge);

    srand(time(NULL));

    // ���� ���� �Է�
    while (a->num < edge) {
        int num1 = rand() % node;
        int num2 = rand() % node;

        // �ߺ� ���� üũ �� �ڱ� �ڽŰ��� ���� ����
        int retry = 0;
        for (int j = 0; j < a->num; j++) {
            if ((num1 == a->arrNum[j].fir && num2 == a->arrNum[j].sec) ||
                (num1 == a->arrNum[j].sec && num2 == a->arrNum[j].fir) ||
                (num1 == num2)) {
                retry = 1;
                break;
            }
        }
        if (retry == 1) continue;

        a->arrNum[a->num].fir = num1;
        a->arrNum[a->num].sec = num2;

        // ���� ����Ʈ�� ��Ŀ� ��� ���� �߰�
        insert_edge(g, num1, num2);
        insert_edge_matrix(num1, num2);

        a->num++;
    }

    // ���� ����Ʈ�� ����� DFS ����
    printf("���� ����Ʈ�� ����� DFS: ");
    dfs_list(g, 0);
    printf("\n");

    // ���� ����Ʈ ���
    print_adj_list(g);

    // ���� ��� ���
    print_adj_matrix(g);

    // ���� ����� ����� DFS ����
    reset_visited(node);
    printf("���� ����� ����� DFS: ");
    dfs_matrix(0, node);
    printf("\n");

    // �޸� ����
    for (int i = 0; i < g->n; i++) {
        GraphNode* node = g->adj_list[i];
        while (node != NULL) {
            GraphNode* temp = node;
            node = node->link;
            free(temp);
        }
    }

    free(a->arrNum);
    free(a);
    free(g);

    return 0;
}
