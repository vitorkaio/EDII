#include "grafosLista.h"

#define ORDEM 7

#define ORIGEM 0
#define DESTINO 5

int main(){

    Grafo g;
    tipoVertice vertice;
    tipoAresta *grau;
    int contador;

    g = criaGrafo(ORDEM);

    if(!g){
        printf("\n Erro ao criar grafo!!!");
        return 0;
    }

    printf("\n**************** Grafo Criado ****************");

    //************************************* Insere Vertices *************************************
    for(contador = 0; contador < ORDEM; contador++){
        vertice.info.chave = contador;
        vertice.status = 0;
        insereVertice(g, vertice);
    }

    //************************************* Inserindo Arestas *************************************

    /*insereAresta(g, 0, 1, 10);
    insereAresta(g, 0, 3, 10);

    insereAresta(g, 1, 2, 10);

    insereAresta(g, 2, 3, 10);*/

    insereAresta(g, 0, 1, 2);
    insereAresta(g, 0, 4, 5);
    insereAresta(g, 0, 6, 1);

    insereAresta(g, 1, 4, 1);
    insereAresta(g, 1, 2, 8);

    insereAresta(g, 2, 3, 4);

    insereAresta(g, 3, 4, 3);
    insereAresta(g, 3, 5, 2);

    imprimeGrafo(g);

    //************************************* BFS *************************************
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

    // ***** Verifica se o grafo é COMPLETO.
    contador = eCompleto(g);

    if(contador == 0)
        printf("\n Grafo nao e completo\n");
    else
        printf("\n Grafo e completo\n");

    // ***** Verifica se o grafo é REGULAR.
    contador = eRegular(g);

    if(contador == 0)
        printf("\n Grafo nao e regular\n");
    else
        printf("\n Grafo e regular\n");

    // ***** Verifica se o grafo é CONEXO.
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

         // ***** Verifica se o grafo tem circuito.
    contador = temCircuito(g);

    if(contador == 0)
        printf("\n Grafo nao tem circuito\n");
    else
        printf("\n Grafo tem circuito\n");

    // ***** Lista de vertices de maiores graus.
    printf("\n\n**************** Lista de grau vertices ****************\n");
    if(listaGraus(g, &grau) == 0)
        printf("\n Erro na lista de grau \n");
    else
        for(contador = 0; contador < g->numeroVertices; contador++)
            printf("\n Vertice: [%d] -> grau: %d\n", grau[contador].verticeAdjacente, grau[contador].peso);


    // Remoção de um vertice.
    printf("\n\n**************** Remocao do vertice: %d ****************\n", ORIGEM);

    removeVertice(g, ORIGEM, &vertice);
    imprimeGrafo(g);

    return 0;
}
