#define NBTESTS 10000
#define NBCAS 4
#include "vect.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Programme de tests aleatoire
// 3 fois plus d'ajout que de suppression
int main() {
    srand(time(NULL));  // Initialize the random generator

    vect_t t1 = vect_new(2);
    if (t1 == NULL) {
        printf("Memory allocation failure. Exiting...\n");
        return EXIT_FAILURE;
    }

    double x;
    int i, j, nb;

    for (j = 0; j < NBTESTS; j++) {
        switch (random() % NBCAS) {
            case 0: case 1: case 2:
                x = random() % 100;
                printf("Append de %lf\n", x);
                t1 = vect_append(x, t1);
                if (t1 == NULL) {
                    printf("Memory allocation failure. Exiting...\n");
                    return EXIT_FAILURE;
                }
                break;
            case 3:
                if (t1->actual_size > 0) {
                    nb = random() % t1->actual_size + 1;
                    printf("Suppression des %d dernieres valeurs : ", nb);
                    t1 = vect_remove_nlast(nb, t1);
                    if (t1 == NULL) {
                        printf("Memory allocation failure. Exiting...\n");
                        return EXIT_FAILURE;
                    }
                }
                break;
        }
        for (i = 0; i < t1->actual_size; i++) {
            printf("%lf ", t1->data[i]);
        }
        puts("");
    }

    printf("Liberation du tableau\n");
    t1 = vect_delete(t1);
}
