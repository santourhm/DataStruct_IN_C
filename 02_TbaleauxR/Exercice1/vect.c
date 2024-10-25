#include "vect.h"



vect_t vect_new(unsigned int n){
    
    vect_t new_tab;
    new_tab = malloc(sizeof(*new_tab));
    if (new_tab==NULL){
        printf("E : Impossible Allocating The Needed Memory");
        return NULL;}
    new_tab->data = (double*) calloc(n,sizeof(double));
    if (new_tab->data==NULL){
        printf("E : Impossible Allocating The Needed Memory");
        free(new_tab);
        return NULL;} 
    new_tab->actual_size = 0;
    new_tab->max_size = n;

    return new_tab;
}

vect_t vect_append(double e, vect_t table){
    

    if (table->actual_size + 1<=table->max_size){
        table->data[table->actual_size] = e;
        table->actual_size++;
        return table;
    }

    double *new_data = realloc(table->data, (2 * table->max_size) * sizeof(double));
    if (new_data == NULL) {
        printf("E : Impossible Allocating The Needed Memory");
        return table; // do not change table->data if realloc fails
    }
    table->data = new_data;
    table->data = new_data ;
    table->data[table->actual_size] = e;
    table->max_size = 2*table->max_size;
    table->actual_size++;
    return table;

}


void vect_print(vect_t table){
    if (table->actual_size ==0) printf("Table is empty");
    printf("#########################\n");
    printf("# taille actuelle :%i \t#\n", table->actual_size);
    printf("# taille maxi :   %i \t#\n",table->max_size);
    printf("#########################\n");
    for (int i = 0; i < table->actual_size; i++){
        printf("(index | element) = (%i | %.2lf) \n",i,table->data[i]);}
    
}

vect_t vect_remove_nlast(int n,vect_t table){

    if (n>table->actual_size) printf("impossible number of elemnts is less then the deleted numbers");
    if (table->actual_size<(table->max_size)/3){
        table->actual_size-=n;
        return table;
    }
    double * new_data = (double*) realloc(table->data,n*sizeof(new_data));
    table->data = new_data;
    table->actual_size-=n;
    table->max_size-=n;
    return table;
}


vect_t vect_delete(vect_t table){
    free(table->data);
    free(table);
    return NULL;}