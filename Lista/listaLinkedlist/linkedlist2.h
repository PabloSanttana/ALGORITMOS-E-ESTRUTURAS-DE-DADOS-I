#pragma once


#include <stdlib.h>
#include <stdio.h>

struct no {
    int val;
    struct no* prox;
};

struct linkedlist {
    struct no* cabeca;
    int qtdade;
};

struct linkedlist* inicializar() {
    struct linkedlist* lista = (struct linkedlist*) malloc(sizeof(struct linkedlist));
    lista->cabeca = NULL;
    lista->qtdade = NULL;
    return lista;
}

struct no* alocarNovoNo(int valor) {
    struct no* newNo = (struct no*) malloc(sizeof(struct no));
    newNo->val = valor;
    newNo->prox = NULL;

    return newNo;
}

void inserirElementoNoFim(struct linkedlist* lista, int valor) {

    if (lista->cabeca != NULL) {
        struct no* current = lista->cabeca;

        while (current->prox != NULL) {
            current = current->prox;
        }
        current->prox = alocarNovoNo(valor);

    }
    else {
        lista->cabeca = alocarNovoNo(valor);
    }

    lista->qtdade++;
  
}

void inserirElementoNoInicio(struct linkedlist* lista, int valor) {
    if (lista->cabeca != NULL) {
        struct no* current = alocarNovoNo(valor);
        current->prox = lista->cabeca;
        lista->cabeca = current;

    }
    else {
        lista->cabeca = alocarNovoNo(valor);
    }

    lista->qtdade++;
}

void inserirElementoEmPosicao(struct linkedlist* lista, int valor, int posicao) {
    if (posicao > 0 && posicao < lista->qtdade) {
        struct no* current = lista->cabeca;
        struct no* temp_current = NULL;

        for (int i = 1; i < posicao; i++) {
            current = current->prox;
        }
        temp_current = alocarNovoNo(valor);
        temp_current->prox = current->prox;
        current->prox = temp_current;
        lista->qtdade++;

    }
    else if (posicao == 0) {
        inserirElementoNoInicio(lista, valor);
    }
    else if (posicao == lista->qtdade) {
        inserirElementoNoFim(lista, valor);
    }
}

int obterElementoEmPosicao(struct linkedlist* lista, int posicao) {
    if (posicao >= 0 && posicao < lista->qtdade) {
        
        struct no* current = lista->cabeca;

        for (int i = 0; i < posicao; i++)
        {
            if (current->prox != NULL) {
                current = current->prox;
            }
            else
            {
                return -0;
            }
        }
        return current->val;
    }
}


// função auxiliar
void removerElementoInicio(struct linkedlist* lista) {

    if (lista->cabeca != NULL) {


        if (lista->cabeca->prox == NULL) {
           free(lista->cabeca );
            lista->cabeca = NULL;
           
        }
        else {
            struct no* current = NULL;

            current = lista->cabeca->prox;

            free(lista->cabeca);
            (lista->cabeca) = current;
        }

        

        lista->qtdade--;
    }
    else {

        printf("Lista vazia \n");
    }


}


// função auxiliar
void removerElementoFinal(struct linkedlist* lista) {

    if (lista->cabeca != NULL) {

        if (lista->cabeca->prox == NULL) {
            free(lista->cabeca);
            lista->cabeca = NULL;
           
        }
        else {
            struct no* current = lista->cabeca;

            while (current->prox->prox != NULL) {
                current = current->prox;
            }
            free(current->prox);
            current->prox = NULL;
            
        }
        lista->qtdade--;
    }
    else {

        printf("Lista vazia \n");
    }
}

void removerElementoEmPosicao(struct linkedlist* lista, int posicao) {

    if (posicao > 0 && posicao < lista->qtdade -1) {

        struct no* current = lista->cabeca;
        struct no* temp_current = NULL;
        for (int i = 1;i < posicao;i++) {
            current = current->prox;
        }

        temp_current = current->prox;
        current->prox = temp_current->prox;

        free(temp_current);
        lista->qtdade--;

    }
    else if (posicao == 0) {
        removerElementoInicio(lista);
    }
    else if (posicao == lista->qtdade -1) {
        removerElementoFinal(lista);
    }
    else {
        printf("Index invalido \n");
    }


}

void imprimirLista(struct linkedlist* lista) {
    //usamos o aux para percorrer a lista
    if (lista->cabeca != NULL) {
        struct no* aux = lista->cabeca;
        //navega partindo da cabeça até chegar NULL
        printf("[");
        do {
            printf("%d", aux->val);
            aux = aux->prox;
            if (aux != NULL) {
                printf(", ");
            }
        } while (aux != NULL);
        printf("]");
    }
    else {
        printf("A lista está vazia!");
    }
}
