#ifndef GRAFOMATRIZ_H_INCLUDED
#define GRAFOMATRIZ_H_INCLUDED

#include "estrutura.h"
#include "fila.h"
#include "pilha.h"

#define INFINITO 1000000
#define MEMBRO 1
#define NAOMEMBRO 0

typedef enum {espera, pronto, visitado} tipoStatus;

typedef struct{

    tipo_elemento info;
    int status;

}tipo_vertice;

typedef struct{

    int conectado;
    int peso;

}tipo_aresta;

typedef struct{

    tipo_vertice *vertice;
    tipo_aresta **aresta;
    int numVertice;
    int ordem;

}tipo_grafo;

typedef tipo_grafo *grafo;

/** Cria o grafo */
grafo cria_grafo(int tamanho);

/** Pesquisa se um chave existe na lista de vertice, caso sim, retorna sua posição, caso contrário
retorna -1. */
int pesquisaVertice(grafo g, int chave);

/** Insere um vertice no grafo. Retorna 1 caso a inserção ocorreu sem problemas, 0 caso contrário. */
int insereVertice(grafo g, tipo_vertice vertice);

/** Remove um vertice do grafo. Retorna 1 em caso de remoção ocorreu sem problemas, 0 caso contrário. */
int removeVertice(grafo g, int chave, tipo_vertice *vertice);

/** Insere uma aresta entre as duas chaves passadas(chaveUm e chaveDois). Retorna 1 em caso de sucesso ou 0
caso contrário. */
int insereAresta(grafo g, int chaveUm, int chaveDois, int peso);

/** Remove uma aresta do grafo. Retorna 1 em caso de sucesso ou 0 caso contrário. */
int removeAresta(grafo g, int chaveUm, int chaveDois);

/** Percorre o grafo usando fila. Algoritmo de busca por largura/amplitude. */
int bfs(grafo g, int chave);

/** Percorre o grafo usando pilha. Algoritmo de busca por profundidade. */
int dfs(grafo g, int chave);

/** Acha o menor caminho entre dois vertices. */
int dijkstra(grafo g, int origem, int destino);

/** Verifica se um grafo é completo, ou seja, verifica se todos os vertices tem ligação direta um com o outro.
Retorna 1 em caso de sucesso ou 0 caso contrário.*/
int eCompleto(grafo g);

/** Verifica se todos os vertices do grafo possuem o mesmo grau, ou seja, se todos possuem a mesma quantidade
de arestas. Retorna 1 em caso de sucesso ou 0 caso contrário.*/
int eRegular(grafo g);

/** Verifica se o grafo é conexo, ou seja, se a partir de um vertice é possível chegar em qualquer outro.
Retorna 1 caso seja possivel ou 0 caso contrário. */
int eConexo(grafo g);

/** Verifica se o grafo é parcial, ou seja, a quantidade de verticies é a mesma que a quantidade de arestas.*/
int eParcial(grafo g);

/** Verifica se o grafo possui um circuito. */
int eCircuito(grafo g);

/** Retorna uma lista com os vertices de maior grau em ordem crescente */
int listaGraus(grafo g, tipo_aresta **aresta);

/** Retorna os vertices adjacentes da chave passada. */
int verticesAdjacentes(grafo g, int chave, tipo_vertice **vertice, int *tamanho);

/** Imprime o grafo. */
void imprime(grafo g);

#endif // GRAFOMATRIZ_H_INCLUDED
