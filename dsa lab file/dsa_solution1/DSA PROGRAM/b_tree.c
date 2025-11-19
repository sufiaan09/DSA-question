#include <stdio.h>
#include <stdlib.h>

#define T 2  // Minimum degree

typedef struct BTreeNode {
    int keys[2*T - 1];
    struct BTreeNode* children[2*T];
    int n;
    int leaf;
} BTreeNode;

BTreeNode* createNode(int leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->leaf = leaf;
    node->n = 0;
    return node;
}

void traverse(BTreeNode* root) {
    if (!root) return;

    for (int i = 0; i < root->n; i++) {
        if (!root->leaf)
            traverse(root->children[i]);
        printf("%d ", root->keys[i]);
    }
    if (!root->leaf)
        traverse(root->children[root->n]);
}

BTreeNode* search(BTreeNode* root, int key) {
    int i = 0;
    while (i < root->n && key > root->keys[i])
        i++;

    if (root->keys[i] == key)
        return root;

    if (root->leaf)
        return NULL;

    return search(root->children[i], key);
}

void splitChild(BTreeNode* parent, int i, BTreeNode* child) {
    BTreeNode* z = createNode(child->leaf);
    z->n = T - 1;

    for (int j = 0; j < T - 1; j++)
        z->keys[j] = child->keys[j + T];

    if (!child->leaf) {
        for (int j = 0; j < T; j++)
            z->children[j] = child->children[j + T];
    }

    child->n = T - 1;

    for (int j = parent->n; j >= i + 1; j--)
        parent->children[j + 1] = parent->children[j];

    parent->children[i + 1] = z;

    for (int j = parent->n - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];

    parent->keys[i] = child->keys[T - 1];
    parent->n++;
}

void insertNonFull(BTreeNode* root, int key) {
    int i = root->n - 1;

    if (root->leaf) {
        while (i >= 0 && root->keys[i] > key) {
            root->keys[i + 1] = root->keys[i];
            i--;
        }
        root->keys[i + 1] = key;
        root->n++;
    } else {
        while (i >= 0 && root->keys[i] > key)
            i--;

        if (root->children[i + 1]->n == 2 * T - 1) {
            splitChild(root, i + 1, root->children[i + 1]);
            if (root->keys[i + 1] < key)
                i++;
        }
        insertNonFull(root->children[i + 1], key);
    }
}

void insert(BTreeNode** root, int key) {
    if (*root == NULL) {
        *root = createNode(1);
        (*root)->keys[0] = key;
        (*root)->n = 1;
        return;
    }

    if ((*root)->n == 2*T - 1) {
        BTreeNode* s = createNode(0);
        s->children[0] = *root;
        splitChild(s, 0, *root);

        int i = (s->keys[0] < key) ? 1 : 0;
        insertNonFull(s->children[i], key);

        *root = s;
    } else {
        insertNonFull(*root, key);
    }
}

int getPred(BTreeNode* root) {
    while (!root->leaf)
        root = root->children[root->n];
    return root->keys[root->n - 1];
}

int getSucc(BTreeNode* root) {
    while (!root->leaf)
        root = root->children[0];
    return root->keys[0];
}

void merge(BTreeNode* root, int idx) {
    BTreeNode* child = root->children[idx];
    BTreeNode* sibling = root->children[idx + 1];

    child->keys[T - 1] = root->keys[idx];

    for (int i = 0; i < sibling->n; i++)
        child->keys[i + T] = sibling->keys[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; i++)
            child->children[i + T] = sibling->children[i];
    }

    for (int i = idx + 1; i < root->n; i++)
        root->keys[i - 1] = root->keys[i];

    for (int i = idx + 2; i <= root->n; i++)
        root->children[i - 1] = root->children[i];

    child->n += sibling->n + 1;
    root->n--;

    free(sibling);
}

void removeNode(BTreeNode* root, int key);

void fill(BTreeNode* root, int idx) {
    if (idx != 0 && root->children[idx - 1]->n >= T)
        root->children[idx]->keys[root->children[idx]->n++] =
            root->keys[idx - 1];
    else if (idx != root->n && root->children[idx + 1]->n >= T)
        root->children[idx]->keys[root->children[idx]->n++] =
            root->keys[idx];
    else {
        if (idx != root->n)
            merge(root, idx);
        else
            merge(root, idx - 1);
    }
}

void removeNode(BTreeNode* root, int key) {
    int idx = 0;
    while (idx < root->n && root->keys[idx] < key)
        idx++;

    if (idx < root->n && root->keys[idx] == key) {
        if (root->leaf) {
            for (int i = idx + 1; i < root->n; i++)
                root->keys[i - 1] = root->keys[i];
            root->n--;
        } else {
            int k;
            if (root->children[idx]->n >= T) {
                k = getPred(root->children[idx]);
                root->keys[idx] = k;
                removeNode(root->children[idx], k);
            } else if (root->children[idx + 1]->n >= T) {
                k = getSucc(root->children[idx + 1]);
                root->keys[idx] = k;
                removeNode(root->children[idx + 1], k);
            } else {
                merge(root, idx);
                removeNode(root->children[idx], key);
            }
        }
    } else {
        if (root->leaf)
            return;

        if (root->children[idx]->n < T)
            fill(root, idx);

        removeNode(root->children[idx], key);
    }
}

int main() {
    BTreeNode* root = NULL;

    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 5);
    insert(&root, 6);
    insert(&root, 12);
    insert(&root, 30);
    insert(&root, 7);
    insert(&root, 17);

    printf("B-Tree traversal: ");
    traverse(root);

    removeNode(root, 6);
    printf("\nAfter deleting 6: ");
    traverse(root);

    removeNode(root, 13);
    printf("\nAfter deleting 13: ");
    traverse(root);

    removeNode(root, 7);
    printf("\nAfter deleting 7: ");
    traverse(root);

    removeNode(root, 4);
    printf("\nAfter deleting 4: ");
    traverse(root);

    printf("\n");
    return 0;
}
