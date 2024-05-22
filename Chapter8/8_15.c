#include <stdio.h>
#include <stdlib.h>

int main(){
    int lowbound, highbound, space;
    scanf("%d %d %d", &lowbound, &highbound, &space);
    int *tag = (int *)malloc(sizeof(int) * (highbound - lowbound) / space);
    for (int i = 0; i < (highbound - lowbound) / space; i++)
        scanf(" %d", &tag[i]);
    int notEmpty = 0;
    for (int i = 0; i < (highbound - lowbound) / space; i++)
        if (tag[i] == 0)
            notEmpty = 1;
    if (notEmpty == 0){
        printf("0 0 0\n");
        return 0;
    }
    
    int i = 0;
    while (i < (highbound - lowbound) / space){
        int j = i, count = 0;
        if (tag[j] == 1){
            i++;
            continue;
        }
        while (tag[j] == 0){
            count++;
            j++;
        }
        if (count >= 1)
            printf("%d %d %d\n", 0, lowbound + i * space, count * space);
        i = j;
    }
    return 0;
}