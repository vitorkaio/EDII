#ifndef GRAFOSLISTA_H_INCLUDED
#define GRAFOSLISTA_H_INCLUDED

#include "lista_encadeada.h"
#include "fila_prioridades.h"
#include "fila.h"
#include "pilha.h"

#define INFINITO 1000000
#define MEMBRO 1
#define NAOMEMBRO 0

typedef enum {espera, pronto, visitado} tipoStatus;


// Cria a estrutura para armazenamentos dos vértices do grafo.
typedef struct{

    tipo_elemento info;
    tipoStatus status;

    // Lista com as arestas do vertice.
    lista listaDeAresta;

}tipoVertice;


// Cria  a estrutra grafo;
typedef struct{

    tipoVertice *vertices;

    int numeroVertices, ordem;

}tipoGrafo;

typedef tipoGrafo *Grafo;

/** Cria o grafo com o tamanho alocado dinamicamente, ou seja, em tempo de execução.*/
Grafo criaGrafo(int tamanho);

/** Insere vertices no grafo.*/
int insereVertice(Grafo g, tipoVertice vertice);

/** Pesquisa se um vértice já existe no grafo.*/
int pesquisaVertice(Grafo g, tipoChave chave);

/** Remove um vértice do grafo.*/
int removeVertice(Grafo g, tipoChave chave, tipoVertice *vertice);

/** Insere uma aresta*/
int insereAresta(Grafo g, tipoChave chaveUm, tipoChave chaveDois, int peso);

/** Remove uma aresta. */
int removeAresta(Grafo g, tipoChave chaveUm, tipoChave chaveDois);

/** Imprime o grafo */
void imprimeGrafo(Grafo g);

/** Busca em largura/amplitude */
int bfs(Grafo grafo, tipoChave chave);

/** Busca em profundidade */
int dfs(Grafo grafo, tipoChave chave);

/** Melhor caminho */
int dijkstra(Grafo g, tipoChave origem, tipoChave destino);

/** Verifica se o grafo e completo, ou seja, se todos os vertices estão conectados um com outro. */
int eCompleto(Grafo g);

/** Verifica se todos os vertices possuem o mesmo grau, ou seja, tenham mesma quantidade de arestas. */
int eRegular(Grafo g);

/** Verifica se o grafo é conexo ou desconexo */
int eConexo(Grafo g);

/** Verifica se o grafo é parcial. */
int eParcial(Grafo g);

/** Verifica se tem circuito. */
int temCircuito(Grafo g);

/** Retorna uma lista com os vertices de maior grau em ordem crescente */
int listaGraus(Grafo g, tipoAresta **aresta);

#endif // GRAFOSLISTA_H_INCLUDED
