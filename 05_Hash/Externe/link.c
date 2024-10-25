#include "link.h"



link_t link_new(void) {
    link_t new_link = malloc(sizeof(struct _link));
    if (new_link == NULL) {
        perror("Error: Unable to allocate memory for link");
        exit(EXIT_FAILURE);
    }
    new_link->data = NULL;
    new_link->hacshcode = 0;
    new_link->next = NULL;
    return new_link;
}

int link_is_empty(link_t l){
    return l == NULL;}



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


link_t link_del_first(link_t l , void* (*delete)(void*)){
    assert(!link_is_empty(l));
    l->data = delete(l->data);
    link_t q;
    q = l->next;
    free(l);
    return q;
}

link_t link_delete(link_t l, void* (*delete_data)(void*)) {
    link_t current = l;
    while (current != NULL) {
        link_t next = current->next;  // Save the next pointer before deleting
        if (delete_data != NULL) {
            delete_data(current->data);  // Free the data using the delete_data function if provided
        }
        free(current);  // Free the current link
        current = next;  // Move to the next link in the list
    }
    return NULL;  // Return NULL when the list is fully deleted
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


link_t link_lookup(void* elem, link_t l, int(*compare)(void* e1, void* e2)){
    link_t q = l;

    while (!link_is_empty(q)){
        if (compare(elem, q->data) == 1) {
            return q;
        }
        q = q->next;
    }

    return NULL; 
}

