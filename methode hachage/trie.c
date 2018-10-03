#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define A_ASCII_CODE 97
#define B_ASCII_CODE 98

/*Methode avec Table de hachage */
/*Trie createTrie(unsigned int maxNode) {
    
    TODO : allocation de la table de hachage 
    
    
    Trie trie = (Trie) malloc(sizeof(trans)  * sizeof(nextNode) *
                              sizeof(finite) * sizeof(maxNode));
    
    return NULL;
}*/


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
