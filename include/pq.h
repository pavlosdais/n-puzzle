#include <stdbool.h>

// heap's minimum starting size
#define MIN_SIZE 4000

typedef void* Pointer;

typedef struct pq* PQueue;

// Pointer to function that compares 2 elements a and b and returns:
// < 0  if a < b
//   0  if a and b are equal
// > 0  if a > b
typedef int (*CompareFunc)(Pointer a, Pointer b);

// Pointer to function that destroys an element value
typedef void (*DestroyFunc)(Pointer value, int n);

// initialize priority queue
void pq_init(PQueue* PQ, CompareFunc compare, DestroyFunc destroy);

// return the size of the priority queue
unsigned int pq_size(PQueue PQ);

// insert value at the priority queue
void pq_insert(PQueue PQ, Pointer value);

// return the element with the highest priority as given by the compare function
// or NULL if it's empty
// it's important to note that once removed, the element is not destroyed by the
// the destroy function (pq_destroy)
Pointer pq_remove(PQueue PQ);

// destroy memory used by the priority queue
void pq_destroy(PQueue PQ, int n);
