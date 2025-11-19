#include <stdio.h>
#include <stdlib.h>

// Structure of a node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node in BST
struct Node* insert(struct Node* root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    else
        printf("Duplicate value not allowed in BST.\n");

    return root;
}

// Function to find the minimum value node in BST
struct Node* findMin(struct Node* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

// Function to delete a node from BST
struct Node* deleteNode(struct Node* root, int value) {
    if (root == NULL) {
        printf("Value not found in BST.\n");
        return root;
    }

    // Traverse the tree
    if (value < root->data)
        root->left = deleteNode(root->left, value);
    else if (value > root->data)
        root->right = deleteNode(root->right, value);
    else {
        // Node found
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            printf("Node %d deleted.\n", value);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            printf("Node %d deleted.\n", value);
            return temp;
        }

        // Node with two children
        struct Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to search for a key in BST
struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->data == key)
        return root;
    if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

// Inorder traversal (Left, Root, Right)
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Main function
int main() {
    struct Node* root = NULL;
    int choice, value, key;
    struct Node* result;

    while (1) {
        printf("\n--- Binary Search Tree Menu ---\n");
        printf("1. Insert an element\n");
        printf("2. Delete an element\n");
        printf("3. Search for a key\n");
        printf("4. Display (Inorder Traversal)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;
            case 3:
                printf("Enter key to search: ");
                scanf("%d", &key);
                result = search(root, key);
                if (result != NULL)
                    printf("Key %d found in BST.\n", key);
                else
                    printf("Key %d not found in BST.\n", key);
                break;
            case 4:
                printf("BST elements (Inorder): ");
                inorder(root);
                printf("\n");
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
