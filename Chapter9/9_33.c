#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int main(){
    int elem, chart[MAX], result[MAX];
    for (int i = 0; i < MAX; i++){
        chart[i] = 0;
        result[i] = 0;
    }
    int k = 0;
    do{
        scanf("%d", &elem);
        chart[k] = elem;
        k++;
    } while (getchar() != '\n');
    scanf("%d", &elem);

    for (int i = 0; i < k; i++){
        if (chart[i] >= elem){
            int insert = chart[i];
            int j = 0;
            while (insert < result[j])
                j++;
            for (int l = k; l > j; l--)
                result[l] = result[l-1];
            result[j] = insert;
        }
    }

    printf("%d", result[0]);
    int l = 1;
    while (result[l] != 0 || result[l+1] != 0){
        printf(" %d", result[l]);
        l++;
    }
    printf("\n");
    return 0;
}
