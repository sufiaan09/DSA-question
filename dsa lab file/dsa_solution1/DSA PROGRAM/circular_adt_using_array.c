#include <stdio.h>
#define SIZE 5  // maximum size of queue

int queue[SIZE];
int front = -1, rear = -1;

// Function to check if the queue is full
int isFull() {
    return (front == 0 && rear == SIZE - 1) || (front == rear + 1);
}

// Function to check if the queue is empty
int isEmpty() {
    return (front == -1);
}

// Function to insert an element (enqueue)
void enqueue(int value) {
    if (isFull()) {
        printf("Queue Overflow! (Circular Queue is Full)\n");
        return;
    }

    if (front == -1)  // first element
        front = 0;

    rear = (rear + 1) % SIZE;
    queue[rear] = value;
    printf("%d inserted into the queue.\n", value);
}

// Function to delete an element (dequeue)
void dequeue() {
    if (isEmpty()) {
        printf("Queue Underflow! (Circular Queue is Empty)\n");
        return;
    }

    printf("%d deleted from the queue.\n", queue[front]);

    if (front == rear) { // Only one element
        front = rear = -1;
    } else {
        front = (front + 1) % SIZE;
    }
}

// Function to display elements of the queue
void display() {
    if (isEmpty()) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Circular Queue elements are: ");
    int i = front;
    while (1) {
        printf("%d ", queue[i]);
        if (i == rear)
            break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

// Main function
int main() {
    int choice, value;

    while (1) {
        printf("\n--- Circular Queue Menu ---\n");
        printf("1. Enqueue (Insert)\n");
        printf("2. Dequeue (Delete)\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                enqueue(value);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                display();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
