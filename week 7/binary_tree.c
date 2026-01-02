#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* root = NULL;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Insert a node into BST
Node* insert(Node* node, int data) {
    if (node == NULL) {
        return createNode(data);
    }
    
    if (data < node->data) {
        node->left = insert(node->left, data);
    } else if (data > node->data) {
        node->right = insert(node->right, data);
    } else {
        printf("Duplicate value %d not inserted\n", data);
    }
    
    return node;
}

// Find minimum value node
Node* findMin(Node* node) {
    if (node == NULL) {
        return NULL;
    }
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Delete a node from BST
Node* deleteNode(Node* node, int data) {
    if (node == NULL) {
        printf("Value %d not found\n", data);
        return NULL;
    }
    
    if (data < node->data) {
        node->left = deleteNode(node->left, data);
    } else if (data > node->data) {
        node->right = deleteNode(node->right, data);
    } else {
        // Node with only one child or no child
        if (node->left == NULL) {
            Node* temp = node->right;
            printf("Deleted %d from tree\n", node->data);
            free(node);
            return temp;
        } else if (node->right == NULL) {
            Node* temp = node->left;
            printf("Deleted %d from tree\n", node->data);
            free(node);
            return temp;
        }
        
        // Node with two children
        Node* temp = findMin(node->right);
        node->data = temp->data;
        node->right = deleteNode(node->right, temp->data);
    }
    
    return node;
}

// Search for a value in BST
Node* search(Node* node, int data) {
    if (node == NULL || node->data == data) {
        return node;
    }
    
    if (data < node->data) {
        return search(node->left, data);
    }
    
    return search(node->right, data);
}

// Inorder traversal (Left-Root-Right)
void inorder(Node* node) {
    if (node != NULL) {
        inorder(node->left);
        printf("%d ", node->data);
        inorder(node->right);
    }
}

// Preorder traversal (Root-Left-Right)
void preorder(Node* node) {
    if (node != NULL) {
        printf("%d ", node->data);
        preorder(node->left);
        preorder(node->right);
    }
}

// Postorder traversal (Left-Right-Root)
void postorder(Node* node) {
    if (node != NULL) {
        postorder(node->left);
        postorder(node->right);
        printf("%d ", node->data);
    }
}

int main() {
    int choice, data;
    Node* result;
    
    while (1) {
        printf("\n--- Binary Search Tree Operations Menu ---\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Inorder Traversal\n");
        printf("5. Preorder Traversal\n");
        printf("6. Postorder Traversal\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                printf("Inserted %d into tree\n", data);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &data);
                root = deleteNode(root, data);
                break;
            case 3:
                printf("Enter value to search: ");
                scanf("%d", &data);
                result = search(root, data);
                if (result != NULL) {
                    printf("Value %d found in tree\n", data);
                } else {
                    printf("Value %d not found in tree\n", data);
                }
                break;
            case 4:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 5:
                printf("Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;
            case 6:
                printf("Postorder Traversal: ");
                postorder(root);
                printf("\n");
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}
