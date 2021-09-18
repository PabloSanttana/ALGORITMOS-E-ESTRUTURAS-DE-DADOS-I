#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct noBst {
	int val;
	struct noBst* esq;
	struct noBst* dir;
};

/**
 * Funcao que aloca um novo noBst, e
 * ajusta os ponteiros esq e dir para NULL.
 **/

struct noBst* alocarNovoNo(int val) {
	struct noBst* raiz = (struct noBst*) malloc(sizeof(struct noBst));
	raiz->esq = NULL;
	raiz->dir = NULL;
	raiz->val = val;
	return raiz;
}

/**
 * Funcao que recebe a raiz de uma BST, e
 * insere um novo valor na BST. Tamanho deve
 * ser incrementado.
 * Ambos tamanho e raiz são passados por referência.
 **/


void inserir(struct noBst** raiz, int val, int* tamanho) {

	//alocando um novo nó 
	if ((*raiz) == NULL) {
		(*raiz) = alocarNovoNo(val);
		(*tamanho)++;
	}
	else {
		if (val <= (*raiz)->val) {
			inserir(&(*raiz)->esq, val, tamanho);
		}
		else {
			inserir(&(*raiz)->dir, val, tamanho);
		}
	}
}

/**
 * Funcao que recebe a raiz de uma BST, e
 * verifica se a mesma contém um dado valor.
 **/

bool buscar(struct noBst* raiz, int val) {

	if (raiz != NULL) {

		if ((raiz)->val == val) {
			return true;
		}
		else {
			if (val <= raiz->val) {
				buscar(raiz->esq, val);
			}
			else {
				buscar(raiz->dir, val);
			}
		}
	}
	else {
		return false;
	}
}


/**
 * Funcao que retorna o maior valor de uma BST.
 **/
int max(struct noBst* raiz) {
	if (raiz != NULL) {
		if (raiz->dir != NULL) {
			max(raiz->dir);
		}
		else {
			return raiz->val;
		}
	}
	else {
		return NULL;
	}
}

/**
 * Funcao que retorna o menor valor de uma BST.
 **/
int min(struct noBst* raiz) {
	//IMPLEMENTAR
	if (raiz != NULL) {
		if (raiz->esq != NULL) {
			min(raiz->esq);
		}
		else {
			return raiz->val;
		}
	}
	else {
		return NULL;
	}
}

/**
 * Funcao que retorna a altura de uma BST.
 * A altura de uma BST é dada pela quantidade
 * de arestas entre a raiz e a folha mais distante.
 **/
int altura(struct noBst* raiz) {

	if (raiz != NULL) {

		//folha  raiz->esq === null e raiz->dir == null
		//encontrar um folha return 0

		if (raiz->esq == NULL && raiz->dir == NULL) {
			return 0;
		}
		else {
			int alturaEsquerda = altura(raiz->esq);
			int alturaDireita = altura(raiz->dir);

			if (alturaEsquerda > alturaDireita) {
				return  (1 + alturaEsquerda);
			}
			else {
				return  (1 + alturaDireita);
			}
		}
	}
	return 0;
}

/**
 * Funcao que navega em-ordem na BST e
 * imprime seus elementos.
 **/
void emOrdem(struct noBst* raiz) {
	if (raiz != NULL) {
		emOrdem(raiz->esq);
		printf(" %d, ", raiz->val);
		emOrdem(raiz->dir);
	}

}

/**
 * Funcao que navega pre-ordem na BST e
 * imprime seus elementos.
 **/
void preOrdem(struct noBst* raiz) {
	if (raiz != NULL) {
		printf("%d, ", raiz->val);
		preOrdem(raiz->esq);
		preOrdem(raiz->dir);
	}
}

/**
 * Funcao que navega pos-ordem na BST e
 * imprime seus elementos.
 **/
void posOrdem(struct noBst* raiz) {

	if (raiz != NULL) {
		posOrdem(raiz->esq);
		posOrdem(raiz->dir);
		printf(" %d, ", raiz->val);
	}
}

/**
 * Funcao que recebe a raiz de uma BST, e
 * remove o no que contem o valor passado como
 * argumento. Tamanho deve ser decrementado.
 * Tamanho é passado por referência.
 **/

 // função auxiliar para pegar o endereço do maior valor
struct noBst* enderecoMaiorValor(struct noBst* raiz) {
	if (raiz != NULL) {
		//vrificando um elemento a frente
		if (raiz->dir->dir != NULL) {
			return enderecoMaiorValor(raiz->dir);
		}
		else
		{
			//pegando valor
			struct noBst* temp = raiz->dir;
			// verificando se não tem elemento a esquerda
			if (temp->esq != NULL) {
				raiz->dir = temp->esq;
			}
			else {
				raiz->dir = NULL;
			}
			return temp;
		}
	}
	else {
		return NULL;
	}
}

// função auxiliar para remover
struct noBst* axuRemover(struct noBst* raiz) {
	struct noBst* temp = raiz;

	// não tem filho
	if (raiz->dir == NULL && raiz->esq == NULL) {
		free(raiz);
		raiz = NULL;
		return raiz;
	}
	// filho a direita 
	else if (raiz->esq == NULL) {
		raiz = raiz->dir;
		temp->dir = NULL;
		free(temp);
		return raiz;
	}
	// filho a esquerda 
	else if (raiz->dir == NULL) {
		raiz = raiz->esq;
		temp->esq = NULL;
		free(temp);
		return raiz;
	}
	// filhos ambos os lados 
	else {
		// pegando maior valor da esquedar 
		temp = enderecoMaiorValor(raiz->esq);
		raiz->val = temp->val;
		free(temp);
		return raiz;
	}
}

struct noBst* remover(struct noBst* raiz, int val, int* tamanho) {

	if (raiz != NULL) {
		// valor menor
		if (val < raiz->val) {

			if (raiz->esq->val == val) {
				raiz->esq = axuRemover(raiz->esq);
				(*tamanho)--;
				return raiz->esq;
			}
			else {
				remover(raiz->esq, val, tamanho);
			}
		}
		// valor maior
		else if (val > raiz->val) {

			if (raiz->dir->val == val) {
				raiz->dir = axuRemover(raiz->dir);
				(*tamanho)--;
				return raiz->dir;
			}
			else {
				remover(raiz->dir, val, tamanho);
			}

		}
		// valor == raiz->val
		else {
			raiz = axuRemover(raiz);
			(*tamanho)--;
			return raiz;
		}
	}
	else {
		return false;
	}
}
