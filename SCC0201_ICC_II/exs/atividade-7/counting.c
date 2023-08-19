#include<stdio.h>
#include<stdlib.h>

void counting(int vetor[], int aux[], int chaves[], int tam, int k)
{
	int i, valor, pos;
	
	for(i = 0; i < tam; i++)
	{
		valor = vetor[i];
		chaves[valor] = chaves[valor] + 1;
	}
	
	pos = tam;

	for(i = k-1; i >= 0; i--)
	{
		chaves[i] = pos - chaves[i];
		pos = chaves[i];
	}
	
	for(i = 0; i < tam; i++)
	{
		valor = vetor[i];
		pos = chaves[valor];
		
		if(i < tam-1)
		{
			printf("%d %d\n", valor, pos);
		}
		else
		{
			printf("%d %d", valor, pos);
		}
		
		aux[pos] = vetor[i];
		
		chaves[valor] = chaves[valor] + 1;
	}
	
	for(i = 0; i < tam; i++)
	{
		vetor[i] = aux[i];
	}

}

int *ler_vetor(int *vetor, int n)
{
	
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &vetor[i]);
	}
	
	return vetor;
}

int main(int argc, char *argv[])
{
	int k, n;
	
	scanf("%d", &k);
	scanf("%d", &n);
	
	int *vetor = malloc(n * sizeof(int));
	int *vetor_aux = malloc(n * sizeof(int));
	int *chaves = malloc(k * sizeof(int));

	vetor = ler_vetor(vetor, n);
	
	for(int i = 0; i < k; i++)
	{
		chaves[i] = 0;
	}
	
	counting(vetor, vetor_aux, chaves, n, k);
	
	free(vetor);
	free(vetor_aux);
	free(chaves);
	
	return 0;
}
