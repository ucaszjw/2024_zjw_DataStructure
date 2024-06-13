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
char commonParent(struct Tnode *root, char a, char b);
int findNode(struct Tnode *node, char value);
int isChild(struct Tnode *root, char child, char parent);
char findParent(struct Tnode *root, char child);
int main(){
    char arr[100];
    scanf("%s", arr);
    int n = strlen(arr);
    int index = 0;
    struct Tnode *root = buildTree(arr, &index, n);
    char a,b;
    scanf(" %c %c", &a, &b);
    printf("%c", commonParent(root, a, b));
    return 0;
}
struct Tnode* buildTree(char arr[], int* pIndex, int n){
    if (*pIndex >= n || arr[*pIndex] == '^') {
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

char commonParent(struct Tnode *root, char a, char b){
    if (isChild(root, a, b))
        return findParent(root, b);
    if (isChild(root, b, a))
        return findParent(root, a);
    while (findNode(root, a) && findNode(root, b)){
        if (findNode(root->left, a) && findNode(root->left, b))
            root = root->left;
        else if (findNode(root->right, a) && findNode(root->right, b))
            root = root->right;
        else
            return root->data;
    }
}

int findNode(struct Tnode *node, char value){
    if (node == NULL)
        return 0;
    if (node->data == value)
        return 1;
    return findNode(node->left, value) || findNode(node->right, value);
}

int isChild(struct Tnode *root, char child, char parent){
    if (root == NULL)
        return 0;
    if (root->data == parent)
        return findNode(root, child);
    return isChild(root->left, child, parent) || isChild(root->right, child, parent);
}

char findParent(struct Tnode *root, char child){
    if (root == NULL)
        return 0;
    if ((root->left && root->left->data == child) || (root->right && root->right->data == child))
        return root->data;
    char left = findParent(root->left, child);
    if (left != 0) return left;
    return findParent(root->right, child);
}