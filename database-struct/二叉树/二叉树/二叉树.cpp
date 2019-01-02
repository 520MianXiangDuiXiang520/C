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
bintNode * roots;   /*ָ����ڵ��ָ��*/

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
		return NULL;
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
		inorder(t->lchild);
		printf("%c", t->info);
		inorder(t->rchild);
	}
}

/*�������*/
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
***  �����������ķǵݹ�ʵ��
****************************************************************/

/*ǰ�����*/
void preorder1(bintNode * s)
{
	seqstack  seq;
	seq.top = 0;  /*��ʼ��ջ*/
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

/*�������*/
void  inorder1(bintNode * s)
{
	seqstack  seq;
	seq.top = 0;  /*��ʼ��ջ*/
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

/*�������*/
void postorder1(bintNode * s)
{
	seqstack  seq;
	seq.top = 0;  /*��ʼ��ջ*/
	while (seq.top != 0 || (s))
	{
		if (s)
		{
			seq.data[seq.top] = s;   /*ӦΪ��Ҫ����tag������ʹ��push*/
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
***  �������Ĵ���
****************************************************************/

/*����ǰ���������*/
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

/*���������������*/
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
***  ����������������
****************************************************************/

/*�������Ĳ���*/
bintNode * find(bintNode * s,datatype x)
{
	bintNode * p;
	if (s==NULL)   /*���������Ϊ��*/
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
/*�������нڵ����*/
int num(bintNode * s)
{
	if (s == NULL)
		return NULL;
	else
		return(num(s->lchild + num(s->rchild )+ 1));
}
/*�ж϶������Ƿ�ȼ�*/
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
/*��Ҷ�ӽڵ����*/
int leafNum(bintNode * s)
{
	int num = 0;
	seqstack  seq;
	seq.top = 0;  /*��ʼ��ջ*/
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
	s = createbintree();   /*ͨ��ǰ���������������*/
	printf("\n�ݹ�ǰ�����\n");
	preorder(s);
	printf("\n�ǵݹ�ǰ�����\n");
	preorder1(s);
	printf("\n�ݹ��������\n");
	inorder(s);
	printf("\n�ǵݹ��������\n");
	inorder1(s);
	printf("\n�ݹ�������\n");
	postorder(s);
	printf("\n�ǵݹ�������\n");
	postorder1(s);
	int n = leafNum(s);
	printf("\nҶ�ӽڵ����Ϊ�� %d",n);
	system("pause");
	return 0;
}