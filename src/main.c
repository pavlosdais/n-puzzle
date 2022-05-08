#include <stdio.h>
#include <stdlib.h>
#include "../include/item.h"
#include "../include/SolvePuzzle.h"

int main(void)
{
    int n;
    printf("Give the size of the puzzle: ");
    scanf("%d", &n);

    puzzlePointer puzzle = createPuzzle(n, NULL);
    if (puzzle == NULL)   // allocation failure
    {
        printf("Error! Can not allocate enough memory, exiting..");
        return 1;
    }

    // save the puzzle
    printf("Give the puzzle: (0 for empty space)\n");
    if(!readArray(puzzle, n))
    {
        printf("Wrong format of puzzle! Exiting..\n");
        DestroyPuzzle(puzzle, n);
        return 1;
    }

    AstarSearch(puzzle, n);
    return 0;
}