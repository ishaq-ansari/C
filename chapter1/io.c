/*
This code demonstrates basic file I/O operations in C, including opening a file,
writing to it, and closing it. It uses assertions to ensure that each operation
is successful.

Usage:
    mkdir -p tmp
    gcc -o io io.c
    ./io
  
*/

#include <stdio.h>      // printf, fprintf, etc.
#include <unistd.h>     // write(), close()
#include <assert.h>     // assert()
#include <fcntl.h>      // open() and file flags
#include <sys/types.h>  // types like mode_t


int main(int argc, char *argv[]) {
    // Open a file for writing (create if it doesn't exist, truncate if it does)
    int fd = open("tmp/file", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
    assert(fd > -1); // Ensure the file was opened successfully

    // Write a string to the file
    int rc = write(fd, "hello world\n", 13);
    assert(rc == 13); // Ensure the correct number of bytes were written
  

    // Close the file descriptor
    int result = close(fd);
    assert(result > -1); // Ensure the file was closed successfully

    printf("File written and closed successfully.\n");
    return 0;
}



/*
The first, a call to open(), opens the file and creates it; the
second, write(), writes some data to the file; the third, close(), simply closes the file thus indicating the program won’t be writing any more
data to it. These system calls are routed to the part of the operating system called the file system, which then handles the requests and returns
some kind of error code to the user.

The file system has to do a fair bit of work:
first figuring out where on disk this new data will reside, and then keeping track of it in various structures the file system maintains. Doing so
requires issuing I/O requests to the underlying storage device, to either
read existing structures or update (write) them.

As anyone who has written a device driver8
knows, getting a device to do something on your
behalf is an intricate and detailed process. It requires a deep knowledge
of the low-level device interface and its exact semantics. Fortunately, the
OS provides a standard and simple way to access devices through its system calls. Thus, the OS is sometimes seen as a standard library

For
performance reasons, most file systems first delay such writes for a while,
hoping to batch them into larger groups. To handle the problems of system crashes during writes, most file systems incorporate some kind of
intricate write protocol, such as journaling or copy-on-write, carefully
ordering writes to disk to ensure that if a failure occurs during the write
sequence, the system can recover to reasonable state afterwards. To make
different common operations efficient, file systems employ many different data structures and access methods, from simple lists to complex btrees. 
*/