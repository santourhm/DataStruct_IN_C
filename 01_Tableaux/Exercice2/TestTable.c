#include "table_g.h"



int main() { int i;
  double* px = malloc(sizeof(*px));
  double* CastPointer = malloc(sizeof(double));  
  table_t tab;

    // Creation du tableau
  tab=table_new(10,NULL,NULL,NULL);
  *px = 2.5;
  tab->data[0] = px;

  ;

  printf("it's: %.1lf ", *((double*) tab->data[0]));
  
}