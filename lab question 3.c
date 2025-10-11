#include <stdio.h>
#define SIZE 10

int undoStack[SIZE];
int redoStack[SIZE];
int topUndo = -1;
int topRedo = -1;

// Push to a stack
void push(int stack[], int *top, int value) {
    if (*top == SIZE - 1) {
        printf("Stack overflow!\n");
        return;
    }
    stack[++(*top)] = value;
}

// Pop from a stack
int pop(int stack[], int *top) {
    if (*top == -1)
        return -1;
    return stack[(*top)--];
}

// Perform a new operation
void performOperation(int op) {
    push(undoStack, &topUndo, op);
    topRedo = -1; // clear redo stack
    printf("Performed operation: op%d\n", op);
}

// Undo the last operation
void undoOperation() {
    int op = pop(undoStack, &topUndo);
    if (op == -1) {
        printf("Nothing to undo.\n");
        return;
    }
    push(redoStack, &topRedo, op);
    printf("Undone. Next operation that can be undone is = ");
    if (topUndo != -1)
        printf("op%d\n", undoStack[topUndo]);
    else
        printf("None\n");
}

// Redo the last undone operation
void redoOperation() {
    int op = pop(redoStack, &topRedo);
    if (op == -1) {
        printf("Nothing to redo.\n");
        return;
    }
    push(undoStack, &topUndo, op);
    printf("Redo completed. Next operation that can be redone is = ");
    if (topRedo != -1)
        printf("op%d\n", redoStack[topRedo]);
    else
        printf("None\n");
}

int main() {
    performOperation(1);
    performOperation(2);
    performOperation(3);

    undoOperation();
    undoOperation();
    redoOperation();

    performOperation(4);
    undoOperation();

    return 0;
}
