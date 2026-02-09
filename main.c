#include <stdio.h>
#include <stdlib.h>
void viewStudents();
void addStudent();
void searchStudent();
void editStudent();
void deleteStudent();
struct Student {
    int id;
    char name[50];
    char course[30];
    int semester;
    float total_fee;
    float fee_paid;
};
void deleteStudent() {
    FILE *fp, *temp;
    struct Student s;
    int deleteID, found = 0;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        printf("\nError creating temporary file!\n");
        fclose(fp);
        return;
    }

    printf("\nEnter Student ID to delete: ");
    scanf("%d", &deleteID);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.id == deleteID) {
            found = 1;   // skip writing this record
        } else {
            fwrite(&s, sizeof(struct Student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found) {
        printf("\nStudent record deleted successfully!\n");
    } else {
        printf("\nStudent ID not found!\n");
    }
}

void editStudent() {
    FILE *fp;
    struct Student s;
    int searchId, found = 0;

    fp = fopen("students.dat", "rb+");
    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nEnter Student ID to edit: ");
    scanf("%d", &searchId);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.id == searchId) {
            found = 1;

            printf("\nEnter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Course: ");
            scanf(" %[^\n]", s.course);

            printf("Enter New Semester: ");
            scanf("%d", &s.semester);

            printf("Enter New Total Fee: ");
            scanf("%f", &s.total_fee);

            printf("Enter New Fee Paid: ");
            scanf("%f", &s.fee_paid);

            /* Move file pointer back to overwrite */
            fseek(fp, -sizeof(struct Student), SEEK_CUR);

            fwrite(&s, sizeof(struct Student), 1, fp);

            printf("\nStudent record updated successfully!\n");
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("\nStudent ID not found!\n");
    }
}
void searchStudent() {
    FILE *fp;
    struct Student s;
    int searchID, found = 0;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nEnter Student ID to search: ");
    scanf("%d", &searchID);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.id == searchID) {
            found = 1;

            printf("\n--- Student Found ---\n");
            printf("ID        : %d\n", s.id);
            printf("Name      : %s\n", s.name);
            printf("Course    : %s\n", s.course);
            printf("Semester  : %d\n", s.semester);
            printf("Total Fee : %.2f\n", s.total_fee);
            printf("Fee Paid  : %.2f\n", s.fee_paid);
            printf("Fee Due   : %.2f\n", s.total_fee - s.fee_paid);

            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("\nStudent ID not found!\n");
    }
}

void addStudent(){
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "ab");
    if(fp==NULL){
        printf("\n Error opening file! \n");
        return;
    }
    printf("\nEnter Student ID:");
    scanf("%d", &s.id);
    printf("Enter Name:");
    scanf(" %[^\n]", s.name);

    printf("Enter Course: ");
    scanf(" %[^\n]", s.course);

    printf("Enter Semester: ");
    scanf("%d", &s.semester);

    printf("Enter Total Fee: ");
    scanf("%f", &s.total_fee);

    printf("Enter Fee Paid: ");
    scanf("%f", &s.fee_paid);    

    fwrite(&s, sizeof(struct Student), 1, fp);

    fclose(fp);

    printf("\n Student added successfully!\n");
}
void viewStudents() {
    FILE *fp;
    struct Student s;
    int found = 0;
    
    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\n--- Student Records ---\n");

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        printf("\nID        : %d", s.id);
        printf("\nName      : %s", s.name);
        printf("\nCourse    : %s", s.course);
        printf("\nSemester  : %d", s.semester);
        printf("\nTotal Fee : %.2f", s.total_fee);
        printf("\nFee Paid  : %.2f", s.fee_paid);
        printf("\nFee Due   : %.2f\n", s.total_fee - s.fee_paid);
        printf("---------------------------");
        found = 1;
    }

    fclose(fp);

    if (!found) {
        printf("\nNo student data available.\n");
    }
}

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
                addStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                editStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 6);

    return 0;
}
