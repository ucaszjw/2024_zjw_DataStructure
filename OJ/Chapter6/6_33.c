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
struct Tnode* buildSubTree(int L[], int R[], int i);
int isChild(struct Tnode *root, int child, int parent);
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
    struct Tnode *root = (struct Tnode *)malloc(sizeof(struct Tnode));
    root = buildTree(L, R, i);
    int parent, child;
    scanf("%d %d", &child, &parent);
    printf("%d\n", isChild(root, child, parent));
    return 0;
}

struct Tnode* buildTree(int L[], int R[], int n){
    if (n <= 0)
        return NULL;
    struct Tnode *root = (struct Tnode *)malloc(sizeof(struct Tnode));
    root->data = L[0];
    root->left = buildSubTree(L, R, L[1]);
    root->right = buildSubTree(L, R, R[1]);
    return root;
}

struct Tnode* buildSubTree(int L[], int R[], int i){
    if (i == 0)
        return NULL;
    struct Tnode *node = (struct Tnode *)malloc(sizeof(struct Tnode));
    node->data = i;
    node->left = buildSubTree(L, R, L[i]);
    node->right = buildSubTree(L, R, R[i]);
    return node;
}

int isChild(struct Tnode *root, int child, int parent){
    if (root == NULL)
        return 0;
    if (root->data == parent){
        if (root->left != NULL && root->left->data == child)
            return 1;
        if (root->right != NULL && root->right->data == child)
            return 1;
    }
    return isChild(root->left, child, parent) || isChild(root->right, child, parent);
}