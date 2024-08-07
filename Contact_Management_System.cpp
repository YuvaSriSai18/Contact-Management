#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    char name[50];
    char phone[15];
    char email[50];

    struct Contact* next;
};

struct Contact* createContact(char name[], char phone[], char email[]) {
    struct Contact* newContact = (struct Contact*)malloc(sizeof(struct Contact));

    if (newContact != NULL) {
        strcpy(newContact->name, name);
        strcpy(newContact->phone, phone);
        strcpy(newContact->email, email);
        newContact->next = NULL;
    }

    return newContact;
}

void addContact(struct Contact** head, char name[], char phone[], char email[]) {
    struct Contact* newContact = createContact(name, phone, email);

    if (newContact != NULL) {
        newContact->next = *head;
        *head = newContact;
        printf("Contact added successfully!\n");
    } else {
        printf("Failed to add contact. Memory allocation error.\n");
    }
}

void printContacts(struct Contact* head) {
    printf("\n--- Contacts ---\n");
    while (head != NULL) {
        printf("Name: %s\nPhone: %s\nEmail: %s\n\n", head->name, head->phone, head->email);
        head = head->next;
    }
}

void deleteContact(struct Contact** head, char name[]) {
    struct Contact* current = *head;
    struct Contact* prev = NULL;

    while (current != NULL && strcmp(current->name, name) != 0) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        if (prev != NULL) {
            prev->next = current->next;
        } else {
            *head = current->next;
        }
        free(current);
        printf("Contact deleted successfully!\n");
    } else {
        printf("Contact not found.\n");
    }
}

void updateContact(struct Contact* head, char name[]) {
    while (head != NULL) {
        if (strcmp(head->name, name) == 0) {
            printf("Enter new phone number for %s: ", name);
            scanf("%s", head->phone);
            printf("Enter new email address for %s: ", name);
            scanf("%s", head->email);
            printf("Contact updated successfully!\n");
            return;
        }
        head = head->next;
    }

    printf("Contact not found.\n");
}

void retrieveContacts(struct Contact* head, char partOfName[]) {
    printf("\n--- Contacts ---\n");
    while (head != NULL) {
        if (strstr(head->name, partOfName) != NULL) {
            printf("Name: %s\nPhone: %s\nEmail: %s\n\n", head->name, head->phone, head->email);
        }
        head = head->next;
    }
}

struct Contact* merge(struct Contact* left, struct Contact* right) {
    struct Contact* result = NULL;

    if (left == NULL) {
        return right;
    } else if (right == NULL) {
        return left;
    }

    if (strcmp(left->name, right->name) <= 0) {
        result = left;
        result->next = merge(left->next, right);
    } else {
        result = right;
        result->next = merge(left, right->next);
    }

    return result;
}

struct Contact* mergeSort(struct Contact* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    struct Contact* slow = head;
    struct Contact* fast = head->next;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    struct Contact* left = head;
    struct Contact* right = slow->next;
    slow->next = NULL;

    left = mergeSort(left);
    right = mergeSort(right);

    return merge(left, right);
}

void sortContacts(struct Contact** head) {
    *head = mergeSort(*head);
    printf("Contacts sorted alphabetically!\n");
}

void writeToFile(struct Contact* head, const char* filename) {
    FILE* file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    while (head != NULL) {
        fprintf(file, "%s %s %s\n", head->name, head->phone, head->email);
        head = head->next;
    }

    fclose(file);
}

struct Contact* readFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return NULL;
    }

    struct Contact* head = NULL;
    char name[50], phone[15], email[50];

    while (fscanf(file, "%s %s %s", name, phone, email) == 3) {
        addContact(&head, name, phone, email);
    }

    fclose(file);

    return head;
}

void freeContacts(struct Contact* head) {
    while (head != NULL) {
        struct Contact* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Contact* contacts = NULL;
    char name[50], phone[15], email[50];
    char choice, option;

    do {
        printf("Choose an option:\n");
        printf("1. Add Contact\n");
        printf("2. Delete Contact\n");
        printf("3. Update Contact\n");
        printf("4. Retrieve Contacts by Name\n");
        printf("5. Sort Contacts by Name\n");
        printf("6. Print All Contacts\n");
        printf("7. Save Contacts to File\n");
        printf("8. Load Contacts from File\n");
        printf("9. Quit\n");
        printf("Enter your choice: ");
        scanf(" %c", &option);

        switch (option) {
            case '1':
                printf("Enter contact details:\n");
                printf("Name: ");
                scanf("%s", name);
                printf("Phone: ");
                scanf("%s", phone);
                printf("Email: ");
                scanf("%s", email);

                addContact(&contacts, name, phone, email);
                break;

            case '2':
                printf("Enter the name of the contact to delete: ");
                scanf("%s", name);
                deleteContact(&contacts, name);
                break;

            case '3':
                printf("Enter the name of the contact to update: ");
                scanf("%s", name);
                updateContact(contacts, name);
                break;

            case '4':
                printf("Enter a part of the name to retrieve contacts: ");
                scanf("%s", name);
                retrieveContacts(contacts, name);
                break;

            case '5':
                sortContacts(&contacts);
                break;

            case '6':
                printContacts(contacts);
                break;

            case '7':
                writeToFile(contacts, "contacts.txt");
                printf("Contacts saved to file successfully!\n");
                break;

            case '8':
                freeContacts(contacts);
                contacts = readFromFile("contacts.txt");
                printf("Contacts loaded from file successfully!\n");
                break;

            case '9':
                writeToFile(contacts, "contacts.txt");
                freeContacts(contacts);
                printf("Exiting the program. Goodbye!\n");
                return 0;

            default:
                printf("Invalid option. Please choose a valid option.\n");
        }

        printf("Do you want to perform another operation? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    freeContacts(contacts);

    return 0;
}