#include "../include/dico_hashset.h"







hashvset_t dico_new(int n){

    hashvset_t new_dico = hashvset_new(n,string_hash,print_key,string_delete,string_compare);
    
    return new_dico;
}


// Function to process each word (this can be modified as needed)


// Insert the processed word into the hash table
void process_and_insert_word(hashvset_t table, char *word) {
    // Vérifier si le mot n'est pas vide après traitement
    if (strlen(word) > 0) {
        // Insérer le mot dans la table de hachage
        hashvset_put(word, table);
    }
}

void dico_process_word(hashvset_t table, char *word) {
    // Convertir le mot en minuscules (traitement insensible à la casse)
    for (int i = 0; word[i]; i++) {
        word[i] = tolower((unsigned char)word[i]);
    }

    // Enlever la ponctuation en fin de mot
    int len = strlen(word);
    while (len > 0 && ispunct((unsigned char)word[len - 1])) {
        word[len - 1] = '\0';  // Enlever la ponctuation en fin de mot
        len--;
    }

    // Enlever la ponctuation en début de mot sans modifier le pointeur original
    char *start = word;
    while (*start && ispunct((unsigned char)*start)) {
        start++;  // Avancer le pointeur au-delà de la ponctuation en début
    }

    // Utiliser strtok pour diviser le mot sur les apostrophes (')
    char *token = strtok(start, "'");  // Diviser sur les apostrophes
    while (token != NULL) {
        // Diviser chaque segment sur les traits d'union et traiter
        char *subtoken = strtok(token, "-");
        while (subtoken != NULL) {
            process_and_insert_word(table, subtoken);  // Traiter chaque segment du mot
            subtoken = strtok(NULL, "-");  // Passer au segment suivant
        }
        token = strtok(NULL, "'");  // Passer au segment suivant après l'apostrophe
    }
}



// Function to load and process words from the text file
int dico_load_text(hashvset_t table , const char* filename){
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 0 ;
    }

    char buffer[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", buffer) == 1) {
        
        dico_process_word(table,buffer);  // Process each word
       
    }

    fclose(file);

    return 1;
}

int dico_load_text_first_k(hashvset_t table , const char* filename , int k){
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 0 ;
    }

    char buffer[MAX_WORD_LENGTH];
    int i = 0;

    while (fscanf(file, "%s", buffer) == 1 && i<k) {
        
        dico_process_word(table,buffer);  // Process each word
        k++;
       
    }

    fclose(file);

    return 1;

}


void dico_print(hashvset_t text){
    hashvset_fprintf(text,stdout);
}

void dico_verify_orthography(hashvset_t TextHash, hashvset_t DicoHash){
    
    for (unsigned int i = 0; i < TextHash->size; i++)
    {    
        if (TextHash->data[i].busy == OCCUPED )
        {  
        
           int index = hashvset_find_key(TextHash->data[i].key,DicoHash);
          
           if (index < 0) {
            print_key(TextHash->data[i].key,stdout); 
            continue;}  
        

        }}}
