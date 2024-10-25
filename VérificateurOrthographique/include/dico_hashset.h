#ifndef _DICO_HASHSET__
#define _DICO_HASHSET__
#include "../include/hashvset.h"
#include "../include/hash.h"
#define MAX_WORD_LENGTH 100
#include <ctype.h>
#include <string.h>
#include <stdlib.h>



/*  fonction que renvoie un tableu de hachage 
pour un ficher.txt , renovie 1 si oui -1 sinon.*/
 
int dico_load_text(hashvset_t table , const char* filename);


/* foction qui suprime les accent et les espaces et tout ce qui pas 
sinfnifigqtife */
hashvset_t dico_new(int n);

int dico_load_text_first_k(hashvset_t table , const char* filename , int k);
void dico_process_word(hashvset_t table ,char *word);

void dico_verify_orthography(hashvset_t TextHash, hashvset_t DicoHash);

void dico_print(hashvset_t text);

#endif 
