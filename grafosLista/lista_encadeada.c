#include "lista_encadeada.h"

lista cria_lista(){

	lista l = (lista)malloc(sizeof(tipo_lista));

	if (l){

		l->primeiro = NULL;
		l->ultimo = NULL;
		l->tamanho = 0;

	}

	return l;
}

int insere_lista(lista l, tipoAresta inf){

	tipo_nodo *p;
	p = (tipo_nodo *)malloc(sizeof(tipo_nodo));

	if (p){
		p->aresta = inf;
		p->prox = NULL;

		if (!l->primeiro)
			l->primeiro = p;

		else{
			l->ultimo->prox = p;
            l->ultimo = p;
		}
        l->ultimo = p;
		l->tamanho++;

		return 1;
	}
	return 0;

}
int remove_lista(lista l, int vertice, tipoAresta *e){
	tipo_nodo *p = NULL, *ant = NULL;
	p = l->primeiro;

	while (p){
		if (p->aresta.verticeAdjacente == vertice)
			break;
		else{
			ant = p;
			p = p->prox;
		}
	}
	if (p){
		if (l->primeiro == p)
			l->primeiro = p->prox;
		else
		if (l->ultimo == p){
			l->ultimo = ant;
			ant->prox = NULL;
		}
		else
			ant->prox = p->prox;

		*e = p->aresta;
		free(p);
		l->tamanho--;
		return 1;
	}
	return 0;
}

int pesquisa_lista(lista l, int vertice){

	tipo_nodo *p;
	p = l->primeiro;

	if (!p)
		return 0;

	while (p){
		if (vertice == p->aresta.verticeAdjacente)
            return 1;
		else
			p = p->prox;

	}

	return 0;
}

int pesquisa_lista_dijkistra(lista l, int vertice){

    tipo_nodo *p;
    int pos = 1;

    p = l->primeiro;
    while(p != NULL){
        if(p->aresta.verticeAdjacente == vertice){
            return pos;
        }else{
            p = p->prox;
            pos++;
        }
    }
    return 0;
}

// Pesquisa se uma candidato já votou. Passa a lista, tipoAresta nova.
/*int pesquisaVotoEleitores_lista(lista l, tipoAresta tipoAresta){

tnodo p;
	p = l->primeiro;
	while (p){
		if (!strcmp(tipoAresta.titulo, p->tipoAresta.titulo) && (tipoAresta.classeCandidadato == p->tipoAresta.classeCandidadato))
			return 0;
		else
			p = p->prox;

	}

	return 1;
}*/

void termina_lista(lista l){
	tipo_nodo *p;
	p = l->primeiro;
	while (p){
		p = l->primeiro;
		l->primeiro = p->prox;
		free(p);
	}
	l->tamanho = 0;
}


void imprimeLista(lista l){

    tipo_nodo *no;
    no = l->primeiro;

    while(no){

        printf("( [%d], %d ) ", no->aresta.verticeAdjacente, no->aresta.peso);
        no = no->prox;

    }

}


int pegaElemento(lista l, tipoAresta *a, int indice){

    int i;
    tipo_nodo *p;

    if(indice < 1 || indice > l->tamanho)
        return 0;

    p = l->primeiro;
    for(i = 1; i < indice; i++)
        p = p->prox;
    *a = p->aresta;
    return 1;
}

