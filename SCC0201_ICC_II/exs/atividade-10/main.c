#include <stdio.h>
#include <stdlib.h>

int makeHash(int num, int size) {
    return num % size;
}

void insert(int *table, int size, int num) {
    int pos = makeHash(num, size);

    while (table[pos] != -1) {
        if(table[pos] == num) break;
        pos = makeHash(pos+1, size);
    }

    table[pos] = num;
}

int search(int *table, int size, int num) {
    int pos = makeHash(num, size);

	int i;
    for(i=0; i<size; i++) {
        if(table[pos] == num) return pos;
        pos = makeHash(pos+1, size);
    }

    return -1;
}

void removal(int *table, int size, int num) {
    int pos = makeHash(num, size);

	int i;
    for(i=0; i<size; i++) {
        if(table[pos] == num){
            table[pos] = -1;
            break;
        }

        pos = makeHash(pos+1, size);
    }
}

int main() {
    int cap, n1, n2, n3, val, i;

    scanf("%d", &cap);

    int *table = (int*) calloc(cap, sizeof(int));
	for(i =0; i<cap; i++){
        table[i] = -1;
    }

    scanf("%d", &n1);

    for (i = 0; i < n1; i++) {
        if(i < cap) {
            scanf("%d", &val);
            insert(table, cap, val);
        } else {
            scanf("%d", &val);
        }
    }

    scanf("%d", &n2);

    for (i = 0; i < n2; i++) {
        scanf("%d", &val);
        removal(table, cap, val);
    }

    scanf("%d", &n3);

    for (i = 0; i < n3; i++) {
        scanf("%d", &val);
        printf("%d ", search(table, cap, val));
    }
}
