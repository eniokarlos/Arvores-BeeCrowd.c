#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct arv{   
    long int info;
    struct arv* esq;
    struct arv* dir;
}Arv;

unsigned short int b;

Arv* add_busca(Arv* a, long int v){
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
        if(b){
            printf("%li", a->info);
            b = 0;
        }
        else{
            printf(" %li", a->info);
        }
        print_ord(a->dir);
    }
}

void print_pre(Arv* a){
    if(a != NULL){
        if(b){
            printf("%li", a->info);
            b = 0;
        }
        else{
            printf(" %li", a->info);
        }
        print_pre(a->esq);
        print_pre(a->dir);
    }
}

void print_pos(Arv* a){
    if(a != NULL){
        print_pos(a->esq);
        print_pos(a->dir);
        if(b){
            printf("%li", a->info);
            b = 0;
        }
        else{
            printf(" %li", a->info);
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

Arv* remover(Arv* raiz, long int c){
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
        Arv* aux = raiz->dir;
        while(aux->dir != NULL){
            aux = aux->dir;
        }
        raiz->info = aux->info;
        aux->info = c;
        raiz->esq = remover(raiz->esq, c);
    }
    return raiz;
}

long int convert_int(char* c){
    char aux[7];
    long int valor;
    int i, a=0;
    for(i=0; i < strlen(c); i++){
        if (c[i] > 47 && c[i] < 58){
            aux[a] = c[i];
            a++;
        if (i == strlen(c) -1){
            aux[a] = '\0';
            valor = atoi(aux);
            }
        }
    }
    return valor;
}

int main(){
    char opc[30];
    unsigned short int i;
    long int info;
    Arv* a1 = NULL;
    while(scanf("%[^\n]", opc) != EOF){
        getchar();
        if(opc[0] == 'I' && opc[1] == ' '){
            info = convert_int(opc);
            a1=add_busca(a1, info);
        }
        else if(opc[0] == 'P' && opc[1] == ' '){
            info = convert_int(opc);
            i=find(a1,info);
            if(i)
                printf("%hu existe\n", info);
            else
                printf("%hu nao existe\n", info);
        }
        else if(opc[0] == 'R' && opc[1] == ' '){
            a1 = remover(a1, info);
        }

        else if(strcmp(opc,"INFIXA")==0){  
            b = 1;
            print_ord(a1);
            printf("\n");
        }
        else if(strcmp(opc,"PREFIXA")==0){  
            b = 1;
            print_pre(a1);
            printf("\n");
        }
        else if(strcmp(opc,"POSFIXA")==0){  
            b = 1;
            print_pos(a1);
            printf("\n");
        }
    }
    return 0;
}