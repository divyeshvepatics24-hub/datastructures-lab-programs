#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Queue structure for BFS
typedef struct {
    int items[MAX];
    int front;
    int rear;
} Queue;

void initQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue* q) {
    return q->front == -1;
}

void enqueue(Queue* q, int value) {
    if (q->front == -1) {
        q->front = 0;
    }
    q->items[++(q->rear)] = value;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) {
        return -1;
    }
    int value = q->items[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    return value;
}

// BFS traversal function
void BFS(int graph[MAX][MAX], int vertices, int start) {
    int visited[MAX] = {0};
    Queue q;
    initQueue(&q);
    
    printf("BFS Traversal starting from vertex %d: ", start);
    
    visited[start] = 1;
    enqueue(&q, start);
    
    while (!isEmpty(&q)) {
        int current = dequeue(&q);
        printf("%d ", current);
        
        // Visit all adjacent vertices
        for (int i = 0; i < vertices; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                visited[i] = 1;
                enqueue(&q, i);
            }
        }
    }
    printf("\n");
}

int main() {
    int vertices, edges;
    int graph[MAX][MAX] = {0};
    int choice, start, u, v;
    
    printf("Enter number of vertices: ");
    scanf("%d", &vertices);
    
    if (vertices <= 0 || vertices > MAX) {
        printf("Invalid number of vertices!\n");
        return 1;
    }
    
    while (1) {
        printf("\n--- BFS Graph Traversal Menu ---\n");
        printf("1. Add Edge\n");
        printf("2. Display Adjacency Matrix\n");
        printf("3. Perform BFS\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter edge (u v): ");
                scanf("%d %d", &u, &v);
                if (u >= 0 && u < vertices && v >= 0 && v < vertices) {
                    graph[u][v] = 1;
                    graph[v][u] = 1; // For undirected graph
                    printf("Edge added between %d and %d\n", u, v);
                } else {
                    printf("Invalid vertices!\n");
                }
                break;
            case 2:
                printf("Adjacency Matrix:\n");
                printf("   ");
                for (int i = 0; i < vertices; i++) {
                    printf("%2d ", i);
                }
                printf("\n");
                for (int i = 0; i < vertices; i++) {
                    printf("%2d ", i);
                    for (int j = 0; j < vertices; j++) {
                        printf("%2d ", graph[i][j]);
                    }
                    printf("\n");
                }
                break;
            case 3:
                printf("Enter starting vertex: ");
                scanf("%d", &start);
                if (start >= 0 && start < vertices) {
                    BFS(graph, vertices, start);
                } else {
                    printf("Invalid starting vertex!\n");
                }
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}
