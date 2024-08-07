# Contact Management System in C

A simple contact management system implemented in C, using linked lists for storing contact information. The system allows adding, deleting, updating, retrieving, sorting, and saving contacts to a file.

## Features

- Add a new contact
- Delete an existing contact
- Update contact details
- Retrieve contacts by name
- Sort contacts alphabetically by name
- Print all contacts
- Save contacts to a file
- Load contacts from a file

## Installation

1. **Clone the repository**:
    ```sh
    git clone https://github.com/YuvaSriSai18/contact-management-system.git
    cd contact-management-system
    ```

2. **Compile the program**:
    ```sh
    gcc contact_management.c -o contact_management
    ```

## Usage

1. **Run the program**:
    ```sh
    ./contact_management
    ```

2. **Follow the on-screen menu** to perform various operations:
    - Add Contact
    - Delete Contact
    - Update Contact
    - Retrieve Contacts by Name
    - Sort Contacts by Name
    - Print All Contacts
    - Save Contacts to File
    - Load Contacts from File
    - Quit

## Code Overview

### Structure Definition

The `Contact` structure is defined as follows:

```c
struct Contact {
    char name[50];
    char phone[15];
    char email[50];
    struct Contact* next;
};
