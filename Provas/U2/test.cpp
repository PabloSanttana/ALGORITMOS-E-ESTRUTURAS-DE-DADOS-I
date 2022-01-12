#include "pch.h"

#include "./ordenacao.h"

#include <windows.h>


TEST(TestCaseName, TestName) {
    float tempoTotalMedia = 0.0;
    float vetorTime[20];
  
    for (int varregura = 0; varregura < 20; varregura++) {
        LARGE_INTEGER tempoInicial, tempoFinal, freq;
        float tempoTotal;

        struct array* v;
        // 43000
        long int tamanho = 43000;
        v = inicializar(tamanho);

        // inserirElemetoOrdenado(v);
       //  inserirElemetoaleatorios(v);
          inserirElemetoDecrescente(v);
            
        
         // printfVetor(v);
      //  printf("[%ld] / [%ld] \n", v->elementos[0], v->elementos[tamanho - 1]);
        
       // printf("\n");
        // iniciar a contagem tempo
        QueryPerformanceCounter(&tempoInicial);

       // selectionSorInPlace(v);
       // bubbleSort(v);
       // insertionSort(v);
       // mergeSort(v->elementos, v->tamanho);
        quickSort(v->elementos, 0, v->tamanho -1 );
       // quick_sort(v->elementos, 0, v->tamanho - 1);
       
       // quickSortPivoRandomizada(v->elementos, 0, v->tamanho -1);
       // countingSort(&(v->elementos), v->tamanho);

        QueryPerformanceCounter(&tempoFinal);
        QueryPerformanceFrequency(&freq);
        tempoTotal = ( (float)(tempoFinal.QuadPart - tempoInicial.QuadPart) / freq.QuadPart ) * 1000;
        vetorTime[varregura] = tempoTotal;
        tempoTotalMedia = tempoTotal + tempoTotalMedia;
        printf("tempo = %Lf \n", tempoTotal );
     
       // printfVetor(v);
        printf("[%ld] / [%ld] \n", v->elementos[0], v->elementos[tamanho - 1]);

      
        free(v);

    }

    printf("Media tempo = %Lf \n", tempoTotalMedia / 20);
    printf("mediana tempo = %Lf \n", CalcularMediana(vetorTime, 20));
   
    for (int i = 0; i < 20; i++)
    {
        printf("[%Lf]", vetorTime[i]);
    }

//  EXPECT_TRUE(true);
  
}