#ifndef _hashvset
#define  _hashvset
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <assert.h>

typedef enum { EMPTY, FREE, OCCUPED} hash_state_t;

// Le  TAD :
typedef struct {
  void* key;
  unsigned int hashcode;
  hash_state_t busy;
}  cellhashvset_t;

typedef struct {
  unsigned int total_number;
  unsigned int size;
  unsigned int (*hachage)(void *);
  cellhashvset_t * data;
  void* (*delete_key)(void*);
  int (*compare_key)(void* e1, void* e2);
  void (*print_key)(void*, FILE*);
}* hashvset_t;


hashvset_t hashvset_new(int n, unsigned int (*fhachage)(void * ),
      void (*print_key)(void*,FILE*),
      void* (*delete_key)(void*),int (*compare_key)(void* e1, void* e2) );
hashvset_t hashvset_delete(hashvset_t table);
int hashvset_put(void* key, hashvset_t table) ;
int hashvset_remove_key(void* key, hashvset_t table) ;
int hashvset_find_key(void* key, hashvset_t table) ;
void hashvset_printf(hashvset_t table) ;
void hashvset_fprintf(hashvset_t t,FILE*fp) ;
// sens =1 pour accroitre la table, -1 sinon
int hashvset_new_length(int sens, hashvset_t table);
#endif

