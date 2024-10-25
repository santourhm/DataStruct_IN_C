#include "hashlset.h"




hashlset_t hashlset_new(int n, unsigned int (*fhachage)(void * ),void (*print_key)(void*,FILE*),void* (*delete_key)(void*),
int (*compare_key)(void* e1, void* e2) ){
    hashlset_t tab = malloc(sizeof(*tab));
    if (tab==NULL)
    {
        return NULL;
    }
    tab->data = calloc(n,sizeof(*tab->data));
    if (tab->data ==NULL)
    {
        free(tab);
        return NULL;
    }
    tab->size = n;
    tab->total_number = 0;
    tab->hachage = fhachage;
    tab->delete_key = delete_key;
    tab->print_key = print_key;
    tab->compare_key = compare_key;

    return tab;
}


hashlset_t hashlset_delete(hashlset_t table) {
    assert(table != NULL);
    for (int i = 0; i < table->size; i++) {  // Traverse the entire size
        table->data[i] = link_delete(table->data[i],table->delete_key);  // Free each linked list
    }
    free(table->data);  // Free the array of pointers
    free(table);  // Free the structure itself
    return NULL;
}

int hashlset_resize(hashlset_t table, unsigned int new_size){

    link_t* new_table = (link_t*) calloc(new_size, sizeof(link_t));
    
    for (int i = 0; i < table->size; i++)
    {
        link_t current = table->data[i];
        while (!link_is_empty(current)){
            link_t next = current->next;
            unsigned int new_slot = (current->hacshcode) % new_size; 
            current->next = new_table[new_slot];
            new_table[new_slot] = current;
            current = next;   
            }
    
    }

    free(table->data);
    table->size = new_size;
    table->data = new_table;

    return 1;
    
}



int hashlset_put(void* key, hashlset_t table) {
    assert(table != NULL);
    assert(table->size > 0);
    
    int hashcode = table->hachage(key);
    int slot = hashcode % table->size;

    // Resize the table if the load factor exceeds 0.7
    float facteur_charge = (float) table->total_number / table->size;
    if (facteur_charge > 0.7) {    
        if (!hashlset_resize(table, 2 * table->size)) return 0;
        slot = hashcode % table->size;  // Recalculate slot after resizing
    }

    // Check if the key is already present
    if (link_lookup(key, table->data[slot], table->compare_key)) {
        return 1;  // Key already exists, do nothing
    }

    // Insert the key into the slot
    table->data[slot] = link_add_first(key, table->data[slot]);
    table->data[slot]->hacshcode = hashcode;
    table->total_number++;
    return 1;  // Success
}

void hashlset_fprintf(hashlset_t table, FILE *fp) {
    assert(table != NULL && fp != NULL);

    fprintf(fp, "Hash Table Contents:\n");
    fprintf(fp, "====================\n");
    fprintf(fp, "Total elements: %u\n", table->total_number);
    fprintf(fp, "Table size: %u\n\n", table->size);

    for (unsigned int i = 0; i < table->size; i++) {
        fprintf(fp, "Slot %u: ", i);
        
        link_t current = table->data[i];
        if (link_is_empty(current)) {
            fprintf(fp, "[Empty]\n");
        } else {
            fprintf(fp, "\n");
            while (current != NULL) {
                fprintf(fp, "    -> Key: ");
                table->print_key(current->data, fp);  // Print the key using the provided function
                fprintf(fp, ", Hashcode: %u\n", current->hacshcode);
                current = current->next;
            }
        }
    }

    fprintf(fp, "\nEnd of Hash Table\n");
    fprintf(fp, "====================\n");
}

int hashlset_find_key(void* key, hashlset_t table){
    unsigned int slot = table->hachage(key) % table->size;
    if (link_lookup(key,table->data[slot],table->compare_key))
    {
        return 1;
    }
    return 0;
}
