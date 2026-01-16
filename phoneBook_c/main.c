#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_CONTACTS 100
#define NAME_LEN 50
#define PHONE_LEN 20


struct Contact {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
};

void addContact(struct Contact contacts[], int* count);
void printContacts(struct Contact contacts[], int count);

int safeInput(const char* format, void* value);

int safeInputString(char* buffer, int size);

int safeInputWithCheck(const char* format, void* value, int(*check)(void*));

int main() {
    struct Contact contacts[MAX_CONTACTS] = { 0 };  // מאגר אנשי קשר
    int count = 0;                 // כמה אנשי קשר קיימים כרגע
    int choice = 0;

    for (int i = 0; i < MAX_CONTACTS; i++) {
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
        //scanf("%d", &choice);
        safeInput("%d", &choice);


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

    for (int i = 0; i < MAX_CONTACTS; i++) {
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
    safeInputString(contacts[index].name, NAME_LEN);


    printf("Enter phone: ");
    safeInputString(contacts[index].phone, PHONE_LEN);

    (*count)++;
    printf("Contact added successfully!\n");
}

void printContacts(struct Contact contacts[], int count)
{
    int printed = 0;

    for (int i = 0; i < MAX_CONTACTS; i++) {
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

int safeInput(const char* format, void* value) {
    while (1) {
        if (scanf(format, value) == 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            return 1;
        }

        printf("Invalid input. Try again.\n");

        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

int safeInputString(char* buffer, int size) {
    if (fgets(buffer, size, stdin) == NULL) {
        printf("Input error. Try again.\n");
        return 0;
    }

    // הסרת תו ה־'\n' אם קיים
    int len = 0;
    while (buffer[len] != '\0') {
        if (buffer[len] == '\n') {
            buffer[len] = '\0';
            break;
        }
        len++;
    }

    return 1;
}

int safeInputWithCheck(
    const char* format,
    void* value,
    int (*check)(void*)
)
{
    while (1) {
        if (!safeInput(format, value))
            continue;

        if (check == NULL || check(value))
            return 1;

        printf("Value not valid. Try again.\n");
    }
}


