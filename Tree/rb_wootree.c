#if 1
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

typedef struct
{
	int sid;
	struct rb_node tree;
}SAWON;

#define offsetof(TYPE, MEMBER)	((size_t) & ((TYPE*)0)->MEMBER)

#define container_of(ptr, type, member)	({	\
			const typeof(	((type*)0)->member) *__mptr = (ptr); \
			(type*)(	(char *)__mptr - offsetof(type, member)); })

#define rb_entry(ptr, type, member)	container_of(ptr, type, member)
#define rb_parent(r)	((struct rb_node*)((r)->rb_parent_color & ~3))
#define rb_color(r)		((r)->rb_parent_color & 1)
#define rb_is_red(r)	(!rb_color(r))
#define rb_is_black(r)	rb_color(r)
#define rb_set_red(r)	do { (r)->rb_parent_color &= ~1; } while (0)
#define rb_set_black(r) do { (r)->rb_parent_color |= 1; }  while (0)

void rb_link_node(struct rb_node * node, struct rb_node * parent, struct rb_node **rb_link)
{
	node->rb_parent_color = (unsigned long) parent;
	node->rb_left = node->rb_right = NULL;
	*rb_link = node;

}
void rb_set_parent(struct rb_node *rb, struct rb_node *p)
{
	rb->rb_parent_color = (rb->rb_parent_color & 3) | (unsigned long)p;
}
void __rb_rotate_left(struct rb_node *node, struct rb_root *root)
{
	struct rb_node *right = node->rb_right;
	struct rb_node *parent = rb_parent(node);

	if((node->rb_right = right->rb_left))
		rb_set_parent(right->rb_left, node);
	right->rb_left = node;

	rb_set_parent(right, parent);

	if(parent)
	{
		if(node == parent->rb_left)
			parent->rb_left = right;
		else
			parent->rb_right = right;
	}
	else
		root->rb_node = right;
	rb_set_parent(node,right);
}
void __rb_rotate_right(struct rb_node *node, struct rb_root *root)
{
	struct rb_node *left = node->rb_left;
	struct rb_node *parent = rb_parent(node);

	if((node->rb_left = left->rb_right))
		rb_set_parent(left->rb_right, node);
	left->rb_right = node;

	rb_set_parent(left, parent);

	if(parent)
	{
		if(node == parent->rb_right)
			parent->rb_right = left;
		else
			parent->rb_left = left;
	}
	else
		root->rb_node = left;
	rb_set_parent(node,left);
}
void rb_insert_color(struct rb_node *node, struct rb_root *root)
{
	struct rb_node *parent, *gparent;

	rb_set_black(root->rb_node);
	while((parent = rb_parent(node)) && rb_is_red(parent))
	{
		 gparent = rb_parent(parent);
		 if(parent == gparent->rb_left)
		 {
			 {
				register struct rb_node *uncle = gparent->rb_right;
				if(uncle && rb_is_red(uncle))
				{
					rb_set_black(uncle);
					rb_set_black(parent);
					rb_set_red(gparent);
					node = gparent;
					continue;
				}
			}
			if(parent->rb_right == node)
			{
				register struct rb_node *tmp;
				__rb_rotate_left(parent, root);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			rb_set_black(parent);
			rb_set_red(gparent);
			__rb_rotate_right(gparent, root);
		 }
		else
		{
			{
				register struct rb_node *uncle = gparent->rb_left;
				if(uncle && rb_is_red(uncle))
				{
					rb_set_black(uncle);
					rb_set_black(parent);
					rb_set_red(gparent);
					node = gparent;
					continue;
				}
			}
			if(parent->rb_left == node)
			{
				register struct rb_node *tmp;
				__rb_rotate_right(parent, root);
				tmp = parent;
				parent = node;
				node = tmp;
			}
			rb_set_black(parent);
			rb_set_red(gparent);
			__rb_rotate_left(gparent, root);
		}
	}
	rb_set_black(root->rb_node);
}
//---------------------------------------------------------------------
SAWON* insert_data(struct rb_root *root, int sid, struct rb_node *node)
{
	struct rb_node **p = &root->rb_node;
	struct rb_node * parent = NULL;
	SAWON *s;

	while(*p)
	{
		parent = *p;
		s = rb_entry(parent, SAWON, tree);

		if(sid < s->sid)
			p = &(*p)->rb_left;
		else if(sid > s->sid)
			p = &(*p)->rb_right;
		else
			return s;
	}
	rb_link_node(node, parent, p);
	rb_insert_color(node, root);
	return NULL;
}
void _display(struct rb_node *temp, int (*a)[10], int *row, int *col)
{
	if(temp == 0)
		return;
	(*row)++;
	_display(temp->rb_left, a, row,col);
	a[*row][(*col)++] = rb_entry(temp, SAWON,tree)->sid;
	_display(temp->rb_right, a, row, col);
	(*row)--;
}
void display(struct rb_root * root)
{
	int i, j;
	int a[10][10] = {{0,},};
	int row = -1;
	int col = 0;
	system("clear");
	_display(root->rb_node, a, &row, &col);
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			if(a[i][j] == 0)
				printf("%4c", ' ');
			else
				printf("%4d", a[i][j]);
		}
		printf("\n\n");
	}
	getchar();
}

int main()
{
	struct rb_root root = {0,};
	SAWON s[8];
//	int a[4] = {1,3,7};
	int a[8] = {1,2,3,4,5,6,7,8};
	int i;

	display(&root);
	for(i=0;i<8;i++)
	{
		s[i].sid = a[i];
		insert_data(&root, a[i], &s[i].tree);

		display(&root);
	}
//	__rb_rotate_left(root.rb_node, &root);
//	__rb_rotate_right(root.rb_node, &root);
	
	display(&root);
	return 0;
}
#endif
