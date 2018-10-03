#ifndef TRIE_H
#define TRIE_H

struct _list {
	int startNode,        /* etat de depart de la transition */
		targetNode;       /* cible de la transition          */
	char letter;          /* etiquette de la transition      */
	struct _list *next;   /* maillon suivant                 */
};
typedef struct _list *List;

struct _trie {
	int maxNode;      /* Nombre maximal de noeuds du trie    */
	int nextNode;     /* Indice du prochain noeud disponible */
	List *transition; /* listes d’adjacence                  */
	char *finite;     /* etats terminaux                     */
};

#endif

