To compile, just type:

```
prompt> make
```

See the highly primitive `Makefile` for details.

Then, run it:

````
prompt> ./virtual-addresses
```s
````



When run on a 64-bit Mac, we get the following output:
location of code : 0x1095afe50
location of heap : 0x1096008c0
location of stack: 0x7fff691aea64

From this, you can see that code comes first in the address space, then
the heap, and the stack is all the way at the other end of this large virtual
space. All of these addresses are virtual, and will be translated by the OS
and hardware in order to fetch values from their true physical locations.