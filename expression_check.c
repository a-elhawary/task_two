#include "stdio.h"
#include "stdlib.h"

typedef struct node
{
    char data;
    struct node *next;
} node_s;

typedef struct stack
{
    node_s *top;
    int currentSize;
} stack_s;

stack_s *initStack()
{
    stack_s *stack = (stack_s *)malloc(sizeof(stack_s));
    stack->currentSize = 0;
    stack->top = NULL;
    return stack;
}

void push(stack_s *stack, char data)
{
    node_s *oldTop = stack->top;
    stack->top = (node_s *)malloc(sizeof(node_s));
    stack->top->data = data;
    stack->top->next = oldTop;
    stack->currentSize++;
}

char pop(stack_s *stack)
{
    char data = stack->top->data;
    node_s *newHead = stack->top->next;
    free(stack->top);
    stack->top = newHead;
    stack->currentSize--;
    return data;
}

void printStack(stack_s *stack)
{
    node_s *currentNode = stack->top;
    int i = 0;
    printf("Printing stack\n");
    while (currentNode != NULL)
    {
        printf("Stack element %i: %c\n", i, currentNode->data);
        currentNode = currentNode->next;
        i++;
    }
}

void testStack()
{
    stack_s *stack = initStack();
    char currentData;
    printf("Enter some data: ");
    scanf("%c", &currentData);
    while (currentData != '@')
    {
        if (currentData != '-')
        {
            push(stack, currentData);
            printStack(stack);
        }
        else
        {
            printf("popped %c\n", pop(stack));
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        printf("Enter some data: ");
        scanf("%c", &currentData);
    }
}

char expression_check(char *expression)
{
    int i = 0;
    stack_s *stack = initStack();
    while (expression[i] != '\0')
    {
        printf("%c\n", expression[i]);
        switch (expression[i])
        {
        case '(':
        case '[':
        case '{':
            push(stack, expression[i]);
            break;
        case ')':
            if (pop(stack) != '(')
                return 0;
            break;
        case ']':
            if (pop(stack) != '[')
                return 0;
            break;
        case '}':
            if (pop(stack) != '{')
                return 0;
            break;
        }
        printStack(stack);
        printf("\n");
        i++;
    }
    if (stack->currentSize > 0)
    {
        return 0;
    }
    return 1;
}

int main()
{
    char *expression;
    printf("Please enter a mathematical expression (not whitespaces): ");
    scanf("%s", expression);
    if (expression_check(expression) == 0)
    {
        printf("Unbalanced Statement\n");
    }
    else
    {
        printf("Balanced Statement\n");
    }
    return 0;
}