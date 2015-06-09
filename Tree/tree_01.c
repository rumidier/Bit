#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
  int data;
  struct _node *left;
  struct _node *right;
} NODE;

NODE *root;

typedef enum {LEFT, RIGHT } TYPE;
void insert_data ( int data, NODE *s, TYPE type )
{
  NODE *temp;
  temp = malloc (sizeof(NODE));
  temp->data = data;
  temp->left = temp->right = 0;

  if (root == 0)
    {
      root = temp;
      return;
    }

  if (type == LEFT)
    s->left = temp;
  else if (type == RIGHT)
    s->right = temp;
}

void in_order (NODE *temp)
{
  if (temp == 0)
    return;

  in_order (temp->left);
  printf("%d\n", temp->data);
  in_order(temp->right);
}

void display ( NODE *temp )
{
  if (temp == 0)
    return;
  display (temp->right);
  printf("%d\n", temp->data);
  display(temp->left);
}

void indent_display ( NODE *temp )
{
  static int indent = -1;
  if (temp == 0)
    return;
  ++indent;
  display (temp->right);
  printf("%*d\n", indent * 4, temp->data);
  display(temp->left);
  --indent;
}

int
main (int argc,
      char *argv[])
{
  insert_data (1, 0, LEFT);
  insert_data (2, root, LEFT);
  insert_data (3, root, RIGHT);
  insert_data (4, root->left, LEFT);
  insert_data (5, root->left, RIGHT);
  insert_data (6, root->right, LEFT);
  insert_data (7, root->right, RIGHT);
  in_order (root);
  printf("--------------------\n");
  display (root);
  printf("--------------------\n");
  indent_display (root);

  return 0;
}
