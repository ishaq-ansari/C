#include <stdio.h>

void func() {
  int x = 3000; // thanks, Perry.
  x = x + 3; // line of code we are interested in
}

int main() {
  func();
  return 0;
}


/*
to test this: first compile it with:
gcc -g chapter5/test.c -o chapter5/test

then run it with:
otool otool -tv test
*/