#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

struct RBNode {
    int key;
    int color;
    struct RBNode *left, *right, *parent;
};

struct RBNode* createRBNode(int key) {
    struct RBNode* node = (struct RBNode*)malloc(sizeof(struct RBNode));
    node->key = key;
    node->color = RED;
    node->left = node->right = node->parent = NULL;
    return node;
}

void leftRotate(struct RBNode **root, struct RBNode *x) {
    struct RBNode *y = x->right;
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void rightRotate(struct RBNode **root, struct RBNode *y) {
    struct RBNode *x = y->left;
    y->left = x->right;

    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;

    x->right = y;
    y->parent = x;
}

void rbInsertFixup(struct RBNode **root, struct RBNode *z) {
    while (z->parent && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            struct RBNode *y = z->parent->parent->right;

            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {
            struct RBNode *y = z->parent->parent->left;

            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

void rbInsert(struct RBNode **root, int key) {
    struct RBNode *z = createRBNode(key);
    struct RBNode *y = NULL;
    struct RBNode *x = *root;

    while (x != NULL) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if (y == NULL)
        *root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    rbInsertFixup(root, z);
}

void inorderRB(struct RBNode* root) {
    if (root != NULL) {
        inorderRB(root->left);
        printf("%d(%s) ", root->key, root->color == RED ? "R" : "B");
        inorderRB(root->right);
    }
}

int main() {
    struct RBNode *root = NULL;
    int keys[] = {10, 5, 15, 1, 6};
    int n = 5;

    for (int i = 0; i < n; i++)
        rbInsert(&root, keys[i]);

    printf("Red-Black Tree Inorder Traversal:\n");
    inorderRB(root);

    return 0;
}
