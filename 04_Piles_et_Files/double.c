#include "double.h"
#include <stdint.h>  // To use intptr_t
#include <limits.h>  // To get INT_MAX, INT_MIN

// Affichage d'une chaine de type mystring
void double_fprintf(void* val, FILE* fp) {
    fprintf(fp, "%lf ", *(double*)val);
}

void double_printf(void* val) {
    double_fprintf(val, stdout);
}

// Test l'egalite de 2 reels
int double_equal(void* pv1, void* pv2) {
    return *(double*)pv1 == *(double*)pv2;
}

// Génération d'un reel aléatoire
void double_random(void* p) {
    *(double*)p = random() % 100;
}

// Updated version: double_new can now accept either an int or a double.
double* double_new(void* val) {
    double* p = (double*)malloc(sizeof(*p));
    
    // Check if the input is an integer (we assume integers are cast as intptr_t)
    if ((intptr_t)val <= INT_MAX && (intptr_t)val >= INT_MIN) {
        // If the value is in the range of an integer, treat it as an int and convert to double
        *p = (double)(intptr_t)val;
    } else {
        // Otherwise, treat it as a pointer to a double
        *p = *(double*)val;
    }

    return p;
}

// Free the allocated memory for a double
void* double_delete(void* p) {
    free(p);
    return NULL;
}
