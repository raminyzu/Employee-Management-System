#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct employee {
    char id[20]; // Changed to char array to allow alphanumeric IDs
    char name[50];
    float salary;
    char address[100];
    char phone[15];
};

void addEmployee(FILE *myfile);
void listEmployees(FILE *myfile);
void searchEmployee(FILE *myfile);
void updateEmployee(FILE *myfile);
void deleteEmployee(FILE *myfile);

int main() {
    FILE *myfile;
    int choice;
    char password[20];
    const char correctPassword[] = "admin";

    printf("Enter Password to Access the System: ");
    scanf("%s", password);

    if (strcmp(password, correctPassword) != 0) {
        printf("Incorrect Password! Exiting program...\n");
        return 0;
    }

    printf("Access Granted! Welcome to Employee Management System.\n");

    myfile = fopen("emp.txt", "ab+");
    if (myfile == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    while (1) {
        printf("\n=== Employee Management System ===\n");
        printf("1. Add Employee\n");
        printf("2. List Employees\n");
        printf("3. Search Employee by ID\n");
        printf("4. Update Employee Info\n");
        printf("5. Delete Employee\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(myfile); break;
            case 2: listEmployees(myfile); break;
            case 3: searchEmployee(myfile); break;
            case 4: updateEmployee(myfile); break;
            case 5: deleteEmployee(myfile); break;
            case 0:
                fclose(myfile);
                printf("Exiting program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

void addEmployee(FILE *myfile) {
    struct employee emp;

    printf("\n--- Add New Employee ---\n");
    printf("Enter ID: ");
    scanf("%s", emp.id);

    // Clear the newline character left in the buffer after `scanf`
    while (getchar() != '\n');

    printf("Enter Name: ");
    fgets(emp.name, sizeof(emp.name), stdin);
    emp.name[strcspn(emp.name, "\n")] = '\0'; // Remove trailing newline

    printf("Enter Salary: ");
    scanf("%f", &emp.salary);

    // Clear the newline character left in the buffer after `scanf`
    while (getchar() != '\n');

    printf("Enter Address: ");
    fgets(emp.address, sizeof(emp.address), stdin);
    emp.address[strcspn(emp.address, "\n")] = '\0'; // Remove trailing newline

    printf("Enter Phone Number: ");
    scanf("%s", emp.phone);

    fwrite(&emp, sizeof(emp), 1, myfile);
    printf("Employee added successfully!\n");
}

void listEmployees(FILE *myfile) {
    struct employee emp;

    rewind(myfile);
    printf("\n--- Employee List ---\n");
    while (fread(&emp, sizeof(emp), 1, myfile)) {
        printf("ID: %s\nName: %s\nSalary: %.2f\nAddress: %s\nPhone: %s\n",
               emp.id, emp.name, emp.salary, emp.address, emp.phone);
        printf("-------------------------------\n");
    }
}

void searchEmployee(FILE *myfile) {
    struct employee emp;
    char searchID[20];
    int found = 0;

    printf("\n--- Search Employee ---\n");
    printf("Enter Employee ID to search: ");
    scanf("%s", searchID);

    rewind(myfile);

    while (fread(&emp, sizeof(emp), 1, myfile)) {
        if (strcmp(emp.id, searchID) == 0) {
            printf("Employee Found:\n");
            printf("ID: %s\nName: %s\nSalary: %.2f\nAddress: %s\nPhone: %s\n",
                   emp.id, emp.name, emp.salary, emp.address, emp.phone);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No employee found with ID %s.\n", searchID);
    }
}

void updateEmployee(FILE *myfile) {
    struct employee emp;
    char searchID[20];
    int found = 0;
    FILE *tempFile;

    printf("\n--- Update Employee Info ---\n");
    printf("Enter Employee ID to update: ");
    scanf("%s", searchID);

    tempFile = fopen("temp.txt", "wb");
    rewind(myfile); // Reset file pointer to the beginning

    while (fread(&emp, sizeof(emp), 1, myfile)) {
        if (strcmp(emp.id, searchID) == 0) {
            found = 1;
            printf("Enter New ID: ");
            scanf("%s", emp.id);
            printf("Enter New Name: ");
            fflush(stdin);
            fgets(emp.name, sizeof(emp.name), stdin);
            emp.name[strcspn(emp.name, "\n")] = '\0'; // Remove newline
            printf("Enter New Salary: ");
            scanf("%f", &emp.salary);
            printf("Enter New Address: ");
            fflush(stdin);
            fgets(emp.address, sizeof(emp.address), stdin);
            emp.address[strcspn(emp.address, "\n")] = '\0'; // Remove newline
            printf("Enter New Phone Number: ");
            scanf("%s", emp.phone);
        }
        fwrite(&emp, sizeof(emp), 1, tempFile);
    }

    fclose(myfile);
    fclose(tempFile);

    // Replace old file with updated file
    remove("emp.txt");
    rename("temp.txt", "emp.txt");

    // Reopen the updated file for further operations
    myfile = fopen("emp.txt", "ab+");

    if (found)
        printf("Employee updated successfully!\n");
    else
        printf("No employee found with ID %s.\n", searchID);
}

void deleteEmployee(FILE *myfile) {
    struct employee emp;
    char searchID[20];
    int found = 0;
    FILE *tempFile;

    printf("\n--- Delete Employee ---\n");
    printf("Enter Employee ID to delete: ");
    scanf("%s", searchID);

    tempFile = fopen("temp.txt", "wb");
    rewind(myfile);

    while (fread(&emp, sizeof(emp), 1, myfile)) {
        if (strcmp(emp.id, searchID) == 0) {
            found = 1;
            printf("Deleting Employee: ID %s, Name %s\n", emp.id, emp.name);
        } else {
            fwrite(&emp, sizeof(emp), 1, tempFile);
        }
    }

    fclose(myfile);
    fclose(tempFile);

    remove("emp.txt");
    rename("temp.txt", "emp.txt");

    myfile = fopen("emp.txt", "ab+");
    if (found)
        printf("Employee deleted successfully!\n");
    else
        printf("No employee found with ID %s.\n", searchID);
}
