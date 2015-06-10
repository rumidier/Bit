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

void _display ( NODE *temp, int (*a)[10], int *row, int *col )
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
  int array[10][10] = {{0, }, };
  int row = -1;
  int col = 0;

  system("clear");
  printf("\n");
  _display(root, array, &row, &col);

  for (i=0; i<5; i++)
    {
      for (j=0; j<10; j++)
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
  printf("node [%d]\n", node);

  if (key == node->data)
    {
      printf("return node [%d]\n", node);
      return node;
    }
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

#define max(a, b) (((a) > (b)) ? (a) : (b))
int get_height (NODE *node)
{
  int height = 0;
  if (node != NULL)
    height = 1 + max(get_height(node->left), get_height(node->right));
  return height;
}

int get_balance (NODE *node)
{
  if (node == NULL) return 0;
  return get_height(node->left) - get_height(node->right);
}


int
main (int argc,
      char *argv[])
{
  int rl[8] = {6,3,1,7,5,12,9,4};
  NODE *node = 0;

  int i;
  int height;
  int in;

  print(root);
  for (i = 0; i < 8; i++)
    {
      insert_data(rl[i]);
      print(root);
    }
  insert_data(14);
  print(root);

  while (1) {
    printf("input the node data(exit: -1): ");
    fflush(stdin);
    scanf("%d", &in);


    if (in == -1) break;
    printf("in : %d\n", in);
    printf("root: %d\n", root);
    NODE *babo;
    babo = search(root, in);
    printf("babo[%d]\n", babo);
//    height = get_height(node);
    height = get_balance(node);
//    printf("%d 높이는 %d\n", in, height);
    printf("%d 밸런스값: %d\n", in, height);
    getchar();
  }

  return 0;
}
