// check tree is Subtree from another tree with AVL self balancing self before
// answering exam on hackkerrank
// https://www.hackerrank.com/contests/post-test/challenges/sub-tree
// failed testcase 1

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


struct Node{
    int data;
    struct Node *left, *right;
    int height;
};

int max(int a, int b)
{
    return (a > b) ? a:b;
}
int height(struct Node *node)
{
    if(node == NULL)
        return 0;
    return node->height;
}
struct Node *newNode(int data)
{
    struct Node *node = (struct Node*) malloc(sizeof(struct Node));

    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
};

struct Node* putarKanan(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    return x;
};
struct Node *putarKiri(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    return y;
};
int seimbang(struct Node *node)
{
    if(node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

struct Node *insert(struct Node* node, int data)
{
    if(node == NULL) return newNode(data);

    if(data < node->data)
        node->left = insert(node->left, data);
    if(data > node->data)
        node->right = insert(node->right, data);
    else
        return node;

    node->height = 1+max(height(node->left), height(node->right));

    ///left left case
    if(seimbang(node) > 1 && data < node->left->data)
        return  putarKanan(node);

    ///right right case
    if(seimbang(node) < -1 && data > node->right->data)
        return  putarKiri(node);

    ///left right
    if(seimbang(node) > 1 && data > node->left->data)
    {
        node->left = putarKiri(node->left);
        return putarKanan(node);
    }

    ///right left case
    if(seimbang(node) < -1 && data < node->right->data)
    {
        node->right = putarKanan(node->right);
        return putarKiri(node);
    }

    return node;
};

void preorder(struct Node *node)
{
    if(node != NULL)
    {
        printf("%d", node->data);
        preorder(node->left);
        preorder(node->right);
    }
}


int sama(struct Node *node1, struct Node *node2)
{
    if(node1 == NULL && node2 == NULL)  return 1;
    if(node1 == NULL || node2 == NULL)  return 0;
    
    return (node1->data == node2->data && 
           sama(node1->left, node2->left) &&
           sama(node2->right, node2->right));
}

int cekSubtree(struct Node *root1, struct Node *root2)
{
    if(root1 == NULL || root2 == NULL)   
        return 0;
    
    if(sama(root1, root2))
        return 1;
    
    return cekSubtree(root1->left, root2)||cekSubtree(root1->right, root2);
}
int main()
{
    struct Node *root1 = NULL;
    struct Node *root2 = NULL;

    int n1, n2, i = 0;
    scanf("%d %d", &n1, &n2);
    int angka;
    for(i=0; i<n1; i++)
    {
        scanf("%d", &angka);
        root1 = insert(root1, angka);
    }
    for(i=0; i<n2; i++)
    {
        scanf("%d", &angka);
        root2 = insert(root2, angka);
    }
    if(cekSubtree(root1, root2))    printf("True");
    else                            printf("False");
}
