#include <stdio.h>
#include <stdlib.h>

struct Student {
    int id;
    char name[50];
    char course[30];
    int semester;
    float total_fee;
    float fee_paid;
};

void menu() {
    printf("\n--- Student Management System ---\n");
    printf("1. Add Student\n");
    printf("2. View All Students\n");
    printf("3. Search Student by ID\n");
    printf("4. Edit Student\n");
    printf("5. Delete Student\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;

    do {
        menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Add Student selected\n");
                break;
            case 2:
                printf("View Students selected\n");
                break;
            case 3:
                printf("Search Student selected\n");
                break;
            case 4:
                printf("Edit Student selected\n");
                break;
            case 5:
                printf("Delete Student selected\n");
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 6);

    return 0;
}
