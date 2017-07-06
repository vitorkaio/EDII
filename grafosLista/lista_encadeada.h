#ifndef LISTA_ENCADEADA_H_INCLUDED
#define LISTA_ENCADEADA_H_INCLUDED

#include "Estrutura.h"

// Cria as arestas do grafo
typedef struct{
    int verticeAdjacente; // Qual vertice está conectado.
    int peso; // Para verificar o grafo ponderado.
}tipoAresta;

typedef struct nodo {
  tipoAresta aresta;
  struct nodo *prox;

} tipo_nodo;

typedef struct{

   tipo_nodo *primeiro, *ultimo;
   int tamanho;

} tipo_lista;

typedef tipo_lista *lista;

lista cria_lista();

// Insere uma tipoAresta na lista.
int insere_lista(lista, tipoAresta);

// Remove uma tipoAresta da lista.
int remove_lista(lista, int, tipoAresta*);

int pesquisa_lista(lista, int);

int pesquisa_lista_dijkistra(lista, int);

void termina_lista(lista);

int pegaElemento(lista l, tipoAresta *a, int indice);

void imprimeLista(lista);



#endif // LISTA_ENCADEADA_H_INCLUDED
