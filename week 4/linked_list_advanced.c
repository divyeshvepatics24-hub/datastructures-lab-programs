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

// Insert at end (helper function)
void insertAtEnd(int data) {
    Node* newNode = createNode(data);
    if (newNode == NULL) return;
    
    if (head == NULL) {
        head = newNode;
        return;
    }
    
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    printf("Inserted %d\n", data);
}

// Delete by value
void deleteByValue(int value) {
    if (head == NULL) {
        printf("List is empty! Cannot delete\n");
        return;
    }
    
    // If head node contains the value
    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        printf("Deleted %d from list\n", value);
        free(temp);
        return;
    }
    
    Node* temp = head;
    while (temp->next != NULL && temp->next->data != value) {
        temp = temp->next;
    }
    
    if (temp->next == NULL) {
        printf("Value %d not found in the list\n", value);
        return;
    }
    
    Node* toDelete = temp->next;
    temp->next = toDelete->next;
    printf("Deleted %d from list\n", value);
    free(toDelete);
}

// Sort the list using bubble sort
void sortList() {
    if (head == NULL || head->next == NULL) {
        printf("List is empty or has only one element\n");
        return;
    }
    
    int swapped;
    Node* ptr1;
    Node* lptr = NULL;
    
    do {
        swapped = 0;
        ptr1 = head;
        
        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                // Swap data
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    
    printf("List sorted successfully\n");
}

// Reverse the list
void reverseList() {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    Node* prev = NULL;
    Node* current = head;
    Node* next = NULL;
    
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    head = prev;
    printf("List reversed successfully\n");
}

// Concatenate two lists
void concatenate() {
    Node* head2 = NULL;
    int n, data;
    
    printf("Enter number of elements for second list: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Invalid number of elements\n");
        return;
    }
    
    printf("Enter elements for second list:\n");
    for (int i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &data);
        
        Node* newNode = createNode(data);
        if (newNode == NULL) continue;
        
        if (head2 == NULL) {
            head2 = newNode;
        } else {
            Node* temp = head2;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    
    if (head == NULL) {
        head = head2;
    } else {
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = head2;
    }
    
    printf("Lists concatenated successfully\n");
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
    int choice, data;
    
    while (1) {
        printf("\n--- Advanced Linked List Operations Menu ---\n");
        printf("1. Insert Element\n");
        printf("2. Delete by Value\n");
        printf("3. Sort List\n");
        printf("4. Reverse List\n");
        printf("5. Concatenate Lists\n");
        printf("6. Display\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &data);
                insertAtEnd(data);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &data);
                deleteByValue(data);
                break;
            case 3:
                sortList();
                break;
            case 4:
                reverseList();
                break;
            case 5:
                concatenate();
                break;
            case 6:
                display();
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}
