#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*typedef struct{

    char nome[30];
    int quantidade;
    long id;
    float preco;

}tipoElemento;*/

typedef int tipoElemento;

typedef struct nodo{

    tipoElemento elemento;
    struct nodo *proximo;

}tipoNodo;

typedef tipoNodo *tNodo;

typedef struct{

    tNodo inicio, fim;
    int quantidade;

}tipoFila;

typedef tipoFila *Fila;


Fila criaFila();
int filaVazia(Fila f);
int enfileira(Fila f, tipoElemento e);
int desinfileira(Fila f, tipoElemento *e);
int filaCheia(Fila f);
int tamanhoFila(Fila f);
void imprimeFila(Fila f);


#endif // FILA_H_INCLUDED
