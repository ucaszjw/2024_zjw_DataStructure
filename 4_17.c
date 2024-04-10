#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *Replace(char *s, char *t, char *v);
int main(){
    char *s, *t, *v, *result;
    s = (char *)malloc(100*sizeof(char));
    t = (char *)malloc(100*sizeof(char));
    v = (char *)malloc(100*sizeof(char));
    result = (char *)malloc(100*sizeof(char));
    scanf("%s", s);
    scanf("%s", t);
    scanf("%s", v);

    result = Replace(s, t, v);
    printf("%s\n", result);
}

char *Replace(char *s, char *t, char *v){
    if (strstr(s, t) == NULL){
        return s;
    }
    char *pos = strstr(s, t);
    char *result = (char *)malloc(100*sizeof(char));
    char *s1 = &s[0];
    int i = 0;
    while (s1 != pos){
        result[i]=*s1;
        s1++;
        i++;
    }
    int j = 0;
    while (v[j] != '\0'){
        result[i] = v[j];
        i++;
        j++;
    }
    s1 = pos + strlen(t);
    while (*s1 != '\0'){
        result[i] = *s1;
        s1++;
        i++;
    }
    result[i] = '\0';
    return result;
}