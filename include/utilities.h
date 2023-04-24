#pragma once
#include "item.h"

typedef struct point
{
    SHORT_INT x;
    SHORT_INT y;
}
point;

typedef struct puzzleState
{
    State puzzle;
    struct puzzleState* prev_puzzle;
    point* empty_space;
    char came_from;  // u for up, d for down, l for left and r for right
    int h, g;
}
puzzleState;
typedef puzzleState* puzzlePointer;

State PuzzleForm(puzzlePointer puzzle);
void swap(unsigned char* a, unsigned char* b);
void printSequence(puzzlePointer A, int n);
void printPuzzle(State A, int n);