#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tri.h"  // Sorting functions (quicksort, heapsort, mergesort)
#include "vect.h" // Vect structure definition
void* delete_int(void* a) {
    free(a);
    return NULL;
}


// Function to generate random integer vector
vect_t randominttabgeneration(unsigned n, int (*compar)(void*, void*), void (*print)(void*, FILE*)) {
    vect_t vect = vect_new(n, print,delete_int, compar);
    for (unsigned i = 0; i < n; i++) {
        int *value = malloc(sizeof(int));
        *value = rand() % n;
        vect_append(value, vect);
    }
    return vect;
}


int compare_int(void* a, void* b) {
    int* int_a = (int*) a;
    int* int_b = (int*) b;
    return (*int_a - *int_b); // retourne 0 si égal, négatif si a < b, positif si a > b
}


/* Fonction pour afficher un entier */
void print_int(void* a, FILE* stream) {
    fprintf(stream, "%d ", *(int*) a);
}

/* Fonction pour supprimer un entier (nécessaire pour vect_t) */


// Print function for intege

int main() {
    clock_t avant, apres;
    double temps_qsort, temps_quick, temps_merge, temps_heap;
    int k, total_number = 10000000;
    vect_t t1, t2, t3, t4;

    // Open a file to write sorting times
    FILE* fp = fopen("tempstri.dat", "w");
    if (!fp) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    // Perform sorting for different sizes
    for (k = 1; k <= total_number; k *= 2) {
        // Generate random vectors
        t1 = randominttabgeneration(k,  compare_int, print_int);
        t2 = randominttabgeneration(k,  compare_int, print_int);
        t3 = randominttabgeneration(k,  compare_int, print_int);
        t4 = randominttabgeneration(k,  compare_int, print_int);

        // Time C's built-in qsort
        avant = clock();
        qsort(t1->data, t1->actual_size, sizeof(void*),  compare_int);
        apres = clock();
        temps_qsort = ((double)apres - avant) / CLOCKS_PER_SEC;

        // Time custom quicksort
        avant = clock();
        quicksort(t2);
        apres = clock();
        temps_quick = ((double)apres - avant) / CLOCKS_PER_SEC;

        // Time custom mergesort
        avant = clock();
        mergesort(t3);
        apres = clock();
        temps_merge = ((double)apres - avant) / CLOCKS_PER_SEC;

        // Time custom heapsort
        avant = clock();
        heapsort(t4);
        apres = clock();
        temps_heap = ((double)apres - avant) / CLOCKS_PER_SEC;

        // Write results to file
        fprintf(fp, "%d\t%lf\t%lf\t%lf\t%lf\n", k, temps_qsort, temps_quick, temps_merge, temps_heap);

        // Clean up memory
        vect_delete(t1);
        vect_delete(t2);
        vect_delete(t3);
        vect_delete(t4);
    }

    // Close file and generate plot using gnuplot
    fclose(fp);
    system("gnuplot -p -e \"set logscale x; "
           "plot 'tempstri.dat' u 1:2 with line lt 4 title 'qsort', "
           "'tempstri.dat' u 1:3 with line lt 6 title 'quicksort', "
           "'tempstri.dat' u 1:4 with line lt 2 title 'mergesort', "
           "'tempstri.dat' u 1:5 with line lt 3 title 'heapsort'; quit\"");

    return 0;
}
