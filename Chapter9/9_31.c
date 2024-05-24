#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct Tnode{
    int data;
    struct Tnode *left;
    struct Tnode *right;
};
struct NodeList
{
    int data;
    int left;
    int right;
}List[100];

struct Tnode* buildTree(struct NodeList List[]);
struct Tnode* buildSubTree(struct NodeList List[], int i);
int isBST(struct Tnode *root);
int main(){
    int i = 0;
    int data;
    int left, right;
    char buf[100];
    while (fgets(buf, 100, stdin) != NULL && buf[0] != '\n') {
        sscanf(buf, "%d %d %d", &data, &left, &right);
        List[i].data = data;
        List[i].left = left;
        List[i].right = right;
        i++;
    }
    struct Tnode *root = buildTree(List);
    printf("%d\n", isBST(root) ? 1 : 0);
    return 0;
}

struct Tnode* buildTree(struct NodeList List[]){
    struct Tnode *root = (struct Tnode *)malloc(sizeof(struct Tnode));
    root->data = List[0].data;
    if (List[0].left == -1)
        root->left = NULL;
    else
        root->left = buildSubTree(List, List[0].left);
    if (List[0].right == -1)
        root->right = NULL;
    else
        root->right = buildSubTree(List, List[0].right);
    return root;
}

struct Tnode* buildSubTree(struct NodeList List[], int i){
    struct Tnode *node = (struct Tnode *)malloc(sizeof(struct Tnode));
    node->data = List[i].data;
    if (List[i].left == -1)
        node->left = NULL;
    else
        node->left = buildSubTree(List, List[i].left);
    if (List[i].right == -1)
        node->right = NULL;
    else
        node->right = buildSubTree(List, List[i].right);
    return node;
}

int isBST(struct Tnode *root){
    if (root == NULL)
        return 1;
    if (root->left != NULL && root->left->data > root->data)
        return 0;
    if (root->right != NULL && root->right->data < root->data)
        return 0;
    return isBST(root->left) && isBST(root->right);
}