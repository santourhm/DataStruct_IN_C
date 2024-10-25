#include <stdio.h>
#include <stdlib.h>
#include "vect.h"  // Assuming vect.h contains the structure and function declarations

// Functions for handling `double` data type

// Print a `double`
void double_fprint(void* p, FILE* fp) {
    fprintf(fp, "%lf ", *(double*)p);
}

// Compare two `double` values
int double_equal(void* p1, void* p2) {
    return (*(double*)p1 == *(double*)p2);
}

// Delete (free) a `double` pointer
void* double_delete(void* p) {
    free(p);
    return NULL;
}

int main() {
    printf("=== Test Vector Creation ===\n");
    
    vect_t tab = vect_new(5, double_fprint, double_delete, double_equal);
    if (!tab) {
        fprintf(stderr, "Error creating vector\n");
        return 1;
    }

    printf("=== Test Vector Append ===\n");
   
    for (int i = 0; i < 5; i++) {
        double* px = (double*) malloc(sizeof(double));
        if (!px) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        *px = i * 1.1;  // Assign values like 0.0, 1.1, 2.2, 3.3, 4.4
        tab = vect_append(px, tab);
        
    }
    printf("=== Test Vector Print ===\n");
    vect_printf(tab);  // Should print: 0.0 1.1 2.2 3.3 4.4
    printf("\n");

    printf("=== Test Find Element ===\n");
    double target = 2.2;
    int found_index = vect_find(&target, tab);
    if (found_index != -1) {
        printf("Element %lf found at index %d\n", target, found_index);
    } else {
        printf("Element %lf not found\n", target);
    }

    printf("=== Test Remove Element ===\n");
    tab = vect_remove_at(found_index, tab);  
    vect_printf(tab);  // Should print: 0.0 1.1 3.3 4.4
    printf("\n");

   printf("=== Test Vector Delete ===\n");
    tab = vect_delete(tab); 

    if (!tab) {
        printf("Vector deleted successfully\n");
    }

    return 0;
}
