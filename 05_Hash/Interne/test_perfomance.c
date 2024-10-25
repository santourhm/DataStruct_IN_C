#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hashvset.h"

// Fonction de hachage basique pour des chaînes de caractères (hash djb2)
unsigned int string_hash(void* key) {
    char* str = (char*) key;
    unsigned int hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}

// Fonction pour comparer deux chaînes de caractères
int compare_strings(void* e1, void* e2) {
    return strcmp((char*)e1, (char*)e2);
}

// Fonction pour afficher une chaîne de caractères
void print_string(void* key, FILE* fp) {
    fprintf(fp, "%s", (char*)key);
}

// Fonction pour supprimer une chaîne de caractères (libérer la mémoire)
void* delete_string(void* key) {
    free(key);
    return NULL;
}

// Générer une clé aléatoire (chaîne de caractères)
char* generate_random_key(int length) {
    char* key = malloc(length + 1);
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < length; i++) {
        key[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    key[length] = '\0';
    return key;
}

int main() {
    srand(time(NULL)); // Initialisation de l'aléatoire
    
    // Créer une nouvelle table de hachage avec une taille initiale de 16
    hashvset_t table = hashvset_new(16, string_hash, print_string, delete_string, compare_strings);
    if (table == NULL) {
        fprintf(stderr, "Erreur de création de la table de hachage.\n");
        return 1;
    }

    int num_insertions = 100000; // Nombre d'insertion pour le test
    int key_length = 10;         // Longueur des clés aléatoires

    // Mesurer le temps d'insertion
    clock_t start_insertion = clock();

    for (int i = 0; i < num_insertions; i++) {
        char* key = generate_random_key(key_length);
        if (hashvset_put(key, table) != 1) {
            fprintf(stderr, "Erreur d'insertion pour la clé : %s\n", key);
            free(key); // Libérer la clé si l'insertion échoue
        }
    }

    clock_t end_insertion = clock();
    double insertion_time = (double)(end_insertion - start_insertion) / CLOCKS_PER_SEC;

    printf("Temps d'insertion pour %d éléments: %f secondes\n", num_insertions, insertion_time);

    // Afficher la table après insertion (facultatif)
    // hashvset_fprintf(table, stdout);

    // Mesurer le temps de réinitialisation (redimensionnement vers plus grand)
    clock_t start_resize = clock();
    hashvset_new_length(1, table); // Agrandir la table
    clock_t end_resize = clock();
    double resize_time = (double)(end_resize - start_resize) / CLOCKS_PER_SEC;

    printf("Temps de redimensionnement (agrandissement): %f secondes\n", resize_time);

    // Libérer la mémoire et supprimer la table
    table = hashvset_delete(table);

    return 0;
}
