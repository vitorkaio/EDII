#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#include "Estrutura.h"

typedef struct nodo{
    tipo_elemento info;
    struct nodo *prox;
}tipo_nodo;

typedef struct{
    tipo_nodo *incio, *fim;
    int tamanho;
}tipo_fila;

typedef tipo_fila *fila;

fila criaFila();

void terminaFila(fila);
int enfilera(fila, tipo_elemento);
int desenfilera(fila, tipo_elemento*);
int filaCheia(fila);
int filaVazia(fila);
int tamanho(fila);

#endif // FILA_H_INCLUDED
