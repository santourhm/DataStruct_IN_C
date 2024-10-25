#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashvset.h"

// Simple hash function for strings
unsigned int string_hash(void *str) {
    unsigned int hash = 5381;  // Use unsigned int for the hash variable
    char *s = (char *)str;     // Cast to char* from void*
    int c;

    while ((c = *s++)) {
        hash = ((hash << 5) + hash) + (unsigned char)c;  // hash * 33 + c, cast to unsigned char to avoid negative values from char
    }

    return hash;
}

// Function to compare two string keys
int string_compare(void *e1, void *e2) {
    return strcmp((char *) e1, (char *) e2);
}

// Function to delete a string key (free memory)
void* string_delete(void *key) {
    free(key);
    return NULL;
}

// Function to print a string key
void print_key(void *key, FILE *fp) {
    fprintf(fp, "%s", (char *) key);
}

// Test function to verify all hashvset functionality
int main() {
    // Create a new hash set with initial size of 8
    hashvset_t table = hashvset_new(8, string_hash, print_key, string_delete, string_compare);

    // Insert keys into the hash set
    char *key1 = strdup("key1");
    char *key2 = strdup("key2");
    char *key3 = strdup("key3");

    printf("Inserting key1, key2, and key3:\n");
    hashvset_put(key1, table);
    hashvset_put(key2, table);
    hashvset_put(key3, table);

    // Print the table after insertion
    printf("Table after insertion:\n");
    hashvset_printf(table);

    // Find keys in the table
    printf("\nFinding keys:\n");
    int idx1 = hashvset_find_key("key1", table);
    int idx2 = hashvset_find_key("key2", table);
    int idx3 = hashvset_find_key("key3", table);
    int idx4 = hashvset_find_key("non_existent_key", table);

    printf("key1 found at index: %d\n", idx1);
    printf("key2 found at index: %d\n", idx2);
    printf("key3 found at index: %d\n", idx3);
    printf("non_existent_key found at index: %d\n", idx4); // Should print -1

    // Remove key2 from the table
    printf("\nRemoving key2:\n");
    hashvset_remove_key("key2", table);

    // Print the table after removal
    printf("Table after removal of key2:\n");
    hashvset_printf(table);

    // Test automatic resizing on insertion (add more keys)
    char *key4 = strdup("key4");
    char *key5 = strdup("key5");
    printf("\nInserting key4 and key5:\n");
    hashvset_put(key4, table);
    hashvset_put(key5, table);

    // Print the table after inserting more keys
    printf("Table after more insertions:\n");
    hashvset_printf(table);

    // Cleanup the hash table
    printf("\nCleaning up hash set:\n");
    table = hashvset_delete(table);

    return 0;
}
