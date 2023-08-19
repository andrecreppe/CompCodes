#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) { 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
  
int partition(int arr[], int low, int high) { 
    int pivot = arr[high];
    int i = (low - 1);
  
    for (int j = low; j <= high - 1; j++) { 
        if (arr[j] < pivot) { 
            i++;
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 

void quickSort(int arr[], int low, int high) { 
    if (low < high) {
        int pi = partition(arr, low, high); 

        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
} 

void printArray(int arr[], int size) { 
    int i; 
    for (i = 0; i < size; i++) 
        printf("%d ", arr[i]);
    printf("\n"); 
}

// ====================

int busca(int a[], int n, int x) {
  int inf = 0;
  int sup = n-1;
  int half;

  while (inf <= sup) {
    half = (inf + sup)/2;

    if (x == a[half]) {
      return 1;
    } else if (x < a[half]) {
      sup = half-1;
    } else {
      inf = half+1;
    }
  }
  return 0;
}

// ====================

int main(int argc, char *argv[]) {
    int n1, n2, i, x;
    int *v1;

    scanf("%d", &n1);
    v1=(int *)malloc(n1*sizeof(int));
    for(i=0; i<n1; i++) {
      scanf("%d", &v1[i]);
    }

    quickSort(v1, 0, n1-1);

    scanf("%d", &n2);
    for(i=0; i<n2; i++) {
      scanf("%d", &x);

      int r = busca(v1, n1, x);
      printf("%d\n", r);
    }

    return 0;
}
