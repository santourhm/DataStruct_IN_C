#ifndef _TABLE_H_
#define _TABLE_H_
#include <stdio.h>
#include <stdlib.h>

// table dynamique

typedef struct  {
    double* data  ;     // Les données du tableau
    size_t size;    // La taille maximale
} * table_t;


table_t new_table(int n); //creation dun noveau tableau

table_t delete_table(table_t tab); //suppression du tableau tab

void printf_table(table_t tab); // afffichage de tab

int min_table(table_t tab); //minimum du tableau

int max_table(table_t tab); //max du tableau

int append_table(double val, table_t tab); // Ajouter un element à tab

int insert_at_table(double val ,int index, table_t tab); // insertion d'un élement à la position index on suppose que index est entre 0 et n-1 

int remove_at_table(int index, table_t tab); //supression de l'element d'undice index



#endif