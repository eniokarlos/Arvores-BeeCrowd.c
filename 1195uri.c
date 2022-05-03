#include <stdlib.h>
#include <stdio.h>

typedef struct arv{   
    int info;
    struct arv* esq;
    struct arv* dir;
}Arv;

typedef struct lista{
    int info;
    struct lista* prox;
}Lista;

Lista * L1 = NULL;

Lista * adicionar(Lista* L, int v){
    Lista * novo = (Lista *) malloc(sizeof(Lista));
	novo->info = v;
	novo->prox = NULL;
	if (L == NULL)
		return novo;

	Lista * aux = L;
	while(aux->prox != NULL){
		aux = aux->prox;
	}
	aux->prox = novo;
	return L;
}

Lista * remover(Lista* L){
    Lista * p = L;
    while(p != NULL){
        Lista * t = p->prox;
        free(p);
        p = t;
    }
}

Arv* add_busca(Arv* a, int v){
    if(a== NULL){
        a = (Arv*) malloc(sizeof(Arv));
        a->info = v;
        a->esq = a->dir = NULL;
    }
    else if(v < a->info)
        a->esq = add_busca(a->esq, v);
    else 
        a->dir = add_busca(a->dir, v);
    return a;
}

Arv* del(Arv* a){
    if(a != NULL){
        del(a->esq);
        del(a->dir);
        free(a);
    } 
    return NULL;
}

void add_pre(Arv * a){
    if(a != NULL){
        L1 = adicionar(L1, a->info);
        add_pre(a->esq);
        add_pre(a->dir);     
    }
}

void add_ord(Arv* a){
    if(a != NULL){
        add_ord(a->esq);
        L1 = adicionar(L1, a->info);
        add_ord(a->dir); 
    }
}

void add_pos(Arv* a){
    if(a != NULL){
        add_pos(a->esq);
        add_pos(a->dir);
        L1 = adicionar(L1, a->info);
    }
}

void imprimir(){
    Lista* aux = L1;
    for(aux = L1; aux != NULL; aux = aux->prox){
        printf("%hu", aux->info);
        if(aux->prox != NULL)
            printf(" ");
    }
    remover(L1);
    L1 = NULL;
}

int main(void){
    unsigned short int c, n, val, i;
    Arv* a1 = NULL;
    scanf("%hu", &c);
    for(i = 0; i < c; i++){
        scanf("%hu", &n);
        while(n--){
            scanf("%hu", &val);
            a1 = add_busca(a1,val);
        }
        printf("Case %hu:\n", i+1);
        printf("Pre.: ");
        add_pre(a1);
        imprimir();
        printf("\n");
        printf("In..: ");
        add_ord(a1);
        imprimir();
        printf("\n");
        printf("Post: ");
        add_pos(a1);
        imprimir();
        a1 = del(a1);
        printf("\n\n");
    }
    return 0;
}