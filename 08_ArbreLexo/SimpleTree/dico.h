#ifndef _DICO_HASHSET__
#define _DICO_HASHSET__
#define MAX_WORD_LENGTH 100

#include "stree.h"


/*  fonction que renvoie un tableu de hachage 
pour un ficher.txt , renovie 1 si oui -1 sinon.*/
 
int dico_load_text(tree_t table , const char* filename);


/* foction qui suprime les accent et les espaces et tout ce qui pas 
sinfnifigqtife */
tree_t dico_new();

int dico_load_text_first_k(tree_t table , const char* filename , int k);
void dico_process_word(tree_t table ,char *word);

void dico_verify_orthography(tree_t TextHash, tree_t DicoHash);

void dico_print(tree_t text);

#endif 
