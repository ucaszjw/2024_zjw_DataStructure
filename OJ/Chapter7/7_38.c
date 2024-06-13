#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printHouxu(char n[], int L[], int R[], int i);
int main() {
    int numV;
    scanf("%d", &numV);
    getchar();
    int *L, *R;
    char *n;
    L = (int *)malloc(numV * sizeof(int));
    R = (int *)malloc(numV * sizeof(int));
    n = (char *)malloc(numV * sizeof(char));
    for (int i = 0; i < numV; i++) {
        L[i] = 0;
        R[i] = 0;
    }

    char str[100];
    for (int i = 0; i < numV; i++){
        fgets(str, 100, stdin);
        if (strlen(str) > 4){
            n[i] = str[0];
            L[i] = str[4] - '0';
            R[i] = str[2] - '0';
        }
        else
            n[i] = str[0];
    }
    printHouxu(n, L, R, 0);
    return 0;
}

void printHouxu(char n[], int L[], int R[], int i) {
    if (i >= 0 && n[i] != '0') {
        if (L[i] != 0) {
            printHouxu(n, L, R, L[i]);
        }
        if (R[i] != 0) {
            printHouxu(n, L, R, R[i]);
        }
        printf("%c", n[i]);
    }
}