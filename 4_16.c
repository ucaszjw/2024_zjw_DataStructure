#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int StrCompare(char *s, char *t, int len_s, int len_t);

int main(){
    char *s, *t;
    s = (char *)malloc(100 * sizeof(char));
    t = (char *)malloc(100 * sizeof(char));
    scanf("%s", s);
    scanf("%s", t);
    int len_s = strlen(s);
    int len_t = strlen(t);
    printf("%d", StrCompare(s, t, len_s, len_t));
    free(s);
    free(t);
    return 0;
}

int StrCompare(char *s, char *t, int len_s, int len_t){
    int i = 0, j = 0;
    while (s[i] == t[j] && i < len_s && j < len_t){
        i++;
        j++;
    }
    if (i == len_s && j == len_t)
        return 0;
    else if ((i != len_s && j != len_t && s[i] < t[j]) || (i == len_s && j != len_t))
        return -1;
    else
        return 1;
}