#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int tipoElemento;

typedef struct nodoPilha{
    struct nodoPilha *proximo;
    tipoElemento elemento;
}tipoNodoPilha;

typedef tipoNodoPilha *tNodoPilha;

typedef struct{
    tNodoPilha topo;
    int quantidade;
}tipoPilha;

typedef tipoPilha *Pilha;

Pilha criaPilha();
int pilhaVazia(Pilha p);
int push(Pilha p, tipoElemento e);
int pop(Pilha p, tipoElemento *e);
int tamanhoPilha(Pilha p);

#endif // PILHA_H_INCLUDED
