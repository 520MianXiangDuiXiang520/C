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
bintNode *root;   /*指向根节点的指针*/

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
		printf("\n空栈！\n");
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
		preorder(t->lchild);
		printf("%c", t->info);
		preorder(t->rchild);
	}
}

/*后序遍历*/
void postorder(bintNode * t)
{
	if (t)
	{
		preorder(t->lchild);
		preorder(t->rchild);
		printf("%c", t->info);
	}
}

/***************************************************************
***  二叉树遍历的非递归实现
****************************************************************/

/*前序遍历*/
void preorder1(bintNode * s)
{
	seqstack * seq;
	seq->top = 0;  /*初始化栈*/
	while (seq->top != 0 || (s))
	{
		if (s)
		{
			printf("%c", s->info);
			push(seq, s);
			s = s->lchild;
		}
		else
		{
			s=pop(seq);
			s = s->rchild;
		}
	}
}

/*中序遍历*/
void  inorder1(bintNode * s)
{
	seqstack * seq;
	seq->top = 0;  /*初始化栈*/
	while (seq->top != 0 || (s))
	{
		if (s)
		{
			push(seq, s);
			s = s->lchild;	
		}
		else
		{
			s = pop(seq);
			printf("%c", s->info);
			s = s->rchild;
		}
	}
}

/*后序遍历*/
void postorder1(bintNode * s)
{
	seqstack * seq;
	seq->top = 0;  /*初始化栈*/
	while (seq->top != 0 || (s))
	{
		if (s)
		{
			seq->data[seq->top] = s;   /*应为需要定义tag，不能使用push*/
			seq->tag[seq->top] = 0;
			seq->top++;
			s = s->lchild;
		}
		else
		{
			if (seq->tag[seq->top - 1] == 0)
			{
				seq->top--;
				s = seq->data[seq->top];
				printf("%c", s->info);
				s = NULL;
			}
			else
			{
				s = seq->data[seq->top - 1];
				seq->tag[seq->top-1] = 1;
				s = s->rchild;
			}
		}
	}
}

/***************************************************************
***  二叉树的创建
****************************************************************/

/*根据前序遍历创建*/