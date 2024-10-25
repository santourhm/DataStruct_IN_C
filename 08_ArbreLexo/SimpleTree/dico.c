#include "stree.h"  // Include the header for the Trie structure
#include "dico.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>


// Create a new Trie
tree_t dico_new() {
    return NewTree();  // Initialize the Trie
}

// Function to process each word (this can be modified as needed)
void process_and_insert_word(tree_t tree, char *word) {
    // Check if the word is not empty after processing
    if (strlen(word) > 0) {
        AddWordInTree(word, tree);  // Insert the processed word into the Trie
    }
}



// Function to process French words and handle accented characters
void dico_process_word(tree_t tree, char *word) {
    // Convert the word to lowercase (case-insensitive processing)
    for (int i = 0; word[i]; i++) {
        word[i] = tolower((unsigned char)word[i]);
    }

    // Remove punctuation from the end of the word
    int len = strlen(word);
    while (len > 0 && ispunct((unsigned char)word[len - 1])) {
        word[len - 1] = '\0';  // Remove punctuation from the end of the word
        len--;
    }

    // Remove punctuation from the start of the word without modifying the original pointer
    char *start = word;
    while (*start && ispunct((unsigned char)*start)) {
        start++;  // Move the pointer past the leading punctuation
    }

    // Use strtok to split the word on apostrophes (')
    char *token = strtok(start, "'");  // Split on apostrophes
    while (token != NULL) {
        // Split each segment on hyphens and process
        char *subtoken = strtok(token, "-");
        while (subtoken != NULL) {
            process_and_insert_word(tree, subtoken);  // Process each segment of the word
            subtoken = strtok(NULL, "-");  // Move to the next segment
        }
        token = strtok(NULL, "'");  // Move to the next segment after the apostrophe
    }
}


// Function to load and process words from the text file
int dico_load_text(tree_t tree, const char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 0;
    }

    char buffer[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", buffer) == 1) {
        dico_process_word(tree, buffer);  // Process each word
    }

    fclose(file);
    return 1;
}

// Load first k words from a text file into the Trie
int dico_load_text_first_k(tree_t tree, const char* filename, int k) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 0;
    }

    char buffer[MAX_WORD_LENGTH];
    int i = 0;

    while (fscanf(file, "%s", buffer) == 1 && i < k) {
        dico_process_word(tree, buffer);  // Process each word
        i++;  // Increment the count of processed words
    }

    fclose(file);
    return 1;
}

/* // Print the Trie (This function needs to be implemented)
void dico_print(tree_t tree) {
    // Implement a function to print the Trie, if needed
    // This can be a recursive function that traverses the Trie and prints each word
}

// Function to verify spelling by checking against the Trie
void dico_verify_orthography(tree_t TextTrie, tree_t DicoTrie) {
    // Assuming TextTrie is a Trie of words from a document
    // This function should traverse the TextTrie and check each word against the DicoTrie

    // Here you would need to implement the traversal and verification logic.
    // Pseudocode example:
    // Traverse TextTrie and for each word, use LookForWordInTree to check if it exists in DicoTrie
}
 */