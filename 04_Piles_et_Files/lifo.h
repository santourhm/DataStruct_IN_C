#ifndef _LIFO_H_
#define _LIFO_H_
#include <stdio.h>
#include<assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct _vect_t{
    void* * data;
    unsigned int max_size;
    unsigned int actual_size;
    void (*fprintf_data)(void*,FILE*);
    void* (*delete_data)(void*);
    int (*equal_data)(void*,void*); 
} * vect_t ;

typedef vect_t stack_t;


// Creation d'une pile de n elements
stack_t stacks_new(unsigned int n,void (*print_data)(void*,FILE*),
      void* (*delete_data)(void*),int (*equal_data)(void*,void*)) ;

// Empiler un element
stack_t stacks_push(void* e, stack_t table)  ;

// Depile un element en le retournant, supprime l'element de la pile
void* stacks_pop(stack_t table);

// Retourne le premier element, sans le supprimer
void* stacks_peek(stack_t table);

// Pile vide ?
int stacks_is_empty(stack_t l);

// Affiche la pile
void stacks_printf(stack_t table);
void stacks_fprintf( stack_t table,FILE*);

// Supprime la pile
stack_t stacks_delete(stack_t table);
#endif





