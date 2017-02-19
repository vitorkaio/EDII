#include "fila.h"
#include "pilha.h"

void managerFila();
void managerPilha();

/* *********************************** MAIN ***********************************  */
int main(){

    //managerFila();
    managerPilha();

    return 0;
}

/* *********************************** managerPilha ***********************************  */
void managerPilha(){

    Pilha p;
    tipoElemento e;

    p = criaPilha();

    if(p)
        printf("\n Pilha criada!!!\n");

    else{
        printf("\nErro ao criar pilha!!!\n\n");
        return;
    }

    e = 65;
    push(p, e);

    e = 50;
    push(p, e);

    e = 100;
    push(p, e);

    while(pop(p, &e) != 0)
        printf("\n -> %d", e);


}


/* *********************************** managerFila ***********************************  */
void managerFila(){

    Fila f;
    tipoElemento e;
    //int v;

    f = criaFila();

    if (f)
        printf("\nFila criada!!!\n");

    else{
        printf("\nErro ao criar fila!!!\n\n");
        return;
    }

    e = 65;
    enfileira(f, e);

    e = 50;
    enfileira(f, e);

    e = 100;
    enfileira(f, e);

    // Verifica se a insercao ocorreu.
    /*if(v == 1)
        printf("\nElemento inserido!!!");
    else
        printf("\nErro ao inserir elemento!!!");*/

    imprimeFila(f);

    desinfileira(f, &e);
    printf("Removido: %d\n", e);

    imprimeFila(f);

    printf("Quantidade: %d\n", tamanhoFila(f));
}

/* Teste com String

    //scanf("%s", nome);
    //imprimeTexto(nome);
    //printf("\n T-> %s \n", nome);

void imprimeTexto(char *n){

    printf("\n Texto: %s \n", n);
    strcpy(n, "hhhh");
}*/
