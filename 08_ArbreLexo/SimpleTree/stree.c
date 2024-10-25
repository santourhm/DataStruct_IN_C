#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stree.h"

// Fonction pour créer un nouvel arbre
tree_t NewTree(void) {
    tree_t Tree = (tree_t)malloc(sizeof(*Tree));
    if (Tree) {
        for (int i = 0; i < NB_ALPHA; i++) {
            Tree->sons[i] = NULL;  // Initialisation des fils à NULL
        }
        Tree->finWord = 0;  // Initialisation de finWord à 0
    }
    return Tree;
}

// Fonction pour ajouter un mot dans l'arbre
tree_t AddWordInTree(const char *word, tree_t tree) {
    if (tree == NULL) {  // Corriger l'erreur d'affectation
        tree = NewTree();
    }
    
    tree_t current = tree;
    for (int i = 0; word[i] != '\0'; ++i) {
        int index = word[i] - 'a';
        if (index < 0 || index >= NB_ALPHA) {
            continue;  // Ignorer les caractères non alphabétiques
        }
        if (current->sons[index] == NULL) {
            current->sons[index] = NewTree();  // Créer un nouveau nœud si nécessaire
        }
        current = current->sons[index];
    }
    current->finWord = 1;  // Marquer la fin du mot
    return tree;
}

// Fonction pour rechercher un mot dans l'arbre
int LookForWordInTree(const char *word, tree_t tree) {
    if (tree == NULL) return 0;  // Vérifier si l'arbre est vide

    tree_t current = tree;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (index < 0 || index >= NB_ALPHA) return 0;  // Ignorer les caractères non alphabétiques
        if (current->sons[index] == NULL) return 0;  // Si un nœud n'existe pas, le mot n'est pas présent
        current = current->sons[index];
    }

    return (current != NULL) && current->finWord ;  // Vérifier la fin du mot
    
}

// Fonction pour supprimer l'arbre et libérer la mémoire
tree_t DeleteTree(tree_t tree) {
    if (tree == NULL) return NULL;

    for (int i = 0; i < NB_ALPHA; i++) {
        if (tree->sons[i] != NULL) {
            DeleteTree(tree->sons[i]);  // Appel récursif pour libérer les fils
        }
    }

    free(tree);  // Libérer la mémoire du nœud courant
    return NULL;  // Retourner NULL après suppression
}