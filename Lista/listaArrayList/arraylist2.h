#pragma once
#include <stdio.h>
#include <stdlib.h>

struct arraylist {
    int* vetor;
    int qtdade;
    int capacidade;
};

void exibirLista(struct arraylist* lista) {
    printf("[");
    for (int i = 0; i < lista->qtdade; i++) {
        printf("%d", lista->vetor[i]);
        if (i < lista->qtdade - 1) {
            printf(", ");
        }
    }
    printf("]");
}

struct arraylist* inicializar(int capacidade) {
    struct arraylist* lista = (struct arraylist*)malloc(sizeof(struct arraylist));
    lista->vetor = (int*)calloc(capacidade, sizeof(int));
    lista->qtdade = 0;
    lista->capacidade = capacidade;
    return lista;
}

int obterElementoEmPosicao(struct arraylist* lista, int posicao) {
    if (posicao >= 0 && posicao < lista->qtdade ) {
        return lista->vetor[posicao];
    }
    else
    {
        //   printf("Index invalido \n");
    }
}

void duplicarCapacidade(struct arraylist* lista) {
    lista->vetor = (int*)realloc(lista->vetor,2 * lista->capacidade * sizeof(int));
    lista->capacidade = lista->capacidade * 2;
}

void inserirElementoNoFim(struct arraylist* lista, int valor) {
    if ((lista->qtdade) < (lista->capacidade)) {
        lista->vetor[lista->qtdade] = valor;
        lista->qtdade++;
    }
    else {

        duplicarCapacidade(lista);
        lista->vetor[lista->qtdade] = valor;
        lista->qtdade++;
    }
}

void inserirElementoEmPosicao(struct arraylist* lista, int valor, int posicao) {
    if (posicao >= 0 && posicao < lista->qtdade) {
        lista->qtdade++;
        if (lista->qtdade >= lista->capacidade) {
            duplicarCapacidade(lista);
        }

        for (int i = lista->qtdade; i > posicao; i--) {
            lista->vetor[i] = lista->vetor[i - 1];
        }
        lista->vetor[posicao] = valor;


    }
    else if (posicao == (lista->qtdade)) {
        inserirElementoNoFim(lista, valor);
    }
    else {
        //  printf("posicao incorreta \n");
    }
}

void atualizarElemento(struct arraylist* lista, int valor, int posicao) {
    if (posicao >= 0 && posicao <= lista->qtdade) {
        lista->vetor[posicao] = valor;
        // printf("Elemento %d alterado com sucesso \n", posicao);
    }
    else {
        //  printf("Elemento nao encontrado na lista, posicao incorrenta \n");
    }
}

void removerElementoNoFim(struct arraylist* lista) {
    lista->qtdade--;
}

void removerElementoEmPosicao(struct arraylist* lista, int posicao) {
    if (posicao >= 0 && posicao <  lista->qtdade -1) {
        lista->qtdade--;
        for (int i = posicao; i < lista->qtdade;i++) {
            lista->vetor[i] = lista->vetor[i + 1];
        }
        //  printf("remoção com sucesso \n");
    }
    else if (posicao == lista->qtdade-1) {
        removerElementoNoFim(lista);
    }
    else {
        //  printf("posicao incorrenta");
    }
}

