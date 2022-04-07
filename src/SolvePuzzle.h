#include <stdbool.h>
#include "item.h"

typedef struct puzzleState puzzleState;
typedef puzzleState* puzzlePointer;

void AstarSearch(puzzlePointer puzzle, int n);
puzzlePointer createPuzzle(int n, puzzlePointer prev_puzzle);
bool readArray(puzzlePointer newPuz, int n);
void DestroyPuzzle(puzzlePointer A, int n);