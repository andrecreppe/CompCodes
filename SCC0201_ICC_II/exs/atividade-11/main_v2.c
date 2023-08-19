#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000
#define true 1
#define false 0

int findOverlap(char* s1, char* s2) {
	int i = 0, j = 0;
	int n = 0, firstPos = 0, first = true;
    int s1Len = strlen(s1), s2Len = strlen(s2);
    
	while(true) {
//		printf("\n(%d) %c <> (%d) %c", i, s1[i], j, s2[j]);
		if(s1[i] == s2[j]) {
			j++;
			n++;
			
			if(first) {
				firstPos = i;
				first = false;
			}
		} else if(n > 0) {	
			j = 0;
			n = 0;
			
			i = firstPos;
			first = true;
		}
		
		i++;
		
		if(i == s1Len) break;
		if(n == s2Len) break;
	}
    
    return n;
}

int main() {
	int i, j, k;
	int n, overlap, maxOverlap, readA, readB, isSubstring;
	int first = true;
	char newRead[MAX_SIZE] = "";
	
	// Reads quantity
	scanf("%d", &n);
	
	// Reads input
	char reads[n+1][MAX_SIZE];
	for(i=0; i<n; i++) {
		scanf("%s", reads[i]);
		fflush(stdin);
	}
	
	for(k=n; k>1; k--) {
//		printf("\n");
		
		maxOverlap = 0; first = true;
		
		// Reads permutation
		for(i=0; i<n; i++) {
			for(j=0; j<n; j++) {
				isSubstring = false;
				
				if(i == j) continue; // do not compare the same items
				
				isSubstring = (strstr(reads[i], reads[j]) != NULL);
				if(isSubstring) { // substring
					overlap = strlen(reads[j]);
				} else { // overlap
					overlap = findOverlap(reads[i], reads[j]);
				}
				
				if(overlap > maxOverlap || first) {
					maxOverlap = overlap;
					readA = i;
					readB = j;
					first = false;
					
					memset(newRead, 0, strlen(newRead));
					if(isSubstring) { // substring
						strncpy(newRead, reads[i], strlen(reads[i])+1);
					} else { // overlap
						strncpy(newRead, reads[i], strlen(reads[i]) - overlap);
						strcat(newRead, reads[j]);
					}
				}
				
//				printf("%s <> %s = %d overlaps\n", reads[i], reads[j], overlap);
			}
		}
		
//		printf("> Max overlap: %d\n", maxOverlap);
//		printf("> Fused read: (%d) %s + (%d) %s = %s\n", readA, reads[readA], readB, reads[readB], newRead);
		
//		for(i=0; i<n; i++) {
//			printf("# %s ", reads[i]);
//		}
//		printf("\n");
		
		if(readA > readB) readB++;
		
	    // Remove fused reads
		for(i = readA; i<n-1; i++) {
			strncpy(reads[i], reads[i+1], strlen(reads[i+1])+1);
		} n--;
		
//		for(i=0; i<n; i++) {
//			printf("%s # ", reads[i]);
//		}
//		printf("\n");
		
		for(i = readB-1; i<n-1; i++) {
			strncpy(reads[i], reads[i+1], strlen(reads[i+1])+1);
		}
		
//		for(i=0; i<n; i++) {
//			printf("%s # ", reads[i]);
//		}
//		printf("\n");
		
		// Shift elements forward
		for(i=n-1; i>=0; i--) {
			strncpy(reads[i], reads[i-1], strlen(reads[i-1])+1);
		}
		strncpy(reads[0], newRead, strlen(newRead)+1);
		
//		for(i=0; i<n; i++) {
//			printf("# %s ", reads[i]);
//		}
//		printf("\n");
	}
	
	printf("%s", reads[0]);

	return 0;	
}

