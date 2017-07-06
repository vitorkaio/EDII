#include "grafoMatriz.h"

grafo cria_grafo(int tamanho){

    int linha, coluna;
    grafo g;

    g = (grafo)malloc(sizeof(tipo_grafo));

    if(!g)
        return NULL;

    g->vertice = (tipo_vertice *)malloc(tamanho * sizeof(tipo_vertice));

    if(!g->vertice){
        free(g);
        return NULL;
    }

    g->aresta = (tipo_aresta **)malloc(tamanho * sizeof(tipo_aresta*));

    if(!g->aresta){
        free(g->vertice);
        free(g);
        return NULL;
    }

    for(linha = 0; linha < tamanho; linha++){

        g->aresta[linha] = (tipo_aresta*)malloc(tamanho * sizeof(tipo_aresta));

        for(coluna = 0; coluna < tamanho; coluna++){
            g->aresta[linha][coluna].conectado = 0;
            g->aresta[linha][coluna].peso = 0;
        }

    }

    g->numVertice = 0;
    g->ordem = tamanho;
    return g;
}

//********************************************* Pesquisa Vertice *********************************************
int pesquisaVertice(grafo g, int chave){

    int contador;

    for(contador = 0; contador < g->numVertice; contador++)
        if(g->vertice[contador].info.chave == chave)
            return contador;


    return -1;

}

//********************************************* Insere Vertice *********************************************
int insereVertice(grafo g, tipo_vertice vertice){

    if(pesquisaVertice(g, vertice.info.chave) != -1)
        return 0;

    // Verifica se o número de vertice atingiu o limite.
    if(g->ordem == g->numVertice)
        return 0;

    g->vertice[g->numVertice++] = vertice;

    return 1;
}

//********************************************* Remove Vertice *********************************************
int removeVertice(grafo g, int chave, tipo_vertice *vertice){

    int contador;
    int pos = pesquisaVertice(g, chave);

    if(pos == -1)
        return -1;

    *vertice = g->vertice[pos];

    g->numVertice -= 1;
    g->vertice[pos] = g->vertice[g->numVertice];

    for(contador = 0; contador < g->numVertice; contador++){
        g->aresta[contador][pos] = g->aresta[g->numVertice][pos];
        g->aresta[pos][contador] = g->aresta[pos][g->numVertice];
    }

    return 1;
}

//********************************************* Insere Aresta *********************************************
int insereAresta(grafo g, int chaveUm, int chaveDois, int peso){

    int posUm, posDois;

    // Evitar loop
    if(chaveUm == chaveDois)
        return 0;

    posUm = pesquisaVertice(g, chaveUm);

    if(pesquisaVertice(g, posUm) == -1)
        return 0;


    posDois = pesquisaVertice(g, chaveDois);

    if(pesquisaVertice(g, posDois) == -1)
        return 0;


    g->aresta[posUm][posDois].conectado = 1;
    g->aresta[posUm][posDois].peso = peso;

    g->aresta[posDois][posUm].conectado = 1;
    g->aresta[posDois][posUm].peso = peso;

    return 1;

}

//********************************************* Remove Aresta *********************************************
int removeAresta(grafo g, int chaveUm, int chaveDois){

     int posUm, posDois;

    // Evitar loop
    if(chaveUm == chaveDois)
        return 0;

    posUm = pesquisaVertice(g, chaveUm);

    if(pesquisaVertice(g, posUm) == -1)
        return 0;


    posDois = pesquisaVertice(g, chaveDois);

    if(pesquisaVertice(g, posDois) == -1)
        return 0;


    g->aresta[posUm][posDois].conectado = 0;
    g->aresta[posUm][posDois].peso = 0;

    g->aresta[posDois][posUm].conectado = 0;
    g->aresta[posDois][posUm].peso = 0;

    return 1;

}

//********************************************* BFS *********************************************
int bfs(grafo g, int chave){

    fila f = criaFila();
	tipo_elemento elemento;
	int i, origem;

	if(!f)
        return 0;

	//int contadorConectado;

	origem = pesquisaVertice(g, chave);

	if(origem == -1)
        return 0;


	for(i = 0; i < g->numVertice; i++)
		g->vertice[i].status = 0;

	elemento = g->vertice[origem].info;
	g->vertice[origem].status = 1;

	//contadorConectado = 1;

	enfilera(f, elemento);

	while(filaVazia(f) == 0){
		desenfilera(f, &elemento);
		int k = pesquisaVertice(g, elemento.chave);

		for(i = 0; i < g->numVertice; i++)
			if(g->aresta[k][i].conectado == 1 && g->vertice[i].status == 0){
				elemento = g->vertice[i].info;
				printf(" no = %d\n", elemento.chave);
				//contadorConectado++;
				enfilera(f, elemento);
				g->vertice[i].status = 1;
			}
	}// while

    terminaFila(f);

    //if(contadorConectado != g->numVertice)
        //return 0;

	return 1;

}

//********************************************* DFS *********************************************
int dfs(grafo g, int chave){

	int v = pesquisaVertice(g, chave), i, k;

	if(v == -1)
        return 0;

	pilha p = cria_pilha();

	tipo_elemento e;

	for(i = 0; i < g->numVertice; i++)
		g->vertice[i].status = 0;

	g->vertice[v].status = 1;
	e.chave = chave;

	//printf("Chave = %d\n", e.chave);
	push(p, e);

	while(!vazia(p)){

		peek(p, &e);

        k = pesquisaVertice(g, e.chave);

        for(i = 0; i < g->numVertice; i++){
            if(g->aresta[k][i].conectado == 1 && g->vertice[i].status == 0){
                v = i;
                break;
            }
            else
                v = -1;
        }

		if(v == -1)
			pop(p, &e);

		else{
			g->vertice[v].status = 1;
			e.chave = g->vertice[v].info.chave;
			push(p, e);
			printf(" no = %d\n", e.chave);
		}

	}

	return 1;
}

//********************************************* DIJKSTRA *********************************************
int dijkstra(grafo g, int origem, int destino){


	int *dist, *per ,*path;
	int corrente, s,t,i, k, dc;
	int menor_dist, nova_dist,caminho;

	s = pesquisaVertice(g,origem);
	t = pesquisaVertice(g,destino);

	if(s==-1||t==-1)
		return 0;

	dist =(int*)malloc(sizeof(int)*g->numVertice);
	per =(int*)malloc(sizeof(int)*g->numVertice);
	path =(int*)malloc(sizeof(int)*g->numVertice);

	for (i = 0; i < g->numVertice; i++) {
		per[i] = NAOMEMBRO;
		dist[i] = INFINITO;
	}
	per[s] = MEMBRO;
	dist[s] = 0;

	corrente = s;
	k = corrente;

	while (corrente != t) {

		menor_dist = INFINITO;
		dc = dist[corrente];

		for (i = 0; i < g->numVertice; i++)
		{
			if (per[i] == NAOMEMBRO && g->aresta[corrente][i].conectado)
			{

				nova_dist = dc + g->aresta[corrente][i].peso;

				if (nova_dist < dist[i])
				{
					dist[i] = nova_dist;
					path[i] = corrente;
				}


				/*if (dist[i] < menor_dist)
               {
                   menor_dist = dist[i];
                   k = i;
               }*/
			}

		}

		menor_dist = INFINITO;
		for(i = 0; i < g->numVertice; i++)
			if(per[i] == NAOMEMBRO && dist[i]<menor_dist){
				k = i;
				menor_dist = dist[i];
			}

		corrente = k;
		per[corrente] = MEMBRO;

	}

	printf("\n\nRESULTADO: ");
	caminho = t;

	printf("%d <- ", t);

	while (caminho != s)
	{
		printf("%d", path[caminho]);
		caminho = path[caminho];

		if (caminho != s)
			printf (" <- ");
	}

	printf("\n\ncusto: %d\n\n", dist[t]);
	free(dist);
	free(per);
	free(path);
	return 1;


}

//********************************************* eCompleto *********************************************
int eCompleto(grafo g){

    int linha, coluna;

    for(linha = 0; linha < g->numVertice; linha++)
        for(coluna = 0; coluna < g->numVertice; coluna++){

            if(g->aresta[linha][coluna].conectado == 0){
                if(linha == coluna)
                    continue;
                else
                    return 0;
            }

    }

    return 1;

}

//********************************************* eRegular *********************************************
int eRegular(grafo g){

    int vet[g->numVertice];
    int linha, coluna;

    for(linha = 0; linha < g->numVertice; linha++){

        vet[linha] = 0;

        for(coluna = 0; coluna < g->numVertice; coluna++){

                if(g->aresta[linha][coluna].conectado == 1)
                    vet[linha] += 1;

        }
    }

    // Verifica se existe valores diferentes.
    for(linha = 0; linha < g->numVertice; linha++)
    for(coluna = 0; coluna < g->numVertice; coluna++){
        if(vet[linha] != vet[coluna])
            return 0;
    }

    return 1;

}

//********************************************* eConexo *********************************************
int eConexo(grafo g){

    // Para verificar se um grafo é conexo, basta utilizar o bfs e incrementar uma variavel(contador) toda vez
    // que um vertice é encontrado, depois verificar no final se o contador é o mesmo que a quantidade de
    // vertice do grafo, caso não seja, é pq algum vertice não foi alcançado e por isso o grafo é desconexo.

    fila f;
    int i, k, origem, contador;
    tipo_elemento elemento;

    f = criaFila();

    if(!f)
        return 0;


    origem = pesquisaVertice(g, 0);

    if(origem == -1)
        return 0;


    for(i = 0; i < g->numVertice; i++)
        g->vertice[i].status = 0;

    elemento = g->vertice[origem].info;
    g->vertice[origem].status = 1;
    contador = 1;

    enfilera(f, elemento);

    while(!filaVazia(f)){

        desenfilera(f, &elemento);
        k = pesquisaVertice(g, elemento.chave);

        for(i = 0; i < g->numVertice; i++){
            if(g->aresta[k][i].conectado == 1 && g->vertice[i].status == 0){
                elemento = g->vertice[i].info;
                contador++;
                enfilera(f, elemento);
                g->vertice[i].status = 1;
            }
        }

    }

    if(contador != g->numVertice)
        return 0;

    return 1;

}

//********************************************* eParcial *********************************************
int eParcial(grafo g){

    // Passa por toda a matriz e soma em um contador todas as arestas conectadas e no final
    // divide por dois e compara com a quantidade de vertices.

    int i, k, contador = 0;

    for(i = 0; i < g->numVertice; i++)
        for(k = 0; k < g->numVertice; k++)
            if(g->aresta[i][k].conectado == 1)
                contador++;

    contador = contador / 2;

    if(contador != g->numVertice)
        return 0;

    return 1;

}

//********************************************* lista grau *********************************************
int listaGraus(grafo g, tipo_aresta **aresta){

    int i, k;
    tipo_aresta aux;

    *aresta = (tipo_aresta*)malloc(g->numVertice * sizeof(tipo_aresta));

    if(!aresta)
        return 0;

    // Inicializa o vetor de aresta com zero no peso.
    for(i = 0; i < g->numVertice; i++){
        (*aresta)[i].conectado = g->vertice[i].info.chave;
        (*aresta)[i].peso = 0;
    }

    // Percorre linha e coluna e toda vez que achar um vertice conectado(1) incrementa o array de aresta.
    for(i = 0; i < g->numVertice; i++)
        for(k = 0; k < g->numVertice; k++){
            if(g->aresta[i][k].conectado == 1){
            (*aresta)[i].conectado = g->vertice[i].info.chave;
            (*aresta)[i].peso += 1;
        }
    }

    // Ordena o vetor.
    for(i = 0; i < g->numVertice; i++){
        for(k = 0; k < g->numVertice; k++)
        if((*aresta)[k].peso < (*aresta)[i].peso){
            aux = (*aresta)[k];
            (*aresta)[k] = (*aresta)[i];
            (*aresta)[i] = aux;
        }

    }

    return 1;

}

//********************************************* vertices adjacentes *********************************************
int verticesAdjacentes(grafo g, int chave, tipo_vertice **vertice, int *tamanho){

    int i, k = 0, pos, contador = 0;

    pos = pesquisaVertice(g, chave);

    if(pos == -1)
        return 0;

    // Primeiro verifica quantos vertices estão conectados a chave passada.
    for(i = 0; i < g->numVertice; i++){
        if(g->aresta[pos][i].conectado == 0)
            continue;
        else
            contador++;
    }

    // Cria um vetor com a quantidade exata de vertices adjacentes.
    *vertice = (tipo_vertice*)malloc(contador * sizeof(tipo_vertice));

     if(!vertice)
        return 0;

      // Então pega todos os vertices adjacentes a chave e salva no vertor.
      for(i = 0; i < g->numVertice; i++){
        if(g->aresta[pos][i].conectado == 0)
            continue;
        else
            (*vertice)[k++].info.chave = g->vertice[i].info.chave;
    }

    *tamanho = contador;

    return 1;

}

//********************************************* Imprime Grafo *********************************************
void imprime(grafo g){

    int i, k;

    for(i = 0; i < g->numVertice; i++){
            printf("\nVertice: [%d]-> ", g->vertice[i].info.chave);
        for(k = 0; k < g->numVertice; k++){

                if(g->aresta[i][k].conectado == 1)
                    printf("%d, ", g->vertice[k].info.chave);

            }
        }
}

//********************************************* eCircuito *********************************************
int eCircuito(grafo g){

    // A ideia é utilizar o dfs, toda vez que o mesmo não conseguir progredir, ou seja, dar o pop
    // Verificar se todos os vertices já foram visitados, caso não, é pq o grafo tem um circuito, ou seja,
    // o dfs encontrou um caminho sem volta e então regride, repetindo assim um vértice.

    pilha p;
    tipo_elemento e;
    int origem, contador, i, k, v;

    p = cria_pilha();
    origem = pesquisaVertice(g, g->vertice[0].info.chave);

    if(!p || origem == -1)
        return 0;


    for(i = 0; i < g->numVertice; i++)
        g->vertice[i].status = 0;

    e = g->vertice[origem].info;
    g->vertice[origem].status = 1;

    push(p, e);

    while(!vazia(p)){

        peek(p, &e);
        k = pesquisaVertice(g, e.chave);

        for(i = 0; i < g->numVertice; i++){

            if(g->aresta[k][i].conectado == 1 && g->vertice[i].status == 0){
                v = i;
                break;
            }

            else
                v = -1;

        }

        // Aqui será feita a verificação, quando v é igual a -1, quer dizer que a busca ficou presa.
        if(v == -1){
            pop(p, &e);
            // Percorre a lista de vértices, se todos já foram visitados, quer dizer que o pop é para
            // finalizar a busca, caso não, é pq a busca repetirá um vertice.
            for(contador = 0; contador < g->numVertice; contador++){

                if(g->vertice[contador].status == 0)
                    return 1;
            }
        }

        else{
            e = g->vertice[v].info;
            // print
            push(p, e);
            g->vertice[v].status = 1;
        }

    }

    return 0;

}
