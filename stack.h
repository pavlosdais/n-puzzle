#include "item.h"
typedef struct StackNode* Stack;
typedef struct puzzleState puzzleState;
typedef puzzleState* puzzlePointer;

void StackInit(Stack* S);
void Push(Stack* S, puzzlePointer puzzle);
void DestroyStack(Stack S, int n);
char checkState(Stack S, State A, int h, int n);