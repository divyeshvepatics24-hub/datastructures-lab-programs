#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* head = NULL;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Insert at beginning
void insertAtBeginning(int data) {
    Node* newNode = createNode(data);
    if (newNode == NULL) return;
    
    newNode->next = head;
    head = newNode;
    printf("Inserted %d at beginning\n", data);
}

// Insert at end
void insertAtEnd(int data) {
    Node* newNode = createNode(data);
    if (newNode == NULL) return;
    
    if (head == NULL) {
        head = newNode;
        printf("Inserted %d at end\n", data);
        return;
    }
    
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    printf("Inserted %d at end\n", data);
}

// Insert at position
void insertAtPosition(int data, int position) {
    if (position < 1) {
        printf("Invalid position!\n");
        return;
    }
    
    if (position == 1) {
        insertAtBeginning(data);
        return;
    }
    
    Node* newNode = createNode(data);
    if (newNode == NULL) return;
    
    Node* temp = head;
    for (int i = 1; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Position out of range!\n");
        free(newNode);
        return;
    }
    
    newNode->next = temp->next;
    temp->next = newNode;
    printf("Inserted %d at position %d\n", data, position);
}

// Delete from beginning
void deleteFromBeginning() {
    if (head == NULL) {
        printf("List is empty! Cannot delete\n");
        return;
    }
    
    Node* temp = head;
    head = head->next;
    printf("Deleted %d from beginning\n", temp->data);
    free(temp);
}

// Delete from end
void deleteFromEnd() {
    if (head == NULL) {
        printf("List is empty! Cannot delete\n");
        return;
    }
    
    if (head->next == NULL) {
        printf("Deleted %d from end\n", head->data);
        free(head);
        head = NULL;
        return;
    }
    
    Node* temp = head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    
    printf("Deleted %d from end\n", temp->next->data);
    free(temp->next);
    temp->next = NULL;
}

// Delete from position
void deleteFromPosition(int position) {
    if (head == NULL) {
        printf("List is empty! Cannot delete\n");
        return;
    }
    
    if (position < 1) {
        printf("Invalid position!\n");
        return;
    }
    
    if (position == 1) {
        deleteFromBeginning();
        return;
    }
    
    Node* temp = head;
    for (int i = 1; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    
    if (temp == NULL || temp->next == NULL) {
        printf("Position out of range!\n");
        return;
    }
    
    Node* toDelete = temp->next;
    temp->next = toDelete->next;
    printf("Deleted %d from position %d\n", toDelete->data, position);
    free(toDelete);
}

// Search for an element
void search(int data) {
    Node* temp = head;
    int position = 1;
    
    while (temp != NULL) {
        if (temp->data == data) {
            printf("Element %d found at position %d\n", data, position);
            return;
        }
        temp = temp->next;
        position++;
    }
    
    printf("Element %d not found in the list\n", data);
}

// Display the list
void display() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    Node* temp = head;
    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    int choice, data, position;
    
    while (1) {
        printf("\n--- Linked List Operations Menu ---\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert at Position\n");
        printf("4. Delete from Beginning\n");
        printf("5. Delete from End\n");
        printf("6. Delete from Position\n");
        printf("7. Search\n");
        printf("8. Display\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &data);
                insertAtBeginning(data);
                break;
            case 2:
                printf("Enter value to insert: ");
                scanf("%d", &data);
                insertAtEnd(data);
                break;
            case 3:
                printf("Enter value to insert: ");
                scanf("%d", &data);
                printf("Enter position: ");
                scanf("%d", &position);
                insertAtPosition(data, position);
                break;
            case 4:
                deleteFromBeginning();
                break;
            case 5:
                deleteFromEnd();
                break;
            case 6:
                printf("Enter position to delete: ");
                scanf("%d", &position);
                deleteFromPosition(position);
                break;
            case 7:
                printf("Enter value to search: ");
                scanf("%d", &data);
                search(data);
                break;
            case 8:
                display();
                break;
            case 9:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}
