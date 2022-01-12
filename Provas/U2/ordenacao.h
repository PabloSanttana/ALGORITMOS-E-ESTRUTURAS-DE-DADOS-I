#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>



struct array {
	long int* elementos;
	long int tamanho;    //tam do array
	long int qtdade;     //qtdade de elementos no array    
};

struct array* inicializar(long int tamanho) {
	struct array* vetor = (struct array*) malloc(sizeof(struct array));
	vetor->elementos = (long int*)malloc(tamanho * sizeof(long int));
	vetor->qtdade = 0;
	vetor->tamanho = tamanho;
	return vetor;
}

void inserirElemeto(struct array* vetor, long int elemento) {
	if (vetor->qtdade < vetor->tamanho) {
		vetor->elementos[vetor->qtdade] = elemento;
		vetor->qtdade++;
	}
	else {
		printf("Vetor cheio \n");
	}
}


void inserirElemetoOrdenado(struct array* vetor) {
	for (long int i = 0; i < vetor->tamanho; i++)
	{
		inserirElemeto(vetor, i);

	}
}

void inserirElemetoaleatorios(struct array* vetor) {
	srand(30);
	long int temp;
	for (long int i = 0; i < vetor->tamanho; i++)
	{
		// gerando valores aleatórios entre zero e 100 
		temp = rand() % vetor->tamanho;
		inserirElemeto(vetor, temp);
	}
}

void inserirElemetoDecrescente(struct array* vetor) {
	for (long int i = vetor->tamanho ; i > 0; i--)
	{
		inserirElemeto(vetor, i);

	}
}

void printfVetor(struct array* vetor) {
	for (long int i = 0; i < vetor->tamanho; i++)
	{

		printf("[%d]", vetor->elementos[i]);

	}
	printf(" \n");
}



void trocarIndex(long int* v, long int i, long int j) {
	long int temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

// selectionSort in-place
void selectionSorInPlace(struct array* vetor) {

	long int indexMenor = 0;
	for (long int i = 0; i < vetor->tamanho - 1; i++) {
		indexMenor = i;
		for (long int j = i + 1; j < vetor->tamanho; j++) {
			if (vetor->elementos[j] < vetor->elementos[indexMenor]) {
				indexMenor = j;
			}

		}
		trocarIndex(vetor->elementos, indexMenor, i);

	}
}

void bubbleSort(struct array* vetor) {
	for (long int varredura = 0; varredura < vetor->tamanho - 1; varredura++)
	{
		bool validation = false;
		for (long int i = 0; i < vetor->tamanho - 1 - varredura; i++)
		{
			if (vetor->elementos[i] > vetor->elementos[i + 1]) {
				long int temp = vetor->elementos[i];
				vetor->elementos[i] = vetor->elementos[i + 1];
				vetor->elementos[i + 1] = temp;
				validation = true;
			}
		}
		if (!validation) {
			//printf("Array ja esta ordenado \n");
			return;
		}
	}
}

void insertionSort(struct array* vetor) {
	for (int i = 1; i < vetor->qtdade; i++) {
		int selecionado = vetor->elementos[i];
		int j;
		for (j = i; j > 0 && vetor->elementos[j - 1] > selecionado; j--) {
			vetor->elementos[j] = vetor->elementos[j - 1];
		}

		vetor->elementos[j] = selecionado;
	}
}

float CalcularMediana(float *vetor, int tamanho) {
	for (int i = 1; i < tamanho; i++) {
		float selecionado = vetor[i];
		int j;
		for (j = i; j > 0 && vetor[j - 1] > selecionado; j--) {
			vetor[j] = vetor[j - 1];
		}

		vetor[j] = selecionado;
	}
	int meio = tamanho / 2;
	

	return  (vetor[meio-1] + vetor[meio]) / 2;

}



void merge(long int* v, long int tamV, long int* e, long int tamE, long int* d, long int tamD) {
	long int indexV = 0;
	long int indexE = 0;
	long int indexD = 0;
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


void mergeSort(long int* v, long int tamV) {
	if (tamV > 1) {
		//primeiro quebramos o vetor em 2 vetores menores
		long int meio = tamV / 2;

		long int tamV1 = meio;
		long int* v1 = (long int*)malloc(tamV1 * sizeof(long int));
		for (int i = 0; i < meio; i++) {
			v1[i] = v[i];
		}

		long int tamV2 = tamV - meio;
		long int* v2 = (long int*)malloc(tamV2 * sizeof(long int));
		for (long int i = meio; i < tamV; i++) {
			v2[i - meio] = v[i];
		}

		mergeSort(v1, tamV1);
		mergeSort(v2, tamV2);
		merge(v, tamV, v1, tamV1, v2, tamV2);

		free(v1);
		free(v2);
	}
}


void swap(long int* v, long int i, long int j) {
	long int temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}


long int particiona(long int* v, long int ini, long int fim) {
	long int pIndex = ini;
	long int pivo = v[fim];
	for (long int i = ini; i < fim; i++) {
		if (v[i] <= pivo) {
			swap(v, i, pIndex);
			pIndex++;
		}
	}
	swap(v, pIndex, fim);
	return pIndex;
}

void quickSort(long int* v, long int ini, long int fim) {
	if (fim > ini) {
		long int indexPivo = particiona(v, ini, fim);
		quickSort(v, ini, indexPivo - 1);
		quickSort(v, indexPivo + 1, fim);   //indexPivo já está no seu local
	}
	
}


// teste 








long int particionaPivoRandomizada(long int* v, long int ini, long int fim) {

	// gerar numero Randomizada entre ini e fim
	long int pivot_index = ini + rand() % (fim - ini + 1);

	swap(v, pivot_index, fim);

	long int pIndex = ini;
	long int pivo = v[fim];
	for (long int i = ini; i < fim; i++) {
		if (v[i] <= pivo) {
			swap(v, i, pIndex);
			pIndex++;
		}
	}
	swap(v, pIndex, fim);
	return pIndex;
}

void quickSortPivoRandomizada(long int* v, long int ini, long int fim) {
	if (fim > ini) {
		long int indexPivo = particionaPivoRandomizada(v, ini, fim);
		quickSortPivoRandomizada(v, ini, indexPivo - 1);
		quickSortPivoRandomizada(v, indexPivo + 1, fim);   //indexPivo já está no seu local
	}
}


void countingSort(long int** v, long int tamV) {
	long int iMenor = 0;
	long int iMaior = 0;
	for (long int i = 0; i < tamV; i++) {
		if ((*v)[i] < (*v)[iMenor])
			iMenor = i;
		if ((*v)[i] > (*v)[iMaior])
			iMaior = i;
	}

	long int vMenor = (*v)[iMenor];
	long int vMaior = (*v)[iMaior];

	long int novoTam = (*v)[iMaior] - (*v)[iMenor] + 1;
	//o vetor contagem dirá quantas vezes cada elemento 
	//aparece no vetor v
	long int* contagem = (long int*)calloc(novoTam, sizeof(long int));
	for (long int i = 0; i < tamV; i++) {
		//precisamos ter cuidado para ajustar o índice
		//para a posiçao correta assumindo que o menor
		//valor pode não ser 0
		long int indiceContagem = (*v)[i] - (*v)[iMenor];
		contagem[indiceContagem]++;
	}

	//fazer com que contagem possua valores cumulativos
	for (long int i = 1; i < novoTam; i++)
		contagem[i] += contagem[i - 1];

	long int* ordenado = (long int*)malloc(tamV * sizeof(long int));
	bool* adicionado = (bool*)calloc(tamV, sizeof(bool));
	for (long int i = 0; i < tamV; i++) {
		long int indiceOrdenado = contagem[(*v)[i] - (*v)[iMenor]] - 1;
		while (adicionado[indiceOrdenado])
			indiceOrdenado--;
		ordenado[indiceOrdenado] = (*v)[i];
		adicionado[indiceOrdenado] = true;
	}
	(*v) = ordenado;
}



void quick_sort(long int* a, int left, int right) {
	int i, j, x, y;

	i = left;
	j = right;
	x = a[(left + right) / 2];

	while (i <= j) {
		while (a[i] < x && i < right) {
			i++;
		}
		while (a[j] > x && j > left) {
			j--;
		}
		if (i <= j) {
			y = a[i];
			a[i] = a[j];
			a[j] = y;
			i++;
			j--;
		}
	}

	if (j > left) {
		quick_sort(a, left, j);
	}
	if (i < right) {
		quick_sort(a, i, right);
	}
}