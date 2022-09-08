#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "../include/item.h"
#include "../include/SolvePuzzle.h"

// function_protypes
bool continue_playing();

int main(void)
{
    int n;
    bool continue_pl = true;
    puzzlePointer puzzle;

    while(continue_pl)
    {
        printf("Give the size of the puzzle: ");
        scanf("%d", &n);

        puzzle = createPuzzle(n, NULL);
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

        clock_t cur_time = clock();
        AstarSearch(puzzle, n);
        
        // calculate the time (in seconds it took for the puzzle to be solved)
        double time_elapsed = ((double)(clock() - cur_time))/CLOCKS_PER_SEC;
        printf("Solved in %.3f seconds\n", time_elapsed);

        continue_pl = continue_playing();
    }
    
    return 0;
}

bool continue_playing()
{
    getchar();
    char answer;
    printf("\nWant to continue? (y/n) ");
    scanf("%c", &answer);
    if (answer == 'n' || answer == 'N') return false;
    
    printf("\n");
    return true;
}
