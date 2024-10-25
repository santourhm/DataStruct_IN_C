#include "../include/hash.h"

// Simple hash function for strings
unsigned int string_hash(void *str) {
    unsigned int hash = 5381;  // Use unsigned int for the hash variable
    char *s = (char *)str;     // Cast to char* from void*
    int c;

    while ((c = *s++)) {
        hash = ((hash << 5) + hash) + (unsigned char)c;  // hash * 33 + c, cast to unsigned char to avoid negative values from char
    }

    return abs(hash);
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
    fprintf(fp, "%s \n", (char *) key);
}