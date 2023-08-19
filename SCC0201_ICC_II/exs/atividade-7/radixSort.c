#include<stdio.h>
#include<stdlib.h>

int isola_digito(int num, int p, int e)
{
	int dig;
	
	dig = (num >> (p * e)) & ((1 << e) - 1);
	
	return dig;
}

void reseta_vetor(int *vetor, int tam){
	for(int i = 0; i < tam; i++){
		vetor[i] = 0;
	}
}

void counting(unsigned int vetor[], int vetor_dig[], unsigned int aux[], int chaves[], int tam, int k)
{
	int i, valor, pos;
	
	for(i = 0; i < tam; i++)
	{
		valor = vetor_dig[i];
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
		valor = vetor_dig[i];
		pos = chaves[valor];
		
		aux[pos] = vetor[i];
		
		chaves[valor] = chaves[valor] + 1;
	}
	
	for(i = 0; i < tam; i++)
	{
		vetor[i] = aux[i];
		
		if(i == tam-1)
		{
			printf("%u", vetor[i]);
		}
		else
		{
			printf("%u ", vetor[i]);
		}
	}
	reseta_vetor(chaves, k);
}

void radix_sort(unsigned int vetor[], int vetor_dig[], unsigned int aux[], int chaves[], int e, int base, int tam)
{
	int i, cont = 0;
	unsigned int maior = 0;
	
	for(i = 0; i < tam; i++)
	{
		if(vetor[i] > maior)
		{
			maior = vetor[i];
		}
	}
	
	while(maior > 0)
	{
		maior = maior/base;
		cont ++;
	}
	
	for(i = 0; i < cont; i++)
	{
		for(int j = 0; j < tam; j++)
		{
			vetor_dig[j] = isola_digito(vetor[j], i, e);
			// printf("vetor_dig[%d] = %d ", j, vetor_dig[j]);
		}
		// printf("\n");
		
		counting(vetor, vetor_dig, aux, chaves, tam, base);
		
		if(i != cont - 1)
		{
			printf("\n");
		}
	}
	
}

unsigned int *ler_vetor(unsigned int *vetor, int n)
{
	
	for(int i = 0; i < n; i++)
	{
		scanf("%u", &vetor[i]);
	}
	
	return vetor;
}

int main(int argc, char *argv[])
{
	int n, e, base = 1;
	
	scanf("%d", &e);
	scanf("%d", &n);
	
	for(int i = 0; i < e; i++)
	{
		base *= 2;
	}
	
	unsigned int *vetor = malloc(n * sizeof(int));
	int *vetor_dig = malloc(n * sizeof(int));
	unsigned int *aux = malloc(n * sizeof(int));
	int *chaves = malloc(base * sizeof(int));
	
	if(vetor == NULL)
	{
		printf("Problema ao alocar o vetor\n");
		exit(-1);
	}
	
	vetor = ler_vetor(vetor, n);
	
	radix_sort(vetor, vetor_dig, aux, chaves, e, base, n);
	
	free(vetor);
	free(vetor_dig);
	free(aux);
	free(chaves);
	
	return 0;
}



