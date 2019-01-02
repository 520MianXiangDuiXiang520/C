/*普通单链表的创建 creat() */
/*输出单链表中个节点的值 display() */
/*在单链表中查找第i个节点的值 find() */
/*插入 add() */
/*删除 dele() */
#include<stdio.h>
#include<stdlib.h>
typedef struct link{
	int info;
	link *next;
}link;

/*建立一个空的单链表*/

link *none()
{
	return NULL;
}

/*前插法创建单链表*/

link * creat_q()
{
	link *head,*s;
	int info,num,i;
	i = 0;
	head = NULL;
	printf("\n请输入要创建的单链表的节点数：\n");
	scanf("%d", &num);
	printf("\n请输入单链表节点！ 反向！！\n");
	while (i<num)
	{
		scanf("%d", &info);
		s = (link*)malloc(sizeof(link));
		s->info = info;
		s->next = head;
		head = s;
		i++;
	}
	return head;
}

/*后插法创建单链表*/
link * creat_h()
{
	link *head, *s,*p=NULL;
	int info, num, i;
	i = 0;
	head = NULL;
	printf("\n请输入要创建的单链表的节点数：\n");
	scanf("%d", &num);
	printf("\n请输入单链表节点！ 正向！！\n");
	while (i < num)
	{	
		scanf("%d", &info);
		s = (link*)malloc(sizeof(link));
		s->info = info;
		if (head == NULL)
		{
			head = s;
		}
		else
		{
			p->next = s;
		}
		p = s;
		if (p != NULL)
			p->next = NULL;
		i++;
	}
	return head;
}

/*输出*/

void display(link *head)
{
	link *p;
	p = head;//定义一个副本，输出相当于删除，故使用副本进行
	if (!p)
	{
		printf("\n空链表！\n");
	}
	else
	{
		printf("\n单链表为：\n");
		while (p)
		{
			printf("%d->", p->info);
			p = p->next;
		}
	}
}

link * find(link * head,int i)
{
	link * p;
	p = head;
	int count = 0;
	while (count != i)
	{
		p = p->next;
		count++;
	}
	return p;
}
//插入
link * add(link * head)
{
	link * p;
	link * s;
	int i;
	printf("\n请输入要插入的位置：");
	scanf("%d", &i);
	p = find(head, i);
	printf("\n请输入要插入的值：\n");
	int info;
	scanf("%d", &info);
	s = (link*)malloc(sizeof(link));
	s->info = info;
	if (i == 0)
	{
		s->next = head;
		head = s;
	}
	else
	{

		s->next = p->next;
		p->next = s;
	}
	return head;
}

//删除
link * dele(link * head)
{
	link * p;
	printf("\n请输入要删除的值的位置：");
	int i = scanf("%d", &i);
	p = find(head, i-1);
	if (i == 0)
	{
		head = head->next;
	}
	else
	{
		p->next = p->next->next;
	}
	return head;
}

link * dele_info(link * head)
{
	link * p=NULL;
	link * s=head;
	printf("\n请输入你要i删除的值：");
	int info;
	scanf("%d", &info);
	while (s&&s->info != info)
	{
		p = s;
		s = s->next;
	}
	if (s)
	{
		if (!p)
			head = head->next;
		else
			p->next = s->next;
		free(s);
	}
	return head;
}

//change

link * change(link * head)
{
	int change;
	printf("\n请输入你要修改的值：");
	scanf("%d", &change);
	printf("\n请输入改正值：");
	int tur;
	scanf("%d", &tur);
	link * p = head;
	while (p&&p->info != change)
	{
		p = p->next;
	}
	if (p)
	{
		p->info = tur;
	}
	return head;
}

int main()
{
	link *head;
	link * p;
	int i;
	head=creat_h();
	display(head);
	printf("\n请输入要查找的位置：");
	scanf("%d", &i);
	link * w=find(head,i);
	printf("\n您要查找的位置上的值为：%d\n", w->info);
	head=add(head);
	display(head);
	head = dele_info(head);
	display(head);
	head = change(head);
	display(head);

	system("pause");
	return 0;
}