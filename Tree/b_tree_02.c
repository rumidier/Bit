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
  NODE *temp, **p = &root;
  temp = malloc ( sizeof(NODE) );
  temp->data = data;
  temp->left = temp->right = 0;

  while (*p)
    {
      if ( (*p)->data > data )
        p = &(*p)->left;
      else if ( (*p)->data < data )
        p = &(*p)->right;
      else
        return;
    }
  *p = temp;
}

void display (NODE *data) {

  static int indent = -1;
  if ( data == 0)
    return;

  ++indent;
  display (data->left);
  printf("%*d\n", indent * 4, data->data);
  display(data->right);
  --indent;
}

void __fill ( NODE *temp, int *a, int *n)
{
  if (temp == 0)
    return;
  __fill(temp->left, a, n);
  a[(*n)++] = temp->data;
  __fill(temp->right, a, n);
}

NODE* __bal (int *a, int n)
{
  int mid = n/2;
  NODE *temp;
  temp = malloc (sizeof(NODE));

  if (n < 1)
    return 0;

  temp->data = a[mid];
  temp->left = __bal(a, mid);
  temp->right = __bal(a + mid + 1, n - mid - 1);

  return temp;
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

int
main (int argc,
      char *argv[])
{
  NODE * node = 0;
  int i;
  int a[] = {6,3,1,5,7,11};
  display(root);

  display(root);

  int num_1 = 0, num_2 = 0;
  for(i=0; i<7; i++)
    {
      insert_data(a[i]);
    }
  //__fill (root, &num_1, &num_2);
  root = __bal (a, 7);
  display(root);
}
