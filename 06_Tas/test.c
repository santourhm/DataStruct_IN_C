#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

// Example functions for handling integer data in the heap
void print_int(void* data, FILE* file) {
    fprintf(file, "%d", *(int*)data);
}

void* delete_int(void* data) {
    if (data) {
        free(data);
    }
    return NULL;
}


int compare_int(void* a, void* b) {
    int int_a = *(int*)a;
    int int_b = *(int*)b;
    return (int_a - int_b);
}

int main() {
    // Create a new heap with space for 10 elements
    heap_t my_heap = heap_new(10, print_int, delete_int,compare_int);
    
    // Check if the heap is initially empty
    if (heap_is_empty(my_heap)) {
        printf("Heap is initially empty.\n");
    } else {
        printf("Heap is not empty.\n");
    }

    // Add some elements to the heap
    int* value1 = malloc(sizeof(int));
    *value1 = 42;
    heap_add(value1, my_heap);

    int* value2 = malloc(sizeof(int));
    *value2 = 15;
    heap_add(value2, my_heap);

    int* value3 = malloc(sizeof(int));
    *value3 = 30;
    heap_add(value3, my_heap);

   

    // Print the current state of the heap
    printf("Heap contents after adding 42, 15, 30:\n");
    heap_printf(my_heap);

    // Get the extrema (assumes it's a max-heap or min-heap depending on your implementation)
    int* extrema = (int*)heap_get_extrema(my_heap);
    printf("Current extrema: %d\n", *extrema);

    // Delete the extrema from the heap and reprint the heap state
    heap_delete_extrema(my_heap);
    printf("Heap contents after deleting the extrema:\n");
    heap_printf(my_heap);

    // Verify the heap property (custom verification function)
    if (heap_verification(my_heap)) {
        printf("Heap property is maintained.\n");
    } else {
        printf("Heap property is violated.\n");
    }

    // Clean up by deleting the heap
    heap_delete(my_heap);

    printf("Heap deleted.\n");

    return 0;
}
