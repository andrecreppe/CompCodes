#include<stdio.h>
#include<stdlib.h>

void shell(int v[], int n);
void quick(int v[], int c, int f); //recursivo

int cQk = 0; // Cont Quick
int cSh = 0; // Cont Shell

int main() {
    int n=1,*v1,*v2,*v3,j;
    scanf("%d", &n);

    int i;
    v1=(int *)malloc(n*sizeof(int)); 
    v2=(int *)malloc(n*sizeof(int)); 
    v3=(int *)malloc(n*sizeof(int));

    i = 0;
    while(i<n) {
        scanf("%d", &v1[i]);
        i++;
    }

    i = 1;
    while(i<=n) {
        for(j=0;j<i;j++){
            v2[j]=v1[j];
            v3[j]=v1[j];
        }
        
    	cQk = 0;
		cSh = 0;
        shell(v2,i);
        quick(v3,0,i-1);

        if(cSh==cQk) printf("- ");
        else if(cSh>cQk) printf("Q ");
        else if(cSh<cQk) printf("S ");

        i++;
	}

    return 0;
}

void shell(int v[], int n) {
    int gap = 1;
    int k,i,j;          
 
    while(gap <= n) {
        gap *= 2;
    }
    gap = gap / 2 - 1;
    while(gap > 0) {
        for ( k = 0; k < gap; k++){
            for (i = k + gap; i < n; i += gap){
            	cSh++;
                int x = v[i];
                j = i - gap;
                if(j>=0) cSh++;
                while(j >= 0 && v[j] > x) {
                    v[j+gap] = v[j];
                    cSh++;
                    j-=gap;
                    if(j>=0) cSh++;
                }
                v[j+gap] = x;
                cSh++;
            }
        }
        gap /= 2;
    }
}

void quick(int v[], int c, int f) {
    if(c >= f) return;
    int m = (c+f)/ 2; 
    int pivo = v[m]; 
    cQk++;
    int i = c;
    int j = f;
    while(1){
    	cQk++;
        while(v[i]< pivo){
            i++;
            cQk++;
        } 
        cQk++;
        while(v[j]> pivo){
            j--;
            cQk++;
        }
        if(j<=i) {
    		break;
    	}
		cQk+=3;	
        int tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
        i++;
        j--;
    }
    quick(v,c,j);
    quick(v,j+1,f);
}
