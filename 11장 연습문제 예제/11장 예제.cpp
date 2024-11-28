/*#include <stdio.h>

#define INF 99999
#define N 6
#define MAX_VERTICES 100

typedef struct {
    int n;
    int weight[N][N];
} GraphType;

// Function to print the matrix
void printMatrix(int dist[N][N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
    printf("\n"); // Add an extra newline for better readability
}

void floyd(GraphType* g) {
    int A[N][N];
    int i, j, k;

    // Initialize A with the original weights
    for (i = 0; i < g->n; i++)
        for (j = 0; j < g->n; j++)
            A[i][j] = g->weight[i][j];

    printf("Initial distance matrix:\n");
    printMatrix(A, g->n);

    // Apply Floyd-Warshall algorithm
    for (k = 0; k < g->n; k++) {
        for (i = 0; i < g->n; i++) {
            for (j = 0; j < g->n; j++) {
                if (A[i][k] != INF && A[k][j] != INF && (A[i][k] + A[k][j] < A[i][j])) {
                    A[i][j] = A[i][k] + A[k][j];
                }
            }
        }
        printf("Distance matrix after considering vertex %d:\n", k);
        printMatrix(A, g->n);
    }

    // Optionally, you can update the graph's weight matrix with the shortest distances
    // for (i = 0; i < g->n; i++)
    //     for (j = 0; j < g->n; j++)
    //         g->weight[i][j] = A[i][j];
}

int main() {
    GraphType graph;
    graph.n = N;

    // Initialize the graph's weight matrix
    int initialWeights[N][N] = {
        {0,    50,   45,   10,   INF, INF},
        {INF,  0,    10,   15,   INF, INF},
        {INF,  INF,  0,    INF,  30,  INF},
        {20,   INF,  INF,  0,    15,  INF},
        {INF,  20,   35,   INF,  0,   INF},
        {INF,  INF,  INF,  INF,  3,   0}
    };

    // Copy initialWeights to graph.weight
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            graph.weight[i][j] = initialWeights[i][j];

    printf("Initial Graph:\n");
    printMatrix(graph.weight, graph.n);

    floyd(&graph);

    return 0;
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX
#define TRUE 1
#define FALSE 0

typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

typedef struct {
    int n;             // Number of vertices
    Node** adj_list;   // Array of adjacency lists
} GraphType;

int distance[6];      // Global distance array
int found[6];         // Global found array
int pathArray[6];


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
    int i, u;
    Node* temp;
    for (i = 0; i < g->n; i++) {
        distance[i] = INF;
        found[i] = FALSE;
        pathArray[i] = INF;
    }
    distance[start] = 0;

    for (i = 0; i < g->n - 1; i++) {
        u = choose(distance, g->n, found);

        if (u == -1) break;
        found[u] = TRUE;
        pathArray[i] = u;
        for (temp = g->adj_list[u]; temp != NULL; temp = temp->next) {
            if (!found[temp->vertex]) {
                if (distance[u] + temp->weight < distance[temp->vertex]) {
                    distance[temp->vertex] = distance[u] + temp->weight;
                }
            }
        }
        printf("path: ");
        for (int j = 0; j <= i; j++) {
            printf("%d ", pathArray[j]);
            if (j <= i - 1) printf(" -> ");
            
        }
        printf("\ndistance: ");
        for (int j = 0; j < 6; j++) {
            if (distance[j] == INF)
                printf("INF ");
            else  printf("%d ", distance[j]);
        }
        printf("\n\n");
    }


}

GraphType* create_graph(int n) {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    g->n = n;
    g->adj_list = (Node**)malloc(n * sizeof(Node*));
    for (int i = 0; i < n; i++) {
        g->adj_list[i] = NULL;
    }
    return g;
}

void add_edge(GraphType* g, int u, int v, int weight) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->vertex = v;
    node->weight = weight;
    node->next = g->adj_list[u];
    g->adj_list[u] = node;
}

int main() {
    GraphType* g = create_graph(6);

    add_edge(g, 0, 1, 50);
    add_edge(g, 0, 2, 45);
    add_edge(g, 0, 3, 10);
    add_edge(g, 1, 2, 10);
    add_edge(g, 1, 3, 15);
    add_edge(g, 2, 4, 30);
    add_edge(g, 3, 0, 20);
    add_edge(g, 3, 4, 15);
    add_edge(g, 4, 1, 20);
    add_edge(g, 4, 2, 35);
    add_edge(g, 5, 4, 3);

    dikstra(g, 0);

    // Free allocated memory
    for (int i = 0; i < g->n; i++) {
        Node* current = g->adj_list[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(g->adj_list);
    free(g);

    return 0;
}
