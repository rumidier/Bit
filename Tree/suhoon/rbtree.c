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
#define RB_RED      0
#define RB_BLACK    1
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define container_of(ptr,type,member)  ({  \
                                        const typeof(  ((type *)0)->member) *__mptr = (ptr); \
                                        (type *)( (char *) __mptr - offsetof(type, member));})

#define rb_entry(ptr, type, member)  container_of(ptr, type, member)


#define rb_parent(r)   ((struct rb_node *)((r)->rb_parent_color & ~3))//컬러비트를 초기화
#define rb_color(r)   ((r)->rb_parent_color & 1)//참이면 블랙
#define rb_is_red(r)  (!rb_color(r))//참이면 레드
#define rb_set_red(r)   do {(r)->rb_parent_color &= ~1;} while(0)//레드로 셋
#define rb_set_black(r) do { (r)->rb_parent_color |= 1;} while(0)//블랙으로 셋

void rb_set_parent(struct rb_node *rb, struct rb_node *p)
{
  rb->rb_parent_color = (rb->rb_parent_color & 3) | (unsigned long)p;
}
//첫번째인자 SAWON구조체의 노드
//두번째인자 부모노드
//세번째인자 p 부모주소를 받을 더블포인터
//이 함수는 p에다가 SAWON구조체를 넣어주는 함수임.
//이함수를 실행하면 SAWON의 노드가 단말노드로서 트리에 붙음.
//루트가 없을시 루트로 넣어줌
void rb_link_node(struct rb_node * node, struct rb_node * parent, struct rb_node **rb_link)
{
  node->rb_parent_color = (unsigned long) parent;
  node->rb_left = node->rb_right = NULL;//SAWON구조체의 노드에 널값을 세팅
  *rb_link = node;//노드를 트리에 붙이는 코드
  //rb_link는 단말노드의 왼쪽 또는 오른쪽 포인터의 주소를 가지고 있음.
}

static void __rb_rotate_right(struct rb_node *node, struct rb_root *root)
{
  struct rb_node *left = node->rb_left;
  struct rb_node *parent = rb_parent(node);

  if ((node->rb_left = left->rb_right))
    rb_set_parent(left->rb_right, node);
  left->rb_right = node;

  rb_set_parent(left, parent);

  if (parent)
    {
      if (node == parent->rb_right)
        parent->rb_right = left;
      else
        parent->rb_left = left;
    }
  else
    root->rb_node = left;
  rb_set_parent(node, left);
}

void __rb_rotate_left(struct rb_node *node, struct rb_root *root)
{
  struct rb_node *right = node->rb_right;
  struct rb_node *parent = rb_parent(node);

  if((node->rb_right = right->rb_left))
    rb_set_parent(right->rb_left,node);
  right->rb_left = node;

  rb_set_parent(right,parent);

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
//첫번째 인자 SAWON구조체의 노드
//두번째 인자 root
void rb_insert_color(struct rb_node *node,struct rb_root *root)
{
  struct rb_node *parent,*gparent;//아빠,할아버지 선언

  while((parent = rb_parent(node)) && rb_is_red(parent))//노드의 부모주소를 parent에 넣고 parent가 레드이면
    {//부모가 빨가이면 회전하는데 삼촌이 빨간색인지 확인해야함
      gparent = rb_parent(parent);//gparent에 parent의 주소를 넣음
      if(parent == gparent -> rb_left)//parent가 gparent의 왼쪽에 붙어있으면
        {
            {//지역변수를 위한 괄호
              register struct rb_node *uncle = gparent -> rb_right;//삼촌은 할아버지의 오른쪽노드
              if(uncle && rb_is_red(uncle))//삼촌이 빨간색이면
                {
                  rb_set_black(uncle);//삼촌을 블랙으로
                  rb_set_black(parent);//아빠를 블랙으로
                  rb_set_red(gparent);//할아버지를 레드로  //
                  node = gparent;//할아버지를 새로운 로드로 하여 
                  continue;//다시 트리 확인
                }
            }//지역변수를 위한 괄호
          if(parent->rb_right == node)//노드가 부모의 오른쪽에 붙은상황,parent는 gparent의 왼쪽에 붙어있음.
            //	(LR인 경우)
            {
              register struct rb_node *tmp;//스왑변수
              __rb_rotate_left(parent,root);//왼쪽으로 회전시켜서 LL상태로 만듬
              tmp = parent;
              parent = node;
              node = tmp;
            }//부모와 자식을 바꿔줌
          //LL상태면 아래코드 실행
          rb_set_black(parent);//아빠를 블랙으로
          rb_set_red(gparent);//할아버지를 레드로
          __rb_rotate_right(gparent,root);//오른쪽으로 회전시켜서 균형맞춤
        }
      else//parent가 gparent의 오른쪽에 붙어있으면
        {
            {//지역변수를 위한 괄호
              register struct rb_node *uncle = gparent->rb_left;//삼혼은 할아버지의 왼쪽 노드
              if(uncle && rb_is_red(uncle))//삼촌이 빨강이면
                {
                  rb_set_black(uncle);//삼촌을 블랙으로
                  rb_set_black(parent);//아빠를 블랙으로
                  rb_set_red(gparent);//할아버지를 레드로
                  node = gparent;//할아버지를 새로운 노드로 하여
                  continue;//다시 트리 확인
                }
            }//지역변수를 위한 괄호
          if(parent->rb_left == node)//노드가 부모의 왼쪽에 붙은 상황,parent는 gparent의 오른쪽에 붙어있음,
            //(RL인경우)
              {
                register struct rb_node *tmp;//스왑변수
                __rb_rotate_right(parent,root);//오른쪽으로 회전시켜서 RR상태로 만듬
                tmp = parent;
                parent = node;
                node = tmp;
              }//부모와 자식을 바꿔줌
          //RR상태면 아래코드 실행
          rb_set_black(parent);//아빠를 블랙으로 
          rb_set_red(gparent);//할아버지를 레드로
          __rb_rotate_left(gparent,root);//왼쪽으로 회전시켜서 균형 맞춤
        }
    }
  rb_set_black(root->rb_node);//루트를 검은색으로 셋
}

//-------------------------------------------------------
typedef struct
{
  int sid;
  int color;
}INFO;
//데이터를 받아서 트리에 넣는 함수
//첫번째 인자 root
//두번째인자 데이터
//세번째인자 SAWON구조체의 노드
SAWON* insert_data(struct rb_root *root, int sid, struct rb_node *node)
{
  struct rb_node **p = &root->rb_node;//부모 주소를 받은 더블포인터(최초는 루트이다)
  struct rb_node * parent = NULL;//부모의 주소를 받을 노드 포인터
  SAWON *s;//parent를 멤버로하는 구조체의 주소를 받을 포인터

  while(*p)//루트가 비어있지않으면
    {
      parent = *p;//p를 부모에 넣는다.
      s = rb_entry(parent,SAWON,tree);//부모의 구조체주소를 s에 넣는다.

      if(sid < s->sid)//입력값이 부모의 값보다 작으면
        p = &(*p)->rb_left;//p의 왼쪽포인터의 주소를 p에 넣는다.
      else if(sid > s->sid)//입력값이 부모의 값보다 크면
        p = &(*p)->rb_right;//p의 오른쪽포인터의 주소를 p에 넣는다.
      else
        return s;//같으면 안넣음.
    }
  rb_link_node(node, parent, p);//p에 노드를 넣고 노드의 컬러에 parent를 넣는 코드
  rb_insert_color(node,root);//컬러를 맞춰줌
  return NULL;
}

//첫번째인자 root의 노드
//두번째인자 2차원 배열의 포인터
//세번째인자 행포인터
//네번째인자 열포인터
//두번째인자로 받은 2차원 배열에 값을 집어넣음. 
void __display(struct rb_node *temp, INFO (*a)[10],int *row, int *col)
{
  if(temp == 0)//재귀함수 탈출조건 - temp가 0이란 말은 단말노드의 왼쪽 혹은 오른쪽멤버까지 왔다는것을 의미
    return ;
  ++*row;//재귀함수로 들어가기전에 행을 증가시킴 (초기값은 -1)
  __display(temp->rb_left,a,row,col);//왼쪽 노드로 들어감
  a[*row][(*col)].color = rb_color(temp);//컬러를 집어넣음
  a[*row][(*col)++].sid = rb_entry(temp,SAWON,tree)->sid;//데이터를 집어넣고 열을 증가시킴
  __display(temp->rb_right,a,row,col);//오른쪽 노드로 들어감
  --*row;//빠져나올때마다 행을 감소시킴
  //설명:재귀적으로 왼쪽단말노드부터 container연산하여 배열에 집어넣음.
  //들어갈때마다 행을 증가시켜서 가장 깊이있는 노드는 가장 높은 행에 집어넣고
  //집어넣을때마다 열을 증가시켜 왼쪽 -> 루트 ->오른쪽노드순으로 배열에 채워지게함
  return;
}

void display(struct rb_root *root)
{
  int i,j;//반복변수
  int row = -1;//행
  int col = 0;//열
  INFO a[10][10] = {0, };//데이터값을 담을 2차원 배열 선언,INFO는 데이터와 컬러로 구성됨
  system("clear");
  __display(root->rb_node,a,&row,&col);//2차원배열에 값을 넣음
  for(i=0;i<10;i++)
    {
      for(j=0;j<10;j++)
        {
          if(a[i][j].sid == 0)//데이터값이 없을떄
            printf("%4c",' ');//공백출력
          else//데이터값이 있을때
            {
              if(a[i][j].color ==1)//블랙이면
                printf("[%2d]",a[i][j].sid);//블랙은 []출력
              else//레드면
                printf("<%2d>",a[i][j].sid);//레드는 <>출력
            }
        }
      printf("\n");
    }
  getchar();
}

int main()
{
  struct rb_root root = {0,};//루트 생성
  SAWON s[8];//연결할 데이터 생성
  int a[8] = {8,7,6,5,4,3,2,1};//데이터값 생성
  int i;//인덱스

  display(&root);
  for(i=0;i<8;i++)
    {
      s[i].sid = a[i];//데이터에 값을 넣어줌
      insert_data(&root,a[i],&s[i].tree);//인설트함수실행
      display(&root);//잘들어갔는지 디스플레이

    }
  //	__rb_rotate_left(root.rb_node,&root);
  //__rb_rotate_left(root.rb_node->rb_right,&root);
  //	__rb_rotate_right(root.rb_node,&root);
  display(&root);//한번더~
  return 0;
}
