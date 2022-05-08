#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/item.h"
#include "../include/utilities.h"
#include "../include/PriorityQueue.h"
#include "../include/stack.h"

#define ABS(A, B) ((A > B)? (A-B): (B-A))

// Function Prototypes
void explore_neighbours(PriorityQueue* Q, Stack* explored_states, puzzlePointer puzzle, int n, int old_g, int old_h);
int heuristicEval(State puzzle, int n);
int heuristicEvalFix(int old_h, puzzlePointer old_puzzle, puzzlePointer new_puzzle, int n);
bool isEndState(State puzzle, int n);
void DestroyPuzzle(puzzlePointer A, int n);
puzzlePointer createPuzzle(int n, puzzlePointer prev_puzzle);
puzzlePointer copyPuzzle(puzzlePointer puzzle, int n);

void AstarSearch(puzzlePointer puzzle, int n)
{
    // Puzzle is solvable, start the search
    int g = 0, h;

    PriorityQueue Q;
    QueueInit(&Q);
    Enqueue(&Q, puzzle, g, heuristicEval(PuzzleForm(puzzle), n));  // calculate h only for the first state, then keep updating it

    // Use a stack to store all the puzzle states checked and not found to be in the terminal state
    Stack explored_states;
    StackInit(&explored_states);

    while(!IsEmpty(Q))
    {
        puzzlePointer p = Dequeue(&Q, &g, &h);
        if (isEndState(PuzzleForm(p), n))  // Puzzle is solved
        {
            if (g == 0) printf("\nPuzzle already solved");
            else if (g == 1) printf("\nSolved in 1 move");
            else printf("\nSolved in %d moves", g);
            printSequence(p, n);
            DestroyPuzzle(p, n);
            break;
        }
        explore_neighbours(&Q, &explored_states, p, n, g, h);
    }
    DestroyStack(explored_states, n);
    DestroyPQueue(Q, n);
}

void explore_neighbours(PriorityQueue* Q, Stack* explored_states, puzzlePointer puzzle, int n, int old_g, int old_h)
{
    // Save the previous puzzle before exploring the puzzles that can be created
    Push(explored_states, puzzle);

    /* directional vectors with the coordinates of adjacent cells (c,r) of a piece in the puzzle
    -left (c-1,r)
    -right (c+1,r)
    -down (c,r+1)
    -up (c,r-1) */
    SHORT_INT dr[] = {-1, 1, 0, 0};
    SHORT_INT dc[] = {0, 0, 1, -1};

    char* dir = "lrdu";
    char* op_dir = "rlud";
    for (int i = 0; i < 4; i++)
    {
        // avoid making duplicates by not repeating the move that brought the puzzle in its currect form
        /* for example: i = 0 so, dir[0] = l and op_dir[0] = r
        so puzzle came from a right move so avoid making the same puzzle by moving left */
        if (puzzle->came_from == op_dir[i]) continue;

        // new adjacent cell (rr, cc) - new empty space
        SHORT_INT rr = puzzle->empty_space->x + dr[i];
        SHORT_INT cc = puzzle->empty_space->y + dc[i];
        if (rr < 0 || cc < 0 || rr >= n || cc >= n) continue;  // cell out of bounds

        // create the new puzzle form
        puzzlePointer new_puzzle = copyPuzzle(puzzle, n);
        if (new_puzzle == NULL) return;  // memory allocation failure

        // move piece to the new empty space - empty space becomes the place where the piece used to be
        swap(&(new_puzzle->puzzle[puzzle->empty_space->x][puzzle->empty_space->y]), &(new_puzzle->puzzle[rr][cc]));
        new_puzzle->empty_space->x = rr;
        new_puzzle->empty_space->y = cc;

        new_puzzle->came_from = dir[i];
        Enqueue(Q, new_puzzle, old_g+1, heuristicEvalFix(old_h, puzzle, new_puzzle, n));
    }
}

bool isEndState(State puzzle, int n)
{
    int correct_piece = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (puzzle[i][j] == 0) continue;
            else if (puzzle[i][j] != correct_piece++) return false;
        }
    }
    return true;
}

int heuristicEval(State puzzle, int n)
{
    // Find the sum of the manhattan distance each piece needs, in order to get to its correct position 
    int total_distance = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (puzzle[i][j] != 0)
            {
                SHORT_INT x = (puzzle[i][j]-1) / n;
                SHORT_INT y = (puzzle[i][j]-1) % n;
                total_distance += ABS(x,i) + ABS(y,j);
            }
        }
    }
    return total_distance;
}

/* From a puzzle to a new puzzle, the only thing that changes in the sum of the manhattan distance(md) 
of all pieces is the md of the previous empty space and the new empty space.
Fix the heuristic calculation by removing the md of the old puzzle's, now new empty space
and adding the md of the old empty space now occupied piece */
int heuristicEvalFix(int old_h, puzzlePointer old_puzzle, puzzlePointer new_puzzle, int n)
{
    SHORT_INT x1 = (old_puzzle->puzzle[new_puzzle->empty_space->x][new_puzzle->empty_space->y]-1) / n;
    SHORT_INT y1 = (old_puzzle->puzzle[new_puzzle->empty_space->x][new_puzzle->empty_space->y]-1) % n;

    SHORT_INT x2 = (new_puzzle->puzzle[old_puzzle->empty_space->x][old_puzzle->empty_space->y]-1) / n;
    SHORT_INT y2 = (new_puzzle->puzzle[old_puzzle->empty_space->x][old_puzzle->empty_space->y]-1) % n;

    int old_md = ABS(x1, new_puzzle->empty_space->x) + ABS(y1, new_puzzle->empty_space->y);
    int new_md = ABS(x2, old_puzzle->empty_space->x) + ABS(y2, old_puzzle->empty_space->y);

    return old_h-old_md+new_md;
}

// Functions needed in main
puzzlePointer createPuzzle(int n, puzzlePointer prev_puzzle)
{
    // Create the puzzle
    puzzlePointer new_puzzle = malloc(sizeof(puzzleState));
    if (new_puzzle == NULL) return NULL;  // allocation failure
    new_puzzle->puzzle = malloc(sizeof(SHORT_INT*) * n);
    if (new_puzzle->puzzle == NULL) return NULL;  // allocation failure
    for (int i = 0; i < n; i++)
    {
        new_puzzle->puzzle[i] = malloc(sizeof(SHORT_INT) * n);
        if (new_puzzle->puzzle[i] == NULL) return NULL;  // allocation failure
    }
    
    // Create the empty space
    new_puzzle->empty_space = malloc(sizeof(point));
    if (new_puzzle->empty_space == NULL) return NULL;

    // fill the contents of the puzzle
    new_puzzle->prev_puzzle = prev_puzzle;
    return new_puzzle;
}

bool readArray(puzzlePointer newPuz, int n)
{
    SHORT_INT num_of_empty_spaces = 0;
    newPuz->came_from = -1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            scanf("%hhu", &(newPuz->puzzle[i][j]));
            if (newPuz->puzzle[i][j] < 0 || newPuz->puzzle[i][j] > n*n-1) return false;
            else if (newPuz->puzzle[i][j] == 0)
            {
                num_of_empty_spaces++;
                newPuz->empty_space->x = i;
                newPuz->empty_space->y = j;
            }
            if (num_of_empty_spaces > 1) return false;  // more than one empty space found, error
        }
        if (num_of_empty_spaces > 1) return false;  // more than one empty space found, error
    
    if (num_of_empty_spaces != 1) return false;  // we need exactly 1 empty space
    return true;
}

void DestroyPuzzle(puzzlePointer A, int n)
{
    if (A == NULL) return;
    for (int i = 0; i < n; i++)
        free(A->puzzle[i]);
    
    free(A->puzzle);
    free(A->empty_space);
    free(A);
}

puzzlePointer copyPuzzle(puzzlePointer puzzle, int n)
{
    puzzlePointer new_puzzle = createPuzzle(n, puzzle);
    if (new_puzzle == NULL) return NULL;  // allocation failure
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            new_puzzle->puzzle[i][j] = puzzle->puzzle[i][j];
    
    return new_puzzle;
}