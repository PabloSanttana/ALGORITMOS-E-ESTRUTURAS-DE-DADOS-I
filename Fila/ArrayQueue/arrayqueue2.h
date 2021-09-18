#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct arrayqueue {
    int frente;
    int tras;
    int* elementos;
    int tamanho;    //tam do array
    int qtdade;     //qtdade de elementos no array    
};

struct arrayqueue* inicializar(int tamArray) {
    
    struct arrayqueue* fila = (struct arrayqueue*) malloc(sizeof(struct arrayqueue));
    fila->elementos = (int*)calloc(tamArray, sizeof(int));
    fila->frente = -1;
    fila->tras = -1;
    fila->qtdade = 0;
    fila->tamanho = tamArray;
    return fila;
}

//se a fila estiver nula, instancie a fila com tamanho 10
//por causa da possibilidade de instanciacao usamos struct arrayqueue**
//se a fila encher, simplesmente não enfileire
void enfileirar(struct arrayqueue** fila, int val) {
    if ((*fila == NULL)) {
        (*fila) = inicializar(10);
    }
    if ((*fila)->qtdade == (*fila)->tamanho) {
        return; // fila cheia
    }
    else
    {
        (*fila)->tras = ((*fila)->tras + 1) % (*fila)->tamanho;
        if ((*fila)->frente == -1) {
            (*fila)->frente = ((*fila)->frente + 1) % (*fila)->tamanho;
        }

    }
    
    (*fila)->elementos[(*fila)->tras] = val;
    (*fila)->qtdade++;
   
}

//retorne a constante INT_MIN se a fila for nula ou vazia
int desenfileirar(struct arrayqueue* fila) {

    if (fila != NULL) {
        if (fila->qtdade > 0) {
            fila->qtdade--;
            if (fila->qtdade == 0) {
                int aux = fila->frente;
                fila->frente = -1;
                fila->tras = -1;
                return fila->elementos[aux];
            }
            else
            {
                int aux = fila->frente;
                fila->frente = (fila->frente + 1) % fila->tamanho;
                return fila->elementos[aux];
            }
        }
        else
        {
            return INT_MIN;
        }

    }
    else {
        return INT_MIN;
    }
}

//retorne a constante INT_MIN se a fila for nula ou vazia
int frente(struct arrayqueue* fila) {
    //TODO

    if (fila != NULL) {
        if (fila->qtdade > 0) {
           return fila->elementos[fila->frente];
        }
        else
        {
            return INT_MIN;
        }

    }
    else {
        return INT_MIN;
    }

 
}

