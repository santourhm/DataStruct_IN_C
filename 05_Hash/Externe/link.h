#ifndef _LINK_T_
#define _LINK_T_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



typedef struct _link{
   void* data;
   unsigned int hacshcode;
   struct _link * next; 
} * link_t;

link_t link_new(void);

int link_is_empty(link_t l);

link_t link_delete(link_t l, void* (*delete_data)(void*));

link_t link_add_first(void* e, link_t l);

link_t link_del_first(link_t l , void* (*delete_data)(void*));

link_t link_add_last(void* e, link_t l);

link_t link_del_last(link_t l, void* (*delete_data)(void*));

link_t link_lookup(void* elem, link_t l, int(*compare)(void* e1, void* e2));

#endif