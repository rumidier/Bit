#include <stdio.h>
#include <stdlib.h>
struct rb_node
{
  unsigned long rb_parent_color;
  struct rb_node *rb_right;
  struct rb_node *rb_left;
};

struct rb_root
{
  struct rb_node *rb_node;
};

typedef struct _sawon
{
  int sid;
  struct rb_node tree;
} SAWON;

typedef struct _info {
  int sid;
  int color;
} INFO;

SAWON *pim;

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#define container_of(ptr, type, member) ({ \
                                         const typeof( ((type *)0)->member) *__mptr = (ptr); \
                                         (type *)( (char *) __mptr - offsetof(type, member));})
#define rb_entry(ptr, type, member) container_of(ptr, type, member)

/*
 offsetof (TYPE, MEMBER)
 TYPE = SAWON
 MEMBER = tree
 ((size_t) &((SAWON *)0)->tree)
 자료형의 크기를 구하므로 64비트 크기는 8

 const typeof ( ((type *)0)->member) *__mptr = (ptr);
 const struct rb_node *__mptr = root_node;
 (SAWON *)( ( (char *) __mptr - 8))
*/

void __display (struct rb_node *temp, INFO(*depot)[10], int *row, int *col)
{
  if (temp == 0)
    return;
  ++*row;
  __display(temp->rb_left, depot, row, col);
  depot[*row][(*col)].color = 1;
  depot[*row][(*col)++].sid = rb_entry(temp, SAWON, tree)->sid;
  __display(temp->rb_right, depot, row, col);
}

void display(struct rb_root *root)
{
  int i, j;
  int row = -1;
  int col =  0;
  INFO depot[10][10] = {{}, };
  
  system("clear");
  __display(root->rb_node, depot, &row, &col);

  for (i=0; i<10; i++)
    {
      for (j=0; j<10; j++)
        {
          if(depot[i][j].sid == 0)
            printf("%3c", ' ');
          else
            {
              if (depot[i][j].color == 1)
                printf("[%2d]", depot[i][j].sid);
              else
                printf("<%2d>", depot[i][j].sid);
            }
        }
      printf("\n");
    }
  getchar();
}

SAWON *insert_data (struct rb_root *header, int sid, struct rb_node *node)
{
  struct rb_node **root  = &header->rb_node;
  struct rb_node *parent = NULL;
  SAWON *pim;

  while(*root)
    {
      parent = *root;
      pim    = rb_entry(parent, SAWON, tree); //구조체의 0번지 주소값을 가져옴 
      printf("debug pid - [%d]\n", pim->sid);

      if (sid < pim->sid)
        {
          printf("sid++ : %d\n", pim->sid);
          root = &(*root)->rb_left;
        }
      else if (sid > pim->sid)
        {
          printf("sid-- : %d\n", pim->sid);
          root = &(*root)->rb_right;
        }
      else
        return pim;
    }
  node->rb_left = node->rb_right = NULL;
  *root = node;

  return NULL;
}

int sawon_count = 1;

int
main (int argc,
      char *argv[])
{
  int i;
  int datas[20] = { 93, 108, 60, 24, 46, 128, 197, 38, 173, 16, 95, 135, 137, 196, 153, 47, 88, 101, 178, 110 };
  struct rb_root header = {0, };

  //display(&root);
  for (i=0; i<20; i++)
    {
      pim = (SAWON *)realloc(pim, (sawon_count + 1) * sizeof(SAWON));
      sawon_count++;
      pim[i].sid = datas[i];
      printf("addr : %p\n", header.rb_node);
      insert_data(&header, datas[i], &pim[i].tree);
      //display(&root);
    }
  //display(&root);

  return 0;
}
