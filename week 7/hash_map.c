#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

// Node structure for chaining
typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

// Hash table
Node* hashTable[TABLE_SIZE];

// Initialize hash table
void initHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
}

// Hash function
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Create a new node
Node* createNode(int key, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Insert key-value pair
void insert(int key, int value) {
    int index = hashFunction(key);
    Node* newNode = createNode(key, value);
    
    if (newNode == NULL) return;
    
    // If slot is empty
    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
        printf("Inserted key %d with value %d at index %d\n", key, value, index);
        return;
    }
    
    // Check if key already exists
    Node* temp = hashTable[index];
    while (temp != NULL) {
        if (temp->key == key) {
            temp->value = value;
            printf("Updated key %d with value %d at index %d\n", key, value, index);
            free(newNode);
            return;
        }
        if (temp->next == NULL) break;
        temp = temp->next;
    }
    
    // Add to end of chain
    temp->next = newNode;
    printf("Inserted key %d with value %d at index %d (chained)\n", key, value, index);
}

// Search for a key
int search(int key) {
    int index = hashFunction(key);
    Node* temp = hashTable[index];
    
    while (temp != NULL) {
        if (temp->key == key) {
            printf("Key %d found with value %d at index %d\n", key, temp->value, index);
            return temp->value;
        }
        temp = temp->next;
    }
    
    printf("Key %d not found\n", key);
    return -1;
}

// Delete a key
void delete(int key) {
    int index = hashFunction(key);
    Node* temp = hashTable[index];
    Node* prev = NULL;
    
    while (temp != NULL) {
        if (temp->key == key) {
            if (prev == NULL) {
                // First node in chain
                hashTable[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            printf("Deleted key %d from index %d\n", key, index);
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    
    printf("Key %d not found\n", key);
}

// Display hash table
void display() {
    printf("\n--- Hash Table ---\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        Node* temp = hashTable[i];
        if (temp == NULL) {
            printf("Empty\n");
        } else {
            while (temp != NULL) {
                printf("[%d: %d] -> ", temp->key, temp->value);
                temp = temp->next;
            }
            printf("NULL\n");
        }
    }
}

int main() {
    int choice, key, value;
    
    initHashTable();
    
    while (1) {
        printf("\n--- Hash Map Operations Menu ---\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter key: ");
                scanf("%d", &key);
                printf("Enter value: ");
                scanf("%d", &value);
                insert(key, value);
                break;
            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                search(key);
                break;
            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                delete(key);
                break;
            case 4:
                display();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}
