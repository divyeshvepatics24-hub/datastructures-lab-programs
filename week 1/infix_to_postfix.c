#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    char items[MAX];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

int isFull(Stack* s) {
    return s->top == MAX - 1;
}

void push(Stack* s, char c) {
    if (isFull(s)) {
        printf("Stack Overflow!\n");
        return;
    }
    s->items[++(s->top)] = c;
}

char pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack Underflow!\n");
        return '\0';
    }
    return s->items[(s->top)--];
}

char peek(Stack* s) {
    if (isEmpty(s)) {
        return '\0';
    }
    return s->items[s->top];
}

// Function to determine operator precedence
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

// Function to check if character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Function to convert infix to postfix
void infixToPostfix(char* infix, char* postfix) {
    Stack s;
    initStack(&s);
    int i = 0, j = 0;
    
    while (infix[i] != '\0') {
        char ch = infix[i];
        
        // If character is operand, add to output
        if (isalnum(ch)) {
            postfix[j++] = ch;
        }
        // If character is '(', push to stack
        else if (ch == '(') {
            push(&s, ch);
        }
        // If character is ')', pop until '(' is found
        else if (ch == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[j++] = pop(&s);
            }
            if (!isEmpty(&s) && peek(&s) == '(') {
                pop(&s); // Remove '(' from stack
            }
        }
        // If character is an operator
        else if (isOperator(ch)) {
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(ch)) {
                postfix[j++] = pop(&s);
            }
            push(&s, ch);
        }
        i++;
    }
    
    // Pop remaining operators from stack
    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s);
    }
    
    postfix[j] = '\0';
}

int main() {
    char infix[MAX], postfix[MAX];
    int choice;
    
    while (1) {
        printf("\n--- Infix to Postfix Conversion Menu ---\n");
        printf("1. Convert Infix to Postfix\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline
        
        switch (choice) {
            case 1:
                printf("Enter infix expression: ");
                fgets(infix, MAX, stdin);
                infix[strcspn(infix, "\n")] = '\0'; // Remove newline
                
                infixToPostfix(infix, postfix);
                printf("Postfix expression: %s\n", postfix);
                break;
            case 2:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}
