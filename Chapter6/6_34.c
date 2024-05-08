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
int isDescendant(struct Tnode *root, int child, int parent);
int findNode(struct Tnode *node, int value);
int main(){
    int T[100];
    int L[100];
    int R[100];
    int i = 0;
    do
    {
        scanf("%d", &T[i]);
        i++;
    } while ((getchar() != '\n'));
    i = 0;
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
    printf("%d\n", isDescendant(root, child, parent));
    return 0;
}

struct Tnode* buildTree(int L[], int R[], int n){
    if (n <= 0)
        return NULL;
    struct Tnode *root = (struct Tnode *)malloc(sizeof(struct Tnode));
    root->data = 1;
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

int isDescendant(struct Tnode *root, int child, int parent){
    if (root == NULL)
        return 0;
    if (root->data == parent)
        return findNode(root, child);
    return isDescendant(root->left, child, parent) || isDescendant(root->right, child, parent);
}

int findNode(struct Tnode *node, int value){
    if (node == NULL)
        return 0;
    if (node->data == value)
        return 1;
    return findNode(node->left, value) || findNode(node->right, value);
}