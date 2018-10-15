#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define A_ASCII_CODE 97
#define B_ASCII_CODE 98


/* Totalement inspire par la fonction des paires de cantor
 * https://en.wikipedia.org/wiki/Pairing_function#Cantor_pairing_function */
int hasher(int etat, char letter) {
    int b = (int) letter;
    return (int)((etat + b) * (etat + b + 1) / 2 + etat);
}

List find_maillon_in_list(List list, int startNode, unsigned char letter) {
    while (list != NULL) {
        if (list->startNode == startNode && list->letter == letter) {
            return list;
        }
        list = list->next;
    }
    return NULL;
}

void insertInTrie(Trie trie, unsigned char *w) { 
    if (trie == NULL) {
        perror("le trie est NULL");
        return;
    }
    int noeud = 0;

    /* Pour chaque symbole dans w */
    while (w != NULL && *w != '\0') {

        /*On determine le hash de la transition*/
        int key = hasher(noeud, *w);
        List list = trie->transition[key];

        /*On regarde si un tel maillon existe dans la hashtable. Si c'est le cas, on le skippe*/
        List found = find_maillon_in_list(list, noeud, *w);
        if (found != NULL) {
            continue;
        }

        /* On regarde si on a de la place pour l'insertion */
        if (trie->nextNode +1 >= trie->maxNode) {
            perror("ya plus de place a l'aide\n");
            return;
        }

        /*On alloue le debut de la liste chainee qui n'a pas etee definie.*/
        List head = malloc(sizeof(struct _list));
        if (head == NULL) {
            perror("echec de malloc");
            return;
        }
        
        /*Construction du premier maillon*/
        ++trie->nextNode;

        head->startNode = noeud;
        head->targetNode = trie->nextNode;
        head->letter = *w;
        head->next = list;
        
        trie->transition[key] = head;

        noeud = head->targetNode;

        ++w;
    }
    /*le dernier noeud est un etat terminal.*/
    trie->finite[noeud]='1';
}



/*Methode avec Table de hachage */
Trie createTrie(int maxNode) {
    Trie trie = malloc(sizeof(struct _trie));
    if (trie == NULL) {
        perror("createTrie");
        return NULL;
    }
    trie->maxNode = maxNode;
    trie->nextNode = 0;
    trie->transition = calloc((size_t) maxNode*10000, sizeof(List));
    trie->finite = calloc((size_t)maxNode, sizeof(char));
    return trie;
}

Trie build_prefixes(unsigned char * w){
    /* Un automate qui reconnait un mot unique et dont tout les états sont finaux va reconnaitre exactement tout les préfixes.*/
    Trie trie = createTrie((unsigned int)strlen(w)+1);
    insertInTrie(trie,w);
    for(unsigned int i = 0; i!=strlen(w); ++i){
        trie->finite[i]='1';
    }
    return trie;
}

Trie build_suffixes(unsigned char *w) {
    Trie trie = createTrie((unsigned int)strlen(w) + 1);
    for (unsigned int i = 0; i <= strlen(w)-1; ++i) {
        insertInTrie(trie, w + i);
    }
    return trie;
}

int main(void){
    for(int i = 1; i!=99; ++i){
		for(int j=97; j!=122;++j){
			printf("pour %d, %d, hash= %d\n",i,j,hasher(i,(char)j));
		}
    }
    return 0;
}
