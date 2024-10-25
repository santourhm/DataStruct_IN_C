#include "heap.h"


heap_t heap_new(unsigned int n,void (*print_data)(void*,FILE*),
      void* (*delete_data)(void*),int (*compare_data)(void*,void*)) {

    heap_t heap = vect_new(n,print_data,delete_data,compare_data);
    return heap;}

int heap_is_empty(heap_t heap){
    return heap->actual_size == 0 ;
}

int heap_add(void* valeur, heap_t tas){
    
    assert(tas != NULL);
    
    // Check if the heap is full
    if (tas->actual_size >= tas->max_size) return 0;

    // If heap is empty, insert the first element
    if (heap_is_empty(tas)) {
        tas->data[0] = valeur;
        tas->actual_size++;
        return 1;
    }

    // Insert at the end of the heap
    int i = tas->actual_size;
    tas->data[i] = valeur;
    
    // Adjust heap upwards (heapify-up)
    while (i > 0) {
        int father = HEAP_FATHER(i);
       
        if (tas->equal_data(tas->data[father], valeur) >= 0) {
            // Heap property is satisfied
            break;
        }

        // Swap current node with its father
        void* swap_data = tas->data[father];
        tas->data[father] = tas->data[i];
        tas->data[i] = swap_data;

        // Move up to the father's index
        i = father;
    }
    
    // Increment the heap size after insertion
    tas->actual_size++;
    
    return 1;    
}


void* heap_get_extrema(heap_t tas){
    
    assert( tas != NULL );
    assert( tas->actual_size != 0 );
    return tas->data[0];

}

int heap_delete_extrema(heap_t tas) {
     
    assert(tas != NULL);
    assert(tas->actual_size != 0);
    
    // Replace root with the last element
    tas->data[0] = tas->data[tas->actual_size - 1];
    tas->actual_size--;

    int index = 0;
    int j = 0;

    // Heapify down
    while (HEAP_LEFTSON(index) < tas->actual_size) {
        // Choose the larger of the two children (if both exist)
        if (HEAP_RIGHTSON(index) < tas->actual_size && 
            tas->equal_data(tas->data[HEAP_LEFTSON(index)], tas->data[HEAP_RIGHTSON(index)]) < 0) {
            j = HEAP_RIGHTSON(index);
        } else {
            j = HEAP_LEFTSON(index);
        }

        // If the parent is larger than the largest child, stop
        if (tas->equal_data(tas->data[index], tas->data[j]) >= 0) {
            break;
        }

        // Swap the current node with the larger child
        void* swap_data = tas->data[index];
        tas->data[index] = tas->data[j];
        tas->data[j] = swap_data;

        // Move down to the child's index
        index = j;
    }

    // Optionally call delete_data on the last element (which was swapped out)

    return 1;
}


int heap_verification(heap_t tas) {
    
    for (int i = 0; i < tas->actual_size; i++) {   
        // Check if the left child exists and violates the heap property
        if (HEAP_LEFTSON(i) < tas->actual_size) {
            if (tas->equal_data(tas->data[HEAP_LEFTSON(i)], tas->data[i]) > 0) {
                return 0;
            }
        }
        
        // Check if the right child exists and violates the heap property
        if (HEAP_RIGHTSON(i) < tas->actual_size) {
            if (tas->equal_data(tas->data[HEAP_RIGHTSON(i)], tas->data[i]) > 0) {
                return 0;
            }
        }
    }

    // If no violations are found, the heap is valid
    return 1;
}


heap_t heap_delete(heap_t tas){
    tas = vect_delete(tas);
    return NULL;
}
  // Affichage du tas
void heap_printf(heap_t tas){
    heap_fprintf(tas,stdout);
}
void heap_fprintf(heap_t heap, FILE* file) {
    if (heap == NULL || file == NULL) {
        fprintf(stderr, "Error: Invalid heap or file pointer.\n");
        return;
    }

    fprintf(file, "Heap (size: %u, max size: %u):\n", heap->actual_size, heap->max_size);

    // Loop through the heap data and use the custom print function
    for (unsigned int i = 0; i < heap->actual_size; i++) {
        fprintf(file, "Element %u: ", i);
        heap->fprint_data(heap->data[i], file); // Print each element using the provided function
        fprintf(file, "\n");
    }
}
