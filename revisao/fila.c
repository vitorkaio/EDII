#include "fila.h"

Fila criaFila(){

    Fila f;

    f = (Fila)malloc(sizeof(tipoFila));

    if(f){

        f->inicio = NULL;
        f->fim = NULL;
        f->quantidade = 0;
        return f;
    }

    return NULL;
}

int filaVazia(Fila f){

    if(f->quantidade == 0)
        return 1;

    return 0;

}

int enfileira(Fila f, tipoElemento e){

    // f == NULL
    if(!f)
        return 0;

    tNodo no;

    no = (tNodo)malloc(sizeof(tipoNodo));

    // no != NULL
    if(no){

        no->elemento = e;

        // Se n�o houver nodos cadastrados, ent�o cadastra.
        if(f->inicio == NULL){

            no->proximo = f->inicio;
            f->inicio = no;
            f->fim = no;
            f->quantidade++;

            return 1;

        }

        else{

            no->proximo = f->fim->proximo;
            f->fim->proximo = no;
            f->fim = no;
            f->quantidade++;

            return 1;

        }

    }

    return 0;

}

int desinfileira(Fila f, tipoElemento *e){

    tNodo no;

    if(filaVazia(f) == 1)
        return 0;

    no = f->inicio;
    f->inicio = no->proximo;

    // Lembrar de colocar o * para guardar o valor.
    *e = no->elemento;
    free(no);
    f->quantidade--;

    return 1;

}


int tamanhoFila(Fila f){

    return f->quantidade;

}


void imprimeFila(Fila f){

    tNodo no;

    if(!f){
        printf("\nFila n�o foi criada\n");
        return;
    }

    if(f->quantidade == 0){
        printf("\nFila vazia\n");
        return;
    }

    no = f->inicio;
    printf("\nFila:\n");
    while(no){

        //printf("\n\n\n Dados \n Nome: %s\n id: %ld", no->elemento.nome, no->elemento.id);
        printf("[%d]", no->elemento);
        no = no->proximo;

    }

    printf("\n\n");

}
