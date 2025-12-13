
// this reqeuests memory on the stack

void func() {
  int x; // declares an integer on the stack
  ...
  }


// this requests memory on the heap
void func() {
  int *x = malloc(sizeof(int)); // allocates an integer on the heap
  ...
  free(x); // frees the allocated memory
  }

//declaration of said pointer (int *x)
//allocation of memory for an integer (malloc(sizeof(int)))
// the routine returns the address of such an integer (upon success, or NULL on failure