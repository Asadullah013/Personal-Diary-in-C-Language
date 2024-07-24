#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a note
typedef struct Note {
    char text[100];
    struct Note* next;
} Note;

// Function to display the contents of the notes
void displayNotes(Note* head) {
    printf("\nNotes:\n");
    Note* current = head;
    int noteNumber = 1;
    while (current != NULL) {
        printf("%d. %s\n", noteNumber, current->text);
        current = current->next;
        noteNumber++;
    }
    printf("\n");
}

// Function to insert a new note
Note* insertNote(Note* head, const char* newText) {
    Note* newNode = (Note*)malloc(sizeof(Note));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    strcpy(newNode->text, newText);
    newNode->next = head;

    return newNode;
}

// Function to delete a note
Note* deleteNote(Note* head, int noteNumber) {
    if (noteNumber < 1) {
        printf("Invalid note number. Please enter a positive number.\n");
        return head;
    }

    if (head == NULL) {
        printf("No notes to delete.\n");
        return head;
    }

    if (noteNumber == 1) {
        Note* newHead = head->next;
        free(head);
        return newHead;
    }

    Note* current = head;
    int i = 1;
    for (i = 1; i < noteNumber - 1 && current->next != NULL; i++) {
        current = current->next;
    }

    if (i == noteNumber - 1 && current->next != NULL) {
        Note* deletedNote = current->next;
        current->next = current->next->next;
        free(deletedNote);
        printf("Note %d deleted.\n", noteNumber);
    } else {
        printf("Note number %d not found.\n", noteNumber);
    }

    return head;
}

// Function to free the memory allocated for the linked list
void freeNotes(Note* head) {
    Note* current = head;
    while (current != NULL) {
        Note* next = current->next;
        free(current);
        current = next;
    }
}

// Function to save notes to a file
void saveNotesToFile(Note* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for writing.\n");
        exit(1);
    }

    Note* current = head;
    while (current != NULL) {
        fprintf(file, "%s\n", current->text);
        current = current->next;
    }

    fclose(file);
}

// Function to load notes from a file
Note* loadNotesFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        // If the file doesn't exist, return NULL
        return NULL;
    }

    Note* head = NULL;
    char buffer[100];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline character
        head = insertNote(head, buffer);
    }

    fclose(file);
    return head;
}

int main() {
    int a;
    int b = 1234;
    char c[20];
    char d[] = "admin";
    char filename[] = "notes.txt";  // File to store notes

    printf("Enter Username: ");
    scanf("%s", c);
    printf("Enter Password: ");
    scanf("%d", &a);

    if (a == b && strcmp(c, d) == 0) {
        // Load existing notes from the file
        Note* notes = loadNotesFromFile(filename);

        char inputBuffer[100];
        int noteNumber;

        while (1) {
            printf("\n*****************");
	    printf("\nPersonal Diary\n");
            printf("1. Add Note\n");
            printf("2. View Notes\n");
            printf("3. Delete Note\n");
            printf("4. Save and Exit\n");
            printf("\n*****************\n");
	    printf("Enter your choice: ");
            int choice;
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Enter the text for the note: ");
                    getchar();  // Consume the newline character left in the buffer
                    fgets(inputBuffer, sizeof(inputBuffer), stdin);
                    inputBuffer[strcspn(inputBuffer, "\n")] = '\0';  // Remove newline character
                    notes = insertNote(notes, inputBuffer);
                    printf("Note added successfully.\n");
                    break;
                case 2:
                    displayNotes(notes);
                    break;
                case 3:
                    printf("Enter the note number to delete: ");
                    scanf("%d", &noteNumber);
                    notes = deleteNote(notes, noteNumber);
                    break;
                case 4:
                    // Save notes to file before exiting
                    saveNotesToFile(notes, filename);
                    freeNotes(notes);
                    printf("Notes saved and exiting. Thank you!\n");
                    exit(0);
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}
