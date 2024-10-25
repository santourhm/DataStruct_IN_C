#include "tri.h"
#include "vect.h"

/* Fonction pour comparer des entiers */
int compare_int(void* a, void* b) {
    int* int_a = (int*) a;
    int* int_b = (int*) b;
    return (*int_a - *int_b); // retourne 0 si égal, négatif si a < b, positif si a > b
}

/* Fonction pour afficher un entier */
void print_int(void* a, FILE* stream) {
    fprintf(stream, "%d ", *(int*) a);
}

/* Fonction pour supprimer un entier (nécessaire pour vect_t) */
void* delete_int(void* a) {
    free(a);
    return NULL;
}

/* Fonction pour initialiser un vecteur d'entiers avec des données aléatoires */
vect_t init_vect_int(size_t size) {
    vect_t vect = vect_new(size,print_int,delete_int,compare_int);
    for (size_t i = 0; i < size; i++) {
        int* val = (int*) malloc(sizeof(int)); // allouer de la mémoire pour chaque entier
        *val = rand() % 100; // nombre aléatoire entre 0 et 99
        vect_append(val,vect); // ajouter l'entier au vecteur
    }
    return vect;
}


/* Test de la fonction quicksort */
void test_quicksort() {
    vect_t tab = init_vect_int(10); // initialiser un vecteur avec 10 éléments
    printf("Avant quicksort:\n");
    vect_printf(tab);

    quicksort(tab);

    printf("\nAprès quicksort:\n");
    vect_printf(tab);
    printf("\n");

    vect_delete(tab); // nettoyage
}

/* Test de la fonction mergesort */
void test_mergesort() {
    vect_t tab = init_vect_int(10);
    printf("Avant mergesort:\n");
    vect_printf(tab);

    mergesort(tab);

    printf("\nAprès mergesort:\n");
    vect_printf(tab);
    printf("\n");

    vect_delete(tab); // nettoyage
}

/* Test de la fonction heapsort */
void test_heapsort() {
    vect_t tab = init_vect_int(10);
    printf("Avant heapsort:\n");
    vect_printf(tab);

    heapsort(tab);

    printf("\nAprès heapsort:\n");
    vect_printf(tab);
    printf("\n");

    vect_delete(tab); // nettoyage
}



int main() {
     // initialiser le générateur de nombres aléatoires

    printf("Test de quicksort:\n");
    test_quicksort();

    printf("Test de mergesort:\n");
    test_mergesort();

    printf("Test de heapsort:\n");
    test_heapsort();

    return 0;
}
