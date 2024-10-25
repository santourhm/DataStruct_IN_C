#ifndef _HASHLSET_H__
#define _HASHLSET_H__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "link.h"


// Definition de la structure
typedef struct {
/* Nombre d'elements de l'ensemble */
    unsigned int total_number;
    /* Taille du tableau */
    unsigned int size;
    /* La fonction de hachage pour cet ensemble */
    unsigned int (*hachage)(void *);
    /* Le tableau de pointeurs vers maillons */
    link_t * data;  
    /* Les fonctions classques */
    void* (*delete_key)(void*);
    int (*compare_key)(void* e1, void* e2);
    void (*print_key)(void*, FILE*);
}* hashlset_t;


// prototypes des fonctions
// Creation d'un ensemble vide de taille n
hashlset_t hashlset_new(int n, unsigned int (*fhachage)(void * ),
void (*print_key)(void*,FILE*),
void* (*delete_key)(void*),
int (*compare_key)(void* e1, void* e2) );
// Destruction de l'ensemble
hashlset_t hashlset_delete(hashlset_t table);
//Ajout d'un element
int hashlset_put(void* key, hashlset_t table) ;
// Presence de l'element
int hashlset_find_key(void* key, hashlset_t table) ;
// Suppression de l'element
int hashlset_remove_key(void* key, hashlset_t table) ;
// Affichage de l'ensemble
void hashlset_fprintf(hashlset_t table, FILE*fp) ;



#endif