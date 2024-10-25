#include "tri.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>



/* partitionner le tableau `tab` entre les indices `gauche`et `droite`*/
int partitionner(vect_t tab, int gauche, int droit){
    assert(tab != NULL);
    assert(tab->data != NULL);
    assert(tab->equal_data != NULL);

    void *pivot = tab->data[droit];
    int i = gauche - 1;

    for (int j = gauche; j < droit; j++) {
        if (tab->equal_data(pivot, tab->data[j]) >= 0) {
            i++;
            void *temp = tab->data[i];
            tab->data[i] = tab->data[j];
            tab->data[j] = temp;
        }
    }

    void *temp = tab->data[droit];
    tab->data[droit] = tab->data[i + 1];
    tab->data[i + 1] = temp;

    return i + 1;
}
/* tri recursif du tableau `tab` entre les indices `gauche`et `droite` */
void quick_sortrec(vect_t tab, int gauche, int droit){
    if (gauche < droit)
    {
        int pivot = partitionner(tab ,gauche ,droit);
        quick_sortrec(tab ,gauche ,pivot - 1);
        quick_sortrec(tab ,pivot + 1,droit);
    }
}


void quicksort(vect_t tab){
    assert( tab != NULL );
    assert( tab->actual_size > 0 );
    
    quick_sortrec(tab, 0, tab->actual_size - 1);
}

void fusion(vect_t tab, vect_t tmp, size_t gauche, size_t droit){
    size_t milieu = (droit + gauche) / 2;
    size_t i = gauche;
    size_t j = milieu + 1;
    size_t k = gauche;

    while (i <= milieu && j <= droit) {
        if (tab->equal_data(tab->data[i], tab->data[j]) <= 0)
            tmp->data[k++] = tab->data[i++];
        else
            tmp->data[k++] = tab->data[j++];
    }

    while (i <= milieu) tmp->data[k++] = tab->data[i++];
    while (j <= droit) tmp->data[k++] = tab->data[j++];

    for (size_t idx = gauche; idx <= droit; idx++)  // Correction ici aussi
        tab->data[idx] = tmp->data[idx];
}

/* Tri récursif du tableau `tab` entre les indices `gauche` et `droit` à l'aide du tableau `tmp` */
void _trifusionrec(vect_t tab, vect_t tmp, size_t gauche, size_t droit) {
    if (gauche < droit) {
        size_t milieu = (gauche + droit) / 2;
        _trifusionrec(tab, tmp, gauche, milieu);       // Correction ici : gauche -> milieu
        _trifusionrec(tab, tmp, milieu + 1, droit);
        fusion(tab, tmp, gauche, droit);
    }
}

/* Tri du tableau `tab` entier (fonction wrapper cachant les autres paramètres à l'utilisateur) */
void mergesort(vect_t tab) {
    if (tab == NULL || tab->actual_size <= 1) {
        return;
    }

    vect_t tmp = vect_new(tab->max_size, NULL, NULL, NULL);
    _trifusionrec(tab, tmp, 0, tab->actual_size - 1);

    tmp = vect_delete(tmp);
}


void heapify(vect_t tab, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && tab->equal_data(tab->data[left], tab->data[largest]) > 0)
        largest = left;

    if (right < n && tab->equal_data(tab->data[right], tab->data[largest]) > 0)
        largest = right;

    if (largest != i) {
        void *tmp = tab->data[i];
        tab->data[i] = tab->data[largest];
        tab->data[largest] = tmp;

        heapify(tab, n, largest);
    }
}

void heapsort(vect_t tab) {
    if (tab == NULL || tab->actual_size <= 1) return;

    int n = tab->actual_size;

    // Construire le tas (heapify)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(tab, n, i);

    // Extraire les éléments un par un du tas
    for (int i = n - 1; i > 0; i--) {
        // Échanger l'élément le plus grand (racine) avec le dernier élément
        void *tmp = tab->data[0];
        tab->data[0] = tab->data[i];
        tab->data[i] = tmp;

        // Réajuster le tas réduit
        heapify(tab, i, 0);
    }
}



