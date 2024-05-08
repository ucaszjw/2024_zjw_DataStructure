#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct Tnode{
    char data;
    struct Tnode *left;
    struct Tnode *right;
};
struct NodeList
{
    char data;
    int left;
    int right;
}List[100];

struct Tnode* buildTree(struct NodeList List[]);
struct Tnode* buildSubTree(struct NodeList List[], int i);
void printXianxu(struct Tnode *root);
int main(){
    int i = 0;
    char data;
    int left, right;
    while (scanf("%c %d %d", &data, &left, &right) == 3) {
        getchar();
        List[i].data = data;
        List[i].left = left;
        List[i].right = right;
        i++;
    }
    struct Tnode *root = buildTree(List);
    printXianxu(root);
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
    node->data = List[i-1].data;
    if (List[i-1].left == -1)
        node->left = NULL;
    else
        node->left = buildSubTree(List, List[i-1].left);
    if (List[i-1].right == -1)
        node->right = NULL;
    else
        node->right = buildSubTree(List, List[i-1].right);
    return node;
}

void printXianxu(struct Tnode *root){
    if (root == NULL)
        return;
    printf("%c ", root->data);
    printXianxu(root->left);
    printXianxu(root->right);
}