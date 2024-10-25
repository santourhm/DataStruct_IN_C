#include "table_g.h"

table_t table_new(unsigned int n,void (*print_data)(void*,FILE*), void* (*delete_data)(void*),int (*equal_data)(void*,void*)){
    table_t VoidTab ;

    VoidTab = malloc(sizeof(*VoidTab));

    if (VoidTab == NULL){
        printf("Error allocating memory");
        return NULL;
    }
    VoidTab->data = calloc(n,sizeof(*(VoidTab->data)));
    if (VoidTab->data == NULL){
        printf("Error allocating memory");
        return NULL;
    }
    VoidTab->actual_size = 0;
    VoidTab->max_size = n;
    VoidTab->delete_data = delete_data;
    VoidTab->fprintf_data = print_data;


    return VoidTab;
}

table_t table_delete(table_t tab){
    if (tab == NULL) return NULL;
    if (tab->delete_data)
    for (int i = 0 ; i < tab->actual_size; i++){
        tab->delete_data(tab->data[i]);
    }
    free(tab);
    return NULL;

}









