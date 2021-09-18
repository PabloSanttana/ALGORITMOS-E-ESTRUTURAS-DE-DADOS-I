#pragma once


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <queue>
using namespace std;

void atualizar(struct noBst* no);
struct noBst* balancear(struct noBst* no);
struct noBst* rebalancearEsqEsq(struct noBst* no);
struct noBst* rebalancearEsqDir(struct noBst* no);
struct noBst* rebalancearDirDir(struct noBst* no);
struct noBst* rebalancearDirEsq(struct noBst* no);

/**
 * Embora durante a aula eu disse que precisar�amos
 * das vari�veis alturaEsq e alturaDir, na verdade n�o
 * � necess�rio. Depois de implementar que percebi algo
 * �bvio: para pegar a altura de uma sub-�rvore basta
 * obter o valor da vari�vel altura na sub-�rvore. (:
 **/
struct noBst {
    int val;
    int altura;
    int balanco;
    struct noBst* esq;
    struct noBst* dir;
};

/**
 * Funcao que aloca um novo noBst, e
 * ajusta os ponteiros esq e dir para NULL,
 * e vari�veis altura e balanco para 0.
 **/
struct noBst* alocarNovoNo(int val) {
    //IMPLEMENTAR
    struct noBst* raiz = (struct noBst*) malloc(sizeof(struct noBst));
    raiz->esq = NULL;
    raiz->dir = NULL;
    raiz->val = val;
    raiz->balanco = 0;
    raiz->altura = 0;
    return raiz;
}

/**
 * Funcao que rotaciona uma arvore para a
 * direita e retorna a nova raiz.
 **/
struct noBst* rotacaoDireita(struct noBst* arvore) {
    //IMPLEMENTAR
    struct noBst* esq = arvore->esq;
    arvore->esq = arvore->esq->dir;
    esq->dir = arvore;
    atualizar(arvore);
    atualizar(esq);
    return esq;
}

/**
 * Funcao que rotaciona uma arvore para a
 * esquerda e retorna a nova raiz.
 **/
struct noBst* rotacaoEsquerda(struct noBst* arvore) {
    //IMPLEMENTAR
    struct noBst* dir = arvore->dir;
    arvore->dir = arvore->dir->esq;
    dir->esq = arvore;
    atualizar(arvore);
    atualizar(dir); 
    return dir;
}

/**
 * Funcao que recebe a raiz de uma BST, e
 * insere um novo valor na BST. Tamanho deve
 * ser incrementado.
 * Ambos tamanho e raiz s�o passados por refer�ncia.
 * Lembrar de atualizar altura e fator de balanco dos n�s
 * antecessores do n� inserido, bem como balance�-los caso
 * seja necess�rio.
 * Dica: reutilizar a fun��o de inserir de BST, e lembrar
 * de como usar inteligentemente a recurs�o para conseguir
 * atualizar e balancear os n�s antecessores.
 **/
void inserir(struct noBst** raiz, int val, int* tamanho) {
    //IMPLEMENTAR
    //alocando um novo n� 
        if ((*raiz) == NULL) {
            (*raiz) = alocarNovoNo(val);
            (*tamanho)++;
        }
        else {
            if (val < (*raiz)->val) {
                inserir(&(*raiz)->esq, val, tamanho);
            }
            else {
                inserir(&(*raiz)->dir, val, tamanho);
            }
        }

        atualizar((*raiz));
        (*raiz) = balancear((*raiz));
}



/**
 * Funcao que recebe a raiz de uma BST e atualiza sua altura
 * e fator de balan�o.
 * Lembre que a altura das sub-�rvores direita e esquerda
 * n�o v�o mudar, por isso a implementa��o n�o � t�o complicada.
 **/
void atualizar(struct noBst* no) {
    //IMPLEMENTAR
    if (no != NULL) {
       // no->altura = altura(no);
       
        if (no->dir == NULL && no->esq == NULL) {
            no->altura = 0;
            no->balanco = 0;
        }
        else if (no->esq == NULL) {
            no->balanco = no->dir->altura - 0;
            no->altura = no->dir->altura + 1;
        }
        else if (no->dir == NULL) {
            no->balanco = 0 - no->esq->altura;
            no->altura = no->esq->altura + 1;
        }
        else {
            no->balanco = no->dir->altura - no->esq->altura;

            no->altura = no->balanco >= 0 ? no->dir->altura + 1 : no->esq->altura + 1;
        }

    }

}

/**
 * Funcao que recebe a raiz de uma BST e usa as rota��es
 * apropriadas para balancear uma �rvore desbalanceada no caso 1.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa fun��o deve retornar a nova raiz.
 **/
struct noBst* rebalancearEsqEsq(struct noBst* no) {
    return  rotacaoDireita(no);
}

/**
 * Funcao que recebe a raiz de uma BST e usa as rota��es
 * apropriadas para balancear uma �rvore desbalanceada no caso 2.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa fun��o deve retornar a nova raiz.
 **/
struct noBst* rebalancearEsqDir(struct noBst* no) {
    no->esq = rotacaoEsquerda(no->esq);
    return  rebalancearEsqEsq(no) ;
}

/**
 * Funcao que recebe a raiz de uma BST e usa as rota��es
 * apropriadas para balancear uma �rvore desbalanceada no caso 3.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa fun��o deve retornar a nova raiz.
 **/
struct noBst* rebalancearDirDir(struct noBst* no) {
    //IMPLEMENTAR
    return rotacaoEsquerda(no);
}

/**
 * Funcao que recebe a raiz de uma BST e usa as rota��es
 * apropriadas para balancear uma �rvore desbalanceada no caso 4.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa fun��o deve retornar a nova raiz.
 **/
struct noBst* rebalancearDirEsq(struct noBst* no) {
    //IMPLEMENTAR
    no->dir = rotacaoDireita(no->dir);
    return rebalancearDirDir(no);
}

/**
 * Funcao que recebe a raiz de uma BST e identifica em qual caso
 * ela se encaixa para executar os procedimentos de balanceamento
 * corretos:
 *      - Caso 1: esquerda-esquerda e esquerda-cheio
 *      - Caso 2: esquerda-direita
 *      - Caso 3: direita-direita e direita-cheio
 *      - Caso 4: direita-esquerda
 * Dica: usar fator de balan�o do n� e de uma de suas sub-�rvores
 * para descobrir qual � o caso.
 **/
struct noBst* balancear(struct noBst* no) {
    //IMPLEMENTAR
    if (no == NULL) {
        return NULL;
    }
    if (no->balanco == -2) {

        if (no->esq->balanco <= 0) {
            no = rebalancearEsqEsq(no);       
        }
        else {
            no = rebalancearEsqDir(no);     
        }

    }
    else if (no->balanco == 2) {

        if (no->dir->balanco <= 0) {
            no = rebalancearDirEsq(no);  
        }
        else {
            no = rebalancearDirDir(no);
        }
    }
    return no;

}



/**
 * Funcao que retorna o maior valor de uma �rvore.
 * Mesma implementa��o da BST.
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
 * Funcao que retorna o menor valor de uma �rvore.
 * Mesma implementa��o da BST.
 **/
int min(struct noBst* raiz) {
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
 * Funcao que retorna a altura de uma �rvore.
 * A altura de uma �rvore � dada pela quantidade
 * de arestas entre a raiz e a folha mais distante.
 * Mesma implementa��o da BST.
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


// fun��o auxiliar para pegar o endere�o do maior valor
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
            // verificando se n�o tem elemento a esquerda
            if (temp->esq != NULL) {
                raiz->dir = temp->esq;
            }
            else {
                raiz->dir = NULL;
            }
            return temp;
        }
        atualizar(raiz);
        raiz = balancear(raiz);
    }
    else {
        return NULL;
    }
}




// fun��o auxiliar para remover
struct noBst* axuRemover(struct noBst* raiz) {
    struct noBst* temp = raiz;

    // n�o tem filho
    if (raiz->dir == NULL && raiz->esq == NULL) {
        free(raiz);
        raiz = NULL;
       
    }
    // filho a direita 
    else if (raiz->esq == NULL) {
        raiz = raiz->dir;
        temp->dir = NULL;
        free(temp);
       
    }
    // filho a esquerda 
    else if (raiz->dir == NULL) {
        raiz = raiz->esq;
        temp->esq = NULL;
        free(temp);
       
    }
    // filhos ambos os lados 
    else {
        // pegando maior valor da esquedar 
        if (raiz->esq->dir != NULL) {
            temp = enderecoMaiorValor(raiz->esq);
            raiz->val = temp->val;
        }
        else {
            temp = raiz->esq;
            raiz->esq = temp->esq;
            raiz->val = temp->val;
        }
        free(temp);
      
    }
    atualizar(raiz);
    raiz = balancear(raiz);
    return raiz;
}


/**
 * Funcao que recebe a raiz de uma �rvore, e
 * remove o n� que contem o valor passado como
 * argumento. Tamanho deve ser decrementado.
 * Tamanho � passado por refer�ncia.
 * Lembrar de atualizar altura e fator de balanco dos n�s
 * antecessores do n� removido, bem como balance�-los caso
 * seja necess�rio.
 * Dica: reutilizar a fun��o de remover de BST, e lembrar
 * de como usar inteligentemente a recurs�o para conseguir
 * atualizar e balancear os n�s antecessores.
 **/
struct noBst* remover(struct noBst* raiz, int val, int* tamanho) {
    //IMPLEMENTAR

    if (raiz != NULL) {
        // valor menor
        if (val < raiz->val && raiz->esq != NULL) {

            if (raiz->esq->val == val) {
                raiz->esq = axuRemover(raiz->esq);
                (*tamanho)--;
               
            }
            else {
                raiz->esq =  remover(raiz->esq, val, tamanho);
            }
        }
        // valor maior
        else if (val > raiz->val && raiz->dir != NULL) {
         
            if (raiz->dir->val == val) {
                raiz->dir = axuRemover(raiz->dir);
                (*tamanho)--;
            }
            else {
                raiz->dir = remover(raiz->dir, val, tamanho);
            }

        }
        // valor == raiz->val
        else if(val == raiz->val) {
            raiz = axuRemover(raiz);
            (*tamanho)--;
        }

        atualizar(raiz);
        raiz = balancear(raiz);
        return raiz;
    }
    

  
}

void imprimir(queue<struct noBst*> nosImpressao);

/**
* Fun��o que imprime a �rvore.
* Pode ser �til para depura��o.
**/
void imprimir(struct noBst* raiz) {
    queue<struct noBst*> nosImpressao;
    nosImpressao.push(raiz);
    imprimir(nosImpressao);
}

void imprimir(queue<struct noBst*> nosImpressao) {

    queue<struct noBst*> nosImpressaoProxNivel;

    while (!nosImpressao.empty()) {
        struct noBst* noImpressao = nosImpressao.front();
        //add filhos na fila
        if (noImpressao != NULL) {
            if (noImpressao->esq != NULL)
                nosImpressaoProxNivel.push(noImpressao->esq);
            else
                nosImpressaoProxNivel.push(NULL);
            if (noImpressao->dir != NULL)
                nosImpressaoProxNivel.push(noImpressao->dir);
            else
                nosImpressaoProxNivel.push(NULL);
        }
        nosImpressao.pop();

        if (noImpressao != NULL) {
            cout << to_string(noImpressao->val) << " | ";
        }
        else {
            cout << "N | ";
        }
    }
    cout << endl << endl;
    if (!nosImpressaoProxNivel.empty())
        imprimir(nosImpressaoProxNivel);
}