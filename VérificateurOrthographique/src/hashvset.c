#include "../include/hashvset.h"

hashvset_t hashvset_new(int n, unsigned int (*fhachage)(void * ),
    void (*print_key)(void*,FILE*),
    void* (*delete_key)(void*), int (*compare_key)(void* e1, void* e2)) {
    
    hashvset_t table = (hashvset_t) malloc(sizeof(*table));
    if (table == NULL) {
        return NULL;
    }

    table->data = (cellhashvset_t *) malloc(n * sizeof(cellhashvset_t));
    if (table->data == NULL) {
        free(table);
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        table->data[i].key = NULL;
        table->data[i].busy = EMPTY;
        table->data[i].hashcode = 0;
    }

    table->size = n;
    table->total_number = 0;
    table->hachage = fhachage;
    table->compare_key = compare_key;
    table->delete_key = delete_key;
    table->print_key = print_key;
    
    return table;
}

hashvset_t hashvset_delete(hashvset_t table) {
    assert(table != NULL);

    // Supprimer les clés seulement dans les cases occupées
    for (int i = 0; i < table->size; i++) {
        if (table->data[i].busy == OCCUPED) {
            table->delete_key(table->data[i].key);
        }
    }

    free(table->data);
    free(table);
    return NULL;
}

int hashvset_new_length(int sens, hashvset_t table) {
    unsigned int new_size = (sens > 0) ? (table->size * 2) : (table->size / 2);

    // Allocation de la nouvelle table de hachage
    cellhashvset_t* new_data = calloc(new_size, sizeof(cellhashvset_t));
    if (new_data == NULL) {
        return 0;  // Échec de l'allocation
    }
    
    // Initialiser les cellules de la nouvelle table à EMPTY
    for (unsigned int i = 0; i < new_size; i++) {
        new_data[i].busy = EMPTY;
    }

    // Réinsérer les anciennes données dans la nouvelle table
    for (int i = 0; i < table->size; i++) {
        if (table->data[i].busy == OCCUPED) {
            int slot = table->data[i].hashcode % new_size;

            // Probing linéaire si la case est occupée
            while (new_data[slot].busy == OCCUPED) {
                slot = (slot + 1) % new_size;
            }

            new_data[slot] = table->data[i];  // Copier les données dans le nouvel emplacement
        }
    }

    // Libérer l'ancienne table
    free(table->data);

    // Mettre à jour la table
    table->data = new_data;
    table->size = new_size;
    
    return 1;  // Succès du redimensionnement
}

int hashvset_put(void* key, hashvset_t table) {
    assert(table != NULL);

    float facteur_charge = (float) table->total_number / table->size;
    unsigned int hashcode = table->hachage(key);

    // Resize if load factor exceeds 0.7
    if (facteur_charge > 0.7) {
        if (!(hashvset_new_length(1, table))) {
            return -1;  // Failed to resize
        }
    }

    unsigned int i = 0;
    unsigned int slot;
    while (i < table->size) {
        slot = (hashcode + i) % table->size;

        if (table->data[slot].busy == EMPTY || table->data[slot].busy == FREE) {
            char* new_key = strdup((char*)key);  // Create a copy of the key
            if (new_key == NULL) {
                return -1;  // Memory allocation failed
            }

            table->data[slot].key = new_key;
            table->data[slot].busy = OCCUPED;
            table->data[slot].hashcode = hashcode;
            table->total_number++;
            
            return 1;
        }

        if (table->data[slot].busy == OCCUPED && table->compare_key(table->data[slot].key, key) == 0) {
            return 1;
        }

        i++;
    }

    return 0;  // Failed to insert (table full)
}


void hashvset_printf(hashvset_t table) {
    hashvset_fprintf(table,stdout);
}

void hashvset_fprintf(hashvset_t t, FILE *fp) {
    if (t == NULL || fp == NULL) {
        fprintf(stderr, "Table de hachage ou fichier invalide.\n");
        return;
    }

    fprintf(fp, "Table de hachage (taille: %u, éléments: %u):\n", t->size, t->total_number);
    fprintf(fp, "+-------+-------------------+-------------------+\n");
    fprintf(fp, "| Index |      Etat          |       Clé         |\n");
    fprintf(fp, "+-------+-------------------+-------------------+\n");

    for (unsigned int i = 0; i < t->size; i++) {
        char *state_str;
        switch (t->data[i].busy) {
            case EMPTY:
                state_str = "EMPTY";
                break;
            case FREE:
                state_str = "FREE";
                break;
            case OCCUPED:
                state_str = "OCCUPIED";
                break;
            default:
                state_str = "UNKNOWN";
                break;
        }

        // Afficher l'index et l'état de chaque case
        fprintf(fp, "| %-5u | %-17s | ", i, state_str);

        // Afficher la clé si la case est occupée
        if (t->data[i].busy == OCCUPED) {
            t->print_key(t->data[i].key, fp);  // Utilise la fonction print_key pour afficher la clé
        } else {
            fprintf(fp, "       -         ");
        }

        fprintf(fp, " |\n");
    }

    fprintf(fp, "+-------+-------------------+-------------------+\n");
}



int hashvset_find_key(void* key, hashvset_t table) {
    assert(table != NULL);
    assert(key != NULL);

    unsigned int hashcode = table->hachage(key);
    unsigned int i = 0;
    
    

    while (i < table->size) {
        unsigned int slot = (hashcode + i) % table->size;

        // If the slot is occupied and the key matches, return the slot index
        if (table->data[slot].busy == OCCUPED && table->compare_key(table->data[slot].key, key) == 0) {
            return slot;
        }

        // If the slot is empty, the key does not exist in the table
        if (table->data[slot].busy == EMPTY) {
            return -1;
        }

        // Increment i to probe the next slot
        i++;
    }

    // If the key wasn't found after scanning the whole table, return -1
    return -1;
}



int hashvset_remove_key(void* key, hashvset_t table) {
    assert(table != NULL);
    
    // Find the index of the key to be removed
    int index = hashvset_find_key(key, table);

    // If the key exists in the table (index >= 0)
    if (index >= 0) {
        // Delete the key, mark the slot as FREE
        table->delete_key(table->data[index].key);
        table->data[index].hashcode = 0;
        table->data[index].busy = FREE;

        // Decrement the total number of occupied slots
        table->total_number--;

        // Check the load factor and resize if necessary
        float load_factor = (float)(table->total_number) / table->size;
        if (load_factor < 0.2) {
            if (hashvset_new_length(-1, table) <= 0) {
                return -1; // Failed to resize
            }
        }

        return 1; // Successful removal
    }

    return -1; // Key not found
}
