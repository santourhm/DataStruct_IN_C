#ifndef _HASH__
#define _HASH__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Simple hash function for strings
unsigned int string_hash(void *str);

// Function to compare two string keys
int string_compare(void *e1, void *e2);

// Function to delete a string key (free memory)
void* string_delete(void *key);

// Function to print a string key
void print_key(void *key, FILE *fp);

#endif