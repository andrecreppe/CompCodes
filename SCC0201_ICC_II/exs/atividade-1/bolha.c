#include <stdio.h>
#include "bolha.h"

void bolha(int *vetor, int n)
{
    int final = n - 1;
    int tmp;
    int sentinela; // Guarda último elemento trocado
    do
    {
        sentinela = 0;
        for(int i = 0; i < final; i++)
        {
            printf("C %d %d\n", i, i + 1);
            if(vetor[i] > vetor[i+1])
            {
                sentinela = i;
                printf("T %d %d\n", i, i+ 1);
                tmp = vetor[i];
                vetor[i] = vetor[i+1];
                vetor[i+1] = tmp;
            }
        }
        final = sentinela;
    } while(final > 0);
    
}