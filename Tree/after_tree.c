#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
  int data;
  struct _node *left;
  struct _node *right;
} NODE;

NODE *root;

typedef enum {LEFT, RIGHT} TYPE;

/*
void insert_data (int data, NODE *s, TYPE type)
{
  NODE *temp;
  temp = malloc (sizeof (NODE));
  temp->data = data;
  temp->left = temp->right = 0;

  if (root == 0)
    {
      root = temp;
      return;
    }

  if (type == LEFT)
    s->left = temp;
  else if ( type == RIGHT )
    s->right = temp;
}
*/
//binary input data
void insert_data (int data)
{
  NODE *temp, **p = &root;
  temp = malloc (sizeof(NODE));
  temp->data = data;
  temp->left = temp->right = 0;

  while (*p)
    {
      if ( (*p)->data > data)
        p = &(*p)->left;
      else if ( (*p)->data < data )
        p = &(*p)->right;
      else
        return;
    }
  *p = temp;
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
  indent_display (temp->right);
  printf("%*d\n", indent * 4, temp->data);
  indent_display(temp->left);
  --indent;
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

void _display ( NODE *temp, int (*a)[10], int *row, int *col )
{
  if (temp == 0)
    return;
  ++*row;
  _display(temp->left, a, row, col);
  a[*row][(*col)++] = temp->data;
  _display(temp->right, a, row, col);
  --*row;
}

void print (NODE *temp)
{
  int i,j;
  int array[10][10] = {{0, }, };
  int row = -1;
  int col = 0;

  _display(root, array, &row, &col);
  system("clear");

  for (i=0; i<3; i++)
    {
      for (j=0; j<10; j++)
        {
          if (array[i][j] == 0)
            {
              printf("%4c", ' ');
            }
          else {
            printf("%4d", array[i][j]);
          }
        }
      printf("\n");
    }

  getchar();
}

void __fill (NODE *temp, int *a, int *n)
{
  if (temp == 0)
    return;
  __fill (temp->left, a, n);
  a[(*n)++] = temp->data;
  __fill (temp->right, a, n);
}

NODE* __bal (int *a, int n)
{
  int mid = n/2;
  printf("[%d]\n", mid);
  if (n<1)
    return 0;
  NODE *temp;
  temp = malloc (sizeof(NODE));
  temp->data  = a[mid];
  temp->left  = __bal(a, mid);
  temp->right = __bal (a + mid + 1, n - mid - 1);

  return temp;
}

int
main (int argc,
      char *argv[])
{
  int i;
  int buff[7] = {5, 3, 4, 7, 6, 1, 2};

  for (i=0; i<7; i++)
    {
      insert_data(buff[i]);
  //    print(root);
    }

  int row = -1, col = 0;
//  __fill(root, &row, &col);
//  print(root);
  root = __bal(buff, 7);
  print(root);


  /* 오전 수업
  printf("--------------------\n");
  in_order (root);
  printf("--------------------\n");
  display (root);
  printf("--------------------\n");
  indent_display (root);
  printf("--------------------\n");
  display_2 (root);

  int (*arr)[10];
  arr = __display(root);

  for (i=0; i<3; i++)
    {
      for (j=0; j<10; j++)
        {
          if (arr[i][j] == 0)
            {
              printf("%4c", ' ');
            }
          else {
            printf("%4d", arr[i][j]);
          }
        }
      printf("\n");
    }
  puts("-------------------------------");
  */

  return 0;
}
