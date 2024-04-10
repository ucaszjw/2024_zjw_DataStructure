#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void buildr(char *s, char *t, char *r, int len_s, int len_t);
int findst(char *s, char *t, int len_t, int now_s);
int getPos(char *s, char *r, int len_s, int i);

int main(){
    char *s, *t, *r;
    s = (char *)malloc(100 * sizeof(char));
    t = (char *)malloc(100 * sizeof(char));
    r = (char *)malloc(100 * sizeof(char));
    scanf("%s", s);
    scanf("%s", t);
    int len_s = strlen(s);
    int len_t = strlen(t);
    buildr(s, t, r, len_s, len_t);
    int len_r = strlen(r);
    if (len_r == 0){
        printf("-1");
        free(s);
        free(t);
        free(r);
        return 0;
    }
    printf("%s ", r);
    int pos, i = 0;
    while (i < len_r && (pos=getPos(s, r, len_s, i)) != -1){
        printf("%d", pos);
        i++;
    }
    free(s);
    free(t);
    free(r);
    return 0;
}

void buildr(char *s, char *t, char *r, int len_s, int len_t){
    int now_s = 0, now_t = 0, now_r = 0;
    while (now_s < len_s){
        if (!findst(s, t, len_t, now_s) && !findst(s, r, now_r, now_s)){
            r[now_r] = s[now_s];
            now_r++;
        }
        now_s++;
    }
    r[now_r] = '\0';
}

int findst(char *s, char *t, int len_t, int now_s){
    int now_t = 0;
    while (now_t < len_t){
        if (s[now_s] == t[now_t])
            return 1;
        now_t++;
    }
    return 0;    
}

int getPos(char *s, char *r, int len_s, int i){
    int now_s = 0;
    while (now_s < len_s){
        if (s[now_s] == r[i])
            return now_s;
        now_s++;
    }
    return -1;
}    