#include<stdio.h>
#include<stdlib.h>

void unir_vetores(int vetor[], int i1, int f1, int i2, int f2, int vet_aux[], int *trocas, int *comp)
{
  int cont1 = i1;
  int cont2 = i2;
  int j = 0;
  
  
  while(cont1 <= f1 && cont2 <= f2)
  {
    *comp = *comp + 1;
	
    if(vetor[cont1] <= vetor[cont2])
    { 
      vet_aux[j] = vetor[cont1];
      *trocas = *trocas + 1;
      
      j++;
      cont1++;
    }
    else
    {
      vet_aux[j] = vetor[cont2];
      *trocas = *trocas + 1;
      
      j++;
      cont2++;
    }
  }	

  while(cont1 <= f1)
  {
    vet_aux[j] = vetor[cont1];
    *trocas = *trocas + 1;
    
    j++;
    cont1++;
  }
		
  while(cont2 <= f2)
  {
    vet_aux[j] = vetor[cont2];
    *trocas = *trocas + 1;
    
    j++;
    cont2++;
  }

  j = 0;
  
  for (int i = i1; i <= f2; i++, j++)
  {		
    vetor[i] = vet_aux[j];
    *trocas = *trocas + 1;
  }
}

void merge(int vetor[], int inicio, int fim, int vet_aux[], int *trocas, int *comp)
{
  int meio;
	
  if(inicio >= fim)
  {
    return;
  }
	
  meio = (inicio + fim)/2;
	
  merge(vetor, inicio, meio, vet_aux, trocas, comp);
  merge(vetor, meio+1, fim, vet_aux, trocas, comp);
  unir_vetores(vetor, inicio, meio, meio+1, fim, vet_aux, trocas, comp);
	
}

void merge_sort(int vetor[], int tam, int *trocas, int *comp)
{
  int *vet_aux = (int*) malloc(sizeof(int) * tam);
	
  if(vet_aux == NULL)
  {
    printf("Erro de alocação\n");
    exit(-1);
  }
	
  merge(vetor, 0, tam-1, vet_aux, trocas, comp);
	
  free(vet_aux);
	
}

void insertion_sort(int vetor[], int tam, int *trocas, int *comp)
{
  int val_atual, i, j;
	
  for(i = 1; i < tam; i++)
  {
    val_atual = vetor[i];
    *trocas = *trocas + 1;
    j = i - 1;
    
    while(j >= 0)
    {
      *comp = *comp + 1;
      
      if(val_atual < vetor[j])
      {
        vetor[j+1] = vetor[j];
        *trocas = *trocas + 1;
        j--;
      }
      else
      {
        break;
      }
    }
      
    vetor[j+1] = val_atual;
    *trocas = *trocas + 1;
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
	int n;
	
	scanf("%d", &n);

  int *tamanhos = malloc(n * sizeof(int));
  int *vetor = malloc(sizeof(int));
  int *vetor_lido = malloc(sizeof(int));
  int trocas, comp;
  int *vet_trocas, *vet_comp;
  int i;

  vet_trocas = &trocas;
  vet_comp = &comp;

  for(i = 0; i < n; i++)
  {
    scanf("%d", &tamanhos[i]);
  }
	
  for(i = 0; i < n; i++)
  {
    vetor = realloc(vetor, sizeof(int)*tamanhos[i]);
    
    vetor_lido = realloc(vetor_lido, sizeof(int)*tamanhos[i]);

    vetor_lido = ler_vetor(vetor_lido, tamanhos[i]);
    
    for(int k = 0; k < tamanhos[i]; k++)
    {
      vetor[k] = vetor_lido[k];
    }

    trocas = 0;
    comp = 0;

    insertion_sort(vetor, tamanhos[i], vet_trocas, vet_comp);

    printf("I %d %d %d\n", tamanhos[i], trocas, comp);

    trocas = 0;
    comp = 0;
    
    for(int k = 0; k < tamanhos[i]; k++)
    {
      vetor[k] = vetor_lido[k];
    }

    merge_sort(vetor, tamanhos[i], vet_trocas, vet_comp);

    printf("M %d %d %d\n", tamanhos[i], trocas, comp);
  }
	
	free(vetor);
	free(vetor_lido);
	free(tamanhos);
	
	return 0;
}
