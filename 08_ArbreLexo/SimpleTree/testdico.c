#include "dico.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>

void find_word(tree_t tree, char *word) {
    // Check if the word is not empty after processing
    if (strlen(word) > 0) {
        int f = LookForWordInTree(word, tree);  // Insert the processed word into the Trie
        if (f == 0)
        {
            printf("%s\n",word);
        }
        
    }
}

void process_word(tree_t tree, char *word) {
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
            find_word(tree, subtoken);  // Process each segment of the word
            subtoken = strtok(NULL, "-");  // Move to the next segment
        }
        token = strtok(NULL, "'");  // Move to the next segment after the apostrophe
    }
}

void printWordsFromNode(tree_t node, char *buffer, int depth) {
    if (node == NULL) return;
    
    // Prevent buffer overflow
    if (depth >= MAX_WORD_LENGTH) {
        return;
    }

    if (node->finWord) {
        buffer[depth] = '\0';  // Null-terminate the string
        printf("%s\n", buffer);  // Print the current word
    }

    // Recursively traverse each child node
    for (int i = 0; i < NB_ALPHA; i++) {
        if (node->sons[i] != NULL) {
            buffer[depth] = 'a' + i;  // Add character corresponding to current index
            printWordsFromNode(node->sons[i], buffer, depth + 1);  // Recursive call
        }
    }
}

// Public function to print all words in the Trie
void printTrie(tree_t root) {
    char buffer[MAX_WORD_LENGTH];  // Buffer to hold the current word
    printWordsFromNode(root, buffer, 0);  // Start recursive printing from the root
}

int main(){

    tree_t DicoTree = dico_new();
    dico_load_text(DicoTree,"dico1.txt");
    
     FILE *file = fopen("a_la_recherche_du_temps_perdu.txt", "r");
    if (!file) {
        perror("Error opening file");
        return 0;
    }

    char buffer[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", buffer) == 1) {
        
        process_word(DicoTree, buffer);  // Process each word
    }     
    fclose(file); 

    //printTrie(DicoTree);
    //printf("its : %d",LookForWordInTree("déja",DicoTree));  



}