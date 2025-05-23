#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_STUDENTS 1000
#define DATA_FILE "students.dat"

typedef struct {
    int id;
    char name[MAX_NAME];
    float marks;
} Student;

Student students[MAX_STUDENTS];
int student_count = 0;

// --- Function declarations ---
void load_data();
void save_data();
void add_student();
void list_students();
void search_student();
void delete_student();
void edit_student();
void pause();

int main() {
    int choice;
    load_data();

    while (1) {
        printf("\n=== Student Management System ===\n");
        printf("1. Add Student\n");
        printf("2. List Students\n");
        printf("3. Search Student by ID\n");
        printf("4. Edit Student\n");
        printf("5. Delete Student\n");
        printf("6. Save & Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1: add_student(); break;
            case 2: list_students(); break;
            case 3: search_student(); break;
            case 4: edit_student(); break;
            case 5: delete_student(); break;
            case 6: 
                save_data();
                printf("Data saved. Goodbye!\n");
                exit(0);
            default: printf("Invalid choice.\n");
        }
        pause();
    }
}

// --- Load data from file ---
void load_data() {
    FILE *file = fopen(DATA_FILE, "rb");
    if (file == NULL) return;

    fread(&student_count, sizeof(int), 1, file);
    fread(students, sizeof(Student), student_count, file);
    fclose(file);
}

// --- Save data to file ---
void save_data() {
    FILE *file = fopen(DATA_FILE, "wb");
    if (file == NULL) {
        printf("Failed to save data.\n");
        return;
    }
    fwrite(&student_count, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), student_count, file);
    fclose(file);
}

// --- Add new student ---
void add_student() {
    if (student_count >= MAX_STUDENTS) {
        printf("Max student limit reached!\n");
        return;
    }

    Student s;
    printf("Enter student ID: ");
    scanf("%d", &s.id);
    getchar(); // consume newline

    printf("Enter student name: ");
    fgets(s.name, MAX_NAME, stdin);
    s.name[strcspn(s.name, "\n")] = 0;

    printf("Enter marks: ");
    scanf("%f", &s.marks);

    students[student_count++] = s;
    printf("Student added successfully.\n");
}

// --- List all students ---
void list_students() {
    if (student_count == 0) {
        printf("No students to show.\n");
        return;
    }

    printf("\n%-10s %-30s %-10s\n", "ID", "Name", "Marks");
    printf("---------------------------------------------------------\n");

    for (int i = 0; i < student_count; i++) {
        printf("%-10d %-30s %-10.2f\n", students[i].id, students[i].name, students[i].marks);
    }
}

// --- Search for a student ---
void search_student() {
    int id;
    printf("Enter student ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            printf("Student Found:\n");
            printf("ID: %d\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("Marks: %.2f\n", students[i].marks);
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}

// --- Edit a student ---
void edit_student() {
    int id;
    printf("Enter student ID to edit: ");
    scanf("%d", &id);

    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            printf("Editing student with ID %d\n", id);

            printf("Enter new name: ");
            getchar();
            fgets(students[i].name, MAX_NAME, stdin);
            students[i].name[strcspn(students[i].name, "\n")] = 0;

            printf("Enter new marks: ");
            scanf("%f", &students[i].marks);

            printf("Student updated successfully.\n");
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}

// --- Delete a student ---
void delete_student() {
    int id, found = 0;
    printf("Enter student ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            for (int j = i; j < student_count - 1; j++) {
                students[j] = students[j + 1];
            }
            student_count--;
            printf("Student deleted successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with ID %d not found.\n", id);
    }
}

// --- Pause function ---
void pause() {
    printf("\nPress Enter to continue...");
    getchar();
}

