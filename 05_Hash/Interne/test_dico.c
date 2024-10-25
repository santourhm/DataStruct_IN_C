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
    fprintf(fp, "%s", (char *) key);
}

// Test function to insert words from a file into the hash table
void test_with_file(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file: %s\n", filename);
        return;
    }

    // Create a hash table with an initial size of 16
    hashvset_t table = hashvset_new(16, string_hash, print_key, string_delete, string_compare);

    // Buffer to store each word from the file
    char word[256];
    int i =0;
    while (fscanf(file, "%255s", word) == 1 && i<200) {
        // Duplicate the word for insertion
        char *word_copy = strdup(word);
        if (!word_copy) {
            printf("Memory allocation failed for word: %s\n", word);
            continue;
        }
        i++;
        // Insert the word into the hash table
        hashvset_put(word_copy, table);
    }

    // Close the file after reading all words
    fclose(file);

    // Print the hash table after all insertions
    printf("\nHash Table after inserting words from the file:\n");
    //hashvset_printf(table);
    hashvset_remove_key("romancee",table);
    printf("it's in %d:",hashvset_find_key("romancee",table));
    for (int i = 0; i < table->size; i++)
    {
        if (table->data[i].busy == OCCUPED)
        {
            printf("the hashcode is: %d\n",table->data[i].hashcode);
            print_key(table->data[i].key,stdout);
        }
    }
    table = hashvset_delete(table);
}

int main() {
    // Test with the provided .txt file
    test_with_file("dico1.txt");
    
    

    return 0;
}
