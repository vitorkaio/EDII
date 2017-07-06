#include "grafoMatriz.h"

#define ORDEM 7

#define ORIGEM 0
#define DESTINO 2

int main(){

    grafo g;
    tipo_vertice vertice, *vertex;
    tipo_aresta *grau;
    int contador, i;

    g = cria_grafo(ORDEM);

    if(!g){
        printf("\nErro ao criar grafo!!!\n");
        return 0;
    }

    printf("\n**************** Grafo Criado ****************\n");

    // ************************************ Inserindo vertices ************************************
    for(contador = 0; contador < ORDEM; contador++){

        vertice.info.chave = contador;
        vertice.status = 0;

        if(insereVertice(g, vertice) == 0){
            printf("\nFalha ao inserir vertice\n");
            return 0;
        }
    }

    // ************************************ Inserindo aresta ************************************

    insereAresta(g, 0, 1, 2);
    insereAresta(g, 0, 4, 5);
    insereAresta(g, 0, 6, 1);

    insereAresta(g, 1, 4, 1);
    insereAresta(g, 1, 2, 8);

    insereAresta(g, 2, 3, 4);

    insereAresta(g, 3, 4, 3);
    insereAresta(g, 3, 5, 2);

    // ***** Imprime Grafo
    imprime(g);

    // ************************************ BFS ************************************
    printf("\n\n**************** BFS ****************\n");
    printf("\n Origem: %d\n\n", ORIGEM);
    bfs(g, ORIGEM);

    //************************************* DFS *************************************
    printf("\n\n**************** DFS ****************\n");
    printf("\n Origem: %d\n\n", ORIGEM);
    dfs(g, ORIGEM);

     //************************************* Dijkstra *************************************
    printf("\n\n**************** Dijkstra ****************\n");
    printf("\nOrigem: %d\nDestino: %d\n", ORIGEM, DESTINO);
    dijkstra(g, ORIGEM, DESTINO);

    //************************************* Outros *************************************
    printf("\n\n**************** Outros ****************\n");

    // ***** Verifica se o grafo o COMPLETO.
    contador = eCompleto(g);

    if(contador == 0)
        printf("\n Grafo nao e completo\n");
    else
        printf("\n Grafo e completo\n");

    // ***** Verifica se o grafo o REGULAR.
    contador = eRegular(g);

    if(contador == 0)
        printf("\n Grafo nao e regular\n");
    else
        printf("\n Grafo e regular\n");

    // ***** Verifica se o grafo o CONEXO.
    contador = eConexo(g);

    if(contador == 0)
        printf("\n Grafo nao e conexo\n");
    else
        printf("\n Grafo e conexo\n");

    // ***** Verifica se o grafo é parcial.
    contador = eParcial(g);

    if(contador == 0)
        printf("\n Grafo nao e parcial\n");
    else
        printf("\n Grafo e parcial\n");

    // ***** Verifica se o grafo possui um circuito.
    contador = eCircuito(g);

    if(contador == 0)
        printf("\n Grafo nao tem circuito\n");
    else
        printf("\n Grafo tem circuito\n");

    // ***** Lista de vertices de maiores graus.
    printf("\n\n**************** Lista de grau vertices ****************\n");
    if(listaGraus(g, &grau) == 0)
        printf("\n Erro na lista de grau \n");
    else
        for(contador = 0; contador < g->numVertice; contador++)
            printf("\n Vertice: [%d] -> grau: %d\n", grau[contador].conectado, grau[contador].peso);


    // ***** Lista de vertices de adjacentes a chave passada.
    printf("\n\n**************** Lista de vertices adjacentes a chave ****************\n");

    contador = verticesAdjacentes(g, ORIGEM, &vertex, &i);

    if(contador == 0)
        printf("\n Erro ao recuperar vertices adjacentes! \n");

    else{
        printf("\n Vertice: [%d] -> ", ORIGEM);
        for(contador = 0; contador < i; contador++)
            printf("%d, ", vertex[contador].info.chave);
    }

    printf("\n\n");

    return 0;
}

