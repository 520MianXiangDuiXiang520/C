#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**************************************************************
					  穿线二叉树的定义
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
					  穿线二叉树的创建
***************************************************************/

binthRnode * pre = NULL;   /*设置一个指针 pre 用来记录当前节点中序遍历的前驱节点*/
binthRnode *createbintree()    /*创立一棵普通二叉树*/
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
binthRnode * inthReading(binthRnode * p)   /*对二叉树中序线索化*/
{
	if (p)
	{
		inthReading(p->lchild);   /*线索化左子树*/
		p->ltag = p->lchild ? 0 : 1;   /*有左子女，tag为0，否则为 1 */
		p->rtag = p->rchild ? 0 : 1;
		if (pre)
		{
			if (pre->rtag == 1)
				pre->rchild = p;   /*该节点的右指针指向该节点的中序遍历的后继结点*/
			if (pre->ltag == 1)
				p->lchild = pre;   /*表示该节点的左指针指向该节点的中序遍历的前驱结点*/
		}
		pre = p;
		inthReading(p->rchild);   /*线索化右子树*/
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
				 中序遍历中序穿线二叉树
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