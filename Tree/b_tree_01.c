#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
  int data;
  struct _node *left;
  struct _node *right;
} NODE;

NODE *root;

typedef enum { LEFT, RIGHT } TYPE;

void insert_data (int data) {
  NODE *temp;
  NODE *p = root;
  NODE *prev;
  temp = malloc(sizeof(NODE));
  temp->data = data;
  temp->left = temp->right = 0;

  if (root == 0)
    {
      root = temp;
      return;
    }

  while (p) {
    prev = p;

    if (p->data > data)
      p = p->left;
    else if (p->data < data)
      p = p->right;
    else
      return;
  }
  if (prev->data > data)
    prev->left = temp;
  else
    prev->right = temp;
}

int
main (int argc,
      char *argv[])
{
  int a[] = {4, 2, 1, 3, 6, 5, 7};
  int i;

  //display(root);

  for(i=0; i<7; i++)
    {
      insert_data(a[i]);
      //display(root);
    }
}
