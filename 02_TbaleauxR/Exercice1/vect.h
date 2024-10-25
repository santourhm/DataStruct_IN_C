#ifndef _VECT_H_
#define _VECT_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct  {
    double* data  ;     // Les données du tableau
    size_t max_size;    // La taille maximale
    size_t actual_size; // Le nombre d'element présent
} * vect_t;


vect_t vect_new(unsigned int n) ;

vect_t vect_append(double e, vect_t table)  ;

vect_t vect_remove_nlast(int n, vect_t table)  ;

void vect_print(vect_t table);

vect_t vect_delete(vect_t table)  ;

#endif