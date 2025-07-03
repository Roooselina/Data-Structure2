#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 6000000

int numArr[MAX];
int copyArr[MAX];

int compare(const void* a, const void* b) {
    int num1 = *(int*)a;
    int num2 = *(int*)b;

    if (num1 < num2)
        return -1;
    if (num1 > num2)
        return 1;
    return 0;
}

int sequentialSearch(int list[], int target, int* compareNum) {
    for (int i = 0; i < MAX; i++) {
        (*compareNum)++;
        if (list[i] == target)
            return i;
    }
    return -1;
}

int binarySearch(int list[], int target, int* compareNum) {
    int left = 0;
    int right = MAX - 1;

    while (left <= right) {
        (*compareNum)++;
        int mid = left + (right - left) / 2;

        if (list[mid] == target)
            return mid;

        if (list[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int main() {
    srand(time(NULL));
    int searchIndex;

    for (int i = 0; i < MAX; i++)
        numArr[i] = rand() % 10000 + 1;

    qsort(numArr, MAX, sizeof(int), compare);
    for (int i = 0; i < MAX; i++)
        copyArr[i] = numArr[i];

    searchIndex = rand() % MAX;
    int compareNum = 0;

    // Sequential Search
    clock_t startTime = clock();
    int seqIndex = sequentialSearch(copyArr, copyArr[searchIndex], &compareNum);
    clock_t endTime = clock();
    double sequentialTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    printf("Sequential Search \t| Index: %d, ComparisonNum: %d, Time: %.10f seconds\n", seqIndex, compareNum, sequentialTime);

    // Binary Search
    compareNum = 0;
    startTime = clock();
    int binIndex = binarySearch(numArr, copyArr[searchIndex], &compareNum);
    endTime = clock();
    double binaryTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    printf("Binary Search\t\t| Index: %d, ComparisonNum: %d, Time: %.10f seconds\n", binIndex, compareNum, binaryTime);

    return 0;
}
