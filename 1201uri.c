#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define true 1
#define false 0

typedef struct arv{   
    unsigned info;
    struct arv* esq;
    struct arv* dir;
}Arv;

_Bool flag;
Arv* add_busca(Arv* a, int v);
void print_ord(Arv* a);
void print_pre(Arv* a);
void print_pos(Arv* a);
int find(Arv* a, int c);
Arv * findMax(Arv *root);
Arv * remover(Arv *raiz, int c);

int main(){
    char opc[10];
    int info;
    Arv* a1 = NULL;
    while(scanf("%s%*c", opc) != EOF){
        if(strcmp(opc, "I") == 0){
            scanf("%d%*c", &info), a1=add_busca(a1, info);
        }
        else if(strcmp(opc, "P") == 0){
            scanf("%d%*c", &info);
            if(find(a1,info))
                printf("%d existe\n", info);
            else
                printf("%d nao existe\n", info);
        }
        else if(strcmp(opc, "R") ==0){
            scanf("%d%*c", &info), a1 = remover(a1, info);
        }
        else{  
            flag = true;
            if (strcmp(opc,"INFIXA")==0){
                print_ord(a1), printf("\n");
            }
        
            if(strcmp(opc,"PREFIXA")==0){  
                print_pre(a1), printf("\n");
            }
        
            if(strcmp(opc,"POSFIXA")==0){  
                print_pos(a1), printf("\n");
            }
        }
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

void print_ord(Arv* a){
    if(a != NULL){
        print_ord(a->esq);
        if(flag){
            printf("%d", a->info);
            flag = false;
        }
        else{
            printf(" %d", a->info);
        }
        print_ord(a->dir);
    }
}

void print_pre(Arv* a){
    if(a != NULL){
        if(flag){
            printf("%d", a->info);
            flag = false;
        }
        else{
            printf(" %d", a->info);
        }
        print_pre(a->esq);
        print_pre(a->dir);
    }
}

void print_pos(Arv* a){
    if(a != NULL){
        print_pos(a->esq);
        print_pos(a->dir);
        if(flag){
            printf("%d", a->info);
            flag = false;
        }
        else{
            printf(" %d", a->info);
        }
    }
}

int find(Arv* a, int c){
    if(a == NULL)
        return 0;
    else 
        return a->info == c || 
        find(a->esq,c) ||
        find(a->dir,c);
}

Arv * findMax(Arv *root)
{

	if(!root)
		return NULL;
	else if (!root->dir)
		return root;
	else
		return findMax(root->dir);

}

Arv * remover(Arv *raiz, int c)
{
    if(raiz == NULL){
        return NULL;
    }
    else if(raiz->info > c)
        raiz->esq = remover(raiz->esq, c);
    else if(raiz->info < c)
        raiz->dir = remover(raiz->dir, c);
    else if(raiz->esq == NULL && raiz->dir == NULL){
        free(raiz);
        raiz = NULL;
    }
    else if(raiz->esq == NULL){
        Arv* aux = raiz;
        raiz = raiz->dir;
        free(aux);
    }
    else if(raiz->dir == NULL){
        Arv* aux = raiz;
        raiz = raiz->esq;
        free(aux);
    }
    else{
        Arv* aux = raiz->esq;
        while(aux->dir != NULL){
            aux = aux->dir;
        }
        raiz->info = aux->info;
        aux->info = c;
        raiz->esq = remover(raiz->esq, c);
    }
    return raiz;
}