#include <stdio.h>
#include <stdlib.h>

// Structure for a doubly linked list node
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node* front = NULL;
struct Node* rear = NULL;

// Function to insert at front
void insertFront(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = front;

    if (front == NULL)
        rear = newNode;  // First element
    else
        front->prev = newNode;

    front = newNode;
    printf("%d inserted at front.\n", value);
}

// Function to insert at rear
void insertRear(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = rear;

    if (rear == NULL)
        front = newNode;  // First element
    else
        rear->next = newNode;

    rear = newNode;
    printf("%d inserted at rear.\n", value);
}

// Function to delete from front
void deleteFront() {
    if (front == NULL) {
        printf("Deque Underflow! (Empty)\n");
        return;
    }
    struct Node* temp = front;
    printf("%d deleted from front.\n", front->data);

    front = front->next;
    if (front == NULL)
        rear = NULL;
    else
        front->prev = NULL;

    free(temp);
}

// Function to delete from rear
void deleteRear() {
    if (rear == NULL) {
        printf("Deque Underflow! (Empty)\n");
        return;
    }
    struct Node* temp = rear;
    printf("%d deleted from rear.\n", rear->data);

    rear = rear->prev;
    if (rear == NULL)
        front = NULL;
    else
        rear->next = NULL;

    free(temp);
}

// Function to display deque elements
void display() {
    if (front == NULL) {
        printf("Deque is empty.\n");
        return;
    }

    struct Node* temp = front;
    printf("Deque elements are: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Main function
int main() {
    int choice, value;

    while (1) {
        printf("\n--- Deque Menu ---\n");
        printf("1. Insert at Front\n");
        printf("2. Insert at Rear\n");
        printf("3. Delete from Front\n");
        printf("4. Delete from Rear\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert at front: ");
                scanf("%d", &value);
                insertFront(value);
                break;
            case 2:
                printf("Enter value to insert at rear: ");
                scanf("%d", &value);
                insertRear(value);
                break;
            case 3:
                deleteFront();
                break;
            case 4:
                deleteRear();
                break;
            case 5:
                display();
                break;
            case 6:
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
