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

void display_2 ( NODE *temp )
{
  int i;
  static int indent = -1;
  if (temp == 0)
    return;
  ++indent;
  display_2 (temp->right);
  for (i=0; i< indent; i++)
    printf("%4c", ' ');
  printf("%d\n", temp->data);
  display_2 (temp->left);
  --indent;
}

void indent_display ( NODE *temp )
{
  static int indent = -1;
  if (temp == 0)
    return;
  ++indent;
  indent_display (temp->right);
  printf("%*d\n", indent * 4, temp->data);
  indent_display(temp->left);
  --indent;
}

int ( *__display (NODE *temp) )[10]
{
  static int a[10][10] = {{0,}, };
  static int col=0;
  static int row = -1;
  if ( temp==0 )
    return a;
  ++row;
  __display( temp->left );
  a[row][col++] = temp->data;
  __display( temp->right );
  --row;

  return a;
}

void __display2 (NODE *temp, int (*b)[10], int *row, int *col)
{
  if (temp == 0)
    return;
  ++*row;
  __display2(temp->left, b, row, col);
  b[*row][(*col)++] = temp->data;
  __display2(temp->right, b, row, col);
  --*row;
}

int
main (int argc,
      char *argv[])
{
  int (*arr)[10];
  int brr[10][10] = {{0,}, };
  int i,j;

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
  printf("--------------------\n");
  display_2 (root);
  printf("--------------------\n");
  arr = __display(root);

  for (i=0; i<3; i++)
    {
      for (j=0; j<10; j++)
        {
          if (arr[i][j] == 0)
            {
              printf("%c", ' ');
            }
          else {
            printf("%d", arr[i][j]);
          }
        }
      printf("\n");
    }

  int num_01 = -1;
  int num_02 = 0;
  __display2(root, brr, &num_01, &num_02);
  printf("--------------------\n");

  for (i=0; i<3; i++)
    {
      for (j=0; j<10; j++)
        {
          if (brr[i][j] == 0)
            {
              printf("%c", ' ');
            }
          else {
            printf("%d", brr[i][j]);
          }
        }

      printf("\n");
    }

  return 0;
}
