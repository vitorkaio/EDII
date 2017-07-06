#include <stdio.h>
#include <stdlib.h>
#include "fila_prioridades.h"

fila_prioridade cria_fila_prioridade(int tamanho){
    fila_prioridade fp;
    fp=(fila_prioridade)malloc(sizeof(tipo_fila_prioridade));
    if(fp){
        fp->v = (tipo_elemento*)malloc(sizeof(tipo_elemento)*tamanho);
        if(fp->v){
          fp->numElementos =0;
          fp->tamanho =tamanho;
        }
        else{
            free(fp);
            fp=NULL;
        }
    }
    return fp;

}
void  refaz(int esq, fila_prioridade fp)
{
  int i = esq;
  int j;
  tipo_elemento aux;
  j = i * 2;
  aux = fp->v[i];
  while (j <= fp->numElementos)
  {
    if (j < fp->numElementos)
    { if (fp->v[j].chave < fp->v[j+1].chave)
        j++; }
    if (aux.chave >= fp->v[j].chave)
		  break;
    fp->v[i] = fp->v[j];
    i = j;
    j = i * 2 ;
  }
  fp->v[i] = aux;
}

void constroi(fila_prioridade fp)
{
  int esq;
  esq = fp->numElementos / 2;
  while (esq > 0)
  {
    refaz(esq, fp);
    esq--;
  }
}

int retira(fila_prioridade fp,tipo_elemento *e)
{

  if (fp->numElementos < 1)
    return 0;
  else
  {
    *e= fp->v[1];
    fp->v[1] = fp->v[fp->numElementos];
    fp->numElementos--;
    refaz(1, fp);
  }
  return 1;
}
int  aumentaChave(int i, tipoChave ch, fila_prioridade fp)
{
  tipo_elemento aux;
  if (ch < fp->v[i].chave)
  {
     return 0;
  }
  fp->v[i].chave = ch;
  while (i > 1 && fp->v[i/2].chave < fp->v[i].chave)
  {
    aux = fp->v[i/2];
    fp->v[i/2] = fp->v[i];
    fp->v[i] = aux;
    i /= 2;
  }
  return 1;
}
int insere(fila_prioridade fp,tipo_elemento e)
{
  if(fp->numElementos == fp->tamanho)
    return 0;
  fp->numElementos++;
  fp->v[fp->numElementos] = e;

  aumentaChave(fp->numElementos,e.chave,fp);
  return 1;
}
int getTamanho(fila_prioridade fp){
    return fp->numElementos;
}

void termina(fila_prioridade fp){
    free(fp->v);
    free(fp);
}



///.h
