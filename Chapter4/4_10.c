#include <stdio.h>
#include <string.h>

int main(){
    char str[100];
    char c;
    int i = 0;
    while ((c = getchar()) != '\n'){
        str[i] = c;
        i++;
    }
    str[i] = '\0';
    int len = strlen(str);
    char temp;
    for (int i = 0; i < len/2; i++){
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
    printf("%s", str);
    return 0;
}