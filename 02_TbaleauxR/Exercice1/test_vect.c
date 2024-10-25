#include "vect.h"


int main(){

    vect_t tab ;
    tab = vect_new(3);
    tab->data[0] = 0.1;
    tab->data[1] = 0.2;
    tab->actual_size = 2;
    vect_print(tab);

    tab = vect_append(0.3,tab);
    printf("---------------------------\n");
    vect_print(tab);
    printf("---------------------------\n");
    tab = vect_append(0.4,tab);
    vect_print(tab);
    printf("---------------------------\n");
    vect_remove_nlast(3,tab);
    vect_print(tab);
    tab = vect_append(0.4,tab);
    tab = vect_append(0.6,tab);vect_print(tab);
    tab = vect_append(0.7,tab);
    tab = vect_append(0.8,tab);
    vect_print(tab);
    vect_remove_nlast(tab->actual_size,tab);
    vect_print(tab);
    tab = vect_delete(tab);
     
    return 0; 
}