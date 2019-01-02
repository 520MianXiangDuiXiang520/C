/***************************************************************
***  二叉树
***  1.二叉树的创建
***  2.二叉树的遍历
***  3.统计二叉树的节点数
***  4.求二叉树的高度
***  5.判断二叉树是否等价
****************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 20
typedef char datatype;     //树的节点类型

/*************************************************************** 
***  完全二叉树的顺序存储
****************************************************************/

datatype tree[MAXSIZE];   //定义一维数组用来存储树
int n_all;   //树中实际包含的节点个数

/***************************************************************
***  普通二叉树的顺序存储
****************************************************************/

typedef struct
{
	datatype info[MAXSIZE];
	int lchild, rchild;
	int parent;   /*用来存放父母节点下标*/
}node;
int n;  /*树中实际节点个数*/
int root;  /*用来存放根节点下标*/

/***************************************************************
***  普通二叉树的链式存储
****************************************************************/

typedef struct treeNode
{
	datatype info;
	struct treeNode * lchild, * rchild;
	struct treeNode * parent;
}bintNode;
bintNode * roots;   /*指向根节点的指针*/

/*定义栈，用来实现非递归回溯*/
typedef struct
{
	bintNode * data[100];
	int top;   /*栈顶指针*/
	int tag[100];
}seqstack;
void push(seqstack * p,bintNode * t)   /*入栈*/
{
	p->data[p->top] = t;
	p->top++;
}
bintNode * pop(seqstack * p)
{
	if (p->top != 0)   /*如果栈不为空*/
	{
		p->top--;
		return p->data[p->top];   /*返回栈顶元素*/
	}
	else
	{
		return NULL;
	}
}
/***************************************************************
***  二叉树遍历的递归实现
****************************************************************/

/*前序遍历*/
void preorder(bintNode * t)
{
	if (t)
	{
		printf("%c", t->info);
		preorder(t->lchild);
		preorder(t->rchild);
	}
}

/*中序遍历*/
void inorder(bintNode * t)
{
	if (t)
	{
		inorder(t->lchild);
		printf("%c", t->info);
		inorder(t->rchild);
	}
}

/*后序遍历*/
void postorder(bintNode * t)
{
	if (t)
	{
		postorder(t->lchild);
		postorder(t->rchild);
		printf("%c", t->info);
	}
}

/***************************************************************
***  二叉树遍历的非递归实现
****************************************************************/

/*前序遍历*/
void preorder1(bintNode * s)
{
	seqstack  seq;
	seq.top = 0;  /*初始化栈*/
	while (seq.top != 0 || (s))
	{
		if (s)
		{
			printf("%c", s->info);
			push(&seq, s);
			s = s->lchild;
		}
		else
		{
			s=pop(&seq);
			s = s->rchild;
		}
	}
}

/*中序遍历*/
void  inorder1(bintNode * s)
{
	seqstack  seq;
	seq.top = 0;  /*初始化栈*/
	while (seq.top != 0 || (s))
	{
		if (s)
		{
			push(&seq, s);
			s = s->lchild;	
		}
		else
		{
			s = pop(&seq);
			printf("%c", s->info);
			s = s->rchild;
		}
	}
}

/*后序遍历*/
void postorder1(bintNode * s)
{
	seqstack  seq;
	seq.top = 0;  /*初始化栈*/
	while (seq.top != 0 || (s))
	{
		if (s)
		{
			seq.data[seq.top] = s;   /*应为需要定义tag，不能使用push*/
			seq.tag[seq.top] = 0;
			seq.top++;
			s = s->lchild;
		}
		else
		{
			if (seq.tag[seq.top - 1] == 1)
			{
				seq.top--;
				s = seq.data[seq.top];
				printf("%c", s->info);
				s = NULL;
			}
			else
			{
				s = seq.data[seq.top - 1];
				seq.tag[seq.top-1] = 1;
				s = s->rchild;
			}
		}
	}
}

/***************************************************************
***  二叉树的创建
****************************************************************/

/*根据前序遍历创建*/
bintNode *createbintree()
{
	char ch;
	bintNode *t;
	if ((ch = getchar()) == '#')
		t = NULL;
	else
	{
		t = (bintNode *)malloc(sizeof(bintNode));
		t->info = ch;
		t->lchild = createbintree();
		t->rchild = createbintree();
	}
	return t;
}

/*根据中序遍历创建*/
bintNode *createbintree1()
{
	char ch;
	bintNode *t;
	if ((ch = getchar()) == '#')
		t = NULL;
	else
	{
		t = (bintNode *)malloc(sizeof(bintNode));
		t->lchild = createbintree1();
		t->info = ch;
		t->rchild = createbintree1();
	}
	return t;
}

/***************************************************************
***  二叉树的其他运算
****************************************************************/

/*二叉树的查找*/
bintNode * find(bintNode * s,datatype x)
{
	bintNode * p;
	if (s==NULL)   /*如果二叉树为空*/
	{
		return NULL;
	}
	else
	{
		if (s->info == x)
			return s;
		else
		{
			p = find(s->lchild, x);
			if (p)
				return p;
			else
				return find(s->rchild, x);
		}
	}
}
/*二叉树中节点个数*/
int num(bintNode * s)
{
	if (s == NULL)
		return NULL;
	else
		return(num(s->lchild + num(s->rchild )+ 1));
}
/*判断二叉树是否等价*/
int isequal(bintNode * s1, bintNode * s2)
{
	int t;
	t = 0;
	if (s1 == NULL && s2 == NULL)
		t = 1;
	else
		if (s1 != NULL && s2 != NULL)
			if (s1->info == s2->info)
				if (isequal(s1->lchild, s2->lchild))
					t = isequal(s1->rchild, s2->rchild);
	return t;
}
/*求叶子节点个数*/
int leafNum(bintNode * s)
{
	int num = 0;
	seqstack  seq;
	seq.top = 0;  /*初始化栈*/
	while (seq.top != 0 || (s))
	{
		if (s)
		{
			if (s->lchild==NULL&&s->rchild==NULL)
			{
				num++;
			}
			push(&seq, s);
			s = s->lchild;
		}
		else
		{
			s = pop(&seq);
			s = s->rchild;
		}
	}
	return num;
}
int main()

{
	bintNode * s;
	s = createbintree();   /*通过前序遍历创建二叉树*/
	printf("\n递归前序遍历\n");
	preorder(s);
	printf("\n非递归前序遍历\n");
	preorder1(s);
	printf("\n递归中序遍历\n");
	inorder(s);
	printf("\n非递归中序遍历\n");
	inorder1(s);
	printf("\n递归后序遍历\n");
	postorder(s);
	printf("\n非递归后序遍历\n");
	postorder1(s);
	int n = leafNum(s);
	printf("\n叶子节点个数为： %d",n);
	system("pause");
	return 0;
}