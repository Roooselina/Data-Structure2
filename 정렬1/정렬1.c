#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define SIZE 10
#define SIZE2  50000


void printSort(int num[]) {
    for (int i = 0; i < SIZE; i++) printf("%d ", num[i]);
    printf("\n");
}

void bubbleSort(int num[], int print) {
    int i, j, temp;
    for (i = SIZE - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (num[j] > num[j + 1])
                SWAP(num[j], num[j + 1], temp);
        }
        if (print == 1) {
            printf("Step %d: ", SIZE - i);
            printSort(num);
        }
    }
}

void inc_insertion_sort(int num[], int first, int last, int gap) {
    int i, j, key;
    for (i = first + gap; i <= last; i += gap) {
        key = num[i];
        for (j = i - gap; j >= first && key < num[j]; j -= gap)
            num[j + gap] = num[j];
        num[j + gap] = key;
    }
}

void shellSort(int num[], int print) {
    int gap, step = 1;
    for (gap = SIZE / 2; gap > 0; gap /= 2) {
        if (gap % 2 == 0) gap++;
        for (int i = 0; i < gap; i++) {
            inc_insertion_sort(num, i, SIZE - 1, gap);
        }
        if (print == 1) {
            printf("Step %d: ", step++);
            printSort(num);
        }
    }
}

void insertSort(int num[], int print) {
    int i, j, key;
    for (i = 1; i < SIZE; i++) {
        key = num[i];
        for (j = i - 1; j >= 0 && num[j] > key; j--)
            num[j + 1] = num[j];
        num[j + 1] = key;
        if (print == 1) {
            printf("Step %d: ", i);
            printSort(num);
        }
    }
}

void selectSort(int num[], int print) {
    int i, j, least, temp;
    for (i = 0; i < SIZE - 1; i++) {
        least = i;
        for (j = i + 1; j < SIZE; j++) {
            if (num[j] < num[least]) least = j;
        }
        SWAP(num[i], num[least], temp);
        if (print == 1) {
            printf("Step %d: ", i);
            printSort(num);
        }
    }
}

void copyArray(int dest[], int src[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

int main() {
    int num[SIZE];
    int copiedArray[SIZE];

    srand(time(NULL));
    for (int i = 0; i < SIZE; i++) {
        num[i] = rand() % 100 + 1;
    }

    printf("원본 수열: ");
    printSort(num);

    // 버블 정렬
    printf("\n=========== 버블 정렬 =============\n");
    copyArray(copiedArray, num, SIZE);
    bubbleSort(copiedArray, 1);

    // 선택 정렬
    printf("\n=========== 선택 정렬 =============\n");
    copyArray(copiedArray, num, SIZE);
    selectSort(copiedArray, 1);

    // 삽입 정렬
    printf("\n=========== 삽입 정렬 =============\n");
    copyArray(copiedArray, num, SIZE);
    insertSort(copiedArray, 1);

    // 셸 정렬
    printf("\n=========== 셸 정렬 =============\n");
    copyArray(copiedArray, num, SIZE);
    shellSort(copiedArray, 1);

    // 걸린 시간 측정
    int num2[SIZE2];
    int copiedArray2[SIZE2];
    for (int i = 0; i < SIZE2; i++) {
        num2[i] = rand() % 1000000 + 1;
    }

    // 버블 정렬
    printf("\n=========== 버블 정렬 =============\n");
    copyArray(copiedArray2, num2, SIZE2);
    clock_t start = clock();
    bubbleSort(copiedArray2, 0);
    clock_t end = clock();
    printf("소요시간: %f 초\n", (double)(end - start) / CLOCKS_PER_SEC);

    // 선택 정렬
    printf("\n=========== 선택 정렬 =============\n");
    copyArray(copiedArray2, num2, SIZE2);
    start = clock();
    selectSort(copiedArray2, 0);
    end = clock();
    printf("소요시간: %lf 초\n", (double)(end - start) / CLOCKS_PER_SEC);

    // 삽입 정렬
    printf("\n=========== 삽입 정렬 =============\n");
    copyArray(copiedArray2, num2, SIZE2);
    start = clock();
    insertSort(copiedArray2, 0);
    end = clock();
    printf("소요시간: %lf 초\n", (double)(end - start) / CLOCKS_PER_SEC);

    // 셸 정렬
    printf("\n=========== 셸 정렬 =============\n");
    copyArray(copiedArray2, num2, SIZE2);
    start = clock();
    shellSort(copiedArray2, 0);
    end = clock();
    printf("소요시간: %lf 초\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}