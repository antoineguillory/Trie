#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define A_ASCII_CODE 97
#define B_ASCII_CODE 98

/*Methode avec Table de hachage */
Trie createTrie(unsigned int maxNode) {  

    /*On va determiner la valeur maximale (la taille, au final)
    Qu'aura notre table de hachage. On utilise maxNode et la valeur la plus elevee de la table ascii*/  
    
    Trie trie = (Trie) malloc(sizeof(trans)  * sizeof(nextNode) *
                              sizeof(finite) * sizeof(maxNode));
    
    return NULL;
}

Trie build_prefixes(char * w){
    /* Un automate qui reconnait un mot unique et dont tout les états sont finaux va reconnaitre exactement tout les préfixes.*/
    Trie trie = createTrie(strlen(w)+1);
    insertInTrie(trie,w);
    for(unsigned int i = 0; i!=strlen(w); ++i){
        finite[i]='1';
    }
}

Trie build_suffixes(char *w) {
    Trie trie = createTrie(strlen(w) + 1);
    for (int i = 0; i <= strlen(w); ++i) {
        insertInTrie(trie, w + i);
    }
    return result;
}

/* Totalement inspire par la fonction des paires de cantor
 * https://en.wikipedia.org/wiki/Pairing_function#Cantor_pairing_function */
double hasher(double etat, char letter) {
	double b = (double) (int) letter;
	return (etat + b) * (etat + b + 1) / 2 + etat;
}


int main(void){
    for(int i = 1; i!=99; ++i){
		for(int j=97; j!=122;++j){
			printf("pour %d, %d, hash= %lf\n",i,j,hasher(i,(char)j));
		}
    }
    return 0;
}
