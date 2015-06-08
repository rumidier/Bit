#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
  struct _node *next;
  struct _node *prev;
} NODE;

typedef struct
{
  char name[20];
  NODE list;
} SAWON;

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *) 0)->MEMBER)
#define list_entry(ptr, type, member) \
  ((type *) ((char *)ptr - (unsigned long) &((type *)0)->member))

#define container_of(ptr, type, member) ({ \

const typeof( ((type *)0)->member ) *__mptr = (ptr); \

(type *)(( char *)__mptr - offsetof(type, member)); })

//s = (SAWON *)((char *)temp - (unsigned long) &((SAWON *)0)->list);

void insert_data (NODE *hd, NODE *temp)
{
  temp->next       = hd->next;
  hd->next         = temp;
  temp->prev       = hd;
  temp->next->prev = temp;
}

void __insert_data (NODE *prev, NODE *next, NODE *temp)
{
  temp->next = next;
  prev->next = temp;
  temp->prev = prev;
  next->prev = temp;
}

void insert_front (NODE *head, NODE *temp)
{
  __insert_data(head, head->next, temp);
}

void insert_back (NODE *head, NODE *temp)
{
  __insert_data(head->prev, head, temp);
}

void data_display (NODE *hd)
{
  NODE *temp;
  SAWON *s;
  system("clear");
  printf("[head]");
  for (temp = hd->next; temp != hd; temp = temp->next)
    {
      //s = (SAWON *)((char *)temp - (sizeof(SAWON)-sizeof(NODE)));
      //s = (SAWON *)((char *)temp - (unsigned long) &((SAWON *)0)->list);
      s = container_of(temp,SAWON,list);
      printf("<->[%s]", s->name);
    }
  printf("<->[head]");
  getchar();
}

int
main (int argc,
      char *argv[])
{
  int i;
  NODE *temp;
  SAWON s[5] = {{"홍길동",}, {"이순신",}, {"유관순",}, {"안중근",}, {"박문수"}};

  NODE head = {&head, &head};
  data_display(&head);
  for (i=0; i<5; i++)
    {
      insert_back(&head, &s[i].list);
      data_display(&head);
    }

  return 0;
}
