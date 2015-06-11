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

typedef struct {
	int sid;
	struct rb_node tree;
} SAWON;

#define offsetof(TYPE, MEMBER) ((size_t) & ((TYPE *)0)->MEMBER)
#define rb_entry (ptr, type, member) container_of(ptr, type, member)
#define container_of(ptr,  type, member) ({ \
			const typeof ( ((type*)0)->member) * __mptr = (ptr); \
			(type *)((char *) __mptr - offsetof(type, member));})
#define rb_parent(r) ((struct rb_node *)((r)->rb_parent_color & ~3))

void rb_link_node(struct rb_node * node, struct rb_node  * parent, struct rb_node **rb_link)
{
	node->rb_parent_color = (unsigned long) parent;
	node->rb_left = node->rb_right = NULL;
	*rb_link = node;
}

SAWON* insert_data(struct rb_root *root, int sid, struct rb_node *node)
{
	struct rb_node **p = &root->rb_node;
	struct rb_node *parent = NULL;
	SAWON *s;

	while (*p)
	{
		parent = *p;
		s = rb_entry(parent, SAWON, tree);

		if (sid < s->sid)
			p = &(*p)->rb_left;
		else if (sid > s->sid)
			p = &(*p)->rb_right;
		else
			return s;
	}

	rb_link_node(node, parent, p);
	return NULL;
}


void display(struct rb_root *temp)
{
	int i, j;
	int row = -1;
	int col = 0;
	int a[10][10] = {0, };
	system("clear");
	__display(root->rb_node, a, &row, &col);

	for (i=0; i<10; i++)
	{
		for (j=0; j<10; j++)
		{
			if (a[i][j] != 0)
				printf("%4d", a[i][j]);
			else
				printf("%4c", ' ');
		}
		printf("\n");
	}
	getchar();
}

void __display(struct rb_node *temp, int (*a)[10], int *row, int *col)
{
	if  (temp == 0)
		return;
	++*row;
	__display(temp->rb_left, a, row, col);
	a[*row][(*col)++] = rb_entry(temp, SAWON, tree->sid);
	__display(temp->rb_right, a, row, col);
	--*row;

	return;
}

void __rb_rotate_left (struct rb_node *node, struct tb_root *root)
{
  struct rb_node *right = node->rb_right;
  struct rb_node *parent = rb_parent(node);

  if ((node->rb_right = right->rb_left))
    rb_set_parent(right->rb_left, node);
  right->rb_left = node;

  if (parent)
    {
      if (node == parent->rb_left)
        parent->rb_left = right;
      else
        parent->rb_right = right;
    }
  else
    root->rb_node = right;

  rb_set_parent(node, right);
}

int
main (int argc,
		char *argv[])
{
	struct rb_root root = {0, };
	SAWON s[7];
	//int a[7] = {4, 2, 6, 1, 3, 5, 7};
	int a[7] = {1, 3, 7, 4};
	int i;

	display(&root);
	for (i=0; i<4; i++)
	{
		s[i].sid = a[i];
		insert_data(&root, a[i], &s[i].tree);
		display(&root);
	}

	__rb_rotate_left(rootrb_node);
	display(&root);

	return 0;
}
