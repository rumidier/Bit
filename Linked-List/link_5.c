#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
  int data;
  struct _node *next;
} NODE;

NODE head = {0, &head};

void insert_data (NODE *cur, NODE *temp)
{
  temp->next = cur->next;
  cur->next = temp;
}

void data_dis (NODE *head)
{
  NODE *temp;
  system("clear");
  printf("[head]");

  //for (temp= head->next; temp !=0; temp = temp->next)
  for (temp = head->next; temp != head; temp=temp->next)
    printf("->[%d]", temp->data);

  getchar();
}

int
main (int argc,
      char *argv[])
{
  int i;
  NODE *s;
  NODE *temp;

  data_dis(&head);
  for (i=0; i<7; i++)
    {
      s = (NODE *)malloc (sizeof(NODE));
      s->data = i + 1;
      insert_data(&head, s);
      data_dis(&head);
    }

  temp = (NODE *)malloc(sizeof(NODE));
  temp->data = 8;
  for (s=head.next; s->data != 6; s=s->next);
  insert_data(s, temp);

  data_dis(&head);

  return 0;
}

