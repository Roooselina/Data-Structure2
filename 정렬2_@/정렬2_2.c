#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define len 10
#define SWAP(x, y, temp) { temp = x; x = y; y = temp; }


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


int main() {
	srand((unsigned int)time(NULL));
	int numArray[len];
	int copyedArray[len];

	for (int i = 0; i < len; i++) numArray[i] = rand() % 100 + 1;

	// 문제 2
	printf("퀵 정렬 과정 출력:\n");
	for (int i = 0; i < len; i++) copyedArray[i] = numArray[i];
	quick_sort(copyedArray, 0, len - 1, 1);


	return 0;
}
