#pragma once

#include <stdio.h>
#include <stdlib.h>


struct array {
	int* elementos;
	int tamanho;    //tam do array
	int qtdade;     //qtdade de elementos no array    
};

struct array* inicializar(int tamanho) {
	struct array* vetor = (struct array*) malloc(sizeof(struct array));
	vetor->elementos = (int*)malloc(tamanho * sizeof(int));
	vetor->qtdade = 0;
	vetor->tamanho = tamanho;
	return vetor;
}
void inserirElemeto(struct array* vetor, int elemento) {
	if (vetor->qtdade < vetor->tamanho) {
		vetor->elementos[vetor->qtdade] = elemento;
		vetor->qtdade++;
	}
	else {
		printf("Vetor cheio \n");
	}
}

void inserirElemetoOrdenado(struct array* vetor) {
	for ( int i = 0; i < vetor->tamanho; i++)
	{
		inserirElemeto(vetor, i);

	}
}

void inserirElemetoaleatorios(struct array* vetor) {
	srand(30);
	 int temp;
	for ( int i = 0; i < vetor->tamanho; i++)
	{
		// gerando valores aleatórios entre zero e 100 
		temp = rand() % vetor->tamanho;
		inserirElemeto(vetor, temp);
	}
}

void inserirElemetoDecrescente(struct array* vetor) {
	for ( int i = vetor->tamanho; i > 0; i--)
	{
		inserirElemeto(vetor, i);

	}
}


// selectionSort Out-of-Place
// seleciona o menor elemento é colocar na posição oredanada

void selectionSortop(int** v,int tamanho) {
	int* ordenado = (int*)malloc(tamanho * sizeof(int));
	int indexMenor = 0;
	for (int i = 0; i < tamanho; i++){
		indexMenor = 0;
		for (int j = 0; j < tamanho; j++){

			if ((*v)[j] < (*v)[indexMenor]) {
				indexMenor = j;
			}

		}
		ordenado[i] = (*v)[indexMenor];
		(*v)[indexMenor] = INT_MAX;
	}
	(*v) = ordenado;

}

void trocarIndex(int* v, int i, int j) {
	int temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

// selectionSort in-place
void selectionSorInPlace(int* v, int tamanho) {
	
	int indexMenor = 0;
	for (int i = 0; i < tamanho -1; i++) {
		indexMenor = i;
		for (int j = i + 1; j < tamanho; j++) {
			if ( v[j] < v[indexMenor]) {
				indexMenor = j;
			}

		}
		trocarIndex(v, indexMenor, i);
		
	}
}

// faz uma varredura comparando se o elemento atual é maior que o proximo elemento, de for maior troca de posição
// v = {10,5,4,12}
// v = {5,10,4,12}
// v = {5,4,10,12}
// v ={4,5,10.12}
void bubleSort(int* v, int n) {
	for (int varredura = 0; varredura < n - 1; varredura++) {
		bool trocou = false;
		for (int i = 0; i < n - varredura - 1; i++)
		{
			if (v[i] > v[i + 1]) {
				trocarIndex(v, i, i + 1);
				trocou = true;
			}
		}
		if (trocou == false) {
			return;
		}
	}
	
}

void insertionSortIP(int* v, int tamanho) {
	for (int  i = 1; i < tamanho; i++){
		for (int j = i; j > 0 && v[j - 1] > v[j]; j--){
				int temp = v[j - 1];
				v[j - 1] = v[i];
				v[i] = temp;
		}

	}
}

void bubbleSort(struct array* vetor) {
	for (int varredura = 0; varredura < vetor->qtdade- 1; varredura++)
	{
		bool validation = false;
		for (int i = 0; i < vetor->qtdade - 1 - varredura; i++)
		{
			if (vetor->elementos[i] > vetor->elementos[i+1]) {
				int temp = vetor->elementos[i];
				vetor->elementos[i] = vetor->elementos[i + 1];
				vetor->elementos[i + 1] = temp;
				validation = true;
			}
		}
		if (!validation) {
			printf("Array ja esta ordenado \n");
			return;
		}
	}
}


void insertionSort(struct array* vetor) {
	for (int i = 1; i < vetor->qtdade; i++) {
		int selecionado = vetor->elementos[i];
		int j;
		for ( j = i; j > 0 && vetor->elementos[j-1] > selecionado; j--){
			vetor->elementos[j] = vetor->elementos[j - 1];
		}
		
		vetor->elementos[j] = selecionado;
	}
}


void merge(int* v, int tamV, int* e, int tamE, int* d, int tamD) {
	int indexV = 0;
	int indexE = 0;
	int indexD = 0;
	while (indexE < tamE && indexD < tamD) {
		if (e[indexE] <= d[indexD]) {
			v[indexV] = e[indexE];
			indexE++;
		}
		else {
			v[indexV] = d[indexD];
			indexD++;
		}
		indexV++;
	}
	//ainda poderíamos ter elementos no vetor E que não foram copiados para V
	while (indexE < tamE) {
		v[indexV] = e[indexE];
		indexE++;
		indexV++;
	}
	//ainda poderíamos ter elementos no vetor D que não foram copiados para V
	while (indexD < tamD) {
		v[indexV] = d[indexD];
		indexD++;
		indexV++;
	}
}


void mergeSort(int* v, int tamV) {
	if (tamV > 1) {
		//primeiro quebramos o vetor em 2 vetores menores
		int meio = tamV / 2;

		int tamV1 = meio;
		int* v1 = (int*)malloc(tamV1 * sizeof(int));
		for (int i = 0; i < meio; i++) {
			v1[i] = v[i];
		}

		int tamV2 = tamV - meio;
		int* v2 = (int*)malloc(tamV2 * sizeof(int));
		for (int i = meio; i < tamV; i++) {
			v2[i - meio] = v[i];
		}

		mergeSort(v1, tamV1);
		mergeSort(v2, tamV2);
		merge(v, tamV, v1, tamV1, v2, tamV2);

		free(v1);
		free(v2);
	}
}

void swap(int* v, int i, int j) {
	int temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int particiona(int* v, int ini, int fim) {
	int pIndex = ini;
	int pivo = v[fim];
	for (int i = ini; i < fim; i++) {
		if (v[i] <= pivo) {
			swap(v, i, pIndex);
			pIndex++;
		}
	}
	swap(v, pIndex, fim);
	return pIndex;
}

void quickSort(int* v, int ini, int fim) {
	if (fim > ini) {
		int indexPivo = particiona(v, ini, fim);
		quickSort(v, ini, indexPivo - 1);
		quickSort(v, indexPivo + 1, fim);   //indexPivo já está no seu local
	}
}





int particionaPivoRandomizada(int* v, int ini, int fim) {

	// gerar numero Randomizada entre ini e fim
	int pivot_index = ini + rand() % (fim - ini + 1);

	swap(v, pivot_index, fim);

	int pIndex = ini;
	int pivo = v[fim];
	for (int i = ini; i < fim; i++) {
		if (v[i] <= pivo) {
			swap(v, i, pIndex);
			pIndex++;
		}
	}
	swap(v, pIndex, fim);
	return pIndex;
}

void quickSortPivoRandomizada(int* v, int ini, int fim) {
	if (fim > ini) {
		int indexPivo = particionaPivoRandomizada(v, ini, fim);
		quickSortPivoRandomizada(v, ini, indexPivo - 1);
		quickSortPivoRandomizada(v, indexPivo + 1, fim);   //indexPivo já está no seu local
	}
}





