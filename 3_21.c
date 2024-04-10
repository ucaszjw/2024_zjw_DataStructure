#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 100

void push(char c);
char pop();
int precedence(char c);
void transform(char infix[], char postfix[]);
char stack[MAX];
int top = -1;

int main(){
    char infix[MAX], postfix[MAX];
    fgets(infix, MAX, stdin);

    transform(infix, postfix);
    printf("%s", postfix);
    return 0;
}

void push(char c){
    stack[++top] = c;
}

char pop(){
    return stack[top--];
}

int precedence(char c){
    if (c == '*' || c == '/')
        return 2;
    if (c == '+' || c == '-')
        return 1;
    return 0;
}

void transform(char infix[], char postfix[]){
    int i, j = 0;
    char c;
    for (i = 0; infix[i] != '\0'; i++){
        if (isalpha(infix[i]))
            postfix[j++] = infix[i];
        else if (infix[i] == '(')
            push(infix[i]);
        else if (infix[i] == ')'){
            while ((c = pop()) != '(')
                postfix[j++] = c;
        }
        else{
            while (top != -1 && precedence(stack[top]) >= precedence(infix[i]))
                postfix[j++] = pop();
            push(infix[i]);
        }
    }
    while (top != -1)
        postfix[j++] = pop();
    postfix[j] = '\0';
}