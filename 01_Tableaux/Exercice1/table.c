#include "table.h"
#include <string.h>


table_t new_table(int size) {
    table_t tab = malloc(sizeof(*tab)); 
    if (tab == NULL) return NULL;

    tab->size = size;
    tab->data = malloc(size * sizeof(double)); 
    if (tab->data == NULL) {
        free(tab);
        return NULL;
    }
    return tab;
}


table_t delete_table(table_t tab) {
    if (tab->size <= 0) {
        printf("Table already empty\n");
    } else {
        free(tab->data);
    }
    free(tab);
    return NULL;
}

void printf_table(table_t tab){
    if (tab->size <= 0){
        printf("Table is empty") ;} 
    else {
        for (int i = 0; i < tab->size; i++){
            printf(" element of index %d  : %.1lf \n", i,tab->data[i]);}}
    
    

}

int min_table(table_t tab){
    double min = tab->data[0];
    double im = 0;
    for (int i = 1 ; i < tab->size ; i++){
        if (tab->data[i]<min){
            min = tab->data[i];
            im = i; // récuperer l'indice de min pour chaque itération
        }
    }
    return im; 
}

int max_table(table_t tab){
    double max = tab->data[0];
    double im = 0;
    for (int i = 1 ; i < tab->size ; i++){
        if (tab->data[i]>max){
            max = tab->data[i];
            im = i; // récuperer l'indice de max pour chaque itération
        }
    }
    return im; 
}

int append_table(double val, table_t tab) {
    // Louer à noveau un block de mémoire qui conserve les données du l'encien tableau 
    double* new_data = realloc(tab->data, (tab->size + 1) * sizeof(double));

    if (new_data == NULL) {
        return 0;
    } else {
        tab->data = new_data; // collage du l'encien pointer au noveau
        tab->size++;
        tab->data[tab->size - 1] = val;
        return 1;
    }
}

int insert_at_table(double val ,int index, table_t tab){
  
    if (index < 0 || index > tab->size) {
        return 0;
    }

    double *new_data = (double*) malloc((tab->size + 1) * sizeof(double));
    if (new_data == NULL) {
        return 0;
    }

    memcpy(new_data, tab->data, index * sizeof(double));
    new_data[index] = val;
    memcpy(new_data + index + 1, tab->data + index, (tab->size - index) * sizeof(double));
    free(tab->data);
    tab->data = new_data;
    tab->size++;

    return 1;
}
 

int remove_at_table(int index, table_t tab){
    if (index < 0 || index > tab->size) {
        return 0;
    }
    double *  new_data = (double *) malloc((tab->size-1)*sizeof(double)); 
    if (new_data == NULL) {
        return 0;
    }
    memcpy(new_data,tab->data,(index+1)*sizeof(double));
    memcpy(new_data + index   ,tab->data + index +1 , sizeof(double)*(tab->size-index -1));
    free(tab->data);
    tab->data = new_data;
    tab->size--;
    return 1;


}