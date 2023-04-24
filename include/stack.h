#pragma once
#include "item.h"
#include "utilities.h"

typedef struct StackNode* Stack;


void StackInit(Stack* S);
void Push(Stack* S, puzzlePointer puzzle);
void DestroyStack(Stack S, int n);
char checkState(Stack S, State A, int h, int n);