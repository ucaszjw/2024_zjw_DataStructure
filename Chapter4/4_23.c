#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int len;
    scanf("%d", &len);
    char *s = (char *)malloc(len*sizeof(char));
    scanf("%s", s);
    int i = 0;
    while (i <= len-1-i){
        if (s[i] != s[len-1-i]){
            printf("0");
            return 0;
        }
        i++;
    }
    printf("1");
    return 0;
}