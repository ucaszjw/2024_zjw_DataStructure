#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct Tnode{
    int data;
    struct Tnode *left;
    struct Tnode *right;
};

struct Tnode* buildTree(int L[], int R[], int n);
struct Tnode* buildSubTree(int L[], int R[], int i, int offset);
struct Tnode* findPalace(struct Tnode *root, int pos);
void insertTree(struct Tnode *root, struct Tnode *insRoot);
void printZhongxu(struct Tnode *root);
int main(){
    int L[100];
    int R[100];
    int i = 0;
    do{
        scanf("%d", &L[i]);
        i++;
    } while ((getchar() != '\n'));
    i = 0;
    do{
        scanf("%d", &R[i]);
        i++;
    } while ((getchar() != '\n'));
    struct Tnode *root = buildTree(L, R, i);

    int pos;
    scanf("%d", &pos);
    struct Tnode *p = findPalace(root, pos);

    int Li[100];
    int Ri[100];
    int j = 0;
    do{
        scanf("%d", &Li[j]);
        j++;
    } while ((getchar() != '\n'));
    j = 0;
    do{
        scanf("%d", &Ri[j]);
        j++;
    } while ((getchar() != '\n'));
    struct Tnode *insRoot = buildTree(Li, Ri, j);
    insertTree(p, insRoot);
    printZhongxu(root);
    return 0;
}

struct Tnode* buildTree(int L[], int R[], int n){
    if (n <= 0)
        return NULL;
    int offset = L[0]-1;
    struct Tnode *root = (struct Tnode *)malloc(sizeof(struct Tnode));
    root->data = L[0];
    root->left = buildSubTree(L, R, L[1], offset);
    root->right = buildSubTree(L, R, R[1], offset);
    return root;
}

struct Tnode* buildSubTree(int L[], int R[], int i, int offset){
    if (i == 0)
        return NULL;
    struct Tnode *node = (struct Tnode *)malloc(sizeof(struct Tnode));
    node->data = i;
    node->left = buildSubTree(L, R, L[i-offset], offset);
    node->right = buildSubTree(L, R, R[i-offset], offset);
    return node;
}

struct Tnode* findPalace(struct Tnode *root, int pos){
    if (root == NULL)
        return NULL;
    if (root->data == pos)
        return root;
    struct Tnode *left = findPalace(root->left, pos);
    struct Tnode *right = findPalace(root->right, pos);
    if (left != NULL)
        return left;
    if (right != NULL)
        return right;
    return NULL;
}

void insertTree(struct Tnode *root, struct Tnode *insRoot){
    if (root == NULL)
        return;
    if (root->left == NULL){
        root->left = insRoot;
        return;
    }
    if (root->right == NULL){
        root->right = insRoot;
        return;
    }
    insertTree(root->left, insRoot);
}

void printZhongxu(struct Tnode *root){
    if (root == NULL)
        return;
    printZhongxu(root->left);
    printf("%d ", root->data);
    printZhongxu(root->right);
}