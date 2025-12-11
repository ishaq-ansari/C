/*
This program Virtualizes The CPU

- It takes a string as a command line argument.
- It call Spin(), a function that repeatedly checks the time and 
  returns the string that use passed in CLI once a second has passed.
- After each call to Spin(), it prints the input string to standard output.
- The program runs indefinitely in a loop.

Example usage:
$ ./cpu "Hello, World!"
Output:
Hello, World!
Hello, World!
Hello, World!
...

Running many programs at once:
$ ./cpu "Process 1" & ./cpu "Process 2" & ./cpu "Process 3" &
Output:
Process 1
Process 2
Process 3
Process 1
Process 2
Process 3
...

*/

// Note how we ran three processes at the same time, by using the '&' symbol. Doing so runs a job in the background in the 'zsh' shell

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
// #include "common.h"

void Spin(long iterations) {
    volatile long i;
    for (i = 0; i < iterations; i++) {
        // empty loop to burn CPU
    }
}

int main(int argc, char *argv[]) 
{
  if (argc != 2) {
      fprintf(stderr, "usage: cpu <string>\n");
      exit(1);
  }
  char *str = argv[1];

  while (1) {
      Spin(1);
      printf("%s\n", str);
}

  return 0;
}


/*
In example 2:
Even though we have only one processor, somehow all three of 
these programs seem to be running at the same time! 

This is because the operating system uses a technique called  time-sharing to give the illusion of parallelism.
The operating system, with some help from the hardware, creates the illusion that the system has a very large number of virtual CPUs.

Turning a single CPU (or a small set of them) into a seemingly infinite number of CPUs and thus allowing
many programs to seemingly run at once is what we call virtualizing the CPU
*/