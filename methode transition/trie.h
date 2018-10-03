#ifndef TRIE_H
#define TRIE_H

struct _trie {
    int maxNode;      /* Nombre maximal de noeuds du trie    */
    int nextNode;     /* Indice du prochain noeud disponible */
    int **transition; /* matrice de transition               */
    char *finite;     /* etats terminaux                     */
};

typedef struct _trie *Trie;

#endif

