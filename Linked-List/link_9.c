#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
  void *data;
  struct _node *next;
  struct _node *prev;
} NODE;

typedef struct
{
  char name[20];
} SAWON;

NODE head = {0, &head, &head};

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
    //printf("<->[%s]", temp->data);
      s = (SAWON *)temp->data;
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
  SAWON s[5] = {"홍길동", "이순신", "유관순", "안중근", "박문수"};

  data_display(&head);
  for (i=0; i<5; i++)
    {
      temp = (NODE *)malloc(sizeof(NODE));
      temp->data = s+i;
      insert_back(&head, temp);
      data_display(&head);
    }

  return 0;
}
