#include <stdio.h>
#include <stdlib.h>

// Define the B-Tree node structure
typedef struct BTreeNode {
    int *keys;               // Array of keys
    int t;                   // Minimum degree
    struct BTreeNode **children; // Array of children
    int n;                   // Current number of keys
    int leaf;                // True if the node is a leaf, false otherwise
} BTreeNode;

// Function to create a new B-Tree node
BTreeNode* createNode(int t, int leaf) {
    BTreeNode *newNode = (BTreeNode *)malloc(sizeof(BTreeNode));
    newNode->t = t;
    newNode->leaf = leaf;
    newNode->keys = (int *)malloc((2 * t - 1) * sizeof(int));
    newNode->children = (BTreeNode **)malloc(2 * t * sizeof(BTreeNode *));
    newNode->n = 0;
    return newNode;
}

// Function to traverse the B-Tree in-order
void inorderTraversal(BTreeNode *root) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->n; i++) {
            if (!root->leaf) {
                inorderTraversal(root->children[i]);
            }
            printf("%d ", root->keys[i]);
        }
        if (!root->leaf) {
            inorderTraversal(root->children[i]);
        }
    }
}

// Function to split the child of a node
void splitChild(BTreeNode *parent, int index) {
    int t = parent->t;
    BTreeNode *fullChild = parent->children[index];
    BTreeNode *newChild = createNode(t, fullChild->leaf);

    // Move the second half of the keys and children to the new child
    for (int j = 0; j < t - 1; j++) {
        newChild->keys[j] = fullChild->keys[j + t];
    }
    if (!fullChild->leaf) {
        for (int j = 0; j < t; j++) {
            newChild->children[j] = fullChild->children[j + t];
        }
    }

    // Reduce the number of keys in the full child
    fullChild->n = t - 1;

    // Shift children of parent to make space for the new child
    for (int j = parent->n; j >= index + 1; j--) {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[index + 1] = newChild;

    // Shift keys of parent to make space for the middle key
    for (int j = parent->n - 1; j >= index; j--) {
        parent->keys[j + 1] = parent->keys[j];
    }
    parent->keys[index] = fullChild->keys[t - 1];
    parent->n++;
}

// Function to insert a key into a non-full node
void insertNonFull(BTreeNode *node, int key) {
    int i = node->n - 1;

    if (node->leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->n++;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        if (node->children[i]->n == (2 * node->t - 1)) {
            splitChild(node, i);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

// Function to insert a key into the B-Tree
void insert(BTreeNode **root, int key) {
    BTreeNode *r = *root;
    if (r->n == (2 * r->t - 1)) {
        BTreeNode *newRoot = createNode(r->t, 0);
        newRoot->children[0] = r;
        *root = newRoot;
        splitChild(newRoot, 0);
        insertNonFull(newRoot, key);
    } else {
        insertNonFull(r, key);
    }
}

// Function to delete a key from the B-Tree (not fully implemented)
void deleteKey(BTreeNode *node, int key) {
    printf("Delete operation not implemented.\n");
}

// Main function to test B-Tree operations
int main() {
    int t = 3; // Minimum degree
    BTreeNode *root = createNode(t, 1); // Create the root node as a leaf

    // Inserting keys into the B-Tree
    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    for (int i = 0; i < 8; i++) {
        insert(&root, keys[i]);
        printf("After inserting %d: ", keys[i]);
        inorderTraversal(root);
        printf("\n");
    }

    // Final In-order traversal of the tree
    printf("Final In-order traversal: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
