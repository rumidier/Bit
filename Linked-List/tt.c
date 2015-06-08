#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
  int data;
  struct _node *next;
} NODE;

NODE *head = 0;

//void insert_data (int data)
void insert_data (NODE **head, int data)
{
  NODE *temp;
  temp = (NODE *) malloc (sizeof(NODE));
  temp->data = data;
  temp->next = *head;
  *head = temp;
}

//void display_2 (void) {
//  NODE *temp;
//  temp = (NODE *) malloc (sizeof(NODE));
//
//  if (head->next == NULL) {
//    exit(0);
//  }
//  temp= head->next;
//
//  while (1) {
//    if (temp != 0) {
//      printf("[%d]\n", head->data);
//      temp = head->next;
//    }
//    else {
//      break;
//    }
//  }
//}

void data_dis (NODE *head)
{
  NODE *temp;
  system("clear");
  printf("[head]");
  for (temp= head; temp !=0; temp = temp->next)
    printf("->[%d]", temp->data);

  getchar();
}

int
main (int argc,
      char *argv[])
{
  int i;
  NODE *rear=0;

  data_dis(head);
  for (i=0; i<7; i++)
    {
      insert_data(&head, i+1);
      data_dis(head);
    }
  data_dis(rear);
  for (i=7; i>0; i--)
    {
      insert_data(&rear, i);
      data_dis(rear);
    }
  //display_2();

  return 0;
}

