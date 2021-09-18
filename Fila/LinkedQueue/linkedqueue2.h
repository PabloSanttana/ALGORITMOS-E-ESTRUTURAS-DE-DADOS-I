#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct no {
    int val;
    struct no* prox;
};

struct linkedqueue {
    struct no* frente;
    struct no* tras;
    int qtdade;
};

struct linkedqueue* inicializar() {
    struct linkedqueue* fila = (struct linkedqueue*) malloc(sizeof(struct linkedqueue));
    fila->frente = NULL;
    fila->tras = NULL;
    fila->qtdade = 0;
    return fila;
}

struct no* alocarNovoNo(int valor) {
    struct no* newNo = (struct no*)malloc(sizeof(struct no));
    newNo->val = valor;
    newNo->prox = NULL;
    return newNo;
}

bool vazia(struct linkedqueue* fila) {
    if (fila != NULL) {
        if (fila->qtdade == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }
}

//se a fila estiver nula, instancie a fila
//por causa da possibilidade de instanciacao usamos struct linkedqueue**
void enfileirar(struct linkedqueue** fila, int val) {
    if ((*fila) == NULL) {
        (*fila) = inicializar();
    }
    struct no* current = alocarNovoNo(val);
    
    if ((*fila)->frente == NULL) {
        (*fila)->frente = current;
        (*fila)->tras = current;
    }
    else
    {
        (*fila)->tras->prox = current;
        (*fila)->tras = current;
    }

    (*fila)->qtdade++;
}

//retorne a constante INT_MIN se a fila for nula ou vazia
//lembrem de desalocar o nó removido (free)
int desenfileirar(struct linkedqueue* fila) {
    if (fila != NULL) {
        if (fila->qtdade > 0) {
            fila->qtdade--;
            int aux = fila->frente->val;
            if (fila->qtdade == 0) {
                free(fila->frente);
                return aux;
            }
            else
            {
                struct no* temp = fila->frente->prox;
                free(fila->frente);
                fila->frente = temp;
                return aux;
            }
        }
        else {
            return INT_MIN;
        }
    }
    else
    {
        return INT_MIN;
    }

}

//retorne a constante INT_MIN se a fila for nula ou vazia
int frente(struct linkedqueue* fila) {
    if (fila !=NULL) {
        if (fila->qtdade > 0) {
           return  fila->frente->val;
        }
        else
        {
            return INT_MIN;
        }

    }
    else
    {
        return INT_MIN;
    }
   
}