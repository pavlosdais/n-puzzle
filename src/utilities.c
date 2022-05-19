#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "../include/item.h"

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
    char came_from;
    int h, g;
}
puzzleState;

typedef puzzleState* puzzlePointer;

State PuzzleForm(puzzlePointer puzzle) { return puzzle->puzzle; }

void printSpaces(int m, int a) { for (int i = 0; i < m-a; i++) printf(" "); }

void printS(int n, int m) 
{
    int k = n*m+n+1;
    for (int i = 0; i < k; i++) printf("-");
    printf("\n");
}

int findlen(int a);

void printPuzzle(State A, int n)
{
    int m = 1;
    if (n > 3) m = 2;
    for (int i = 0; i < n; i++)
    {
        printS(n, m);
        printf("|");
        for (int j = 0; j < n; j++)
        {
            if (A[i][j] == 0) printSpaces(m, findlen(A[i][j]));
            else printf("%*d", m, A[i][j]);
            if (j != n-1) printf(" ");
        }
        printf("|");
        printf("\n");
    }
    printS(n, m);
}

void printSequence(puzzlePointer A, int n)
{
    if (A == NULL) return;  // base case
    else
        printSequence(A->prev_puzzle, n);
    
    printf("\n");
    printPuzzle(PuzzleForm(A), n);
}

void swap(SHORT_INT* a, SHORT_INT* b)
{
    SHORT_INT temp = *a;
    *a = *b;
    *b = temp;
}

int findlen(int a)
{
    int l = 0;
    while (a != 0)
    {
        a /= 10;
        l++;
    }
    return l;
}