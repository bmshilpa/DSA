#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tab {
    int pageID;
    char url[100];
    struct Tab* prev;
    struct Tab* next;
} Tab;

Tab* current = NULL;
int pageCounter = 1;

// Function to visit a new page
void visitNewPage(char* url) {
    Tab* newTab = (Tab*)malloc(sizeof(Tab));
    newTab->pageID = pageCounter++;
    strcpy(newTab->url, url);
    newTab->next = NULL;
    newTab->prev = current;

    if (current != NULL)
        current->next = newTab;

    current = newTab;

    printf("Visited new page: [%d] %s\n", current->pageID, current->url);
}

// Function to move back
void goBack() {
    if (current != NULL && current->prev != NULL) {
        current = current->prev;
        printf("Moved back to: [%d] %s\n", current->pageID, current->url);
    } else {
        printf("No previous tab available!\n");
    }
}

// Function to move forward
void goForward() {
    if (current != NULL && current->next != NULL) {
        current = current->next;
        printf("Moved forward to: [%d] %s\n", current->pageID, current->url);
    } else {
        printf("No forward tab available!\n");
    }
}

// Function to show current tab
void showCurrentTab() {
    if (current != NULL) {
        printf("Current Tab -> PageID: %d, URL: %s\n", current->pageID, current->url);
    } else {
        printf("No tab open currently!\n");
    }
}

// Function to close current tab
void closeCurrentTab() {
    if (current == NULL) {
        printf("No tab to close!\n");
        return;
    }

    Tab* temp = current;

    if (current->prev != NULL)
        current->prev->next = current->next;

    if (current->next != NULL)
        current->next->prev = current->prev;

    if (current->next != NULL)
        current = current->next;
    else
        current = current->prev;

    printf("Closed tab: [%d] %s\n", temp->pageID, temp->url);
    free(temp);
}

// Function to show history
void showHistory() {
    if (current == NULL) {
        printf("No history available!\n");
        return;
    }

    Tab* start = current;
    while (start->prev != NULL) start = start->prev;

    printf("\n--- Browser History ---\n");
    while (start != NULL) {
        printf("[%d] %s\n", start->pageID, start->url);
        start = start->next;
    }
    printf("-----------------------\n");
}

int main() {
    int choice;
    char url[100];

    while (1) {
        printf("\n--- Browser Menu ---\n");
        printf("1. Visit a new page\n");
        printf("2. Go back\n");
        printf("3. Go forward\n");
        printf("4. Show current tab\n");
        printf("5. Close current tab\n");
        printf("6. Show history\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter URL: ");
                scanf("%s", url);
                visitNewPage(url);
                break;
            case 2:
                goBack();
                break;
            case 3:
                goForward();
                break;
            case 4:
                showCurrentTab();
                break;
            case 5:
                closeCurrentTab();
                break;
            case 6:
                showHistory();
                break;
            case 7:
                printf("Exiting Browser...\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
