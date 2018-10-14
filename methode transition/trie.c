#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define A_ASCII_CODE 97
#define B_ASCII_CODE 98

/*Methode avec Matrice de transition*/
Trie createTrie(unsigned int maxNode) {
    
    /*Allocation de la matrice de transition*/
    int **trans = (int **)malloc(maxNode * sizeof(int*));
    if(trans == NULL) {
        perror("malloc transition 1");
        exit(EXIT_FAILURE);
    }
    for(unsigned int i = 0; i < maxNode; ++i) {
        trans[i] = (int *)malloc(UCHAR_MAX * sizeof(int));
        if(trans[i] == NULL) {
            perror("malloc transition 2");
            exit(EXIT_FAILURE);
        }
    }
    
    /*Mettons une valeur par defaut a chaque case de la matrice*/
    for(unsigned int k = 0; k<maxNode; ++k) {
        for(int j = 0; j<UCHAR_MAX; ++j) {
            trans[k][j] = -1;
        }
    }
    
    int nextNode = 0;
    char* finite = (char *) malloc(maxNode * sizeof(char));
    if(finite == NULL) {
        perror("malloc finite");
        exit(EXIT_FAILURE);
    }
    
    Trie trie = (Trie) malloc(sizeof(trans)  * sizeof(nextNode) *
                              sizeof(finite) * sizeof(maxNode));
    
    if(trie==NULL){
        perror("malloc trie");
        exit(EXIT_FAILURE);
    }
    
    trie -> maxNode = (int) maxNode;
    trie -> nextNode = nextNode;
    trie -> finite = finite;
    trie -> transition = trans;
    
    return trie;
}

void insertInTrie(Trie trie, char *w) {
    
    size_t wSize = strlen(w);
    /*Verification si le mot w n'est pas le mot vide*/
    if(wSize==(size_t)0){
        perror("w is the empty word");
        return;
    }
    
    /*Iteration sur chaque caractere du mot w */
    for(int i = 0; i <= (int)wSize; ++i){
        /* Si il n'existe pas pour le caractère a la position i
         * du mot w une transition de cet index vers la representation
         * en entier du caractère w[i], j'insere la position du nouveau
         * noeud ainsi insere */
        if(trie->transition[i][(int)w[i]]==-1){
            if((size_t)i == wSize){
                trie->finite = strncat(trie->finite, "1",1);
            } else {
				trie->finite = strncat(trie->finite, "0",1);
			}
            ++(trie->nextNode);
            trie->transition[i][(int)w[i]] = trie->nextNode;
        }
    }
}

int isInTrie(Trie trie, char *w) {
	size_t wLen = strlen(w);
	int i=0;
	for(; i!=(int)wLen; ++i){
		if(trie->transition[i][(int)w[i]] == -1){
			return 0;
		}
	}
	if(trie->finite[i]=='0'){
		return 0;
	}
	return 1;
}

Trie build_prefixes(char * w){
    /* Un automate qui reconnait un mot unique et dont tout les états sont finaux va reconnaitre exactement tout les préfixes.*/
    Trie trie = createTrie((unsigned int)strlen(w)+1);
    insertInTrie(trie,w);
    for(unsigned int i = 0; i!=strlen(w); ++i){
        trie->finite[i]='1';
    }
    return trie;
}

Trie build_suffixes(char *w) {
    Trie trie = createTrie((unsigned int)strlen(w) + 1);
    for (unsigned int i = 0; i <= strlen(w)-1; ++i) {
        insertInTrie(trie, w + i);
    }
    return trie;
}

void testAffichage(Trie trie){
    /*On considère que c'est des mots uniquement avec a et b pour les tests..*/
    puts("  A  B\n");
    for(int i=0; i<trie->maxNode; ++i){
        printf("%d|",i);
        for(int j=A_ASCII_CODE; j!=B_ASCII_CODE+1; ++j){
            printf("%d ", trie->transition[i][j]);
        }
        puts("\n");
    }
    puts("Etats finaux :\n");
    for(unsigned int j=0; j<=strlen(trie->finite)-1;++j){
        printf("%d : %c\n",j,trie->finite[j]);
    }    
    
   /* puts("est dans le trie ?\n");
    printf("doit renvoyer 0 : %d\n",isInTrie(trie,"ababaaa"));
    printf("doit renvoyer 1 : %d\n",isInTrie(trie,"bbbb"));
    printf("doit renvoyer 1 : %d\n",isInTrie(trie,"abababba"));
	printf("doit renvoyer 0 : %d\n",isInTrie(trie,"abababb")); */


    
}

int main(void){
    Trie trie = createTrie(10);
    if(trie==NULL) {
        perror("echec de creation du trie");
        exit(EXIT_FAILURE);
    }
    printf("mallocs reussis \n");
    char* test = "abababba";
    insertInTrie(trie, test);
    char* test2 = "bbbb";
    insertInTrie(trie, test2);
    //testAffichage(trie);
    puts("test suffixes\n");
    Trie trisuff = build_suffixes("baba");
    puts("suffixes buildés\n");

    puts("test prefixes\n");
    Trie tripref = build_prefixes("abababa");
    puts("prefixes buildé\n");

    puts("SUFFIXES :\n");
    testAffichage(trisuff);

    puts("\nPREFIXES : \n");
    testAffichage(tripref);

    return 0;
}
