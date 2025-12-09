/* mem.c: A simple program that allocates memory and modifies it in an infinite loop.
 *
 * This program demonstrates basic memory allocation and manipulation in C.
 * It allocates an integer on the heap, initializes it to zero, and then
 * enters an infinite loop where it increments the integer and prints its value.
 *
 * Usage:
 *   Compile the program using a C compiler (e.g., gcc):
 *     gcc -o mem mem.c
 *
 *   Run the compiled program:
 *     ./mem
 *
 * Note:
 *   This program will run indefinitely until manually terminated (e.g., using Ctrl+C).
 *   It is intended for educational purposes to illustrate memory allocation and CPU usage.
 */

 



#include <unistd.h>    // for getpid()
#include <stdio.h>     // for printf()
#include <stdlib.h>    // for malloc(), exit()
#include <assert.h>


void Spin(long iterations) {
    volatile long i;
    for (i = 0; i < iterations; i++) {
        // empty loop to burn CPU
    }
}

int main(int argc, char *argv[]) 
{
  int *p = malloc(sizeof(int)); // a1
  assert(p != NULL);
  printf("(%d) address pointed to by p: %p\n", getpid(), p); // a2
  *p = 0;   // a3

  while (1) {
      Spin(1);             // burn CPU for a moment
      *p = *p + 1;         // increment the value
      printf("(%d) p: %d\n", getpid(), *p); // a4
  }

  return 0;
}
