#include<stdio.h>
#include<stdlib.h>

typedef struct arv{   
    char info;
    int nivel;
    struct arv* esq;
    struct arv* dir;
}Arv;

Arv* add_busca(Arv* a, int v);
void atr_niveis(Arv* a, int n);
void imp_por_nivel(Arv* a);
void imp_niveis(Arv* a, int niv);
int altura(Arv *a);

int main (void){
    unsigned short int n, num, c, i;
    Arv* a1 = vazio();
    scanf("%hu", &c);
    for(i = 0; i < c; i++){
        scanf("%hu", &n);
        while(n--){
            scanf("%hu", &num);
            a1 = add_busca(a1,num);
        }
        printf("Case %hu:\n", i+1);
        atr_niveis(a1, 0);
        imp_por_nivel(a1);
        a1=del(a1);
        printf("\n\n");
    }
    return 0;
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

void atr_niveis(Arv* a, int n){
    if(a != NULL){
        n++;
        atr_niveis(a->esq,n);
        atr_niveis(a->dir,n);
    }
}

void imp_por_nivel(Arv* a){
    int i;
    int h = altura(a);
    for(i = 0; i<=h; i++){
        imp_niveis(a,i);
    }
    Lista* aux = l;
    for(aux = l; aux != NULL; aux = aux->prox){
        printf("%d", aux->info);
        if(aux->prox != NULL)
            printf(" ");
    }
}

void imp_niveis(Arv* a, int niv){
    if(a != NULL && a->nivel == niv){
        imp_niveis(a->esq, niv);
        imp_niveis(a->dir, niv);
    }
    else if(a!= NULL){
        imp_niveis(a->esq, niv);
        imp_niveis(a->dir, niv);
    }
}

int altura(Arv *a){
    int i;
    if(arv_vazia(a))
        return -1;
    else
        i =  max(altura(a->esq),altura(a->dir));
        return 1 + i;
}