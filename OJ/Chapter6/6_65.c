#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct Tnode{
    char data;
    struct Tnode *left;
    struct Tnode *right;
};

struct Tnode* buildTree(char Xianxu[], char Zhongxu[], int n);
void printHouxu(struct Tnode *root);
int main(){
    char Xianxu[100];
    char Zhongxu[100];
    scanf("%s", Xianxu);
    scanf("%s", Zhongxu);
    int n = strlen(Xianxu);
    struct Tnode *root = buildTree(Xianxu, Zhongxu, n);
    printHouxu(root);
    return 0;
}

struct Tnode* buildTree(char Xianxu[], char Zhongxu[], int n){
    if (n <= 0)
        return NULL;
    struct Tnode *root = (struct Tnode *)malloc(sizeof(struct Tnode));
    root->data = Xianxu[0];
    int i = 0;
    while (Zhongxu[i] != Xianxu[0]){
        i++;
        if (i == n)
            return NULL;
    }
    root->left = buildTree(Xianxu + 1, Zhongxu, i);
    root->right = buildTree(Xianxu + i + 1, Zhongxu + i + 1, n - i - 1);
    return root;
}

void printHouxu(struct Tnode *root){
    if (root == NULL)
        return;
    printHouxu(root->left);
    printHouxu(root->right);
    printf("%c", root->data);
}