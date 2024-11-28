#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define len2 60000
#define BUCKETS 10
#define DIGITS 4
#define SWAP(x, y, temp) { temp = x; x = y; y = temp; }

int sorted[len2];

typedef struct QueueType {
	int* list;
	int front, rear;
	int size;
} QueueType;

void init_queue(QueueType* q, int size) {
	q->list = (int*)malloc(size * sizeof(int));
	q->front = q->rear = 0;
	q->size = size;
}

void free_queue(QueueType* q) {
	free(q->list);
}

int is_empty(QueueType* q) {
	return q->front == q->rear;
}

void enqueue(QueueType* q, int item) {
	q->rear = (q->rear + 1) % q->size;
	q->list[q->rear] = item;
}

int dequeue(QueueType* q) {
	q->front = (q->front + 1) % q->size;
	return q->list[q->front];
}

void merge(int list[], int left, int mid, int right) {
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;

	while (i <= mid && j <= right) {
		if (list[i] <= list[j]) sorted[k++] = list[i++];
		else sorted[k++] = list[j++];
	}
	while (i <= mid) sorted[k++] = list[i++];
	while (j <= right) sorted[k++] = list[j++];

	for (l = left; l <= right; l++) list[l] = sorted[l];
}

// 합병 정렬 메서드
void merge_sort(int list[], int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		merge_sort(list, left, mid);
		merge_sort(list, mid + 1, right);
		merge(list, left, mid, right);
	}
}


int partition(int list[], int left, int right, int isprint) {
	int pivot, temp;
	int low = left;
	int high = right + 1;
	pivot = list[left];

	do {
		do {
			low++;
		} while (low <= right && list[low] < pivot);
		do {
			high--;
		} while (high >= left && list[high] > pivot);
		if (low < high) {
			SWAP(list[low], list[high], temp);
			if (isprint) {
				printf("\n");
				for (int i = 0; i <= right; i++) {
					printf("%d\t", list[i]);
				}
				printf("\n");
				for (int i = 0; i <= right; i++) {
					if (i == low)
						printf("low\t");
					else if (i == high)
						printf("high\t");
					else
						printf("\t");
				}
				printf("\n");
			}
		}
	} while (low < high);

	SWAP(list[left], list[high], temp);
	if (isprint) {
		printf("\n");
		for (int i = 0; i <= right; i++) {
			printf("%d\t", list[i]);
		}


		printf("\n");
		for (int i = 0; i <= right; i++) {
			if (i == high)
				printf("pivot\t");
			else
				printf("\t");
		}
		printf("\n");
	}
	return high;
}

// 퀵 정렬 메서드
void quick_sort(int list[], int left, int right, int isprint) {
	if (left < right) {
		int q = partition(list, left, right, isprint);
		quick_sort(list, left, q - 1, isprint);
		quick_sort(list, q + 1, right, isprint);
	}
}


// 기수 정렬 메서드
void radix_sort(int list[], int n, int isprint) {
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS];

	for (b = 0; b < BUCKETS; b++) {
		init_queue(&queues[b], n);
	}

	for (d = 0; d < DIGITS; d++) {
		for (i = 0; i < n; i++) {
			enqueue(&queues[(list[i] / factor) % 10], list[i]);
		}

		for (b = 0, i = 0; b < BUCKETS; b++) {
			while (!is_empty(&queues[b])) {
				list[i++] = dequeue(&queues[b]);
			}
		}
		factor *= 10;
	}

	for (b = 0; b < BUCKETS; b++) {
		free_queue(&queues[b]);
	}
}

int main() {
	srand((unsigned int)time(NULL));
	int numArray[len2];
	int copyedArray[len2];

	for (int i = 0; i < len2; i++) numArray[i] = rand() % 10000000 + 1;

	// 문제1: 시간 비교
	// 합병 정렬
	for (int i = 0; i < len2; i++) copyedArray[i] = numArray[i];
	int startTime = clock();
	merge_sort(copyedArray, 0, len2 - 1);
	int endTime = clock();
	printf("Merge Sort 정렬 시간: %lf\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);

	// 퀵 정렬
	for (int i = 0; i < len2; i++) copyedArray[i] = numArray[i];
	startTime = clock();
	quick_sort(copyedArray, 0, len2 - 1, 0);
	endTime = clock();
	printf("Quick Sort 정렬 시간: %lf\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);
	
	// 기수 정렬
	for (int i = 0; i < len2; i++) copyedArray[i] = numArray[i];
	startTime = clock();
	radix_sort(copyedArray, len2, 0);
	endTime = clock();
	printf("Radix Sort 정렬 시간: %lf\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);
	return 0;
}
