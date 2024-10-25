#include "vect.h"

vect_t vect_new(unsigned int n,void (*print_data)(void*,FILE*), void* (*delete_data)(void*),int (*equal_data)(void*,void*)){
    
    vect_t tab ;
    tab = malloc(sizeof(*tab));
    if (tab==NULL){
        perror("E : Impossible to allocate nedded memory");
        return NULL;
    }
    tab->data = (void*) calloc(n,sizeof(*tab->data));
    if (tab->data==NULL){
        perror("E : Impossible to allocate nedded memory");
        return NULL;
    }
    tab->actual_size = 0;
    tab->max_size = n;
    tab->fprint_data = print_data;
    tab->equal_data = equal_data;
    tab->delete_data = delete_data;
    return tab;
} 


vect_t vect_append(void* e, vect_t table){
    
    if (table->actual_size+1 <=table->max_size){
        table->data[table->actual_size] = e;
        table->actual_size++;
        return table;
    }

    void** new_data = (void**) realloc(table->data, 2 * table->max_size * sizeof(void*));
    if (new_data == NULL) {
        perror("E : Unable to reallocate memory");
        return table;  // Return the original table if reallocation fails
    }
    table->data = new_data;  // Update table->data to the new pointer
    table->max_size *= 2;    // Double the max_size
    table->data[table->actual_size] = e;
    table->actual_size++;
    return table;    
} 


void vect_printf(vect_t table){
    for (int i = 0; i < table->actual_size; i++){
        table->fprint_data(table->data[i],stdout);
    }
    printf("\n");
}

vect_t vect_delete(vect_t table) {
    if (table == NULL) return NULL;
    if (table->delete_data != NULL) {
        for (unsigned int i = 0; i < table->actual_size; i++) {
            table->delete_data(table->data[i]);
        }
    }
    free(table->data);  // Free the data array itself
    free(table);        // Free the table structure
    return NULL;
}

vect_t vect_remove_at(int i, vect_t table) {
    if (i < 0 || i >= table->actual_size) {
        fprintf(stderr, "E: Invalid index\n");
        return table;
    }
    memmove(&table->data[i], &table->data[i + 1], (table->actual_size - i - 1) * sizeof(void*));
    table->actual_size--;  
    return table;
}


int vect_find(void* param, vect_t l){
    for (int i = 0; i <l->actual_size; i++){
        if (l->equal_data(l->data[i],param)){
            return i;
        }
    }
    return -1;
}

