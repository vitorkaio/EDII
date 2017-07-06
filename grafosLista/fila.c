#include "fila.h"

#include <stdio.h>
#include <stdlib.h>


fila criaFila(){
    fila f = (fila) malloc(sizeof(tipo_fila));

    if(f){
        f->incio = NULL;
        f->fim = NULL;
        f->tamanho = 0;
    }

    return f;
} //

void terminaFila(fila f){
    nodos *p;

    while(f->incio){
        p = f->incio;
        f->incio = p->prox;
        free(p);
    }
    free(f);
} // terminafila()

int enfilera(fila f, tipo_elemento e){
    nodos *p = (nodos*) malloc(sizeof(nodos));

    if(!p)
        return 0;

    p->info = e;
    p->prox = NULL;

    if(!f->incio) // f->inicio == NULL
        f->incio = p;
    else
        f->fim->prox = p;

    f->fim = p;
    f->tamanho++;

    return 1;
} //

int desenfilera(fila f, tipo_elemento *e){
    nodos *p;

    if(f->incio == NULL)
        return 0;

    p = f->incio;
    *e = p->info;
    f->incio = p->prox;
    free(p);
    f->tamanho--;

    return 1;

} //

int filaCheia(fila f){
    nodos *p = (nodos*) malloc(sizeof(nodos));

    if(p){
        free(p);
        return 0;
    }

    return 1;
} //

int filaVazia(fila f){
    return !f->tamanho;
} //

int tamanho(fila f){
    return f->tamanho;
} //
