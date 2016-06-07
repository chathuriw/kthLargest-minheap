#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "Maxfiles.h"
#include <MaxSLiCInterface.h>

// Prototype of a utility function to swap two integers
void swap(int *x, int *y);

// A struct for Min Heap
typedef struct MinHeap_t {
    int *harr; // pointer to array of elements in heap
    int capacity; // maximum possible size of min heap
    int heap_size; // Current number of elements in min heap
} Heap;

void init_min_heap(Heap *heap, int a[], int size); // Constructor
void buildHeap(Heap *heap);
void MinHeapify(Heap *heap, int i);  //To minheapify subtree rooted with index i
int parent(int i)  { return (i-1)/2;  }
int left(int i)    { return (2*i + 1);  }
int right(int i)   { return (2*i + 2);  }
int extractMin(Heap *heap);  // extracts root (minimum) element
int getMin(Heap *heap)     {  return heap->harr[0]; }

void printArray(int *arr, int n) {
	int i = 0;
	for (i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

// to replace root with new node x and heapify() new root
void replaceMin(Heap *heap, int x) {
	heap->harr[0] = x;
	MinHeapify(heap, 0);
}

void init_min_heap(Heap *heap, int a[], int size) {
    heap->heap_size = size;
    heap->harr = a;  // store address of array
}

void buildHeap(Heap *heap) {
	// printf("build heap: \n");
	// printArray(heap->harr, heap->heap_size);

    int i = (heap->heap_size - 1)/2;
    while (i >= 0)
    {
        MinHeapify(heap, i);
        i--;
    }
}

void buildHeap2(Heap *heap) {
	// printf("build heap: \n");
	// printArray(heap->harr, heap->heap_size);

    int i = (heap->heap_size - 1)/2;
    while (i >= 0)
    {
        MinHeapify(heap, i);
        i--;
    }
}

// A utility function to swap two elements
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void MinHeapify(Heap *heap, int i) {
	int le = 0;
	int ri = 0;
	int heapsize = heap->heap_size;
	int *A = heap->harr;
    int largest = 0;
    int next = 0;
	while (i < heapsize) {
		// if (next == i) {
			le = left(i);
			ri = right(i);
			if (le < heapsize && A[le] < A[i]) {
				largest = le;
			} else {
				largest = i;
			}
			if (ri < heapsize && A[ri] < A[largest]) {
				largest = ri;
			}
			if (next == i && largest != i) {
				//printf("Swap indexes (%d, %d) : values (%d, %d)\n", i, largest, A[i], A[largest]);
				swap(&A[i], &A[largest]);
				next = largest;
			}
		//}
		i++;
     }
}

// Function to return k'th largest element from input stream
void kthLargest(int k) {
    // count is total no. of elements in stream seen so far
    int count = 0, x;  // x is for new element

    // Create a min heap of size k
    int *arr = calloc(k, sizeof(int));
    Heap minheap;
    init_min_heap(&minheap, arr, k);

    while (1)
    {
        // Take next element from stream
    	printf("Enter element: ");
        scanf("%d", &x);

        // Nothing much to do for first k-1 elements
        if (count < k-1) {
            arr[count] = x;
            count++;
        } else {
          // If this is k'th element, then store it
          // and build the heap created above
          if (count == k-1)
          {
              arr[count] = x;
              buildHeap(&minheap);
          } else {
			  // If next element is greater than  k'th
			  // largest, then replace the root
			  if (x > getMin(&minheap)) {
				replaceMin(&minheap, x); // replaceMin calls heapify()
			  }
          }

          // Root of heap is k'th largest element
          printf("K'th largest element is %d\n", getMin(&minheap));
          count++;
        }
        // printArray(minheap.harr, minheap.heap_size);
    }
}

// Function to return k'th largest element from input stream
void kthLargestArray(int k, int *array, int arraySize) {
    // count is total no. of elements in stream seen so far
    int count = 0, x;  // x is for new element

    // Create a min heap of size k
    int *arr = calloc(k, sizeof(int));
    Heap minheap;
    init_min_heap(&minheap, arr, k);
    int i = 0;
    for (i = 0; i < arraySize; i++) {
        x = array[i];

        // Nothing much to do for first k-1 elements
        if (count < k-1) {
            arr[count] = x;
            count++;
        } else {
          // If this is k'th element, then store it
          // and build the heap created above
          if (count == k-1)
          {
              arr[count] = x;
              buildHeap(&minheap);
          } else {
			  // If next element is greater than  k'th
			  // largest, then replace the root
			  if (x > getMin(&minheap)) {
				replaceMin(&minheap, x); // replaceMin calls heapify()
			  }
          }

          count++;
        }
        // printArray(minheap.harr, minheap.heap_size);
    }
    // Root of heap is k'th largest element
    printf("K th largest element for whole array = %d\n", getMin(&minheap));
}

#define ARRAY_SIZE 64

int main()
{
	int k = 3;
    int elements = ARRAY_SIZE;
    int array[64] = {2, 4, 4, 5, 6, 3, 2, 1, 10, 11,
                     9, 20, 1, 14, 15, 30, 21, 25, 28, 7, 
                     21, 31, 40, 44, 55, 12, 17, 24, 28, 36,
                     22, 32, 41, 45, 50, 13, 18, 26, 29, 37, 
                     23, 33, 42, 46, 51, 16, 19, 27, 35, 38, 
                     2, 4, 4, 5, 6, 3, 2, 1, 10, 11,
                     9, 20, 1, 14}, i = 0;
    int out[elements];
    int heap[3];
    
    for (i = 0; i < 3; i++) {
    	heap[i] = 0;
    }
    
    MinHeap(64, array, out);
    printf("k th largest element with a sliding window of size 10 for k = %d\n", k);
    printArray(out, elements);
    printf("k th largest in whole array for k = %d\n", k);
    kthLargestArray(k, array, elements);
    return 0;
}

