/* 
  This program virtualizes Memory
  - It allocates some memory (line a1)
  - It prints the address of the allocated memory (line a2)
  - It puts the number zero into the first slot of the newly allocated memory (line a3)
  - Finally, it loops, delaying for a second and incrementing the value
    stored at the address held in p.

  Example usage:
  $ ./mem
  
  Output:
  (12345) address pointed to by p: 0x55f8c3e2d260
  (12345) p: 0
  (12345) p: 1
  (12345) p: 2
  (12345) p: 3
  ...

  Running many programs at once:
  $ ./mem & ./mem & 
  Output:
  (12346) address pointed to by p: 0x55f8c3e2d270
  (12347) address pointed to by p: 0x55f8c3e2d270
  (12346) p: 0
  (12347) p: 0
  (12347) p: 1
  (12346) p: 1
  
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


/*
We see from the example that each running
program has allocated memory at the same address (0x55f8c3e2d270) yet
they do not interfere with each other. Each program has its own private
memory, even though the addresses are the same. 

This is because the operating system, with help from the hardware,
virtualizes memory. Each process accesses its own private virtual address space
(sometimes just called its address space), which the OS somehow maps
onto the physical memory of the machine. The reality, is that physical memory is
a shared resource, managed by the operating system. 

A memory reference within
one running program does not affect the address space of other processes
(or the OS itself); as far as the running program is concerned, it has physical memory all to itself. 

*/