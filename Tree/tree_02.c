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
//int ( *__display (NODE *temp) )[10]
void __display(NODE *temp, int (*a)[10], int *row, int *col)
{
  if ( temp==0 )
    return;
  ++*row;
  __display( temp->left, a, row, col );
  a[*row][*col++] = temp->data;
  __display( temp->right,a,row,col );
  --*row;

  return;
}

void display ( NODE *temp )
{
  int i, j;
  int row = -1;
  int col = 0;
  int a[10][10] = {{0, }, };

  system("clear");
  __display(temp, a, &row, &col);

  for (i=0; i<10; i++)
    {
      for (j=0; j<10; j++)
        {
          if (a[i][j] !=  0)
            printf("%4d", a[i][j]);
          else
            printf("%4c", ' ');
        }
      printf("\n");
    }
  getchar();
}


int
main (int argc,
      char *argv[])
{
  insert_data (1, 0, LEFT);
  display (root);
  insert_data (2, root, LEFT);
  display (root);
  insert_data (3, root, RIGHT);
  display (root);
  insert_data (4, root->left, LEFT);
  display (root);
  insert_data (5, root->left, RIGHT);
  display (root);
  insert_data (6, root->right, LEFT);
  display (root);
  insert_data (7, root->right, RIGHT);
  display (root);

  return 0;
}
