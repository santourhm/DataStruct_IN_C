#include <stdio.h>
#include <stdlib.h>
#include "stree.h"

int main() {
    // Initialisation de l'arbre
    tree_t tree = NewTree();
    
    // Mots à ajouter dans l'arbre
    const char *words[] = {
        "apple",
        "banana",
        "grape",
        "orange",
        "berry",
        "pear"
    };

    // Ajout des mots dans l'arbre
    for (int i = 0; i < 6; i++) {
        tree = AddWordInTree(words[i], tree);
    }

    // Test de recherche des mots
    const char *searchWords[] = {
        "apple",  // Mot qui existe
        "banana", // Mot qui existe
        "grapefruit", // Mot qui n'existe pas
        "orange",  // Mot qui existe
        "pineapple",  // Mot qui n'existe pas
        "pear",   // Mot qui existe
        "peach"   // Mot qui n'existe pas
    };

    printf("=== Test de recherche dans l'arbre ===\n");
    for (int i = 0; i < 7; i++) {
        if (LookForWordInTree(searchWords[i], tree)) {
            printf("Le mot '%s' est présent dans l'arbre.\n", searchWords[i]);
        } else {
            printf("Le mot '%s' n'est pas présent dans l'arbre.\n", searchWords[i]);
        }
    }

    // Suppression de l'arbre
    tree = DeleteTree(tree);
    printf("Arbre supprimé avec succès.\n");

    return 0;
}
