#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// ------------------------------
// Min Binary Heap Structure
// ------------------------------
typedef struct MinHeap {
    int *arr;
    int size;
    int capacity;
} MinHeap;

// ------------------------------
MinHeap* initHeap(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->arr = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// ------------------------------
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// ------------------------------
void heapifyUp(MinHeap *heap, int index) {
    if (index == 0) return;

    int parent = (index - 1) / 2;

    if (heap->arr[parent] > heap->arr[index]) {
        swap(&heap->arr[parent], &heap->arr[index]);
        heapifyUp(heap, parent);
    }
}

// ------------------------------
void heapifyDown(MinHeap *heap, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < heap->size && heap->arr[left] < heap->arr[smallest])
        smallest = left;

    if (right < heap->size && heap->arr[right] < heap->arr[smallest])
        smallest = right;

    if (smallest != index) {
        swap(&heap->arr[smallest], &heap->arr[index]);
        heapifyDown(heap, smallest);
    }
}

// ------------------------------
void insert(MinHeap *heap, int value) {
    if (heap->size == heap->capacity) {
        printf("Heap Overflow\n");
        return;
    }

    heap->arr[heap->size] = value;
    heapifyUp(heap, heap->size);
    heap->size++;
}

// ------------------------------
int extractMin(MinHeap *heap) {
    if (heap->size <= 0)
        return INT_MIN;

    int root = heap->arr[0];

    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    heapifyDown(heap, 0);

    return root;
}

// ------------------------------
int search(MinHeap *heap, int value) {
    for (int i = 0; i < heap->size; i++)
        if (heap->arr[i] == value)
            return i;
    return -1;
}

// ------------------------------
void display(MinHeap *heap) {
    printf("Heap elements: ");
    for (int i = 0; i < heap->size; i++)
        printf("%d ", heap->arr[i]);
    printf("\n");
}

// ------------------------------
void freeHeap(MinHeap *heap) {
    free(heap->arr);
    free(heap);
}

// ------------------------------
// USER INPUT (Exactly what you asked for)
// ------------------------------
int main() {
    int n;

    printf("Enter number of elements to insert: ");
    scanf("%d", &n);

    MinHeap *heap = initHeap(n);

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        insert(heap, val);
    }

    printf("\nFinal Min Heap:\n");
    display(heap);

    printf("Min element (root) = %d\n", heap->arr[0]);

    freeHeap(heap);
    return 0;
}
