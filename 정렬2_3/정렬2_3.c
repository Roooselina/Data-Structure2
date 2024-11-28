#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define len 10
#define len2 60000
#define BUCKETS 10
#define DIGITS 4
#define MAX 100

typedef struct QueueType {
    int data[MAX];
    int front;
    int rear;
} QueueType;

void init_queue(QueueType* q) {
    q->front = -1;
    q->rear = -1;
}

int is_empty(QueueType* q) {
    return q->front == -1;
}

int is_full(QueueType* q) {
    return (q->rear + 1) % MAX == q->front;
}

void enqueue(QueueType* q, int item) {
    if (is_full(q)) {
        fprintf(stderr, "Queue is full\n");
        exit(1);
    }
    if (is_empty(q)) {
        q->front = q->rear = 0;
    }
    else {
        q->rear = (q->rear + 1) % MAX;
    }
    q->data[q->rear] = item;
}

int dequeue(QueueType* q) {
    if (is_empty(q)) {
        fprintf(stderr, "Queue is empty\n");
        exit(1);
    }
    int item = q->data[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1; // Queue is now empty
    }
    else {
        q->front = (q->front + 1) % MAX;
    }
    return item;
}

void print_buckets(QueueType queues[], int isprint) {
    if (!isprint) return;

    printf("=======================\n");
    for (int b = 0; b < BUCKETS; b++) {
        printf("[%d]-> ", b);
        if (is_empty(&queues[b])) {
            printf("\n");
            continue;
        }

        int index = queues[b].front;
        while (1) {
            printf("%d ", queues[b].data[index]);
            if (index == queues[b].rear) break;
            index = (index + 1) % MAX;
        }
        printf("\n");
    }
    printf("=======================\n");
}

void radix_sort(int list[], int n, int isprint) {
    int i, b, d, factor = 1;
    QueueType queues[BUCKETS];

    for (b = 0; b < BUCKETS; b++) {
        init_queue(&queues[b]);
    }

    for (d = 0; d < DIGITS; d++) {
        for (i = 0; i < n; i++) {
            enqueue(&queues[(list[i] / factor) % 10], list[i]);
        }

        print_buckets(queues, isprint);

        for (b = 0, i = 0; b < BUCKETS; b++) {
            while (!is_empty(&queues[b])) {
                list[i++] = dequeue(&queues[b]);
            }
        }
        factor *= 10;

        if (isprint) {
            printf("\n%d단계: ", d + 1);
            for (int j = 0; j < n; j++) {
                printf("%d ", list[j]);
            }
            printf("\n");
        }
    }
}

int main() {
    srand((unsigned int)time(NULL));
    int numArray[len];
    int copyedArray[len];

    for (int i = 0; i < len; i++) numArray[i] = rand() % 100 + 1;

    // 문제 3
    for (int i = 0; i < len; i++) copyedArray[i] = numArray[i];
    printf("기수 정렬 과정 출력:\n");
    radix_sort(copyedArray, len, 1);

    return 0;
}
