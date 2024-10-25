#ifndef _STREE_H__
#define _STREE_H__
#define NB_ALPHA 26
#define NIL NULL

typedef struct _node {
    struct _node *sons[NB_ALPHA]; 
    unsigned int finWord;
    } *  tree_t;

tree_t NewTree(void);

tree_t AddWordInTree(const char *word, tree_t tree);

int LookForWordInTree(const char * word , tree_t tree);

tree_t DeleteTree(tree_t tree);



#endif