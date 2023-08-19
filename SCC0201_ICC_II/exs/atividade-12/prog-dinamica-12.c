#include <stdio.h>
#include <stdlib.h>

int findPathRec(int pos, int **neighbor, int *cache, int *side, int *below, int matSize, int horzSize) {
	if(!(pos >= matSize)) {
		if(!(cache[pos] != -1)) {
			// Para baixo v
			if(!(pos <= (matSize - horzSize))) {
				below[pos] = -1;
			} else {
				int perBelow = neighbor[pos][pos + horzSize - 1];
				below[pos] = findPathRec((pos + horzSize), neighbor, cache, side, below, matSize, horzSize) + perBelow;
			}
			
			// Para o lado >
			if(((pos + 1) % horzSize == 0) && (pos != 0)) {
				side[pos] = -1;
			} else{
				int perSide = neighbor[pos][pos];
				side[pos] = findPathRec((pos + 1), neighbor, cache, side, below, matSize, horzSize) + perSide;
			}
			
			// Melhor caminho
			if(!(side[pos] <= below[pos])){
				cache[pos] = side[pos];
			} else{
				cache[pos] = below[pos];
			}
		}
		
		return cache[pos];
	}
	
	return 0;
}

int main(int argc, char *argv[]){
	int i, vertSize, horzSize;
	int lin, col, nPeople;
	int initialPos = 0;
	
	// Input
	scanf("%d", &vertSize);
	scanf("%d", &horzSize);
	
	int matSize = (vertSize * horzSize) - 1;
	int nStreet = 2 * (vertSize * horzSize) - (vertSize + horzSize);
	
	int *cache = malloc(sizeof(int) * (matSize + 1));
	int *side = malloc(sizeof(int) * (matSize + 1));
	int *below = malloc(sizeof(int) * (matSize + 1));
	
	for(i=0; i<matSize+1; i++) {
		cache[i] = -1;
	}
	
	int **neighbor = malloc(matSize * sizeof(int*));
	for(i=0; i<matSize; i++){
		neighbor[i] = malloc(matSize * sizeof(int));
	}
	
	for(i=0; i<nStreet; i++){
		scanf("%d", &lin);
		scanf("%d", &col);
		scanf("%d", &nPeople);
		neighbor[lin][col-1] = nPeople;
	}

	int res = findPathRec(initialPos, neighbor, cache, side, below, matSize, horzSize);
	printf("%d", res);
	
	return 0;
}

