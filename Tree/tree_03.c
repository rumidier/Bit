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

void insert_data ( int data )
{
  NODE *temp, **p = &root;

  temp       = (NODE*)malloc(sizeof(NODE));
  temp->data = data;
  temp->left = temp->right = 0;

  while (*p)
    {
      if ((*p)->data < data)
        p = &(*p)->right;
      else if ((*p)->data > data)
        p = &(*p)->left;
      else
        return;
    }

  *p = temp;
}
//int ( *__display (NODE *temp) )[10]
//void __display(NODE *temp, int (*a)[10], int *row, int *col)
//{
//  if ( temp==0 )
//    return;
//  ++*row;
//  __display( temp->left, a, row, col );
//  a[*row][*col++] = temp->data;
//  __display( temp->right,a,row,col );
//  --*row;
//
//  return;
//}

//void display ( NODE *temp )
//{
//  int i, j;
//  int row = -1;
//  int col = 0;
//  int a[10][10] = {{0, }, };
//
//  system("clear");
//  __display(temp, a, &row, &col);
//
//  for (i=0; i<10; i++)
//    {
//      for (j=0; j<10; j++)
//        {
//          if (a[i][j] !=  0)
//            printf("%4d", a[i][j]);
//          else
//            printf("%4c", ' ');
//        }
//      printf("\n");
//    }
//  getchar();
//}

NODE *search (NODE *node, int key)
{
  if (node == NULL) return NULL;
  printf("%d->", node->data);
  if (key == node->data)
    return node;
  else if (key < node->data)
    search(node->left, key);
  else
    search(node->right, key);

  return node;
}

NODE * rotate_RR (NODE *parent)
{
  NODE *child = parent->right;
  parent->right = child->left;
  child->left = parent;
  return child;
}

NODE * rotate_LL (NODE *parent)
{
  NODE *child = parent->left;
  parent->left = child->right;
  child->right = parent;
  return child;
}

NODE *rotate_LR (NODE *parent)
{
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

void _display (NODE *temp, int (*b)[10], int *row, int *col)
{
  if (temp == 0)
    return;
  ++*row;
  _display(temp->left, b, row, col);
  b[*row][(*col)++] = temp->data;
  _display(temp->right, b, row, col);
  --*row;
}

int
main (int argc,
      char *argv[])
{
  NODE *node = 0;
  int i;
  /*
  int a[] = {6,3,1,5,7,11};
  display(root);

  for (i=0; i<6; i++)
    {
      insert_data(a[i]);
      display(root);
    }
  insert_data(12);
  display(root);

  printf("RR rotation \n");
  getchar();
  node = search(root, 6);
  node->right = rotate_RR(node->right);
  */
  //display(root);
  int arry[10][10] = {{0, }, };
  int r = -1, c = 0;
  int a[] = {4,2,6,1,3,5,7};

  _display (root, arry, &r, &c);
  for (i=0; i<10; i++)
    {
      insert_data(a[i]);
    }
  _display (root, arry, &r, &c);
  display_2(root);
//  printf("LL rotation test\n");
//  getchar();
//  node = search(root, 7);
//  node->left = rotate_LL(node->left);
//  __display (root, arry, &r, &c);
//  printf("LR rotaion test\n");
//  getchar();
//  node = search(root, 7);
//  root =rotate_LR(node);
//  display(root);

  return 0;
}
