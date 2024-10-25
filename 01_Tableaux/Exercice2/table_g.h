#ifndef _TABLE_G_H_
#define _TABLE_G_H_

#include <stdio.h>
#include <stdlib.h>


typedef struct {
    void* *data;
    size_t max_size;
    size_t actual_size;

    void* (*delete_data)(void*);
    int (*equal_data)(void*,void*);
    void (*fprintf_data)(void*,FILE*);

}* table_t;

table_t table_new(unsigned int n,void (*print_data)(void*,FILE*), void* (*delete_data)(void*),int (*equal_data)(void*,void*));

table_t table_delete(table_t tab);

void table_printf(table_t tab);

int table_append(void* val, table_t tab);

int table_insert_at(void* val, int index, table_t tab);

int table_remove_at(void* val, int index, table_t tab);


#endif