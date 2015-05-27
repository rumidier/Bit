#if 0
int i;
int *p;
#endif

#if 0
#include <stdio.h>
int main()
{
	char ch = 10;
	int *i  = &ch;

	*i = 100;
}
#endif 

#if 0
#include <stdio.h>
int main()
{
	int a[2] = {1,2};
//	int *p = a;
	int *p = &a;

	p[1] = 10;
	printf("a[1] = %d\n",a[1]);

	printf("sizeof(p) = %lu\n",sizeof(p));
	printf("sizeof(a) = %lu\n",sizeof(a));
	printf("sizeof(&a) = %lu\n",sizeof(&a));

}
#endif

#if 0
#include <stdio.h>
int main()
{
	int a[4] = {1,2,3,4};
	int (*p)[4]= a;
	int (*pp)[4] = &a;
}
#endif

#if 0
#include <stdio.h>
int main()
{
	int a[2][2] = {1,2,3,4};

	int (*p)[2] = a;

	p[1][1] = 10;
	printf("a[1][1] = %d\n",a[1][1]);
}
#endif

#if 0
#include <stdio.h>
void init(int * a)
{
	a[1] = 10;

}
int main()
{
	int a[4] = {1,2,3,4};
	init(a);
	printf("a[1] = %d\n",a[1]);
}
#endif
#if 0
#include <stdio.h>
void init(int (*p)[2])
{
	p[1][1] = 10;
}
int main()
{
	int a[2][2] = {1,2,3,4};
	init(a);
	printf("a[1][1] = %d\n",a[1][1]);
}
#endif

#if 0
#include <stdio.h>
void init(int (*p)[2][2])
{
	p[1][1][1] = 10;
}
int main()
{
	int a[2][2][2] = {1,2,3,4,5,6,7,8};
	init(a);
	printf("a[1][1] = %d\n",a[1][1][1]);
}
#endif

#if 0
#include <stdio.h>
int foo(void)
{
	int a = 10;
	return a;
}
int main()
{
	int v;
	v = foo();
	printf("v: %d\n",v);
}
#endif
#if 0
#include <stdio.h>
int* foo(void)
{
	int a = 10;
	return &a;
}
void goo(void)
{
	int i = 5;
}
int main()
{
	int* v;
	v = foo();
	printf("*v: %d\n",*v);
	goo();
	printf("*v: %d\n",*v);

}
#endif

#if 0
#include <stdio.h>
void foo(void)
{
	printf("foo is called\n");
}

int main()
{
	//printf("foo: 0x%x\n",foo);
	void (*p)(void) = foo;
	p();
	return 0;
}
#endif

#if 0
#include <stdio.h>
void foo(int);

void(* bar( void (*fp)(int)))(int)
{
	int i=8;
	return fp;
}
int main()
{
	int i=7;
	void (*p)(int);
	p = bar(foo);
	p(i);
}

void foo(int a)
{
	printf("foo is called\n");
}
#endif

#if 0
#include <stdio.h>
void aaa(void)
{
	printf("aaa called\n");
}
void ccc(void)
{
	printf("ccc called\n");
}
void ( *ddd(void))(void)
{
	return ccc;
}
void (* bbb( void (*p)(void)))(void)
{
	p();
	printf("bbb called\n");
	return ddd();
}
int main()
{
	bbb(aaa)();
	return 0;
}
#endif

#if 0
#include <stdio.h>
void aaa(void)
{
	printf("aaa called\n");
}
void bbb(void)
{
	printf("bbb called\n");
}
void ccc(void)
{
	printf("ccc called\n");
}
void ddd(void)
{
	printf("ddd called\n");
}
void insert(void(*(*fp)[2])(void))
{
	fp[0][0] = aaa;
	fp[0][1] = bbb;
	fp[1][0] = ccc;
	fp[1][1] = ddd;
}
int main()
{
	void (*p[2][2])(void);
	insert(p);
	p[0][0]();
	p[0][1]();
	p[1][0]();
	p[1][1]();

	return 0;

}


#endif
#if 0
#include <stdio.h>
typedef unsigned char uc;
typedef signed char sc;
int main()
{
	uc ch = 255;
	sc sch = 255;
	printf("ch: %d\n",ch);
	printf("sch: %d",sch);
}
#endif

#if 0
#include <stdio.h>
typedef void (*FP1)(void);
void aaa(void)
{
	printf("aaa called\n");
}
void bbb(void)
{
	printf("bbb called\n");
}
void ccc(void)
{
	printf("ccc called\n");
}
void ddd(void)
{
	printf("ddd called\n");
}
//void (*(*insert(void))[2])(void)
FP1 (*insert(void))[2]
{
//	static void (*fp[2][2])(void);
	static FP1 fp[2][2];
	fp[0][0]= aaa;
	fp[0][1] = bbb;
	fp[1][0]= ccc;
	fp[1][1] = ddd;

	return fp;

}
int main()
{
	//void(*(*p)[2])(void);
	FP1 (*p)[2];
	p = insert();
	p[0][0]();
	p[0][1]();
	p[1][0]();
	p[1][1]();
//	void (*p)(void);
//	p =insert();
//	p();
}

#endif
#if 0

#include <stdio.h>
void aaa(void)
{
	printf("aaa called\n");
}
void bbb(void)
{
	printf("bbb called\n");
}
void ccc(void)
{
	printf("ccc called\n");
}
void ddd(void)
{
	printf("ddd called\n");
}

void aa(void)
{
	printf("aa called\n");
}
void bb(void)
{
	printf("bb called\n");
}
void cc(void)
{
	printf("cc called\n");
}
void dd(void)
{
	printf("dd called\n");
}
typedef void (*FP1)(void);
typedef FP1 (*FP2)[2];
//void( * (*trans(void ((*(*fp)[2])(void))))[2])(void)
//FP1 (*trans(void ((*(*fp)[2])(void))))[2]
//FP1 (*trans(FP1(*fp)[2]))[2]
//FP1 (*trans(FP2 fp))[2]
FP2 trans(FP2 fp)
{
	fp[0][0]();
	fp[0][1]();
	fp[1][0]();
	fp[1][1]();
	fp[0][0] = aa;
	fp[0][1] = bb;
	fp[1][0] = cc;
	fp[1][1] = dd;
	return fp;
}
int main()
{
	void (*t[2][2])(void);
	void (*((*r)[2]))(void);

	t[0][0] = aaa;
	t[0][1] = bbb;
	t[1][0] = ccc;
	t[1][1] = ddd;
	r = trans(t);
	r[0][0]();
	r[0][1]();
	r[1][0]();
	r[1][1]();
}

#endif
#if 0
#include <stdio.h>
#include <time.h>
int factorial(int n)
{
	printf("factorial (%d)\n",n);
	if(n == 1) return 1;
	else
		return(n*factorial(n-1));
}
int factorial_iter(int n)
{
	int k, v=1;
	for(k=n;k>0;k--)
		v = v*k;
	return v;
}
int main()
{
	int value;
	int i = 0;
	clock_t start, finish;
	double duration;
	start = clock();
	value = factorial(4000);
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("%f초입니다 .\n",duration);
	start = clock();
	value = factorial_iter(4000);
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("%f초입니다.\n",duration);
	return 0;
}
#endif
#if 0
#include <stdio.h>
#include <time.h>
double slow_power(double x, int n)
{
	int i;
	double r = 1.0;
	for(i=0;i<n;i++)
		r = r*x;
	return r;
}
double power(double x, int n)
{
	if(n==0) return 1;
	else if((n%2)==0)
		return power(x*x, n/2);
	else return x*power(x*x,(n-1)/2);
}

int main()
{
	int i;
	double r;
	clock_t start, end;
	start = clock();
	for(i=0;i<1000000;i++)
		r = slow_power(2,500);
	end = clock();
	printf("%f\n",(double)(end-start)/CLOCKS_PER_SEC);

	start = clock();
	for(i=0;i<1000000;i++)
		r = power(2,500);
	end = clock();
	printf("%f\n",(double)(end-start)/CLOCKS_PER_SEC);
}
#endif

#if 0
#include <stdio.h>
int fib(int n)
{
	if(n==0) return 0;
	if(n==1) return 1;
	return (fib(n-1) + fib(n-2));
}
int fib_iter(int n)
{
	if(n < 2) return n;
	else{
		int i,tmp, current = 1, last = 0;
		for(i=2;i<=n;i++){
			tmp = current;
			current += last;
			last = tmp;
		}
		return current;
	}
}
int main()
{
	int result;
	int cnt;
	printf("원하는 값 입력: ");
	scanf("%d",&cnt);
//	result = fib(cnt);
	result = fib_iter(cnt);
	printf("결과 값은 %d\n",result);

}
#endif

#if 0
#include <stdio.h>
void hanoi_tower(int n, char from, char to,char tmp)
{
	if(n==1)printf("원판 1을 %c에서 %c으로 옮긴다. \n",from,to);
	else{
		hanoi_tower(n-1,from,tmp,to);
		printf("원판 %d을 %c에서 %c으로 옮긴다. \n",n,from,to);
		hanoi_tower(n-1,tmp,to,from);
	}
}
int main()
{
	hanoi_tower(3,'A','B','C');
	return 0;
}
#endif
#if 0

int add(int a, int b)
{
	int result;
	result = a+b;
	return result;
}

int  main()
{
	int sum;
	int op1 = 3;
	int op2 = 4;
	sum = add(op1,op2);
	return 0;
}
#endif
#if 0
#include <stdio.h>

int factorial(int n)
{
	printf("factorial (%d)\n",n);
	if(n == 1) return 1;
	else
		return (n*factorial(n-1));
}
int Factorial(int n, int a)
{
	if(n==0)
		return a;
	else
		return Factorial(n-1,n*a);
}
int main()
{
	int value;
	int a = 1;
	value = factorial(4);
	printf("계산값 : %d\n",value);
	value = Factorial(4,a);
	printf("계산값: %d\n",value);
	return 0;
}
#endif

#if 0
#include <stdio.h>
#define MAX_LIST_SIZE	100
typedef int element;

typedef struct{
	int list[MAX_LIST_SIZE];
	int length;
}ArrayListType;

void init(ArrayListType * L)
{
	L->length = 0;
}
int is_empty(ArrayListType *L)
{
	return L->length == 0;
}
int is_full(ArrayListType *L)
{
	return L->length == MAX_LIST_SIZE;
}
void add(ArrayListType *L , int position, element item)
{
	int i;
	if(!is_full(L) && (position >= 0) && (position <= L->length))
	{
		for(i = (L->length-1); i>= position; i--)
			L->list[i+1] = L->list[i];
		L->list[position] = item;
		L->length++;

	}
} 
void add_first(ArrayListType *L,element item)
{

}
void add_last(ArrayListType *L, element item)
{

}
void display(ArrayListType* L)
{
	int i;
	for(i=0 ;i< L->length;i++)
		printf("%d\n",L->list[i]);
}
element del(ArrayListType *L, int position)
{
	int i;
	element item;
	if(position < 0 || position >= L->length)
	{
		printf(" error 발생 \n");
		return 0;
	}
	item = L->list[position];
	for(i=position; i<(L->length-1);i++)
		L->list[i] = L->list[i+1];
	L->length--;
	return item;
}
//add_first(&list1,70);
//	add_last(&list1,90);
//clear(&list1);
//element replace(&list1,pos,item);
//int is_in_list(&list1,item);
//int get_length(&list);
//element get_entry(&list,pos);
int main()
{
	element val;
	ArrayListType list1;
	init(&list1);
	add(&list1, 0, 10);
	add(&list1, 0, 20);
	add(&list1, 0, 30);
	add(&list1, 1, 40);
	add(&list1, 3, 50);
//	add_first(&list1,70);
//	add_last(&list1,90);
	display(&list1);
	val = del(&list1,3);
	printf("\n");
	display(&list1);
	printf("val : %d\n",val);

}
#endif
#if 0
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode{
	element data;
	struct ListNode* link;
}ListNode;

int main()
{
	ListNode *p1;
	ListNode *p2;
	ListNode *p3;
	p1 = (ListNode *)malloc(sizeof(ListNode));
	p1->data = 10;
	p1->link = NULL;

	p2 = (ListNode *)malloc(sizeof(ListNode));
	p2->data = 20;
	p2->link = NULL;
	p1->link = p2;

	for(p3 = p1; p3 !=  NULL; p3=p3->link)
	{
		printf("data: %d\n",p3->data);
	}
}
#endif

#if 0
#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct ListNode{
	element data;
	struct ListNode* link;
}ListNode;

typedef struct{
	ListNode *head;
	int length;
}ListType;

void init(ListType* list)
{
	if(list == NULL) return;
	list->length = 0;
	list->head = NULL;
}
void insert_node(ListNode **phead, ListNode *p, ListNode *new_node)
{
	ListType * head;
	head = (ListType *)(phead);
	if(*phead == NULL)
	{
		new_node->link = NULL;
		*phead = new_node;
	}
	else if(p == NULL)
	{
		new_node->link = *phead;
		*phead = new_node;
	}
	else
	{
	    new_node->link = p->link;
		p->link = new_node;
	}
	head->length++;
}
ListNode * create(int item)
{
	ListNode * p;
	p = (ListNode *)malloc(sizeof(ListNode));
	p->data = item;
	p->link = NULL;
	return p;
}
ListNode *Entry(ListNode* node,int idx)
{
	int i;
	for(i=0;i<idx; i++)
		node = node->link;
	return node;
}
void remove_node(ListNode **phead, ListNode *p, ListNode *removed)
{
	if(p == NULL)
		*phead = (*phead)->link;
	else
		p->link = removed->link;
	free(removed);
}
#include <stdlib.h>
int main()
{
	ListType list1;
	ListNode *node;
	ListNode *prev;
	int i;
	init(&list1);
	//node = (ListNode *)malloc(sizeof(ListNode));
	//node->data = 10;
	//node->link = NULL;
	node = create(10);
	insert_node(&(list1.head),NULL,node);

//	node = (ListNode *)malloc(sizeof(ListNode));
//	node->data = 20;
//	node->link = NULL;
	node = create(20);
	insert_node(&(list1.head),NULL,node);

//	node = (ListNode *)malloc(sizeof(ListNode));
//	node->data = 30;
//	node->link = NULL;
	node = create(30);
	insert_node(&(list1.head),NULL,node);
	
	node = create(40);
	insert_node(&(list1.head),NULL,node);
	
	for(node = list1.head; node->link != NULL; node = node->link)
	{
		printf("data: %d\n",node->data);
	}
	printf("data: %d\n",node->data);
	printf("list1.length: %d\n",list1.length);
	printf("-------------------------\n");
	node = list1.head;
	prev = Entry(node, 2);

	node = create(50);
	insert_node(&(list1.head),prev,node);
	
	for(node = list1.head; node->link != NULL; node = node->link)
	{
		printf("data: %d\n",node->data);
	}	
	printf("data: %d\n",node->data);

	prev = list1.head->link;
	node = prev->link;
	remove_node(&(list1.head),prev,node);

	printf("-----------------------\n");
	for(node = list1.head; node->link != NULL; node = node->link)
	{
		printf("data: %d\n",node->data);
	}	
	printf("data: %d\n",node->data);
}
#endif


#if 0
#include <stdio.h>

typedef int AAA[5];

int main()
{
	AAA ar;
	int i = 7;
	ar[0] = 1;
	ar[1] = 2;
	ar[2] = 3;
	ar[3] = 4;
	ar[4] = 5;

    ar[3] = i;
}
#endif

#if 0
#include <stdio.h>
#define MAX_STACK_SIZE 100

typedef int StackObject;
int stack[MAX_STACK_SIZE];
int top =-1;
int is_empty()
{
	return (top == -1);
}
int is_full()
{
	return ( top == (MAX_STACK_SIZE-1));
}
void push(StackObject item)
{
	if(is_full()){
		printf("stack is full\n");
		return;
	}
	else
		stack[++top] = item;
}
StackObject pop()
{
	if(is_empty()){
		printf("stack is empty\n");
		return 0;
	}
	else
		return stack[top--]; 
}

StackObject peek()
{
	if(is_empty()){
		printf("stack is empty\n");
		return 0;
	}
	else
		return stack[top]; 
}

void main()
{
	push(1);
	push(2);
	push(3);
	printf("%d\n",pop());
	printf("%d\n",pop());
	printf("%d\n",pop());

}
#endif

#if 0
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 50
#define MAX_STRING 100
typedef struct{
	int student_no;
	char name[MAX_STRING];
	char address[MAX_STRING];
}StackObject;
StackObject* stack[MAX_STACK_SIZE];
int top =-1;
int is_empty()
{
	return (top == -1);
}
int is_full()
{
	return ( top == (MAX_STACK_SIZE-1));
}
void push(StackObject* item)
{
	if(is_full()){
		printf("stack is full\n");
		return;
	}
	else
		stack[++top] = item;
}
StackObject* pop()
{
	if(is_empty()){
		printf("stack is empty\n");
		exit(0);
	}
	else
		return stack[top--]; 
}

StackObject* peek()
{
	if(is_empty()){
		printf("stack is empty\n");
		exit(0);
	}
	else
		return stack[top]; 
}
void init()
{
	top = -1;
}
StackObject* input(void)
{
	StackObject* in;
	in = (StackObject *)malloc(sizeof(StackObject));
	printf("student no을 입력하세요: ");
	scanf("%d",&in->student_no);
	printf("name 을 입력하세요: ");
	scanf("%s",in->name);
	printf("address을 입력하세요: ");
	scanf("%s",in->address);
	return in;
}
void main()
{
	StackObject* in;
	StackObject* out;
	
	int i;
	for(i=0;i<3;i++){
		in = input();
		push(in);
	}
	for(i=0;i<3;i++){
		out = pop();
		printf("name:    %s\n",out->name);
		printf("address: %s\n",out->address);
		printf("no :     %d\n",out->student_no);
		printf("-------------\n");
		free(out);
	}
}
#endif


#if 0
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING 100
typedef struct{
	int student_no;
	char name[MAX_STRING];
	char address[MAX_STRING];
}StackObject;
typedef struct{
StackObject** stack;
int size;
int top;
}Stack;
Stack st1;
int is_empty()
{
	return (st1.top == -1);
}
int is_full()
{
	return ( st1.top == (st1.size-1));
}
void push(StackObject* item)
{
	if(is_full()){
		printf("stack is full\n");
		return;
	}
	else
		(st1.stack)[++(st1.top)] = item;
}
StackObject* pop()
{
	if(is_empty()){
		printf("stack is empty\n");
		exit(0);
	}
	else
		return st1.stack[(st1.top)--]; 
}
/*
StackObject* peek()
{
	if(is_empty()){
		printf("stack is empty\n");
		exit(0);
	}
	else
		return stack[top]; 
}
*/


StackObject* input(void)
{
	StackObject* in;
	in = (StackObject *)malloc(sizeof(StackObject));
	printf("student no을 입력하세요: ");
	scanf("%d",&in->student_no);
	printf("name 을 입력하세요: ");
	scanf("%s",in->name);
	printf("address을 입력하세요: ");
	scanf("%s",in->address);
	return in;
}
void inputstack()
{
	
	int i;
	printf("학생수: ");
	scanf("%d",&i);

	st1.stack = (StackObject**)malloc(sizeof(StackObject* )*i);
	st1.size = i;
	st1.top = -1;

}
void main()
{
	int i;
	StackObject* in;
	StackObject* out;
	inputstack();
	
	for(i=0;i<st1.size;i++){
		in = input();
		push(in);
	}
	for(i=0;i<3;i++){
		out = pop();
		printf("name:    %s\n",out->name);
		printf("address: %s\n",out->address);
		printf("no :     %d\n",out->student_no);
		printf("-------------\n");
		free(out);
	}
}
#endif

#if 0
#include <stdio.h>

int main()
{
	int i = 0;
	int a[5] = {1,2,3,4,5};
	int *p = a;
	char *str = "hello";
	printf("4[a] : %d\n",4[a]);
	printf("a[4] : %d\n",a[4]);
	printf("p[4] : %d\n",p[4]);
	printf("4[p] : %d\n",4[p]);
	printf("str: %s\n",str);
	printf("str: %c\n","hello"[0]);

	
}
#endif

#if 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TRUE 1
#define FALSE  0
#define MAX_STACK_SIZE 100
typedef char element;
typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
}StackType;
void init(StackType *s)
{
	s->top = -1;
}
int is_empty(StackType *s)
{
	return (s->top == -1);
}
int is_full(StackType *s)
{
	return (s->top == (MAX_STACK_SIZE-1));
}
void push(StackType *s, element item)
{
	if(is_full(s)){
		printf("stack full\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}
element pop(StackType *s)
{
	if(is_empty(s)){
		printf("stack empty\n");
		exit(0);
	}
	else return s->stack[(s->top)--];
}

int check_matching(char *in)
{
	StackType s;
	char ch, open_ch;
	int i, n=strlen(in);
	init(&s);

	for(i=0; i< n; i++){
		ch = in[i];
		switch(ch){
		case '(': case '[': case '{':
			push(&s,ch);
			break;
		case ')': case ']': case '}':
			if(is_empty(&s)) return FALSE;
			else{
				open_ch = pop(&s);
				if((open_ch == '(' && ch != ')') ||
                   (open_ch == '[' && ch != ']') ||
				   (open_ch == '{' && ch != '}')) 
					   return FALSE;

			break;
			}
		}
	}
	if(!is_empty(&s))return FALSE;
	return TRUE;
}
int main()
{
	char string[256];
	scanf("%s",string);
	if(check_matching(string) == TRUE)
		printf("successed\n");
	else
		printf("failed\n");
	return 0;
}
#endif

#if 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE  0
#define MAX_STACK_SIZE 100
typedef char element;
typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
}StackType;
void init(StackType *s)
{
	s->top = -1;
}
int is_empty(StackType *s)
{
	return (s->top == -1);
}
int is_full(StackType *s)
{
	return (s->top == (MAX_STACK_SIZE-1));
}
void push(StackType *s, element item)
{
	if(is_full(s)){
		printf("stack full\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}
element pop(StackType *s)
{
	if(is_empty(s)){
		printf("stack empty\n");
		exit(0);
	}
	else return s->stack[(s->top)--];
}
int prec(char op)
{
	switch(op){
	case '(': case ')' : return 0;
	case '+': case '-' : return 1;
	case '*': case '/' : return 2;
	}
	return -1;
}
element peek(StackType *s)
{
	if(is_empty(s)){
		printf("stack empty\n");
		exit(0);
	}
	else
		return s->stack[s->top];
}
void infix_to_postfix(char exp[])
{   
  int i=0;
  char ch, top_op;		
  int len=strlen(exp);
  StackType s;

  init(&s);					
  for(i=0; i<len; i++){
	ch = exp[i];
	
    switch(ch){
	case '+': case '-': case '*': case '/': 
	  
      while(!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
	    printf("%c", pop(&s));
	  push(&s, ch);
	  break;
	case '(':	
	  push(&s, ch);
	  break;
	case ')':	
	  top_op = pop(&s);
	  
	  while( top_op != '(' ){ 
	    printf("%c", top_op);
	    top_op = pop(&s);
	  }
	  break;
	default:		
	  printf("%c", ch);
	  break;
	}
  }
  while( !is_empty(&s) )	
	printf("%c", pop(&s));
}

int main()
{
	char string[256]= "(5*((4+6)/2)+8)";
//	scanf("%s",string);
	infix_to_postfix(string);
	return 0;
}
#endif


#if 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE  0
#define MAX_STACK_SIZE 100
typedef int element;
typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
}StackType;
void init(StackType *s)
{
	s->top = -1;
}
int is_empty(StackType *s)
{
	return (s->top == -1);
}
int is_full(StackType *s)
{
	return (s->top == (MAX_STACK_SIZE-1));
}
void push(StackType *s, element item)
{
	if(is_full(s)){
		printf("stack full\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}
element pop(StackType *s)
{
	if(is_empty(s)){
		printf("stack empty\n");
		exit(0);
	}
	else return s->stack[(s->top)--];
}
int prec(char op)
{
	switch(op){
	case '(': case ')' : return 0;
	case '+': case '-' : return 1;
	case '*': case '/' : return 2;
	}
	return -1;
}
element peek(StackType *s)
{
	if(is_empty(s)){
		printf("stack empty\n");
		exit(0);
	}
	else
		return s->stack[s->top];
}

int eval(char exp[])
{
	int op1, op2,value, i=0;
	int len = strlen(exp);
	char ch;
	StackType s;
	init(&s);
	for(i=0;i<len;i++){
		ch = exp[i];
		if( ch != '+' && ch != '-' && ch != '*' && ch != '/'){
			value = ch - '0';
			push(&s,value);
		}
		else{
			op2 = pop(&s);
			op1 = pop(&s);
			switch(ch){
			case '+': push(&s,op1+op2);break;
			case '-': push(&s,op1-op2);break;
			case '*': push(&s,op1*op2);break;
			case '/': push(&s,op1/op2);break;
			}
		}
	}
	return pop(&s);
}
void infix_to_postfix(char dst[],char exp[])
{   
  int i=0;
  char ch, top_op,temp;		
  int len=strlen(exp);
  StackType s;

  init(&s);					
  
  for(i=0; i<len; i++){
	ch = exp[i];
	
    switch(ch){
	case '+': case '-': case '*': case '/': 
	  
      while(!is_empty(&s) && (prec(ch) <= prec(peek(&s)))){
	    //printf("%c", pop(&s));
		temp = pop(&s);
		printf("%c",temp);
		*dst++ = temp;
	  }
	  push(&s, ch);
	  break;
	case '(':	
	  push(&s, ch);
	  break;
	case ')':	
	  top_op = pop(&s);
	 
	  while( top_op != '(' ){ 
	    printf("%c", top_op);
		*dst++ = top_op;
	    top_op = pop(&s);
	  }
	  break;
	default:		
	  printf("%c", ch);
	  *dst++ = ch;
	  break;
	}
  }
  while( !is_empty(&s) ){	
//	printf("%c", pop(&s));
	  temp = pop(&s);
	  printf("%c",temp);
	  *dst++ = temp;
  }
  *dst = 0;
 
}
int main()
{
	int result;
//	printf("후위표기식은 82/3-32*+\n");
//	result = eval("82/3-32*+");
//	printf("결과값은 %d\n",result);
	
	char string[80];// = "(5*((4+6)/2)+8)";
	char dst[80];

	scanf("%s",string);
	infix_to_postfix(dst,string);

	printf("\ndst: %s\n",dst);
	result = eval(dst);
	printf("result: %d\n",result);
	return 0;
}
#endif

#if 0
//p.142~144
/*
 *	maze.c
 */
#include <stdio.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAZE_SIZE 6

typedef struct  StackObjectRec { 
	short r;
	short c;
} StackObject;

StackObject  stack[MAX_STACK_SIZE]; 
int  top = -1; 
StackObject here={1,0}, entry={1,0};

char maze[MAZE_SIZE][MAZE_SIZE] = {
	{'1', '1', '1', '1', '1', '1'},
	{'e', '0', '1', '0', '0', '1'},
	{'1', '0', '0', '0', '1', '1'},
	{'1', '0', '1', '0', '1', '1'},
	{'1', '0', '1', '0', '0', 'x'},
	{'1', '1', '1', '1', '1', '1'},
};

void initialize()
{
	top = -1;
}

int isEmpty()
{
	return (top == -1);
}

int isFull()
{
	return (top == (MAX_STACK_SIZE-1));
}

void push(StackObject item)
{ 
  	  if( isFull() ) { 
		  printf("stack is full\n");
	  } 
	  else stack[++top] = item; 
}

StackObject pop() 
{ 
   	if( isEmpty() ) {
		printf("stack is empty\n");
	}
	else return stack[top--]; 
} 

void printStack()
{
	int i;
	for(i=5;i>top;i--)
		printf("|     |\n");
	for(i=top;i>=0;i--)
		printf("|(%01d,%01d)|\n", stack[i].r, stack[i].c);
	printf("-------\n");
}

void pushLoc(int r, int c)
{
	if( r < 0 || c < 0 ) return;
	if( maze[r][c] != '1' && maze[r][c] != '.' ){
		StackObject tmp;
		tmp.r = r;
		tmp.c = c;
		push(tmp);
	}
}

void printMaze(char m[MAZE_SIZE][MAZE_SIZE])
{
	int r,c;
	printf("\n\n");
	for(r=0;r<MAZE_SIZE;r++){
		for(c=0;c<MAZE_SIZE;c++){
			if( c == here.c && r == here.r )
				printf("m ");
			else {
				if( m[r][c] == 0 ) printf("0 ");
				else printf("%c ",m[r][c]);
			}
		}
		printf("\n");
	}
	printf("\n\n");
}

void main()
{
	int r,c;
	here = entry;
	printMaze(maze);
	printStack();
	while ( maze[here.r][here.c]!='x' ){
		printMaze(maze);
		r = here.r;
		c = here.c;
		maze[r][c] = '.';
		pushLoc(r-1,c);
		pushLoc(r+1,c);
		pushLoc(r,c-1);
		pushLoc(r,c+1);
		printStack();
		if( isEmpty() ){
			printf("실패\n");
			return;
		}
		else 
			here = pop();
		printMaze(maze);
		printStack();
		getch();
	}
	printf("성공\n");
}

#endif
#if 0
#include <stdio.h>
#define MAX_QUEUE_SIZE 5
typedef int QueueObject;
QueueObject queue[MAX_QUEUE_SIZE];

int front, rear;
void initialize()
{
	front = rear = 0;
}
int isEmpty()
{
	return (front == rear);
}
int isFull()
{
	return ((rear+1)%MAX_QUEUE_SIZE == front);
}
void addq(QueueObject item)
{
	if(isFull()){
		printf("queue is full\n");
	}
	rear = (rear +1)%MAX_QUEUE_SIZE;
	queue[rear] = item;
}
QueueObject deleteq()
{
	if(isEmpty()){
		printf("queue is empty\n");
	}
	front = (front+1)%MAX_QUEUE_SIZE;
	return queue[front];
}
void main()
{
	initialize();
	printf("front %d rear = %d\n",front,rear);
	addq(1);
	addq(2);
	addq(3);
	addq(4);
	printf("deleteq() =%d\n",deleteq());
	printf("deleteq() =%d\n",deleteq());
	printf("deleteq() =%d\n",deleteq());
	addq(5);
	addq(6);
	addq(7);
	printf("deleteq() =%d\n",deleteq());
	printf("deleteq() =%d\n",deleteq());
	printf("deleteq() =%d\n",deleteq());
	printf("deleteq() =%d\n",deleteq());
	printf("front %d rear = %d\n",front,rear);


}
#endif

#if 1
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef int QueueObject;
typedef struct QueueRec{
	QueueObject item;
	struct QueueRec *link;
}QueueNode;
QueueNode *front, *rear, *prev;

void initialize()
{
	front = rear = NULL;
}
int isEmpty()
{
	if (front == NULL)
		rear = NULL;
	return (front == NULL);
}

void addq(QueueObject item)
{
	QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));

	if(temp == NULL){
		printf("메모리를 할당 할 수 없음\n");
		exit(0);
	}
	else{

		temp->item = item;
		temp->link = NULL;
		if(front == NULL)
			front = temp;
		else
			rear->link  = temp;
		rear = temp;
	}
	
}

QueueObject deleteq()
{
	QueueNode *temp = front;
	QueueObject item;

	if(isEmpty()){
		printf("queue is empty\n");
		exit(0);
	}
	else
	{
		item = temp->item;
		front =front->link;
		free(temp);
	//	if(front == NULL)
		//	rear = NULL;
		return item;
	}
}
void add_front(QueueObject item)
{
	QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));

	if(temp == NULL){
		printf("메모리를 할당 할 수 없음\n");
		exit(0);
	}
	else{

		temp->item = item;
		temp->link = NULL;
		if(front == NULL){
			front = temp;
			rear = temp;
		}
		else
		{
			temp->link = front;
			front = temp;
		}
	}

}
void f_prev(void)
{
	if(front == rear)
		return;
	for(prev =front; prev->link != rear; prev = prev->link);

}
QueueObject delete_rear()
{
	QueueNode *temp;
	QueueObject item;
	f_prev();

	if(isEmpty()){
		printf("queue is empty\n");
		return -1;
	}
	if(front == rear)
	{
		item = front->item;
			front = rear = NULL;
			return item;
	}
	temp = rear;
	item = temp->item;
	rear = prev;
	rear->link = NULL;
	free(temp);
	return item;
}


void main()
{
	
	initialize();
	printf("front %d rear = %d\n",front,rear);
//	addq(1);
//	addq(2);
//	addq(3);
	addq(4);
	add_front(8);
	delete_rear();
	delete_rear();
	delete_rear();
	printf("deleteq() =%d\n",deleteq());
	printf("deleteq() =%d\n",deleteq());
	printf("deleteq() =%d\n",deleteq());
	printf("deleteq() =%d\n",deleteq());
	
}

#endif
