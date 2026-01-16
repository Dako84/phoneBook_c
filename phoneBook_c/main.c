#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX_CONTACTS 100
#define NAME_LEN 50
#define PHONE_LEN 20

typedef struct Contact {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
} Contact;

int safeInput(const char* format, void* value);
int safeInputString(char* buffer, int size);

void addContact(Contact contacts[], int* count);
void printContacts(Contact contacts[], int count);
void searchContact(Contact contacts[], int count);
void editContact(Contact contacts[], int count);
void deleteContact(Contact contacts[], int* count);
void saveToFile(Contact contacts[], int count);
void loadFromFile(Contact contacts[], int* count);

int main() {
    Contact contacts[MAX_CONTACTS] = { 0 };
    int count = 0;
    int choice = 0;

    printf("Welcome to the Phone Book Application!\n");

    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Add Contact\n");
        printf("2. Print Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Edit Contact\n");
        printf("5. Delete Contact\n");
        printf("6. Save Contacts to File\n");
        printf("7. Load Contacts from File\n");
        printf("8. Exit\n");
        printf("Choose an option: ");

        safeInput("%d", &choice);

        if (choice == 1) {
            addContact(contacts, &count);
        }
        else if (choice == 2) {
            printContacts(contacts, count);
        }
        else if (choice == 3) {
            searchContact(contacts, count);
        }
        else if (choice == 4) {
            editContact(contacts, count);
        }
        else if (choice == 5) {
            deleteContact(contacts, &count);
        }
        else if (choice == 6) {
            saveToFile(contacts, count);
        }
        else if (choice == 7) {
            loadFromFile(contacts, &count);
        }
        else if (choice == 8) {
            printf("Goodbye!\n");
            break;
        }
        else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
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
        printf("Input error.\n");
        return 0;
    }

    buffer[strcspn(buffer, "\n")] = '\0';
    return 1;
}

void addContact(Contact contacts[], int* count) {
    if (*count >= MAX_CONTACTS) {
        printf("Phone book is full.\n");
        return;
    }

    printf("Enter name: ");
    safeInputString(contacts[*count].name, NAME_LEN);

    printf("Enter phone: ");
    safeInputString(contacts[*count].phone, PHONE_LEN);

    (*count)++;
    printf("Contact added successfully!\n");
}

void printContacts(Contact contacts[], int count) {
    if (count == 0) {
        printf("No contacts to display.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("Contact %d: Name: %s, Phone: %s\n",
            i + 1, contacts[i].name, contacts[i].phone);
    }
}

void searchContact(Contact contacts[], int count) {
    char query[NAME_LEN];

    printf("Enter name to search: ");
    safeInputString(query, NAME_LEN);

    int found = 0;

    for (int i = 0; i < count; i++) {
        if (strstr(contacts[i].name, query)) {
            found++;
            printf("Match %d: Name: %s, Phone: %s\n",
                found, contacts[i].name, contacts[i].phone);
        }
    }

    if (!found)
        printf("No contacts found.\n");
}

void editContact(Contact contacts[], int count) {
    char searchName[NAME_LEN];
    printf("Enter name to edit: ");
    safeInputString(searchName, NAME_LEN);

    int index = -1;

    for (int i = 0; i < count; i++) {
        if (strcmp(contacts[i].name, searchName) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Contact not found.\n");
        return;
    }

    printf("Editing contact: %s\n", contacts[index].name);

    char newName[NAME_LEN];
    char newPhone[PHONE_LEN];

    printf("Enter new name (leave empty to keep current): ");
    safeInputString(newName, NAME_LEN);

    printf("Enter new phone (leave empty to keep current): ");
    safeInputString(newPhone, PHONE_LEN);

    if (strlen(newName) > 0)
        strcpy(contacts[index].name, newName);

    if (strlen(newPhone) > 0)
        strcpy(contacts[index].phone, newPhone);

    printf("Contact updated.\n");
}

void deleteContact(Contact contacts[], int* count) {
    char query[NAME_LEN];

    printf("Enter name to delete: ");
    safeInputString(query, NAME_LEN);

    for (int i = 0; i < *count; i++) {
        if (strcmp(contacts[i].name, query) == 0) {

            for (int j = i; j < *count - 1; j++) {
                contacts[j] = contacts[j + 1];
            }

            (*count)--;

            printf("Contact deleted.\n");
            return;
        }
    }

    printf("Contact not found.\n");
}

void saveToFile(Contact contacts[], int count) {
    FILE* file = fopen("contacts.txt", "w");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s;%s\n", contacts[i].name, contacts[i].phone);
    }

    fclose(file);
    printf("Contacts saved.\n");
}

void loadFromFile(Contact contacts[], int* count) {
    FILE* file = fopen("contacts.txt", "r");
    if (!file) {
        printf("No saved file found.\n");
        return;
    }

    *count = 0;

    char line[200];
    while (fgets(line, sizeof(line), file)) {

        line[strcspn(line, "\n")] = '\0';

        char* name = strtok(line, ";");
        char* phone = strtok(NULL, ";");

        if (!name || !phone)
            continue;

        strcpy(contacts[*count].name, name);
        strcpy(contacts[*count].phone, phone);
        (*count)++;
    }

    fclose(file);
    printf("Contacts loaded.\n");
}