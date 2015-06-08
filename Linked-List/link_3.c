#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
  int data;
  struct _node *next;
} NODE;

NODE head, tail;

void init (void) {
  head.next = &tail;
  tail.next = &head;
}

void insert_data (NODE *head, int data)
{
  NODE *temp;

  temp       = (NODE *) malloc (sizeof(NODE));
  temp->data = data;
  temp->next = head->next;
  head->next = temp;
}

void data_dis (NODE *head)
{
  NODE *temp;
  system("clear");
  printf("[head]");

  //for (temp= head->next; temp !=0; temp = temp->next)
  for (temp = head->next; temp != &tail; temp=temp->next)
    printf("->[%d]", temp->data);

  getchar();
}

int
main (int argc,
      char *argv[])
{
  int i;
  NODE *s;

  init();

  data_dis(&head);
  for (i=0; i<7; i++)
    {
      insert_data(&head, i+1);
      data_dis(&head);
    }

  for (s=head.next; s->data != 6; s=s->next);
  insert_data(s, 8);

  data_dis(&head);

  return 0;
}

