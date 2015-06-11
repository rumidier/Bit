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

void insert_data (int data)
{
  NODE *temp, **p = &root;
  temp = (NODE *)malloc (sizeof(NODE));
  temp->data = data;
  temp->left = 0;
  temp->right = 0;

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

void _display ( NODE *temp, int (*a)[12], int *row, int *col )
{
  if (temp == 0)
    return;
  (*row)++;
  _display(temp->left, a, row, col);
  a[*row][(*col)++] = temp->data;
  _display(temp->right, a, row, col);
  (*row)--;
}

void print (NODE *temp)
{
  int i,j;
  int array[12][12] = {{0, }, };
  int row = -1;
  int col = 0;

  system("clear");
  printf("\n");
  _display(root, array, &row, &col);

  for (i=0; i<12; i++)
    {
      for (j=0; j<12; j++)
        {
          if (array[i][j] == 0)
            {
              printf("%2c", ' ');
            }
          else {
            printf("%2d", array[i][j]);
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


NODE *search (NODE *node, int key)
{
  if (node == NULL) return NULL;
  printf("%d->", node->data);

  if (key == node->data)
    return node;
  else if (key < node->data)
    search (node->left, key);
  else
    search (node->right, key);
}

NODE* rotate_RR (NODE *parent)
{
  NODE *child = parent->right;
  parent->right = child->left;
  child->left = parent;
  return child;
}

NODE* rotate_LL (NODE *parent)
{
  NODE *child   = parent->left;
  parent->left  = child->right;
  child->right  = parent;
  return child;
}

NODE* rotate_LR (NODE *parent)
{
  NODE *child   = parent->left;
  parent->left  = rotate_RR(child);
  return rotate_LL(parent);
}

NODE* rotate_RL (NODE *parent)
{
  NODE *child   = parent->right;
  parent->right  = rotate_LL(child);
  return rotate_RR(parent);
}

int
main (int argc,
      char *argv[])
{
  int i;
  //int buff[] = {7, 3, 1, 6, 5, 12};

//  for (i=0; i<6; i++)
//    {
//      insert_data(buff[i]);
//    }
  //print(root);
  //indent_display (root);
  //root_return = search (root, 5);
  // print(root_return);

  //int rr[10] = {6, 3, 1, 5, 7, 11};
  //int rr[6]   = {20, 10, 40, 30, 50, 60};
  //int ll[5] = {7, 6, 3, 1, 12};
  //int ll[6] = {12, 7, 3, 2, 10, 20};
  //int lr[6] = {7, 3, 1, 6, 12, 5};
  //int lr[6] = {12, 7, 3, 10, 20, 8};
  int rl[7] = {6, 3, 1, 5, 7, 12, 9};
  //int lr[12] = {8, 3, 2, 1, 5, 4, 6, 7, 9, 10, 11, 12};

  int row = -1;
  int col = 0;
  //7
  for (i=0; i<7; i++)
  // 6
  //for (i=0; i<6; i++)
  // 5
  //for (i=0; i<5; i++)
  //for (i=0; i<12; i++)
  //  {
//      insert_data(rr[i]);
//      insert_data(ll[i]);
 //     insert_data(lr[i]);
      insert_data(rl[i]);
   // }
//  _display (root, rr, &row, &col);
//
//  RR Rotation
//  parent 의 좌측을 잡아야 한다
//  print(root);
//  insert_data(12);
//  print(root);
//
//  NODE *root_return;
//  root_return        = search(root, 6);
//  root_return->right = rotate_RR(root_return->right);
//  print(root);
//  print(root);
//
//  NODE *root_return;
//  root_return        = search(root, 20);
//  root = rotate_RR(root_return);
//  print(root);
//
//
//
//
//
//  LL Rotation
//  parent의 좌측을 잡아야한다.
//  print(root);
//  NODE *root_return;
//  root_return        = search(root, 7);
//  root_return->left = rotate_LL(root_return->left);
//  print(root);

//  print(root);
//  NODE *root_return;
//  root_return        = search(root, 12);
//  root = rotate_LL(root_return);
//  print(root);
//
//
//
//
  //LR Rotation //  int lr[6] = {7, 3, 1, 6, 12, 5};
//  print(root);
//  NODE *root_return;
//  root_return = search(root, 7);
//  root = rotate_LR(root_return);
//  print(root);
//
//
//  LR Rotation //int lr[6] = {12, 7, 3, 10, 20, 8};
//  print(root);
//  NODE *root_return;
//  root_return = search(root, 12);
//  root = rotate_LR(root_return);
//  print(root);
//
  //print(root);
//
  ///RL Rotation //int rl[7] = {6, 3, 1, 5, 7, 12, 9};
  print(root);
  NODE *root_return;
  root_return = search(root, 6);
  root_return->right = rotate_RL(root_return->right);
  print(root);

  return 0;
}
