#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**************************************************************
					  ���߶������Ķ���
***************************************************************/

typedef char datatype;
typedef struct tree
{
	datatype data;
	tree * lchild;
	tree * rchild;
	int ltag, rtag;
}binthRnode;

/**************************************************************
					  ���߶������Ĵ���
***************************************************************/

binthRnode * pre = NULL;   /*����һ��ָ�� pre ������¼��ǰ�ڵ����������ǰ���ڵ�*/
binthRnode *createbintree()    /*����һ����ͨ������*/
{
	char ch;
	binthRnode *t;
	if ((ch = getchar()) == '#')
		t = NULL;
	else
	{
		t = (binthRnode *)malloc(sizeof(binthRnode));
		t->data = ch;
		t->lchild = createbintree();
		t->rchild = createbintree();
	}
	return t;
}
binthRnode * inthReading(binthRnode * p)   /*�Զ���������������*/
{
	if (p)
	{
		inthReading(p->lchild);   /*������������*/
		p->ltag = p->lchild ? 0 : 1;   /*������Ů��tagΪ0������Ϊ 1 */
		p->rtag = p->rchild ? 0 : 1;
		if (pre)
		{
			if (pre->rtag == 1)
				pre->rchild = p;   /*�ýڵ����ָ��ָ��ýڵ����������ĺ�̽��*/
			if (pre->ltag == 1)
				p->lchild = pre;   /*��ʾ�ýڵ����ָ��ָ��ýڵ�����������ǰ�����*/
		}
		pre = p;
		inthReading(p->rchild);   /*������������*/
	}
	return p;
}
binthRnode * createthrTree(binthRnode * p)
{
	binthRnode * s;
	p = createbintree();
	s=inthReading(p);
	return s;
}

/**************************************************************
				 ������������߶�����
***************************************************************/

binthRnode * insuccNode(binthRnode * p)
{
	binthRnode * q;
	if (p->rtag == 1)
		return p->rchild;
	else
	{
		q = p->rchild;
		while (q->ltag == 0)
		{
			q = q->lchild;
		}
		return q;
	}
}

void inthrTree(binthRnode * p)
{
	if (p)
	{
		while (p->ltag == 0)
		{
			p = p->lchild;
		}
		do
		{
			printf("%c", p->data);
			p = insuccNode(p);
		} while (p);
	}
}

int main()
{
	binthRnode root;
	binthRnode *s;
	s=createthrTree(&root);
	inthrTree(s);
	system("pause");
	return 0;
}

/*abdh##i##eg###cf##g##*/