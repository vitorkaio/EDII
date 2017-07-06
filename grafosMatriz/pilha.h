#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include "Estrutura.h"


typedef struct nodo_pilha{
  struct nodo_pilha *next;
  tipo_elemento info;

}tipo_nodo_pilha;

typedef struct{
  tipo_nodo_pilha *topo;
  int tamanho;

}tipo_pilha;

typedef tipo_pilha *pilha;

pilha cria_pilha();
int vazia(pilha p);
int termina_pilha(pilha *p);
int push(pilha p, tipo_elemento e);
int pop(pilha p, tipo_elemento *e);
int peek(pilha p, tipo_elemento *e);

#endif // PILHA_H_INCLUDED
