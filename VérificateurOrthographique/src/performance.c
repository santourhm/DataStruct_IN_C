#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/hashvset.h"
#include "../include/dico_hashset.h"

// Fonction pour calculer le nombre de mots dans un fichier
int filelength(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", filename);
        exit(EXIT_FAILURE);
    }
    int count = 0;
    char word[256];
    while (fscanf(file, "%s", word) != EOF) {
        count++;
    }
    fclose(file);
    return count;
}

int main(int ac, char** av) {
    clock_t debut, fin, debut1, fin1;

    if (ac != 2 && ac != 3) {
        printf("Usage : %s fichier_dico fichier_a_verifier\n", av[0]);
        exit(EXIT_FAILURE);
    }

    // Nombre de mots dans le dictionnaire
    int nbwords = filelength(av[1]);

    FILE* ftemps = fopen("temps.dat", "w");
    if (!ftemps) {
        printf("Erreur lors de l'ouverture du fichier temps.dat\n");
        return -1;
    }

    // Boucle pour tester les performances avec différentes tailles de dictionnaire (100 points)
    for (int k = nbwords; k > 1; k -= nbwords / 100) {
        hashvset_t DicoTable = dico_new(k);
        hashvset_t TextTable = dico_new(k);

        debut = clock();
        // Charger le dictionnaire avec les k premiers mots
        if (dico_load_text(DicoTable, av[1]) == -1) {
            printf("Erreur lors du chargement du dictionnaire\n");
            return -1;
        }
        fin = clock();
        if (dico_load_text_first_k(TextTable, av[2],k) == -1) {
            printf("Erreur lors du chargement du dictionnaire\n");
            return -1;
        }
        // Calculer la taille mémoire réelle en Mo
        double taille = ((double)k * sizeof(char) * MAX_WORD_LENGTH) / (1024 * 1024);

        debut1 = clock();
        dico_verify_orthography(TextTable, DicoTable);
        fin1 = clock();

        double temps_cpu_verification = ((double)(fin1 - debut1)) / CLOCKS_PER_SEC;

        // Écrire dans le fichier les données de nombre de mots du dico, taille mémoire, et temps CPU de la vérification
        fprintf(ftemps, "%d %lf %lf %lf\n", k, taille,((double)(fin - debut)) / CLOCKS_PER_SEC ,temps_cpu_verification);

        // Libérer la table de hachage
        hashvset_delete(DicoTable);
        hashvset_delete(TextTable);

    }

    fclose(ftemps);

    /* // Appel à Gnuplot pour tracer et ajuster les courbes
    system("gnuplot -p -e \""
           "set terminal png size 800,600; "
           "set output 'performance.png'; "
           "set title 'Analyse des performances de chargement et vérification'; "
           "set xlabel 'Nombre de mots dans le dictionnaire'; "
           "set ylabel 'Temps (secondes)'; "
           "set y2label 'Taille mémoire (MB)'; "
           "set y2tics nomirror; "
           "set grid; "
           "set y2range [0:*]; "
           "f(x) = a * x + b; "
           "fit f(x) 'temps.dat' using 1:2 via a, b; "
           "plot 'temps.dat' using 1:2 with lines lt 4 axis x1y2 title 'Taille', "
           "f(x) with lines lt 6 axis x1y2 title 'Fit Taille', "
           "g(x) = c * x + d; "
           "fit g(x) 'temps.dat' using 1:3 via c, d; "
           "replot 'temps.dat' using 1:3 with lines lt 2 title 'Recherche', "
           "g(x) with lines lt 8 title 'Fit Recherche'; "
           "quit\""); */

    return 0;
}
