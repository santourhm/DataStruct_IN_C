#include "list.h"



list_t list_new(void (*fprint_data)(void*, FILE*), void* (*delete_data)(void*), int (*equal_data)(void*, void*)) {
    list_t new = (list_t)malloc(sizeof(*new));
    if (new == NULL) {
        perror("E : Error Memory Allocation\n");
        return NULL;
    }

    new->data = NULL;  // Initialize to NULL, no need to allocate memory for link_t here
    new->size = 0;
    new->delete_data = delete_data;
    new->equal_data = equal_data;
    new->fprint_data = fprint_data;

    return new;
}

int link_is_empty(link_t l){
    return l == NULL;}

int list_is_empty(list_t l){
    return (l == NULL || l->size == 0);}

void* list_first(list_t l){
    assert(!list_is_empty(l));
    return l->data->data;
    }


link_t link_add_first(void* e, link_t l){
    link_t new_maillon;
    new_maillon = (void*) malloc(sizeof(*new_maillon));
    if (new_maillon == NULL){
        perror("E : Error Allocating Memory");
        return l;
    }
    new_maillon->data = e;
    new_maillon->next=l;
    return new_maillon;    
}

list_t list_add_first(void* e, list_t l){
    l->data = link_add_first(e,l->data);
    l->size++;
    return l;
}


link_t link_del_first(link_t l , void* (*delete)(void*)){
    assert(!link_is_empty(l));
    l->data = delete(l->data);
    link_t q;
    q = l->next;
    free(l);
    return q;
}

list_t list_del_first(list_t l){
    assert(!list_is_empty(l));
    l->data = link_del_first(l->data,l->delete_data);
    l->size--;
    return l;
}

size_t list_length(list_t l){
    int counter = 0;
    link_t q ;
    q = l->data;
    while (!link_is_empty(q)){
        counter++;
        q = q->next;
    }
    return counter;}


void list_fprintf(list_t l, FILE* fp){
    link_t q;
    q = l->data;
    while (!link_is_empty(q)){
        l->fprint_data(q->data,fp);
        q = q->next;
    }
    printf("\n");
}

void list_printf(list_t l  ){
    list_fprintf(l,stdout);
}


list_t list_delete(list_t l){
    link_t q;
    q = l->data;
    while (!link_is_empty(q)){
        q->data = l->delete_data(q->data);  
        link_t next = q->next;
        free(q);
        q = next;
    }
    free(l);
    return NULL;
}

link_t link_add_last(void* e, link_t l){
    link_t new_maillon = (void*) malloc(sizeof(*new_maillon));
    if (new_maillon == NULL){
        perror("E : Error Allocationg Memory\n");
        return l;
    }
    new_maillon->data = e;
    new_maillon->next = NULL;
     if (link_is_empty(l)) {
        return new_maillon;  
    }
    link_t q;
    q = l;
    while (!link_is_empty(q->next)){
        q = q->next;}
    q->next = new_maillon;
    return l; }

list_t list_add_last(void* e, list_t l){
    l->data = link_add_last(e,l->data);
    l->size++;
    return l;}


link_t link_del_last(link_t l, void* (*delete)(void*)){
    assert(!link_is_empty(l));
    if (l->next == NULL) {
        l->data = delete(l->data);
        free(l);
        return NULL;
    }
    link_t q;
    link_t p = NULL;
    q = l;
    while (!link_is_empty(q)){
        p = q;
        q = q->next;}
    p->next = NULL;
    q->data = delete(q->data) ;
    free(q);
    return l;}

list_t list_del_last(list_t l ){
    l->data = link_del_first(l->data,l->delete_data);
    l->size--;
    return l;}

link_t list_lookup(void* elem, link_t l, int(*compare)(void* e1, void* e2)){
    assert(!link_is_empty(l));
    link_t q = l;

    while (!link_is_empty(q)){
        if (compare(elem, q->data) == 1) {
            return q;
        }
        q = q->next;
    }

    return NULL; 
}

link_t list_find(void* e, list_t l){
    link_t founded;
    founded = list_lookup(e,l->data,l->equal_data);
    return founded;
}

list_t list_remove(void* param, list_t l) {
    assert(!list_is_empty(l));
    
    
    if (l->equal_data(param, l->data->data)) {
        l->data = link_del_first(l->data, l->delete_data); 
        l->size--;
        return l;
    }

  
    link_t q = l->data->next;
    link_t p = l->data;  

    while (!link_is_empty(q)) {
        if (l->equal_data(q->data, param)) {
            p->next = q->next;  
            l->delete_data(q->data);  
            free(q);  
            l->size--;
            return l;
        }
        p = q;  
        q = q->next;
    }
    l->fprint_data(param, stdout);
    printf(" is not in the list!\n");
    return l;
}


void list_simple_visit(list_t l, void (*visit_func)(void*, void*), void* param) {
    assert(!list_is_empty(l)); 

    link_t q = l->data;
    while (!link_is_empty(q)) {
        visit_func(q->data, param); 
        q = q->next;  
    }}


void list_visit(list_t l, int (*exec_on_value)(void*, void*), int (*exec_on_link)(list_t, void*), void* param) {
    assert(!list_is_empty(l)); 
    link_t q = l->data;
    while (!link_is_empty(q)) {
        if (exec_on_value(q->data, param) != 0) {
            break;}

        if (exec_on_link != NULL && exec_on_link(l, param) != 0) {
            break;  
        }
        q = q->next; 
    }
}

