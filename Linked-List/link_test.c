#include <stdio.h>
#include <stdlib.h>

struct _foobar {
  unsigned int foo;
  char bar;
  char boo;
} Foobar;

int
main (int argc,
      char *argv[])
{
  struct _foobar tmp;
  printf("address of &tmp is = %p\n\n", &tmp);
  printf("address of tmp->foo = %p \t offset of tmp->foo %lu\n", &tmp.foo,
         (unsigned long) &((struct _foobar *)0)->foo);
  printf("address of tmp->bar = %p \t offset of tmp->bar %lu\n", &tmp.bar,
         (unsigned long) &((struct _foobar *)0)->bar);
  printf("address of tmp->bar = %p \t offset of tmp->boo %lu\n", &tmp.boo,
         (unsigned long) &((struct _foobar *)0)->boo);

  printf("computed address of &tmp using: \n");
  printf("\taddress and offset of tmp->foo = %p\n", (struct _foobar *)(((char *)&tmp.foo) - ((unsigned long) &((struct _foobar *)0)->foo)));

  printf("\taddress and offset of tmp->bar = %p\n", (struct _foobar *)(((char *)&tmp.bar) - ((unsigned long) &((struct _foobar *)0)->bar)));
  printf("\taddress and offset of tmp->boo = %p\n", (struct _foobar *)(((char *)&tmp.boo) - ((unsigned long) &((struct _foobar *)0)->boo)));
  return 0;
}
