#include <stdio.h>
#include <stdlib.h>
#include "SolvePuzzle.h"

typedef struct PriorityQueueNode
{
    puzzlePointer puzzle;
    int g;
    int h;
    struct PriorityQueueNode* next;
}
PriorityQueueNode;

typedef struct PriorityQueueNode* PriorityQueue;

void QueueInit(PriorityQueue* Queue) { (*Queue) = NULL; }

char IsEmpty(PriorityQueue Queue) { return (Queue == NULL); }

void Enqueue(PriorityQueue* Queue, puzzlePointer puzzle, int g, int h)
{
    // keep the queue sorted by putting the element in the corrent position - O(n)

    // create a new node
    PriorityQueue new_node = malloc(sizeof(PriorityQueueNode));
    if (new_node == NULL) return;  // allocation failure

    // fill the node
    new_node->puzzle = puzzle;
    new_node->g = g;
    new_node->h = h;

    // empty queue - the new node becomes the head of the queue
    if (IsEmpty(*Queue))
    {
        new_node->next = NULL;
        (*Queue) = new_node;
        return;
    }

    int f = g + h;
    // the head of the node has less priority than the new node, meaning the new value should be first
    if (f < ((*Queue)->g + (*Queue)->h))
    {
        new_node->next = (*Queue);
        (*Queue) = new_node;
        return;
    }

    // in any other case, traverse the list and find the correct position to insert the new node
    PriorityQueue tmp = (*Queue);
    while (tmp->next != NULL && (tmp->next->g + tmp->next->h) < f) tmp = tmp->next;

    // put the node at its place
    new_node->next = tmp->next;
    tmp->next = new_node;
}

puzzlePointer Dequeue(PriorityQueue* Queue, int* g, int* h)
{
    // priority queue is already sorted, pop the element - O(1)

    puzzlePointer r = (*Queue)->puzzle;  // save the puzzle
    // save heuristic and static evaluation
    *g = (*Queue)->g;
    *h = (*Queue)->h;

    // remove the node
    PriorityQueue tmp;
    tmp = (*Queue);
    (*Queue) = (*Queue)->next;
    free(tmp);

    // return puzzle
    return r;
}

void DestroyPQueue(PriorityQueue Queue, int n)
{
    PriorityQueue tmp = NULL;
    puzzlePointer tmpPuzzle = NULL;
    while (!IsEmpty(Queue))
    {
        tmp = Queue;
        tmpPuzzle = Queue->puzzle;
        Queue = Queue->next;
        free(tmp);
        DestroyPuzzle(tmpPuzzle, n);  // free the board
    }
}