#include "vect.h"

vect_t vect_new(unsigned int n, void (*print_data)(void*, FILE*), void* (*delete_data)(void*), int (*equal_data)(void*, void*)) {
    vect_t tab;
    tab = malloc(sizeof(*tab));
    if (tab == NULL) {
        perror("E : Impossible to allocate needed memory");
        return NULL;
    }

    tab->data = malloc(n * sizeof(*tab->data));
    if (tab->data == NULL) {
        free(tab); // Free the previously allocated `tab` if `data` allocation fails.
        perror("E : Impossible to allocate needed memory");
        return NULL;
    }

    tab->actual_size = 0;
    tab->max_size = n;
    tab->fprint_data = print_data;
    tab->delete_data = delete_data;
    tab->equal_data = equal_data;
    return tab;
}


vect_t vect_append(void* e, vect_t table){
    
    if (table->actual_size+1 <=table->max_size){
        table->data[table->actual_size] = e;
        table->actual_size++;
        return table;
    }

    void* *new_data = (void*) realloc(table->data, 2*table->max_size*sizeof(*new_data));
    table->data[table->actual_size] = e;
    table->max_size =2*table->max_size;
    table->actual_size++;
    return table;    
} 


void vect_printf(vect_t table){
    for (int i = 0; i < table->actual_size; i++){
        table->fprint_data(table->data[i],stdout);
    }
    printf("\n");
}

vect_t vect_delete(vect_t tab) {
    if (tab) {
        if (tab->delete_data) {
            for (unsigned int i = 0; i < tab->actual_size; ++i) {
                tab->delete_data(tab->data[i]);
            }
        }
        free(tab->data);
        free(tab);
    }
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

