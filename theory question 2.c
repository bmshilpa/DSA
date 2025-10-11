#include <stdio.h>
#include <stdlib.h>

struct Node {
    int songID;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int id) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->songID = id;
    newNode->next = NULL;
    return newNode;
}

// Function to reverse playlist segment
struct Node* reversePlaylistSegment(struct Node* head, int m, int n) {
    if (!head || m == n) return head;

    struct Node dummy;
    dummy.next = head;
    struct Node* prev = &dummy;

    // Move to node before m
    for (int i = 1; i < m; i++)
        prev = prev->next;

    struct Node* start = prev->next;
    struct Node* then = start->next;

    for (int i = 0; i < n - m; i++) {
        start->next = then->next;
        then->next = prev->next;
        prev->next = then;
        then = start->next;
    }

    return dummy.next;
}

// Function to print playlist
void printPlaylist(struct Node* head) {
    while (head) {
        printf("%d", head->songID);
        if (head->next) printf(" -> ");
        head = head->next;
    }
    printf("\n");
}

int main() {
    int n, m, k, id;
    struct Node *head = NULL, *tail = NULL;

    printf("Enter number of songs: ");
    scanf("%d", &n);

    printf("Enter song IDs:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &id);
        struct Node* newNode = createNode(id);
        if (!head) head = tail = newNode;
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    printf("Enter m and n: ");
    scanf("%d %d", &m, &k);

    printf("\nOriginal Playlist:\n");
    printPlaylist(head);

    head = reversePlaylistSegment(head, m, k);

    printf("\nModified Playlist:\n");
    printPlaylist(head);
    return 0;
}
