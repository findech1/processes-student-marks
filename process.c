#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50
#define MAX_ASSIGNMENTS 5

// Structure to hold student information
typedef struct {
    char name[MAX_NAME_LENGTH];
    int marks[MAX_ASSIGNMENTS];
    char grades[MAX_ASSIGNMENTS];
    float average;
    char finalGrade;
} Student;

// Function to determine grade based on marks
char calculateGrade(int marks) {
    if (marks >= 70 && marks <= 100)
        return 'A';  // Using 'A' for 70-100 range
    else if (marks >= 60 && marks <= 69)
        return 'B';
    else if (marks >= 50 && marks <= 59)
        return 'C';
    else if (marks >= 40 && marks <= 49)
        return 'D';
    else
        return 'E';
}

int main() {
    Student students[MAX_STUDENTS];
    int numStudents = 0;
    int numAssignments = 0;
    char choice;
    FILE *file;
    
    printf("Multiple Assignment Grading System\n");
    printf("=================================\n\n");
    
    // Get number of assignments
    printf("How many assignments would you like to grade (1-%d): ", MAX_ASSIGNMENTS);
    scanf("%d", &numAssignments);
    
    // Validate number of assignments
    while (numAssignments < 1 || numAssignments > MAX_ASSIGNMENTS) {
        printf("Invalid number. Please enter between 1 and %d: ", MAX_ASSIGNMENTS);
        scanf("%d", &numAssignments);
    }
    
    // Input student data
    do {
        if (numStudents < MAX_STUDENTS) {
            float sum = 0;
            printf("\nEnter details for student %d:\n", numStudents + 1);
            
            printf("Name: ");
            scanf(" %[^\n]", students[numStudents].name);
            
            // Get marks for each assignment
            for (int i = 0; i < numAssignments; i++) {
                printf("Marks for Assignment %d (0-100): ", i + 1);
                scanf("%d", &students[numStudents].marks[i]);
                
                // Validate marks input
                while (students[numStudents].marks[i] < 0 || students[numStudents].marks[i] > 100) {
                    printf("Invalid marks! Please enter marks between 0-100: ");
                    scanf("%d", &students[numStudents].marks[i]);
                }
                
                // Calculate grade for this assignment
                students[numStudents].grades[i] = calculateGrade(students[numStudents].marks[i]);
                
                // Add to sum for average calculation
                sum += students[numStudents].marks[i];
            }
            
            // Calculate average
            students[numStudents].average = sum / numAssignments;
            
            // Calculate final grade based on average
            students[numStudents].finalGrade = calculateGrade((int)students[numStudents].average);
            
            numStudents++;
        } else {
            printf("\nMaximum number of students reached.\n");
            break;
        }
        
        printf("\nDo you want to add another student? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');
    
    // Write to file
    file = fopen("student_results.csv", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    
    // Write header
    fprintf(file, "Student Name");
    for (int i = 0; i < numAssignments; i++) {
        fprintf(file, ",Assignment %d,Grade", i + 1);
    }
    fprintf(file, ",Average,Final Grade\n");
    
    // Write student data
    for (int i = 0; i < numStudents; i++) {
        fprintf(file, "%s", students[i].name);
        
        for (int j = 0; j < numAssignments; j++) {
            fprintf(file, ",%d,%c", students[i].marks[j], students[i].grades[j]);
        }
        
        fprintf(file, ",%.2f,%c\n", students[i].average, students[i].finalGrade);
    }
    
    // Write grading criteria as specified in the assignment
    fprintf(file, "\nGrading Criteria:\n");
    fprintf(file, "Total score,Grade\n");
    fprintf(file, "0-39,E\n");
    fprintf(file, "40-49,D\n");
    fprintf(file, "50-59,C\n");
    fprintf(file, "60-69,B\n");
    fprintf(file, "70-100,A\n");  // Using 'A' for 70-100 range
    
    fclose(file);
    
    printf("\nStudent results have been written to 'student_results.csv'\n");
    printf("You can now export this file to Excel.\n");
    
    return 0;
}