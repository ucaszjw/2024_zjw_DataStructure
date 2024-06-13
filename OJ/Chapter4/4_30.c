#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int strnum(char *s, char *str);
int main(){
    char s[100];
    scanf("%s", s);
    int len = strlen(s);
    char str[100];
    char longest[100];
    longest[0] = '\0';
    for(int i = 0; i < len; i++){
        for (int j = i+1; j < len; j++){
            for (int k = i; k <= j; k++)
                str[k-i] = s[k];
            str[j-i+1] = '\0';
            if (strlen(str) > strlen(longest) && strnum(s, str) > 1)
                strcpy(longest, str);
        }        
    }
    if (longest[0] == '\0'){
        printf("-1\n");
        return 0;
    }
    printf("%s ", longest);
    printf("%ld\n", strstr(s, longest) - s);
    return 0;
}

int strnum(char *s, char *str) {
    int len_s = strlen(s);
    int len_str = strlen(str);
    int count = 0;
    for (int i = 0; i <= len_s - len_str; i++)
        if (strncmp(s + i, str, len_str) == 0)
            count++;
    return count;
}