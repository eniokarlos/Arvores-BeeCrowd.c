#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 100


typedef struct arv{   
    char info;
    struct arv* esq;
    struct arv* dir;
}Arv;

short indice;

void imprimir_pos(Arv * a);
Arv* add(char letra);
int search(char* str, int inicio, int fim, char letra);
Arv* arvore(char* infixa, char* prefixa, int inicio, int fim);

int main(void){
    short int casos, nos, i;
    char pre[MAX], inf[MAX];
    scanf("%hu", &casos);
    while(scanf("%s %s%*c", pre, inf) != EOF){
        nos = strlen(pre);
        indice = 0;
        Arv *a1 = arvore(inf, pre, 0, nos - 1);
        imprimir_pos(a1);
        printf("\n");

    }
    return 0;
}

Arv* add(char letra){
    Arv *novo = (Arv *) malloc(sizeof(Arv));
	novo->info = letra;
	novo->esq = novo->dir = NULL;
	return novo;
}

int search(char* str, int inicio, int fim, char letra){
    short i;

    for (i = inicio; i <= fim; ++i)
		if (str[i] == letra)
			return i;

	return -1;
}

Arv* arvore(char* infixa, char* prefixa, int inicio, int fim){
    int InfixaIndice;

    if(inicio > fim)
        return NULL;

    Arv* node = add(prefixa[indice++]);
    if(inicio == fim)
        return node;

    InfixaIndice = search(infixa, inicio, fim, node->info);
    node->esq = arvore(infixa, prefixa, inicio, InfixaIndice - 1);
    node->dir = arvore(infixa, prefixa, InfixaIndice + 1, fim);

    return node;

} 

void imprimir_pos(Arv * a){
    if(a != NULL){
        imprimir_pos(a->esq); 
        imprimir_pos(a->dir);  
        printf("%c", a->info);   
    }
}

