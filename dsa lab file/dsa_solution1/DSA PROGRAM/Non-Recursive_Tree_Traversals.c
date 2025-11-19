#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

// Utility function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

/////////////////////////////////////
// NON-RECURSIVE PRE-ORDER TRAVERSAL
/////////////////////////////////////
void preorder(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack[100];
    int top = -1;

    stack[++top] = root;

    printf("Pre-order: ");
    while (top != -1) {
        struct Node* current = stack[top--];
        printf("%d ", current->data);

        // Push right child first, then left child
        if (current->right) stack[++top] = current->right;
        if (current->left)  stack[++top] = current->left;
    }
    printf("\n");
}

/////////////////////////////////////
// NON-RECURSIVE IN-ORDER TRAVERSAL
/////////////////////////////////////
void inorder(struct Node* root) {
    struct Node* stack[100];
    int top = -1;
    struct Node* current = root;

    printf("In-order: ");
    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
    }
    printf("\n");
}

/////////////////////////////////////
// NON-RECURSIVE POST-ORDER TRAVERSAL
// (Using Two Stacks)
/////////////////////////////////////
void postorder(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack1[100], *stack2[100];
    int top1 = -1, top2 = -1;

    stack1[++top1] = root;

    while (top1 != -1) {
        struct Node* current = stack1[top1--];
        stack2[++top2] = current;

        if (current->left)  stack1[++top1] = current->left;
        if (current->right) stack1[++top1] = current->right;
    }

    printf("Post-order: ");
    while (top2 != -1) {
        printf("%d ", stack2[top2--]->data);
    }
    printf("\n");
}

/////////////////////////////////////
// MAIN FUNCTION
/////////////////////////////////////
int main() {
    // Creating a simple tree:
    //        1
    //      /   \
    //     2     3
    //    / \
    //   4   5

    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    preorder(root);
    inorder(root);
    postorder(root);

    return 0;
}
