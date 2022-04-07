#include "item.h"
typedef struct PriorityQueueNode* PriorityQueue;

void QueueInit(PriorityQueue* Queue);
char IsEmpty(PriorityQueue Queue);
void Enqueue(PriorityQueue* Queue, puzzlePointer puzzle, int g, int h);
puzzlePointer Dequeue(PriorityQueue* Queue, int* g, int* h);
void DestroyPQueue(PriorityQueue Queue, int n);