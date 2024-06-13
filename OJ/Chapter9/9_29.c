#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int find(int chart[], int k, int elem);
int main(){
    int elem, chart[MAX], match[MAX];
    for (int i = 0; i < MAX; i++){
        chart[i] = 0;
        match[i] = 0;
    }
    int k = 0;
    do{
        scanf("%d", &elem);
        chart[k] = elem;
        k++;
    } while (getchar() != '\n');
    int l = 0;
    do{
        scanf("%d", &elem);
        match[l] = elem;
        l++;
    } while (getchar() != '\n');
    
    for (int i = 0; i < l-1; i++)
        printf("%d ", find(chart, k, match[i]));
    printf("%d\n", find(chart, k, match[l-1]));
    return 0;    
}

int find(int chart[], int k, int elem){
    for (int i = 0; i < k; i++)
        if (chart[i] == elem)
            return 1;
    return 0;
}