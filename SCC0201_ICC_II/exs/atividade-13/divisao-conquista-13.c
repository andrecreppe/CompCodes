#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

// ======== Quick Sort ========

void swap(float *a, float *b) {
  float t = *a;
  *a = *b;
  *b = t;
}

float partition(float sortArray[], float carryArray[], int l, int h) {
	int i = (l-1);
	int j;
	float pivot = sortArray[h];
	
	for (j=l; j<h; j++) {
		if (sortArray[j] <= pivot) {
			i++;
			
			swap(&sortArray[i], &sortArray[j]);
			swap(&carryArray[i], &carryArray[j]);
		}
	}
	
	swap(&sortArray[i + 1], &sortArray[h]);
	swap(&carryArray[i + 1], &carryArray[h]);
	
	return (i+1);
}

void quickSort(float sortArray[], float carryArray[], int l, int h) {
	if (h > l) {
		int part = partition(sortArray, carryArray, l, h);
		
		quickSort(sortArray, carryArray, l, part-1);
		quickSort(sortArray, carryArray, part+1, h);
	}
}

// ======== Problem ========

float dist(float x1, float x2, float y1, float y2) {
    return sqrtf(powf(x1-x2, 2.) + powf(y1-y2, 2.));
}

float findMinimum(float x[], float y[], int n) {
	int i, j;
    float min = FLT_MAX;
    
    for(i=0; i<n; i++) {
    	for(j=i+1; j<n; j++) {
    		float res = dist(x[i], x[j], y[i], y[j]);
    		
    		if(res < min) {
    			min = res;
			}
		}   
	}
        
    return min;
}

float min(float x, float y) {
	if(x < y) {
		return x;
	} else {
		return y;
	}
}

float sortClosest(float xStrip[], float yStrip[], int size, float d) {
    int i, j;
	float min = d;

    quickSort(xStrip, yStrip, 0, size-1);

    for(i=0; i<size; i++) {
    	for(j=i+1; j<size && (xStrip[j] - xStrip[i]) < min; j++) {
    		float res = dist(xStrip[i], xStrip[j], yStrip[i], yStrip[j]);
    		if (res < min) {
                min = res;
			}
		}
	}

    return min;
}

float findLeast(float x[], float y[], int n) {
    if (n <= 3) {
    	return findMinimum(x, y, n);
	}
	
	int i, j=0;

    int mid = n / 2;
    float midX = x[mid];

    float dl = findLeast(x, y, mid);
    float dr = findLeast(x+mid, y+mid, n-mid);
    float d = min(dl, dr);

    float xStrip[n];
    float yStrip[n]; 
    
    for (i=0; i<n; i++) {
    	if (fabsf(x[i] - midX) < d) {
            xStrip[j] = x[i];
            yStrip[j] = y[i];
			j++;
		}
	}

	float res =  min(d, sortClosest(xStrip, yStrip, j, d));
    return res;
}

// ======== Utils ========

void printArray(float arr1[], float arr2[], int size) {
	int i;
	
	for(i=0; i<size; i++) {
		printf("%.2f  %.2f\n", arr1[i], arr2[i]);
	}
}

// ======== Main ========

int main(int argc, char *argv[]) {
    int n, i;
    
    scanf("%d", &n);
    
    float *x = malloc(n * sizeof(float));
	float *y = malloc(n * sizeof(float));

    for(i=0; i<n; i++) {
        scanf("%f %f", &x[i], &y[i]);
    }
    
    quickSort(x, y, 0, n-1);

    printf("%.6f", findLeast(x, y, n));
    
    return 0;
}

