#include "hashlset.h"
#include <string.h>

// Hash function for strings
unsigned int string_hash(void *key) {
    unsigned int hash = 0;
    char *str = (char *)key;
    while (*str) {
        hash = (hash * 31) + *str++;
    }
    return hash;
}

// Function to compare two string keys
int string_compare(void *e1, void *e2) {
    return strcmp((char *)e1, (char *)e2);
}

// Function to print string keys
void string_print(void *key, FILE *fp) {
    fprintf(fp, "%s", (char *)key);
}

// Function to delete (free) string keys
void *string_delete(void *key) {
    free(key);
    return NULL;
}

int main() {
    // Create a new hash table
    hashlset_t table = hashlset_new(5, string_hash, string_print, string_delete, string_compare);
    if (table == NULL) {
        printf("Failed to create hash table.\n");
        return 1;
    }

    // Add keys to the table
    char *keys[] = {"apple", "banana", "cherry", "date", "elderberry"};
    for (int i = 0; i < 5; i++) {
        char *key_copy = strdup(keys[i]); // Allocate memory for the key
        hashlset_put(key_copy, table);
    }

    // Print the current state of the table
    printf("Initial hash table:\n");
    hashlset_fprintf(table, stdout);

    // Test resizing by adding more elements
    printf("\nAdding more elements and triggering resize:\n");
    char *new_keys[] = {"fig", "grape", "honeydew"};
    for (int i = 0; i < 3; i++) {
        char *key_copy = strdup(new_keys[i]); // Allocate memory for the key
        hashlset_put(key_copy, table);
    }

    // Print the hash table after resizing
    printf("\nHash table after resize:\n");
    hashlset_fprintf(table, stdout);

    
    // Delete the hash table
    printf("\nDeleting the hash table...\n");
    hashlset_delete(table);
    
    printf("Test completed successfully!\n");

    return 0;
}
