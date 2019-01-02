/*��ͨ������Ĵ��� creat() */
/*����������и��ڵ��ֵ display() */
/*�ڵ������в��ҵ�i���ڵ��ֵ find() */
/*���� add() */
/*ɾ�� dele() */
#include<stdio.h>
#include<stdlib.h>
typedef struct link{
	int info;
	link *next;
}link;

/*����һ���յĵ�����*/

link *none()
{
	return NULL;
}

/*ǰ�巨����������*/

link * creat_q()
{
	link *head,*s;
	int info,num,i;
	i = 0;
	head = NULL;
	printf("\n������Ҫ�����ĵ�����Ľڵ�����\n");
	scanf("%d", &num);
	printf("\n�����뵥����ڵ㣡 ���򣡣�\n");
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

/*��巨����������*/
link * creat_h()
{
	link *head, *s,*p=NULL;
	int info, num, i;
	i = 0;
	head = NULL;
	printf("\n������Ҫ�����ĵ�����Ľڵ�����\n");
	scanf("%d", &num);
	printf("\n�����뵥����ڵ㣡 ���򣡣�\n");
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

/*���*/

void display(link *head)
{
	link *p;
	p = head;//����һ������������൱��ɾ������ʹ�ø�������
	if (!p)
	{
		printf("\n������\n");
	}
	else
	{
		printf("\n������Ϊ��\n");
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
//����
link * add(link * head)
{
	link * p;
	link * s;
	int i;
	printf("\n������Ҫ�����λ�ã�");
	scanf("%d", &i);
	p = find(head, i);
	printf("\n������Ҫ�����ֵ��\n");
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

//ɾ��
link * dele(link * head)
{
	link * p;
	printf("\n������Ҫɾ����ֵ��λ�ã�");
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
	printf("\n��������Ҫiɾ����ֵ��");
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
	printf("\n��������Ҫ�޸ĵ�ֵ��");
	scanf("%d", &change);
	printf("\n���������ֵ��");
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
	printf("\n������Ҫ���ҵ�λ�ã�");
	scanf("%d", &i);
	link * w=find(head,i);
	printf("\n��Ҫ���ҵ�λ���ϵ�ֵΪ��%d\n", w->info);
	head=add(head);
	display(head);
	head = dele_info(head);
	display(head);
	head = change(head);
	display(head);

	system("pause");
	return 0;
}