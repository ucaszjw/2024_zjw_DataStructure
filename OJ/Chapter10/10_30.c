#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10000
#define THRESHOLD 3

typedef struct {
    int low;
    int high;
} StackNode;

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[low];
    while (low < high) {
        while (low < high && arr[high] >= pivot) --high;
        arr[low] = arr[high];
        while (low < high && arr[low] <= pivot) ++low;
        arr[high] = arr[low];
    }
    arr[low] = pivot;
    return low;
}

void insertionSort(int arr[], int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void quickSort(int arr[], int low, int high) {
    StackNode stack[MAXSIZE];
    int top = -1;
    stack[++top].low = low;
    stack[top].high = high;

    while (top >= 0) {
        StackNode node = stack[top--];
        low = node.low;
        high = node.high;

        if (high - low <= THRESHOLD) {
            insertionSort(arr, low, high);
            continue;
        }

        int pivot = partition(arr, low, high);
        if (pivot - 1 - low < high - pivot) {
            if (pivot + 1 < high) {
                stack[++top].low = pivot + 1;
                stack[top].high = high;
            }
            high = pivot - 1;
        } else {
            if (pivot - 1 > low) {
                stack[++top].low = low;
                stack[top].high = pivot - 1;
            }
            low = pivot + 1;
        }
        stack[++top].low = low;
        stack[top].high = high;
    }
}

int main() {
    int arr[MAXSIZE];
    int n = 0, x;
    do
    {
        scanf("%d", &x);
        arr[n++] = x;
    } while (getchar() != '\n');
    quickSort(arr, 0, n - 1);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}