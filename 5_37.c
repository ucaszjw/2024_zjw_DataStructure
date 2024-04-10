#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void Delete(char *s, char delete);
int isEmpty(char *s);
int Tidy(char *s);
int main(){
    char s[100];
    scanf("%s", s);
    char delete;
    scanf(" %c", &delete);
    Delete(s, delete);
    if (isEmpty(s)){
        printf("-1\n");
        return 0;
    }
    while (!Tidy(s))
        ;    
    printf("%s\n", s);
    return 0;
}

void Delete(char *s, char delete){
    int i = 0, j = 0;
    while (s[i] != '\0'){
        if (s[i] != delete){
            s[j] = s[i];
            j++;
        }
        i++;
    }
    s[j] = '\0';
}

int isEmpty(char *s){
    int empty = 1;
    for (int i = 0; s[i] != '\0'; i++)
        if (isalpha(s[i]))
            empty = 0;
    return empty;
}

int Tidy(char *s){
    int i = 0;
    int isTidy = 1;
    while (s[i] != '\0'){
        if (s[i] == ','){
            if (s[i+1] == ',' || s[i+1] == ')'){
                int j = i;
                while (s[j] != '\0'){
                    s[j] = s[j+1];
                    j++;
                }
                isTidy = 0;
            }
        }
        else if (s[i] == '('){
            if (s[i+1] == ','){
                int j = i+1;
                while (s[j] != '\0'){
                    s[j] = s[j+1];
                    j++;
                }
                isTidy = 0;
            }
            if (s[i+1] == ')'){
                int j = i;
                while (s[j] != '\0'){
                    s[j] = s[j+2];
                    j++;
                }
                i--;
                isTidy = 0;
            }
        }
        i++;
    }
    return isTidy;
}            