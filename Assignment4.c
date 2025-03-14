/*
Program Name: EECS 348 Assignment 4
Description: CEO Email prioritization progrm

Inputs: test file labeled Assignment4_Test_File.txt
Output: Next email and number of unread emails

Collaborators/Sources: EECS 348 Assignmnet1, DeepSeek AI
                       Utilized DeepseekAI to author the program based on the python implementation from Assignment 1 then
                       went through and annotated the procedure myself

Author: Aiman Boullaouz
Creation Date: 03/11/2025
*/


#include <stdio.h>  //Importing standard input output functions
#include <stdlib.h> //Importing functions for memory management
#include <string.h> //Importing functions for string manipulations
#include <ctype.h>  //Importing more functions for working with strings
#include <stdbool.h> // Importing the boolean data type

//Cant make a class but a struct is close enough to work
//This one represents a email
typedef struct {
    char sender_category[20];   //Stores the sender catagory
    char subject[100];          //Stores the subject of the email
    char date[11];              //Stores the date of the email
    int priority_key;           //Used for priority logic 
} Email;

//This one is the maxheap of emails
typedef struct {
    Email* emails;  //Dynamic array of emails
    int size;       // Current number of emails in the heap
    int capacity;   //Maximum capacity of the heap before any modifications
} MaxHeap;

//In C you cant use a function in main without defining the function and declaring its prototype
//Here all the prototypes that are going to be used in the program are declared
MaxHeap* createHeap();                          // Creates and initializes a new heap
void insertHeap(MaxHeap* heap, Email email);    // Inserts an email into the heap
Email extractMax(MaxHeap* heap);                // Removes and returns the highest priority email
Email peekMax(MaxHeap* heap);                   // Returns the highest priority email without removing it
void heapifyUp(MaxHeap* heap, int index);       // Maintains heap order after insertion
void heapifyDown(MaxHeap* heap, int index);             // Maintains heap order after deletion
int computeCategoryRank(const char* sender_category);   // Assigns a numeric rank to sender categories
int parseDateToInt(const char* date);            // Converts date string to an integer for comparison
void trimWhitespace(char* str);                  // Removes leading and trailing whitespace from a string



/*
Main encapsulates the operation of the program, calls all the functions in a way that perserves the OOP functionality 
without actually using classes and objects.

The program opens the file "Assignment4_Test_File" and reads every line
When it encounters a command like EMAIL NEXT READ or COUNT it will jump to the associated conditional block
execute some code then continue reading lines till the end of the file
*/
int main() {
    MaxHeap* heap = createHeap();                           // Allocate memory and initialize the max heap
    FILE* file = fopen("Assignment4_Test_File.txt", "r");   // Open the input file for reading
    if (!file) {                                            // Check if file opening failed
        perror("Error opening file");                       // Print error message
        return EXIT_FAILURE;                                // Exit the program with failure reason
    }
    
    char line[256]; // Buffer to store each line read from the file
    
    // Read input lines from the file
    while (fgets(line, sizeof(line), file)) {       // Read each line until no more lines
        line[strcspn(line, "\n")] = 0;              // Remove trailing newline character

        // Handle "EMAIL" command to insert an email into the heap
        if (strncmp(line, "EMAIL ", 6) == 0) {      // Check if line starts with "EMAIL "
            char* rest = line + 6;                  // Skip the "EMAIL " part
            char* sender = strtok(rest, ",");       // get sender category
            char* subject = strtok(NULL, ",");       // get subject line
            char* date = strtok(NULL, ",");         // get date string

            if (!sender || !subject || !date) continue; // Ignore incomplete input

            trimWhitespace(sender);     // Remove extra spaces from sender
            trimWhitespace(subject);    // Remove extra spaces from subject
            trimWhitespace(date);       // Remove extra spaces from date

            Email newEmail; // Create a new email object
            strncpy(newEmail.sender_category, sender, sizeof(newEmail.sender_category) - 1);    // Copy sender category
            newEmail.sender_category[sizeof(newEmail.sender_category) - 1] = '\0';              // Adds a null character to the end of the string/array
            strncpy(newEmail.subject, subject, sizeof(newEmail.subject) - 1);                   // Copy subject
            newEmail.subject[sizeof(newEmail.subject) - 1] = '\0';                      // Adds a null character to the end of the string/array
            strncpy(newEmail.date, date, sizeof(newEmail.date) - 1);                    // Copy date
            newEmail.date[sizeof(newEmail.date) - 1] = '\0';                            // Adds a null character to the end of the string/array

            // Compute priority key based on sender category and date
            newEmail.priority_key = computeCategoryRank(newEmail.sender_category) * 100000000 + parseDateToInt(newEmail.date);
            insertHeap(heap, newEmail); // Insert email into the heap
        }

        // Handle "NEXT" command to display the highest priority email
        else if (strcmp(line, "NEXT") == 0) {                       // Check if command is "NEXT"
            if (heap->size > 0) {                                   // Ensure heap is not empty
                Email next = peekMax(heap);                         // Retrieve highest priority email
                printf("Sender: %s\n", next.sender_category);       // Print sender category
                printf("Subject: %s\n", next.subject);              // Print subject
                printf("Date: %s\n", next.date);                    // Print date
            }
        }

        // Handle "READ" command to remove the highest priority email
        else if (strcmp(line, "READ") == 0) {           // Check if command is "READ"
            if (heap->size > 0) {                       // Ensure heap is not empty
                extractMax(heap);                       // Remove highest priority email
            }
        }

        // Handle "COUNT" command to display the number of emails in the heap
        else if (strcmp(line, "COUNT") == 0) {      // Check if command is "COUNT"
            printf("%d\n", heap->size);             // Print the current heap size
        }
    }
    
    fclose(file); // Close the input file
    
    // Free allocated memory before exiting
    free(heap->emails);     // Free memory allocated for email storage
    free(heap);             // Free memory allocated for heap
    return 0;               // Exit program
}


// Function that creates maxheaps
MaxHeap* createHeap() {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));      // Allocate memory for the heap structure
    heap->size = 0;                                         // Initialize heap size to zero
    heap->capacity = 10;                                    // Set initial capacity to 10
    heap->emails = (Email*)malloc(heap->capacity * sizeof(Email)); // Allocate memory for storing emails
    return heap;                                            // Return the newly created heap
}

// Function to add an email to the heap
void insertHeap(MaxHeap* heap, Email email) {
    if (heap->size == heap->capacity) {                                     // Check if the heap needs to be resized
        heap->capacity *= 2;                                                // Double the heap capacity
        heap->emails = (Email*)realloc(heap->emails, heap->capacity * sizeof(Email)); // Reallocate memory for emails
    }
    heap->emails[heap->size] = email;                       // Insert the email at the end of the heap
    heapifyUp(heap, heap->size);                             // Upheaping the new element
    heap->size++;                                            // Increment the heap size
}

// Function to restore characteristics of the heap by moving new elements up
void heapifyUp(MaxHeap* heap, int index) {
    while (index > 0) {                                 // Continue until the root is reached
        int parent = (index - 1) / 2;                   // Get parent index
        if (heap->emails[parent].priority_key >= heap->emails[index].priority_key) // If parent has higher priority, stop
            break;
        Email temp = heap->emails[parent];              // Swap parent and child
        heap->emails[parent] = heap->emails[index];
        heap->emails[index] = temp;
        index = parent;                                 // Move up to parent index
    }
}

// Function to extract and remove the highest-priority email from the heap
Email extractMax(MaxHeap* heap) {
    Email maxEmail = heap->emails[0];                // Store the highest-priority email
    heap->size--;                                    // Decrease heap size
    if (heap->size > 0) {                           // If heap is not empty
        heap->emails[0] = heap->emails[heap->size]; // Move last email to root
        heapifyDown(heap, 0);                       // Restore heap property by moving the new root down
    }
    return maxEmail; // Return the extracted email
}

// Function to restore heap property by moving an element down
void heapifyDown(MaxHeap* heap, int index) {
    int left = 2 * index + 1;                   // Left child index
    int right = 2 * index + 2;                  // Right child index
    int largest = index;                        // Assume current index is largest

    if (left < heap->size && heap->emails[left].priority_key > heap->emails[largest].priority_key) // Compare with left child
        largest = left;
    if (right < heap->size && heap->emails[right].priority_key > heap->emails[largest].priority_key) // Compare with right child
        largest = right;

    if (largest != index) {                 // If a child has higher priority, swap
        Email temp = heap->emails[index];
        heap->emails[index] = heap->emails[largest];
        heap->emails[largest] = temp;
        heapifyDown(heap, largest);         // Recursively heapify the affected subtree
    }
}

// Function to get the highest-priority email without removing it
Email peekMax(MaxHeap* heap) {
    return heap->emails[0];             // Return the top email in the heap
}

// Function to compute the priority rank of an email sender
int computeCategoryRank(const char* sender_category) {
    if (strcmp(sender_category, "Boss") == 0) return 5;                 // Highest priority
    else if (strcmp(sender_category, "Subordinate") == 0) return 4;
    else if (strcmp(sender_category, "Peer") == 0) return 3;
    else if (strcmp(sender_category, "ImportantPerson") == 0) return 2;
    else if (strcmp(sender_category, "OtherPerson") == 0) return 1;    // Lowest priority
    return 0;                                                           // Default case
}

// Function to convert a date string (MM-DD-YYYY) into an integer for comparison
int parseDateToInt(const char* date) {
    char mm[3], dd[3], yyyy[5];                             // Buffers to store date components
    sscanf(date, "%2[^-]-%2[^-]-%4s", mm, dd, yyyy);        // Parse the date string

    int month = atoi(mm);                                    // Convert month to integer
    int day = atoi(dd);                                     // Convert day to integer

    char yyyymmdd[9];                                       // Buffer to store formatted date
    snprintf(yyyymmdd, sizeof(yyyymmdd), "%s%02d%02d", yyyy, month, day); // Format YYYYMMDD
    return atoi(yyyymmdd);                                   // Convert to integer and return
}

// Function to remove leading and trailing whitespace from a string
void trimWhitespace(char* str) {
    if (!str) return;                            // Return if string is null

    char* end;

    while (isspace((unsigned char)*str)) str++; // Move pointer to first non-whitespace character

    if (*str == 0) {                             // If the string is empty after trimming, exit
        return;
    }

    end = str + strlen(str) - 1;                                // move pointer to the last character
    while (end > str && isspace((unsigned char)*end)) end--;    // Move backward to the last non-whitespace character

    *(end + 1) = 0;                             // End the string with Null
}