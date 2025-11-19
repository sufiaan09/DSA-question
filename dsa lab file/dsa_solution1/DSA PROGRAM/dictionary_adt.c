#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10  // size of hash table

// Node structure for each entry (key-value pair)
struct Node {
    int key;
    char value[50];
    struct Node* next;
};

// Hash table (array of pointers)
struct Node* hashTable[SIZE];

// Hash function
int hashFunction(int key) {
    return key % SIZE;
}

// Insert key-value pair
void insert(int key, char* value) {
    int index = hashFunction(key);

    // Create new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    strcpy(newNode->value, value);
    newNode->next = NULL;

    // Insert using separate chaining
    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
    } else {
        struct Node* temp = hashTable[index];
        while (temp->next != NULL) {
            if (temp->key == key) {
                printf("Duplicate key not allowed!\n");
                free(newNode);
                return;
            }
            temp = temp->next;
        }
        if (temp->key == key) {
            printf("Duplicate key not allowed!\n");
            free(newNode);
            return;
        }
        temp->next = newNode;
    }

    printf("Inserted (Key: %d, Value: %s)\n", key, value);
}

// Search by key
void search(int key) {
    int index = hashFunction(key);
    struct Node* temp = hashTable[index];

    while (temp != NULL) {
        if (temp->key == key) {
            printf("Key found! Value = %s\n", temp->value);
            return;
        }
        temp = temp->next;
    }

    printf("Key %d not found in dictionary.\n", key);
}

// Delete a key-value pair
void deleteKey(int key) {
    int index = hashFunction(key);
    struct Node* temp = hashTable[index];
    struct Node* prev = NULL;

    while (temp != NULL) {
        if (temp->key == key) {
            if (prev == NULL)
                hashTable[index] = temp->next;
            else
                prev->next = temp->next;

            free(temp);
            printf("Key %d deleted successfully.\n", key);
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("Key %d not found in dictionary.\n", key);
}

// Display the entire dictionary
void display() {
    printf("\n--- Dictionary Contents ---\n");
    for (int i = 0; i < SIZE; i++) {
        struct Node* temp = hashTable[i];
        if (temp != NULL) {
            printf("Index %d: ", i);
            while (temp != NULL) {
                printf("(%d : %s) -> ", temp->key, temp->value);
                temp = temp->next;
            }
            printf("NULL\n");
        }
    }
    printf("----------------------------\n");
}

// Main function
int main() {
    int choice, key;
    char value[50];

    while (1) {
        printf("\n--- Dictionary (Hash Table) Menu ---\n");
        printf("1. Insert (key, value)\n");
        printf("2. Search by key\n");
        printf("3. Delete a key\n");
        printf("4. Display dictionary\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key (integer): ");
                scanf("%d", &key);
                printf("Enter value (string): ");
                scanf("%s", value);
                insert(key, value);
                break;
            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                search(key);
                break;
            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                deleteKey(key);
                break;
            case 4:
                display();
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
