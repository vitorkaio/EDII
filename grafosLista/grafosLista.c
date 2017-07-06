#include "grafosLista.h"

// Cria o grafo com o tamanho alocado dinamicamente, ou seja, em tempo de execução.
Grafo criaGrafo(int tamanho){

    Grafo grafo = (Grafo) malloc(sizeof(tipoGrafo));
	int linha;

	// Verifica se a alocação falhou.
	if(!grafo)
		return NULL;

	grafo->vertices = (tipoVertice*) malloc(sizeof(tipoVertice) * tamanho);

	// Verifica se a alocação falhou.
	if(!grafo->vertices){
		free(grafo);
		return NULL;
	}

    // Cria a lista de vertices adjscentes.
    for(linha = 0; linha < tamanho; linha++){
        grafo->vertices[linha].listaDeAresta = cria_lista();
    }

	grafo->numeroVertices = 0;
	grafo->ordem = tamanho;

	return grafo;

}

//********************************************* Pesquisa Vertice *********************************************
int pesquisaVertice(Grafo g, tipoChave chave){

    int contador;

    for(contador = 0; contador < g->numeroVertices; contador++)
        if(g->vertices[contador].info.chave == chave)
            return contador;

    return -1;
}

//********************************************* Insere Vertice *********************************************
int insereVertice(Grafo g, tipoVertice vertice){

    if(g->ordem == g->numeroVertices)
        return 0;

    // Verifica se já existe um vertice com essa chave no grafo.
    if(pesquisaVertice(g, vertice.info.chave) != -1)
        return 0;

    // Verifica se o grafo já atingiu o limite de vertices.
    if(g->numeroVertices == g->ordem)
        return 0;

    g->vertices[g->numeroVertices].info = vertice.info;
    g->vertices[g->numeroVertices].status = vertice.status;

    g->numeroVertices++;

    return 1;

}

//********************************************* Remove Vertice *********************************************
int removeVertice(Grafo g, tipoChave chave, tipoVertice *vertice){

    // Pesquisa se o vértice existe no grafo.
    int pos, contador;
    tipoAresta aresta;
    pos = pesquisaVertice(g, chave);

    if(pos == -1)
        return 0;

    // Remover todas as arestar da chave.
    for(contador = 0; contador < g->numeroVertices; contador++){
        //if(removeAresta(g, chave, g->vertices[contador].info.chave) == 0)
        remove_lista(g->vertices[contador].listaDeAresta, chave, &aresta);

    }

    *vertice = g->vertices[pos];

    g->numeroVertices -= 1;
    g->vertices[pos] = g->vertices[g->numeroVertices];

    return 1;

}

//********************************************* Insere Aresta *********************************************
int insereAresta(Grafo g, tipoChave chaveUm, tipoChave chaveDois, int peso){

    tipoAresta arestaUm, arestaDois;
    int posUm, posDois;

    arestaUm.verticeAdjacente = chaveDois;
    arestaUm.peso = peso;

    arestaDois.verticeAdjacente = chaveUm;
    arestaDois.peso = peso;

    // Pesquisa a posição do vertice 1(chaveUm) e do vertice 2(chaveDois)
    posUm = pesquisaVertice(g, chaveUm);

    if(posUm == -1)
        return 0;

    posDois = pesquisaVertice(g, chaveDois);

    if(posDois == -1)
        return 0;

    if(insere_lista(g->vertices[posUm].listaDeAresta, arestaUm) == 0)
        return 0;

    if(insere_lista(g->vertices[posDois].listaDeAresta, arestaDois) == 0)
        return 0;

    return 1;

}

//********************************************* Remove Aresta *********************************************
int removeAresta(Grafo g, tipoChave chaveUm, tipoChave chaveDois){

    int posUm, posDois;
    tipoAresta aresta;

    posUm = pesquisaVertice(g, chaveUm);
    posDois = pesquisaVertice(g, chaveDois);

    if(posUm == -1 || posDois == -1)
        return 0;

    if(remove_lista(g->vertices[posUm].listaDeAresta, chaveDois, &aresta) == 0)
        return 0;

    if(remove_lista(g->vertices[posDois].listaDeAresta, chaveUm, &aresta) == 0)
        return 0;

    return 1;

}

//********************************************* Print Grafo *********************************************
void imprimeGrafo(Grafo g){

    int contador;

    for(contador = 0; contador < g->numeroVertices; contador++){
        printf("\n\n Vertice: [%d] -> ", g->vertices[contador].info.chave);

        imprimeLista(g->vertices[contador].listaDeAresta);
    }

}

//********************************************* BFS *********************************************
int bfs(Grafo grafo, tipoChave chave){

    fila f = criaFila();
	tipo_elemento elemento;
	int i, origem;

	origem = pesquisaVertice(grafo, chave);
	if(origem == -1)
        return 0;


	for(i = 0; i < grafo->numeroVertices; i++)
		grafo->vertices[i].status = espera;

	elemento.chave = grafo->vertices[origem].info.chave;
	grafo->vertices[origem].status = espera;
	grafo->vertices[origem].status = visitado;

	enfilera(f, elemento);

	while(!filaVazia(f)){
		desenfilera(f, &elemento);
		int k = pesquisaVertice(grafo, elemento.chave);

		for(i = 0; i < grafo->numeroVertices; i++)
            // Na matriz é assim: grafo->aresta[k][i].conectado && grafo->vertices[i].status == espera
			if(pesquisa_lista(grafo->vertices[i].listaDeAresta, grafo->vertices[k].info.chave) == 1
                && grafo->vertices[i].status == espera){

                    elemento.chave = grafo->vertices[i].info.chave;
                    printf(" no = %d\n", elemento.chave);
                    enfilera(f, elemento);
                    grafo->vertices[i].status = pronto;
			}
	}// while

		terminaFila(f);
	return 1;

}

//********************************************* DFS *********************************************
int dfs(Grafo grafo, tipoChave chave){

	int v = pesquisaVertice(grafo, chave), i, k;

	if(v == -1)
        return 0;

	pilha p = cria_pilha();
	tipo_elemento e;

	for(i = 0; i < grafo->numeroVertices; i++)
		grafo->vertices[i].status = espera;

	grafo->vertices[v].status = visitado;
	e.chave = chave;

	push(p, e);

	while(!vazia(p)){

		peek(p, &e);

        k = pesquisaVertice(grafo, e.chave);

        for(i = 0; i < grafo->numeroVertices; i++){
            if(pesquisa_lista(grafo->vertices[i].listaDeAresta, grafo->vertices[k].info.chave) == 1 &&
                grafo->vertices[i].status == espera){

                v = i;
                break;

            }

            else
                v = -1;
        }

		if(v == -1)
			pop(p, &e);

		else{
			grafo->vertices[v].status = visitado;
			e.chave = grafo->vertices[v].info.chave;
			push(p, e);
			printf(" no = %d\n", e.chave);
		}

	}

	return 1;
}

//********************************************* DIJKSTRA *********************************************
int dijkstra(Grafo g, tipoChave origem, tipoChave destino){

    int *dist, *per, *path;
    int corrente, s, t, i, k, dc, j;
    int menor_dist, nova_dist,caminho;
    tipoAresta aresta;

    dist = (int*) malloc(sizeof(int) * g->ordem);
    per = (int*) malloc(sizeof(int) * g->ordem);
    path = (int*) malloc(sizeof(int) * g->ordem);

    for (i = 0; i < g->numeroVertices; i++) {
        per[i] = NAOMEMBRO;
        dist[i] = INFINITO;
    }

    s = pesquisaVertice(g, origem);
    t = pesquisaVertice(g, destino);

    if(s == -1 || t == -1)
        return 0;

    per[s] = MEMBRO;
    dist[s] = 0;
    corrente = s;
    k = corrente;

    while (corrente != t){

        menor_dist = INFINITO;
        dc = dist[corrente];

        for (i = 0; i < g->numeroVertices; i++){

            j = pesquisa_lista_dijkistra(g->vertices[corrente].listaDeAresta, g->vertices[i].info.chave);

            if (per[i] == NAOMEMBRO && j != 0){

                pegaElemento(g->vertices[corrente].listaDeAresta, &aresta, j);
                nova_dist = dc + aresta.peso;

                if (nova_dist < dist[i]){

                    dist[i] = nova_dist;
                    path[i] = corrente;
                }
            }
        }

        menor_dist = INFINITO;

        for (i = 0; i < g->numeroVertices; i++){

            if (per[i] == NAOMEMBRO && dist[i] < menor_dist){

                k = i;
                menor_dist = dist[i];
            }
        }

        corrente = k;
        per[corrente] = MEMBRO;
    }

    printf("\nCaminho: ");
    caminho = t;
    printf("%d <- ", g->vertices[t].info.chave);

    while (caminho != s){

        printf("%d", g->vertices[(path[caminho])].info.chave);
        caminho = path[caminho];

        if (caminho != s)
            printf (" <- ");

    }

    printf("\nDistancia: %d\n", dist[t]);
    free(dist);
    free(per);
    free(path);

    return 1;

}

//********************************************* eCompleto *********************************************
int eCompleto(Grafo g){

    int i, k;

    for(k = 0; k < g->numeroVertices; k++)
    for(i = 0; i < g->numeroVertices; i++){

        if(i == k)
            continue;

        else if(pesquisa_lista(g->vertices[i].listaDeAresta, k) == 0)
            return 0;

    }

    return 1;
}

//********************************************* eRegular *********************************************
int eRegular(Grafo g){

    int contador;
    int tamanho;

    tamanho = g->vertices[0].listaDeAresta->tamanho;

    for(contador = 1; contador < g->numeroVertices; contador++)
        if(tamanho != g->vertices[contador].listaDeAresta->tamanho)
            return 0;

    return 1;
}

//********************************************* eConexo *********************************************
int eConexo(Grafo g){

    fila f;
    int origem, contador, i, k;
    tipo_elemento elemento;

    f = criaFila();

    if(!f)
        return 0;

    origem = pesquisaVertice(g, g->vertices[0].info.chave);

    if(origem == -1)
        return 0;

    for(i = 0; i < g->numeroVertices; i++)
        g->vertices[i].status = 0;

    elemento = g->vertices[origem].info;
    g->vertices[origem].status = 1;
    contador = 1;

    enfilera(f, elemento);

    while(!filaVazia(f)){

        desenfilera(f, &elemento);

        k = pesquisaVertice(g, elemento.chave);

        for(i = 0; i < g->numeroVertices; i++)
            if(pesquisa_lista(g->vertices[i].listaDeAresta, g->vertices[k].info.chave) == 1 &&
            g->vertices[i].status == 0){

                elemento = g->vertices[i].info;
                contador++;
                enfilera(f, elemento);
                g->vertices[i].status = 1;
            }
    }

    if(g->numeroVertices != contador)
        return 0;

    return 1;

}

//********************************************* lista grau *********************************************
int listaGraus(Grafo g, tipoAresta **aresta){

    int i, k;
    tipoAresta aux;
    *aresta = (tipoAresta*)malloc(g->numeroVertices * sizeof(tipoAresta));

    if(!aresta)
        return 0;

    for(i = 0; i < g->numeroVertices; i++){
        (*aresta)[i].verticeAdjacente = g->vertices[i].info.chave;
        (*aresta)[i].peso = g->vertices[i].listaDeAresta->tamanho;
    }

    // Ordena o vetor.
    for(i = 0; i < g->numeroVertices; i++){
        for(k = 0; k < g->numeroVertices; k++)
        if((*aresta)[k].peso < (*aresta)[i].peso){
            aux = (*aresta)[k];
            (*aresta)[k] = (*aresta)[i];
            (*aresta)[i] = aux;
        }

    }

    return 1;

}

//********************************************* e parcial *********************************************
int eParcial(Grafo g){

    int i, contador = 0;

    for(i = 0; i < g->numeroVertices; i++)
        contador += g->vertices[i].listaDeAresta->tamanho;

    contador /= 2;

    if(contador != g->numeroVertices)
        return 0;

    return 1;

}

//********************************************* tem circuito *********************************************
int temCircuito(Grafo g){

    pilha p;
    tipo_elemento e;
    int origem, i, k, aux, v;

    p = cria_pilha();

    if(!p)
        return 0;

    origem = pesquisaVertice(g, g->vertices[0].info.chave);

    if(origem == -1)
        return 0;


    for(i = 0; i < g->numeroVertices; i++)
        g->vertices[i].status = 0;

    e = g->vertices[origem].info;
    g->vertices[origem].status = 1;

    push(p, e);

    while(!vazia(p)){

        peek(p, &e);
        k = pesquisaVertice(g, e.chave);

        for(i = 0; i < g->numeroVertices; i++){

                if(i == k)
                    continue;

            if(pesquisa_lista(g->vertices[i].listaDeAresta, g->vertices[k].info.chave) == 1 &&
               g->vertices[i].status == 0){

                    v = i;
                    break;

               }

               else
                v = -1;
        }

        if(v == -1){

            pop(p, &e);

            for(aux = 0; aux < g->numeroVertices; aux++)
                if(g->vertices[aux].status == 0)
                    return 1;

        }

        else{
            e = g->vertices[v].info;
            // print.
            g->vertices[v].status = 1;
            push(p, e);
        }


    }


    return 0;
}
