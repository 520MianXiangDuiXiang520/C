/*���ݽṹ01*/
/*�ڶ���   ���Ա�*/
/*  2.2  ˳���  */
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100//����˳�����󳤶�
typedef int da;//�Զ��� int
/*�Զ���ṹ�� se*/
typedef struct
{
	int a[MAXSIZE];
	int size;//ʵ�ʳ���
}se;
/*��ʼ��˳����ÿձ�*/

void init(se *p)
{
	p->size = 0;
}

/*�ڽṹ��β�����в������*/
void append(se *p, da x)
{
	if (p->size == MAXSIZE)
	{
		printf("˳���ʱ����");
		exit(1);
	}
	p->a[p->size] = x;
	p->size++;
}

/*��ӡ˳�����ڵ��ֵ*/
void dis(se t)
{
	int i;
	if (!t.size)
		printf("�ձ�");
	else
		for (i = 0; i < t.size; i++)
		{
			printf("%d", t.a[i]);
		}
}

/*�ж�˳����Ƿ�Ϊ��*/
int err(se *p)
{
	return(p->size == 0 ? 1 : 0);
}

/*����˳�����ֵΪx��λ��*/

int cha(se *p, int x)
{
	int i = 0;
	while (i < p->size&&p->a[i] != x)
		i++;
	return(i < p->size ? i : -1);
}

/*��ȡ˳����е�i��ڵ��ֵ*/
int huo(se *p, int x)
{
	int i = 0;
	while (i < p->size&&p->a[i] != x)
		i++;
	return(i > p->size ? -1 : i);
}

void fun(se *L)
{
	int i, j, k;
	k = 0;
	for (i = 0; i < L->size; i++)
	{
		for (j = 0; j < k&&L->a[i] != L->a[j]; j++);
		if (j == k)
		{
			if (k != i)
				L->a[k] = L->a[i];
			k++;
		}
	}
}
int main()
{
	int i;
	se h;
	int f;

	// dis(h);
	 /*����init��ʼ��˳���*/
	init(&h);
	/*����apperd������β������*/
	printf("�����ʼ˳���ĳ���\n");
	int pp;
	scanf_s("%d", &pp);
	printf("�������ʼ����\n");
	for (i = 0; i < pp; i++)
	{
		scanf_s("%d", &f);
		append(&h, f);
	}
	printf("��ʼ˳����ǣ�\n");
	dis(h);
	printf("\n");
	int c;
	printf("������Ҫ��β�����������\n");
	scanf_s("%d",&c);
	append(&h,c);
	printf("β��������˳���ʱ:\n");
	/*����se������ӡ˳���*/
	dis(h);
	 printf("\n");
	/*����cha��������x��λ��*/
	int m,g;
	printf("������Ҫ���ҵ�Ԫ��\n");
	scanf_s("%d",&m);
	g=cha(&h,m);
	 printf("%d��λ���� %d  \n",m,g);
	/*����huo������ȡ˳����е�i��ֵ*/
	int j,cc;
	printf("������Ҫ��ȡ��ֵ��λ��\n");
	scanf_s("%d",&j);
	cc=huo(&h,j);
	printf("%d��λ����  %d  \n",j,cc);
	fun(&h);
	dis(h);
	system("pause");
	return 0;
}