/*
This program demonstrates concurrency.

- each thread starts running in a routine called worker(), in which it simply increments a
  shared counter in a loop for 'loops' number of times.
- if loops = 1000, we would expect the final value of counter to be 2000,
  since there are two threads each incrementing it 1000 times.
- however, due to race conditions, the final value of counter is often less than 2000. We easily see this when loops is large, e.g., 10000000.

Usage:
  $ gcc -o threads threads.c -Wall -pthread
  $ ./threads 10000000
  Output:
  Initial value : 0
  Final value: 17345678   <-- likely less than 20000000

Note: -pthread is required in compile to link with the pthread library.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

volatile int counter = 0;
int loops;

void *worker(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        counter++;
    }
    return NULL;
}

int main (int argc, char *argv[]) {
    if (argc != 2) {
      fprintf(stderr, "usage: threads <value>\n");
      exit(1);
    }
    loops = atoi(argv[1]);

    pthread_t p1, p2;
    printf("Initial value : %d\n", counter);

    pthread_create(&p1, NULL, worker, NULL);
    pthread_create(&p2, NULL, worker, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf("Final value: %d\n", counter);
    return 0;
}

/*
the reason for these odd and unusual outcomes relate
to how instructions are executed, which is one at a time.

it takes three instructions: one to load the value of the counter from memory into a register, one to increment it, and one to store it back into memory. Because these three instructions do not execute atomically (all at
once), strange things can happen
*/