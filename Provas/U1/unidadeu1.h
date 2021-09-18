#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct arraylist {
    int* vetor;
    int qtdade;
    int capacidade;
};

struct arraylist* inicializarAL(int capacidade) {
    struct arraylist* lista = (struct arraylist*)malloc(sizeof(struct arraylist));
    lista->vetor = (int*)calloc(capacidade, sizeof(int));
    lista->qtdade = 0;
    lista->capacidade = capacidade;
    return lista;
}

void duplicarCapacidade(struct arraylist* lista) {
    lista->vetor = (int*)realloc(lista->vetor, 2 * lista->capacidade * sizeof(int));
    lista->capacidade = 2 * lista->capacidade;
}

void inserirElementoNoFim(struct arraylist* lista, int valor) {
    if (lista->qtdade == lista->capacidade) {
        duplicarCapacidade(lista);
    }
    lista->vetor[lista->qtdade] = valor;
    lista->qtdade++;
}

int obterElementoEmPosicao(struct arraylist* lista, int posicao) {
    if (posicao >= 0 && posicao < lista->qtdade) {
        return lista->vetor[posicao];
    }
}

void inverterArrayList(struct arraylist* lista) {
    //TODO
    int aux;
    for (int i = 0, j = lista->qtdade - 1 ; i < j ; i++,j--)
    {
        aux = lista->vetor[j];
        lista->vetor[j] = lista->vetor[i];
        lista->vetor[i] = aux;
    }

    //inverte um struct arraylist* in-place
    //in-place significa que não poderá ser usado 
    //nenhum array ou lista adicional, além do original
}





struct no {
    struct no* ant;
    int val;
    struct no* prox;
};

struct doublylinkedlist {
    struct no* cabeca;
    struct no* cauda;
    int qtdade;
};

struct doublylinkedlist* inicializarDLL() {
    struct doublylinkedlist* lista = (struct doublylinkedlist*)malloc(sizeof(struct doublylinkedlist));
    lista->cabeca = NULL;
    lista->cauda = NULL;
    lista->qtdade = 0;
    return lista;
}

struct no* alocarNovoNo(int valor) {
    struct no* novoNo;
    novoNo = (struct no*)malloc(sizeof(struct no));
    novoNo->val = valor;
    novoNo->ant = NULL;
    novoNo->prox = NULL;
    return novoNo;
}

void inserirElementoNoFim(struct doublylinkedlist* lista, int valor) {
    //aloca espaço na memória e popula novoNo
    struct no* novoNo = alocarNovoNo(valor);

    if (lista->cabeca == NULL) {
        //quando a lista é vazia, basta apontar o cabeca e cauda para o novoNo
        lista->cabeca = novoNo;
    }
    else {
        //atualizamos o ponteiro novoNo->ant para o antigo último nó
        novoNo->ant = lista->cauda;
        //ponteiro prox do antigo último nó para o novoNo
        lista->cauda->prox = novoNo;
    }
    //uma certeza: inserindo no fim, a cauda apontará para o novoNo
    lista->cauda = novoNo;
    lista->qtdade++;
}

int obterElementoEmPosicao(struct doublylinkedlist* lista, int posicao) {
    struct no* aux = lista->cabeca;
    for (int i = 0; i < posicao && aux->prox != NULL; i++) {
        aux = aux->prox;
    }
    return aux->val;
}

void inverterDoublyLinkedList(struct doublylinkedlist* lista) {
    //TODO

    //inverte uma struct doublylinkedlist* in-place
    //in-place significa que não poderá ser usado 
    //nenhum array ou lista adicional, além da original

    struct no* temp1 = lista->cabeca;
    struct no* current = lista->cabeca;
    lista->cabeca = lista->cauda;
    lista->cauda = temp1;

    while (current->prox != NULL)
    {
       
        temp1 = current->prox;
        current->prox = current->ant;
        current->ant = temp1;
        current = temp1;
    }
    temp1 = current->prox;
    current->prox = current->ant;
    current->ant = temp1;

    
}

// função auxiliar
int duplicidade(struct arraylist* lista, int value, int index) {

    if (value > lista->vetor[index]) {
        
        while (value > lista->vetor[index])
        {
            index++;
        }
        return index;
    }
    
    return index;

}


// função auxiliar
int getIndex(struct arraylist* lista, int value) {
    int tam = lista->qtdade;
    int inicio = 0;
    int fim = tam;
    int index;

    while (tam >= 1)
    {
         index = ceil((fim + inicio) / 2.0);
        if (lista->vetor[index] == value) {
            return index;
        }
        else if (value < lista->vetor[index])
        {
            fim = index - 1;
        }
        else
        {
            inicio = index + 1;
        }
        tam = fim - inicio + 1;
    }
  
    index = duplicidade(lista, value, index);

    return index; 
}

// função auxiliar
void inserirElementoEmPosicao(struct arraylist* lista, int valor, int posicao) {
    if (posicao >= 0 && posicao < lista->qtdade) {

        if (lista->qtdade == lista->capacidade) {
            duplicarCapacidade(lista);
        }

        for (int i = lista->qtdade; i > posicao; i--) {
            lista->vetor[i] = lista->vetor[i - 1];
        }
        lista->vetor[posicao] = valor;
        lista->qtdade++;

    }
    else if (posicao == (lista->qtdade)) {
        inserirElementoNoFim(lista, valor);
    }
    else {
        //  printf("posicao incorreta \n");
    }
}


void insereOrdenado(struct arraylist* lista, int val) {
    //TODO

    //deve usar o algoritmo de busca binaria para encontrar o indice
    //dps, abre espaco no array, e insere no local encontrado

    if (lista->qtdade == lista->capacidade) {
        duplicarCapacidade(lista);
    }
    if (lista->qtdade == 0) {
        lista->vetor[0] = val;
        lista->qtdade++;
        return;
    }

    int index = getIndex(lista, val);

    inserirElementoEmPosicao(lista, val, index);

}




