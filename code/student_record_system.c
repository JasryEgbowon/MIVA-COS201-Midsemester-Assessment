//Ayo Please note there is a Bug in the code, the when a name with spaces is inputed it runs an infinite the code, please fix it. dont forget

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//definitions
#define MAX_STUDENTS 100
#define PASS_MARK 40.0

// This is  Our student structure - holds all student data [We implemented this from our school]
typedef struct {
    char name[50];
    int rollNumber;
    float marks;
} Student;

// Global variables - our main data storage
Student students[MAX_STUDENTS];
int studentCount = 0;
char currentUser[50];

//The Function declarations used in the code. 
void displayWelcome();
void addStudent();
void displayAllStudents();
void searchStudent();
void calculateAverage();
void sortStudents();
void saveToFile();
void loadFromFile();
void modifyStudent();
int findStudentByRoll(int rollNumber);
void readLine(char *buf, int size);

// Helper to read a whole line from stdin (accepts spaces) and strip newline
void readLine(char *buf, int size) {
    if(buf == NULL || size <= 0) return;
    while (fgets(buf, size, stdin)) {
        size_t len = strlen(buf);
        if (len > 0 && buf[len-1] == '\n') {
            buf[len-1] = '\0';
            if (buf[0] == '\0') {
                // empty line (user just pressed enter) -> prompt again
                continue;
            }
            break;
        }
        // If there's no newline, the input was longer than the buffer - clear rest
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
        if (strlen(buf) == 0) continue;
        break;
    }
}

int main() {
    // Here Welcomes the user (we use functions for better organization)
    displayWelcome();
    
    int choice;
    
    // This is the Main program loop - it keeps the program running until user chooses to exit
    do {
        printf("\n--- Student Record System ---\n");
        printf("1. Add New Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by Roll Number\n");
        printf("4. Modify Student Record\n");
        printf("5. Calculate Average Marks\n");
        printf("6. Sort Students by Marks\n");
        printf("7. Save Records to File\n");
        printf("8. Load Records from File\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        
        scanf("%d", &choice);
        
        // here Handles user choice
        //We used cases a concept we learnt from school also
        switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                modifyStudent();
                break;
            case 5:
                calculateAverage();
                break;
            case 6:
                sortStudents();
                break;
            case 7:
                saveToFile();
                break;
            case 8:
                loadFromFile();
                break;
            case 9:
                printf("Goodbye, %s! Thanks for using our system.\n", currentUser);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 9);
    
    return 0;
}

// Shows welcome message and gets user's name
void displayWelcome() {
    printf("---------------------------------\n");
    printf("   STUDENT RECORD SYSTEM\n");
    printf("---------------------------------\n");
    printf("Welcome! Please enter your name: ");
    readLine(currentUser, sizeof(currentUser));
    printf("Hello, %s! Let's manage some student records.\n", currentUser);
}

// Adds a new student to our system
void addStudent() {
    if(studentCount >= MAX_STUDENTS) { // addStudent() does a capacity check to see if it has reached the maximum number of students
        printf("Sorry, we've reached the maximum number of students!\n");
        return;
    }
    
    Student newStudent;
    
    printf("\n--- Adding New Student ---\n");
    printf("Enter student name: ");
    readLine(newStudent.name, sizeof(newStudent.name));
    printf("Enter roll number: ");
    scanf("%d", &newStudent.rollNumber);
    printf("Enter marks: ");
    scanf("%f", &newStudent.marks);
    
    //This Checks if roll number already exists
    if(findStudentByRoll(newStudent.rollNumber) != -1) {
        printf("Error: Student with roll number %d already exists!\n", newStudent.rollNumber);
        return;
    }
    
    students[studentCount] = newStudent;
    studentCount++;
    
    printf("Student added successfully!\n");
}

// This Shows all students in the system
void displayAllStudents() {
    if(studentCount == 0) {
        printf("No students in the system yet.\n");
        return;
    }
    
    printf("\n--- All Student Records ---\n");
    printf("%-5s %-20s %-10s %-10s\n", "S.No", "Name", "Roll No", "Marks");
    printf("-------------------------------------------------\n");
    
    for(int i = 0; i < studentCount; i++) {
        char status[10];
        if(students[i].marks >= PASS_MARK) {
            strcpy(status, "PASS");
        } else {
            strcpy(status, "FAIL");
        }
        
        printf("%-5d %-20s %-10d %-10.2f (%s)\n", 
               i+1, students[i].name, students[i].rollNumber, 
               students[i].marks, status);
    }
}

// Searches for a student using roll number
void searchStudent() {
    if(studentCount == 0) {
        printf("No students to search.\n");
        return;
    }
    
    int rollNumber;
    printf("Enter roll number to search: ");
    scanf("%d", &rollNumber);
    
    int index = findStudentByRoll(rollNumber);
    if(index == -1) {
        printf("Student with roll number %d not found.\n", rollNumber);
        return;
    }
    
    printf("\n--- Student Found ---\n");
    printf("Name: %s\n", students[index].name);
    printf("Roll Number: %d\n", students[index].rollNumber);
    printf("Marks: %.2f\n", students[index].marks);
    printf("Status: %s\n", students[index].marks >= PASS_MARK ? "PASS" : "FAIL");
}

// Helper function to find student index by roll number
int findStudentByRoll(int rollNumber) {
    for(int i = 0; i < studentCount; i++) {
        if(students[i].rollNumber == rollNumber) {
            return i;
        }
    }
    return -1;
}

// Lets user modify an existing student record
void modifyStudent() {
    if(studentCount == 0) {
        printf("No students to modify.\n");
        return;
    }
    
    int rollNumber;
    printf("Enter roll number of student to modify: ");
    scanf("%d", &rollNumber);
    
    int index = findStudentByRoll(rollNumber);
    if(index == -1) {
        printf("Student not found!\n");
        return;
    }
    
    printf("\nCurrent Details:\n");
    printf("Name: %s\n", students[index].name);
    printf("Marks: %.2f\n", students[index].marks);
    
    printf("\nEnter new name: ");
    readLine(students[index].name, sizeof(students[index].name));
    printf("Enter new marks: ");
    scanf("%f", &students[index].marks);
    
    printf("Student record updated successfully!\n");
}

// this function Calculates and shows average marks of all students
void calculateAverage() {
    if(studentCount == 0) {
        printf("No students to calculate average.\n");
        return;
    }
    
    float total = 0;
    for(int i = 0; i < studentCount; i++) {
        total += students[i].marks;
    }
    
    float average = total / studentCount;
    printf("Average marks of all students: %.2f\n", average);
}

// Sorts students by their marks with the void structure
void sortStudents() {
    if(studentCount == 0) {
        printf("No students to sort.\n");
        return;
    }
    int order;
    printf("Sort by:\n");
    printf("1. Ascending order (lowest to highest)\n");
    printf("2. Descending order (highest to lowest)\n");
    printf("Enter your choice: ");
    scanf("%d", &order);
    
    // Simple bubble sort - easy to understand
    for(int i = 0; i < studentCount - 1; i++) {
        for(int j = 0; j < studentCount - i - 1; j++) {
            int shouldSwap = 0;
            
            if(order == 1) {
                // Ascending order
                shouldSwap = students[j].marks > students[j+1].marks;
            } else if(order == 2) {
                // Descending order  
                shouldSwap = students[j].marks < students[j+1].marks;
            } else {
                printf("Invalid choice!\n");
                return;
            }
            
            if(shouldSwap) {
                // Swap the students when the chosen condition is met
                Student temp = students[j];
                students[j] = students[j+1];
                students[j+1] = temp;
            }
        }
    }
    
    printf("Students sorted successfully!\n");
    displayAllStudents(); // Show the sorted list when done
}

//This Saves all records to a text file
void saveToFile() {
    if(studentCount == 0) {
        printf("No students to save.\n");
        return;
    }
    
    char filename[50];
    printf("Enter filename to save (e.g., records.txt): ");
    readLine(filename, sizeof(filename));
    
    FILE *file = fopen(filename, "w");
    if(file == NULL) {
        printf("Error creating file!\n");
        return;
    }
    
    // Write each student to the file
    for(int i = 0; i < studentCount; i++) {
        // Use '|' as delimiter so names with spaces are preserved
        fprintf(file, "%s|%d|%.2f\n",
            students[i].name,
            students[i].rollNumber,
            students[i].marks);
    }
    
    fclose(file);
    printf("Successfully saved %d students to %s\n", studentCount, filename);
}

// here Loads records from a text file
void loadFromFile() {
    char filename[50];
    printf("Enter filename to load: ");
    readLine(filename, sizeof(filename));
    
    FILE *file = fopen(filename, "r");
    if(file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }
    
    // Reset student count when loading from file
    studentCount = 0;

    // Read each line and parse fields separated by '|'
    char line[200];
    while(studentCount < MAX_STUDENTS && fgets(line, sizeof(line), file)) {
        // remove trailing newline
        size_t ln = strlen(line);
        if (ln > 0 && line[ln-1] == '\n') line[ln-1] = '\0';

        // parse: name up to '|', then roll, then marks
        if (sscanf(line, "%49[^|]|%d|%f", 
                   students[studentCount].name,
                   &students[studentCount].rollNumber,
                   &students[studentCount].marks) == 3) {
            studentCount++;
        }
    }
    
    fclose(file);
    printf("Successfully loaded %d students from %s\n", studentCount, filename);
}