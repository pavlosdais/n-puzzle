#include <stdio.h>
#include <stdlib.h>
#include "../include/item.h"
#include "../include/SolvePuzzle.h"

typedef struct StackNode
{
    puzzlePointer puzzle;
    struct StackNode* next;
}
StackNode;

typedef struct StackNode* Stack;

void StackInit(Stack* S) { (*S) = NULL; }

void Push(Stack* S, puzzlePointer puzzle)
{
    // create a new node
    Stack new_node = malloc(sizeof(StackNode));
    if (new_node == NULL) return;  // allocation failure

    // fill the node
    new_node->puzzle = puzzle;

    new_node->next = *S;
    *S = new_node;
}

void DestroyStack(Stack S, int n)
{
    while (S != NULL)
    {
        Stack tmp = S;
        DestroyPuzzle(S->puzzle, n);  // free the board
        S = S->next;
        free(tmp);
    }
}