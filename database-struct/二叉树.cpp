/***************************************************************
***  ������
***  1.�������Ĵ���
***  2.�������ı���
***  3.ͳ�ƶ������Ľڵ���
***  4.��������ĸ߶�
***  5.�ж϶������Ƿ�ȼ�
****************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 20
typedef char datatype;     //���Ľڵ�����

/*************************************************************** 
***  ��ȫ��������˳��洢
****************************************************************/

datatype tree[MAXSIZE];   //����һά���������洢��
int n_all;   //����ʵ�ʰ����Ľڵ����

/***************************************************************
***  ��ͨ��������˳��洢
****************************************************************/

typedef struct
{
	datatype info[MAXSIZE];
	int lchild, rchild;
	int parent;   /*������Ÿ�ĸ�ڵ��±�*/
}node;
int n;  /*����ʵ�ʽڵ����*/
int root;  /*������Ÿ��ڵ��±�*/

/***************************************************************
***  ��ͨ����������ʽ�洢
****************************************************************/

typedef struct treeNode
{
	datatype info;
	struct treeNode * lchild, * rchild;
	struct treeNode * parent;
}bintNode;
bintNode *root;   /*ָ����ڵ��ָ��*/

/*����ջ������ʵ�ַǵݹ����*/
typedef struct
{
	bintNode * data[100];
	int top;   /*ջ��ָ��*/
	int tag[100];
}seqstack;
void push(seqstack * p,bintNode * t)   /*��ջ*/
{
	p->data[p->top] = t;
	p->top++;
}
bintNode * pop(seqstack * p)
{
	if (p->top != 0)   /*���ջ��Ϊ��*/
	{
		p->top--;
		return p->data[p->top];   /*����ջ��Ԫ��*/
	}
	else
	{
		printf("\n��ջ��\n");
	}
}
/***************************************************************
***  �����������ĵݹ�ʵ��
****************************************************************/

/*ǰ�����*/
void preorder(bintNode * t)
{
	if (t)
	{
		printf("%c", t->info);
		preorder(t->lchild);
		preorder(t->rchild);
	}
}

/*�������*/
void inorder(bintNode * t)
{
	if (t)
	{
		preorder(t->lchild);
		printf("%c", t->info);
		preorder(t->rchild);
	}
}

/*�������*/
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
***  �����������ķǵݹ�ʵ��
****************************************************************/

/*ǰ�����*/
void preorder1(bintNode * s)
{
	seqstack * seq;
	seq->top = 0;  /*��ʼ��ջ*/
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

/*�������*/
void  inorder1(bintNode * s)
{
	seqstack * seq;
	seq->top = 0;  /*��ʼ��ջ*/
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

/*�������*/
void postorder1(bintNode * s)
{
	seqstack * seq;
	seq->top = 0;  /*��ʼ��ջ*/
	while (seq->top != 0 || (s))
	{
		if (s)
		{
			seq->data[seq->top] = s;   /*ӦΪ��Ҫ����tag������ʹ��push*/
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
***  �������Ĵ���
****************************************************************/

/*����ǰ���������*/