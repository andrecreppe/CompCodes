#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bolha.h"
#include "selecao.h"

int main()
{
    char tipo[10];
    int n;
    int *vetor;
    //Leitura dos dados (input)
    scanf("%s", tipo);
    scanf("%d", &n);
    vetor = (int *) malloc(n*sizeof(int));
    if(vetor != NULL)
    {
        for(int i = 0; i < n; i++)
        {
            scanf("%d", &vetor[i]);
        }
    }
    
    //Inicio da lógica de ordenação
    if(strcmp(tipo, "bolha") == 0)
    {
        bolha(vetor, n);
    }
    else if(strcmp(tipo, "selecao") == 0)
    {
        selecao(vetor, n);
    }
    else
    {
        printf("Tipo de ordenação não encontrado\n");
        return -1;
    }

    //Exibe o vetor ordenado
    for(int i = 0; i < n; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("\n");
    free(vetor);    
}