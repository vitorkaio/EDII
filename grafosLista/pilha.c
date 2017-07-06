#include "pilha.h"

#include <stdio.h>
#include <stdlib.h>

pilha cria_pilha()
{
    pilha p;
    p= (pilha)malloc(sizeof(tipo_pilha));
    if (p)
    {

        p->topo = NULL;
        p->tamanho =0;
        return p;
    }
    return 0;
}

int termina_pilha(pilha *p)
{
    tipo_nodo_pilha *a;
    while((*p)->topo)
    {
        a = (*p)->topo;
        (*p)->topo = a->next;
        free(a);
    }
    free(*p);
    return 1;
}

int vazia(pilha p){
    if (p->topo==NULL)
        return 1;
    return 0;
}

int push(pilha p, tipo_elemento e)
{
    tipo_nodo_pilha *a;
    a = (tipo_nodo_pilha *) malloc(sizeof(tipo_nodo_pilha));
    if (a)
    {
        a->info = e;
        a->next =p->topo;
        p->topo = a;
        p->tamanho++;
        return 1;
    }
    return 0;
}


int pop(pilha p, tipo_elemento *e)
{
    tipo_nodo_pilha *a;
    if (vazia(p))
        return 0;
    a = p->topo;
    p->topo = p->topo->next;
    *e = a->info;
    free(a);
    p->tamanho--;
    return 1;
}

int peek(pilha p, tipo_elemento *e){
    if (vazia(p))
        return 0;

    *e = p->topo->info;
    return 1;
}
