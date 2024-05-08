#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct Tnode{
    char data;
    struct Tnode *left;
    struct Tnode *right;
};

struct Tnode* buildTree(char arr[], int* pIndex, int n);
void printZhongxu(struct Tnode *root);
int main(){
    char arr[100];
    scanf("%s", arr);
    int n = strlen(arr);
    int index = 0;
    struct Tnode *root = buildTree(arr, &index, n);
    printZhongxu(root);
}

struct Tnode* buildTree(char arr[], int* pIndex, int n){
    if (*pIndex >= n || arr[*pIndex] == '#') {
        (*pIndex)++;
        return NULL;
    }
    struct Tnode *root = (struct Tnode *)malloc(sizeof(struct Tnode));
    root->data = arr[*pIndex];
    (*pIndex)++;
    root->left = buildTree(arr, pIndex, n);
    root->right = buildTree(arr, pIndex, n);
    return root;
}

void printZhongxu(struct Tnode *root){
    if (root == NULL)
        return;
    if (root->left != NULL && (root->left->left != NULL || root->left->right != NULL) && ((root->data == '*' || root->data == '/') && (root->left->data != '+' || root->left->data != '-'))) {
        printf("(");
        printZhongxu(root->left);
        printf(")");
    }
    else
        printZhongxu(root->left);
    printf("%c", root->data);
    if (root->right != NULL && (root->right->left != NULL || root->right->right != NULL) && ((root->data == '*' || root->data == '/') && (root->right->data != '+' || root->right->data != '-') || (root->data == '-' && (root->right->data == '+' || root->right->data == '-')))) {
        printf("(");
        printZhongxu(root->right);
        printf(")");
    }
    else
        printZhongxu(root->right);
}