#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Tnode{
    char data;
    struct Tnode *firstChild;
    struct Tnode *nextSibling;
};

struct NodeList
{
    char data;
    int child;
    int sibling;
}List[100];

struct Tnode* buildTree(struct NodeList List[]);
struct Tnode* buildSubTree(struct NodeList List[], int i);
void printAoruList(struct Tnode *root, int indent);
int main(){
    int i = 0;
    char data;
    int child, sibling;
    while (scanf("%c %d %d", &data, &child, &sibling) == 3) {
        getchar();
        List[i].data = data;
        List[i].child = child;
        List[i].sibling = sibling;
        i++;
    }
    struct Tnode *root = buildTree(List);
    printAoruList(root, 0);
    return 0;
}

struct Tnode* buildTree(struct NodeList List[]){
    if (List[0].data == -1)
        return NULL;
    struct Tnode *root = (struct Tnode *)malloc(sizeof(struct Tnode));
    root->data = List[0].data;
    root->firstChild = buildSubTree(List, List[0].child);
    root->nextSibling = buildSubTree(List, List[0].sibling);
    return root;
}

struct Tnode* buildSubTree(struct NodeList List[], int i){
    if (i == -1)
        return NULL;
    struct Tnode *node = (struct Tnode *)malloc(sizeof(struct Tnode));
    node->data = List[i-1].data;
    node->firstChild = buildSubTree(List, List[i-1].child);
    node->nextSibling = buildSubTree(List, List[i-1].sibling);
    return node;
}

void printAoruList(struct Tnode *root, int indent){
    if (root == NULL)
        return;
    for (int i = 0; i < indent; i++)
        printf("-");
    printf("%c\n", root->data);
    printAoruList(root->firstChild, indent + 1);
    printAoruList(root->nextSibling, indent);
}