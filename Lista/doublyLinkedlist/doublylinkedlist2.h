#pragma once

#include <stdlib.h>
#include <stdio.h>

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

struct doublylinkedlist* inicializar() {
    struct doublylinkedlist* lista = (struct doublylinkedlist*) malloc(sizeof(struct doublylinkedlist));
    lista->cabeca = NULL;
    lista->cauda = NULL;
    lista->qtdade = NULL;
    return lista;
}

struct no* alocarNovoNo(int valor) {
    struct no* newNo = (struct no*) malloc(sizeof(struct no));
    newNo->val = valor;
    newNo->ant = NULL;
    newNo->prox = NULL;

    return newNo;
}

void inserirElementoNoInicio(struct doublylinkedlist* lista, int valor) {
    
    if (lista->cabeca != NULL){
        
        struct no* current = alocarNovoNo(valor);
        current->prox = lista->cabeca;
        current->ant = lista->cauda;
        lista->cabeca = current;
       
    }
    else {
        lista->cabeca = alocarNovoNo(valor);
        lista->cauda = lista->cabeca;
    }
    lista->qtdade++;
}

void inserirElementoNoFim(struct doublylinkedlist* lista, int valor) {
    
    if (lista->cabeca != NULL) {
        struct no* current = alocarNovoNo(valor);
        struct no* temp = lista->cauda;
        current->ant = temp;
        temp->prox = current;
        lista->cauda = current;

    }
    else {
        lista->cabeca = alocarNovoNo(valor);
        lista->cauda = lista->cabeca;
   
    }

    lista->qtdade++;
}

void inserirElementoEmPosicao(struct doublylinkedlist* lista, int valor, int posicao) {

    if (posicao > 0 && posicao < lista->qtdade) {
        struct no* current = lista->cabeca;
        struct no* temp_current = NULL;

        for (int i = 1; i < posicao; i++) {
            current = current->prox;
        }

        temp_current = alocarNovoNo(valor);
        temp_current->prox = current->prox;
        current->prox->ant = temp_current;
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

int obterElementoEmPosicao(struct doublylinkedlist* lista, int posicao) {
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
void removerElementoInicio(struct doublylinkedlist* lista) {

    if (lista->cabeca != NULL) {

       

        if (lista->cabeca->prox == NULL) {
            free(lista->cabeca);
            lista->cabeca = NULL;
            lista->cauda = NULL;
            lista->qtdade--;
        }
        else {
            struct no* current = NULL;
            current = lista->cabeca->prox;
            current->ant = lista->cauda;

            free(lista->cabeca);
           lista->cabeca = current;   
           lista->qtdade--;
        }

        
    }
    else {

        printf("Lista vazia \n");
    }


}


// função auxiliar
void removerElementoFinal(struct doublylinkedlist* lista) {

    if (lista->cabeca != NULL) {

        if (lista->cabeca->prox == NULL) {
            free(lista->cabeca);
            free(lista->cauda);
            lista->cabeca = NULL;
            lista->cauda = NULL;
            lista->qtdade--;
        }
        else {
            struct no* current = lista->cauda;
            lista->cauda = current->ant;
            lista->cauda->prox = NULL;
            free(current);
            lista->qtdade--;
        }

    }
    else {

        printf("Lista vazia \n");
    }
}




void removerElementoEmPosicao(struct doublylinkedlist* lista, int posicao) {

    if (posicao > 0 && posicao < lista->qtdade - 1) {

        struct no* current = lista->cabeca;
        struct no* temp = NULL;
        for (int i = 1;i < posicao;i++) {
            current = current->prox;
        }

        temp = current->prox;
        current->prox = temp->prox;
        temp->prox->ant = current;

        free(temp);
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

void imprimirLista(struct no** cabeca) {
    //usamos o aux para percorrer a lista
    if ((*cabeca) != NULL) {
        struct no* aux = (*cabeca);
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
