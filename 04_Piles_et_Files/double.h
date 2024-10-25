#ifndef _DOUBLE_H_
#define _DOUBLE_H_
#include <stdio.h>
#include <stdlib.h>

void double_fprintf(void * val,FILE* fp);
void double_printf(void * val);
  // Test l'egalite de 2 reels
int double_equal(void * pv1, void * pv2);
  // Génération d'un reel aléatoire
void double_random(void *p);
  // Clone d'un reel
double* double_new(void * val);

void* double_delete(void *p);

#endif