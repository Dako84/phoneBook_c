#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>



struct Contact {
    char name[50];
    char phone[20];
};

void addContact(struct Contact contacts[], int* count);
void printContacts(struct Contact contacts[], int count);

int main() {
    struct Contact contacts[100];  // מאגר אנשי קשר
    int count = 0;                 // כמה אנשי קשר קיימים כרגע
    int choice;

    for (int i = 0; i < 100; i++) {
        contacts[i].name[0] = '\0';
        contacts[i].phone[0] = '\0';
    }


    printf("Welcome to the Phone Book Application!\n");

    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Add Contact\n");
        printf("2. Print Contacts\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 1) {
            // כאן נוסיף addContact בעתיד
            printf("Add Contact selected.\n");
            addContact(contacts, &count);

        }
        else if (choice == 2) {
            // כאן נוסיף printContacts בעתיד
            printf("Print Contacts selected.\n");
            printContacts(contacts, count);
        }
        else if (choice == 3) {
            printf("Goodbye!\n");
            break;
        }
        else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}

void addContact(struct Contact contacts[], int* count) {
    int index = -1;

    for (int i = 0; i < 100; i++) {
        if (contacts[i].name[0] == '\0') {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Phone book is full.\n");
        return;
    }

    printf("Enter name: "); 
    scanf("%49s", contacts[index].name); 
    while (getchar() != '\n'); // ניקוי ה־Enter שנשאר

    printf("Enter phone: ");
    scanf("%19s", contacts[index].phone);
    while (getchar() != '\n'); // ניקוי ה־Enter שנשאר

    (*count)++;
    printf("Contact added successfully!\n");
}

void printContacts(struct Contact contacts[], int count)
{
    int printed = 0;

    for (int i = 0; i < 100; i++) {
        if (contacts[i].name[0] != '\0') {
            printed++;
            printf("Contact %d: Name: %s, Phone: %s\n",
                printed, contacts[i].name, contacts[i].phone);
        }
    }

    if (printed == 0) {
        printf("No contacts to display.\n");
    }
}


