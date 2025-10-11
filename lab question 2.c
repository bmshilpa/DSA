#include <stdio.h>
#define SIZE 5

int queue[SIZE];
int front = -1, rear = -1;

void enqueue(int id) {
    if ((front == 0 && rear == SIZE - 1) || (rear + 1) % SIZE == front) {
        printf("Queue is full. Please wait.\n");
        return;
    }

    if (front == -1)
        front = 0;

    rear = (rear + 1) % SIZE;
    queue[rear] = id;
    printf("Call added: %d\n", id);
}

void dequeue() {
    if (front == -1) {
        printf("Queue is empty. No calls to remove.\n");
        return;
    }

    printf("Removed customer: %d\n", queue[front]);

    if (front == rear)
        front = rear = -1;
    else
        front = (front + 1) % SIZE;
}

void displayQueue() {
    if (front == -1) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Customers in queue: ");
    int i = front;
    while (1) {
        printf("%d ", queue[i]);
        if (i == rear) break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

int main() {
    enqueue(101);
    enqueue(102);
    enqueue(103);
    enqueue(104);
    enqueue(105);
    displayQueue();

    enqueue(106); // Should show overflow

    dequeue();
    dequeue();
    displayQueue();

    enqueue(106);
    enqueue(107);
    displayQueue();

    return 0;
}
