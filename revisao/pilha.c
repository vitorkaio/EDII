#include "pilha.h"

Pilha criaPilha(){

    Pilha p;
    p = (Pilha)malloc(sizeof(tipoPilha));

    if(!p)
        return NULL;

    p->topo = NULL;
    p->quantidade = 0;

    return p;

}// Fim criaPilha()

int pilhaVazia(Pilha p){

    if(p->quantidade == 0)
        return 1;

    return 0;

}// Fim pilhaVazia()

int push(Pilha p, tipoElemento e){

    if(!p)
        return 0;

    tNodoPilha no;

    no = (tNodoPilha)malloc(sizeof(tipoNodoPilha));

    if(!no)
        return 0;

    else{

        no->elemento = e;

        // Verifica se existe algum no na pilha.
        if(p->topo == NULL){
            no->proximo = p->topo;
            p->topo = no;
            p->quantidade++;
            return 1;
        }

        else{
            no->proximo = p->topo;
            p->topo = no;
            p->quantidade++;
            return 1;
        }

    }

    return 1;

}// Fim push

int pop(Pilha p, tipoElemento *e){

    if(pilhaVazia(p) == 1)
        return 0;

    tNodoPilha no;
    no = p->topo;

    p->topo = no->proximo;
    p->quantidade--;

    *e = no->elemento;
    free(no);

    return 1;

}
