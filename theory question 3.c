#include <stdio.h>
#include <stdlib.h>

struct Node {
    char ch;
    int freq;
    struct Node* left;
    struct Node* right;
};

// Queue structure for level order
struct QueueNode {
    struct Node* data;
    struct QueueNode* next;
};

struct QueueNode* front = NULL;
struct QueueNode* rear = NULL;

void enqueue(struct Node* node) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->data = node;
    newNode->next = NULL;
    if (!rear) front = rear = newNode;
    else {
        rear->next = newNode;
        rear = newNode;
    }
}

struct Node* dequeue() {
    if (!front) return NULL;
    struct QueueNode* temp = front;
    struct Node* node = temp->data;
    front = front->next;
    if (!front) rear = NULL;
    free(temp);
    return node;
}

int isQueueEmpty() {
    return front == NULL;
}

// Create new tree node
struct Node* createNode(char c) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->ch = c;
    newNode->freq = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert character level-wise
void insertChar(struct Node** root, char c) {
    if (*root == NULL) {
        *root = createNode(c);
        return;
    }

    // Check if character already exists (BFS)
    enqueue(*root);
    while (!isQueueEmpty()) {
        struct Node* temp = dequeue();
        if (temp->ch == c) {
            temp->freq++;
            return;
        }
    }

    // Insert at first available position level-wise
    enqueue(*root);
    while (!isQueueEmpty()) {
        struct Node* temp = dequeue();

        if (!temp->left) {
            temp->left = createNode(c);
            return;
        } else enqueue(temp->left);

        if (!temp->right) {
            temp->right = createNode(c);
            return;
        } else enqueue(temp->right);
    }
}

// Level order traversal to print character frequencies
void levelOrder(struct Node* root) {
    if (!root) return;
    enqueue(root);
    while (!isQueueEmpty()) {
        struct Node* temp = dequeue();
        printf("(%c, %d) ", temp->ch, temp->freq);
        if (temp->left) enqueue(temp->left);
        if (temp->right) enqueue(temp->right);
    }
}

int main() {
    struct Node* root = NULL;
    char str[100];
    printf("Enter string: ");
    scanf("%s", str);

    for (int i = 0; str[i] != '\0'; i++)
        insertChar(&root, str[i]);

    printf("Character frequencies (level order):\n");
    levelOrder(root);
    return 0;
}
