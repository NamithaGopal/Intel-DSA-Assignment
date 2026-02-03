#include <stdio.h>
#include <stdlib.h>

struct BSTNode {
    int key;
    struct BSTNode *left, *right;
};

struct BSTNode* createNode(int key) {
    struct BSTNode* temp = (struct BSTNode*)malloc(sizeof(struct BSTNode));
    temp->key = key;
    temp->left = temp->right = NULL;
    return temp;
}

struct BSTNode* bstInsert(struct BSTNode* root, int key) {
    if (root == NULL)
        return createNode(key);

    if (key < root->key)
        root->left = bstInsert(root->left, key);
    else
        root->right = bstInsert(root->right, key);

    return root;
}

void inorder(struct BSTNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

int main() {
    struct BSTNode* root = NULL;
    int keys[] = {10, 5, 15, 3, 7};
    int n = 5;

    for (int i = 0; i < n; i++)
        root = bstInsert(root, keys[i]);

    printf("BST Inorder Traversal: ");
    inorder(root);

    return 0;
}
