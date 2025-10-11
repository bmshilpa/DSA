#include <stdio.h>
#include <string.h>

struct Member {
    char name[50];
    int steps[30];
};

// Function to analyze steps
void analyzeSteps(struct Member members[], int n) {
    for (int i = 0; i < n; i++) {
        int count = 0, max = members[i].steps[0];

        for (int j = 0; j < 30; j++) {
            if (members[i].steps[j] > 10000)
                count++;
            if (members[i].steps[j] > max)
                max = members[i].steps[j];
        }

        printf("\nMember: %s\n", members[i].name);
        printf("Days exceeding 10,000 steps: %d\n", count);
        printf("Maximum step count: %d\n", max);
    }
}

int main() {
    int n;
    printf("Enter number of members: ");
    scanf("%d", &n);

    struct Member members[n];
    for (int i = 0; i < n; i++) {
        printf("\nEnter member name: ");
        scanf("%s", members[i].name);
        printf("Enter 30 days step counts:\n");
        for (int j = 0; j < 30; j++) {
            scanf("%d", &members[i].steps[j]);
        }
    }

    analyzeSteps(members, n);
    return 0;
}
