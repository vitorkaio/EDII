#ifndef FILA_PRIORIDADES_H_INCLUDED
#define FILA_PRIORIDADES_H_INCLUDED
#include "Estrutura.h"

typedef struct{
    int numElementos,tamanho;
    tipo_elemento *v;

}tipo_fila_prioridade;

typedef tipo_fila_prioridade *fila_prioridade;

fila_prioridade cria_fila_prioridade(int);
int insere(fila_prioridade,tipo_elemento);
int  aumentaChave(int, tipoChave, fila_prioridade);
int retira(fila_prioridade,tipo_elemento*);
int getTamanho(fila_prioridade);
void termina(fila_prioridade );
#endif // FILA_PRIORIDADES_H_INCLUDED
