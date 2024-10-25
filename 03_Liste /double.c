#include "double.h"

// Affichage d'une chaine de type mystring
void double_fprintf(double* val,FILE* fp)  { fprintf(fp,"%lf ",*val);}
void double_printf(double* val)  { double_fprintf(val,stdout);}
// Test l'egalite de 2 reels
int double_equal(double* pv1, double* pv2) { return *pv1==*pv2; }
// Génération d'un reel aléatoire
void double_random(double*p){ *p=random()%100;}
// Clone d'un reel
double* double_new(double* val) { double*p = malloc(sizeof(*p));
*p=*val;
return p;
}