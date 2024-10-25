#include "../include/dico_hashset.h"



int main(){

    
    const char * text = "test/a_la_recherche_du_temps_perdu.txt";
    const char * dico =  "test/dico1.txt";
    hashvset_t DicoTable = dico_new(1);
    hashvset_t TextTable = dico_new(1);


    // Charger le dictionnaire avec les k premiers mots
    if (dico_load_text(TextTable, text) == -1) {
        printf("Erreur lors du chargement du dictionnaire\n");
        return -1;
    }
   
    if (dico_load_text(DicoTable, dico) == -1) {
        printf("Erreur lors du chargement du dictionnaire\n");
        return -1;
    }
    // Calculer la taille mémoire réelle en Mo
    
    //dico_print(TextTable);

    dico_verify_orthography(TextTable, DicoTable);
    

}
