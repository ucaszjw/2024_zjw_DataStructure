#include <stdio.h>
#define MAX 1000

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 3*i + 1;
    int mid = 3*i + 2;
    int right = 3*i + 3;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (mid < n && arr[mid] > arr[largest])
        largest = mid;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void ternaryHeapSort(int arr[], int n) {
    for (int i = n / 3 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i=n-1; i>=0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void printArray(int arr[], int n) {
    for (int i=0; i<n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[MAX];
    int x, i = 0;
    do
    {
        scanf("%d", &x);
        arr[i++] = x;
    } while (getchar() != '\n');
    ternaryHeapSort(arr, i);
    printArray(arr, i);
}