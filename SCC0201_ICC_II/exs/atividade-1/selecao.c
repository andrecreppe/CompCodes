#include <stdio.h>
#include "selecao.h"

void selecao(int *vetor, int n)
{
    int iMin; //Indice do vetor de menor valor
    int tmp;
    
    for(int i = 0; i < n-1; i++)
    {
        iMin = i;
        for(int j = i + 1; j < n; j++)
        {
            printf("C %d %d\n", iMin, j);
            if(vetor[iMin] > vetor[j])
            {
                iMin = j;
            }
        }

        if(iMin != i)
        {
            printf("T %d %d\n", i, iMin);
            tmp = vetor[i];
            vetor[i] = vetor[iMin];
            vetor[iMin] = tmp;
        }        
    } 
}