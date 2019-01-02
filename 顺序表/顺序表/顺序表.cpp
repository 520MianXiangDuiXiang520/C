/*数据结构01*/
/*第二章   线性表*/
/*  2.2  顺序表  */
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100//定义顺序表最大长度
typedef int da;//自定义 int
/*自定义结构体 se*/
typedef struct
{
	int a[MAXSIZE];
	int size;//实际长度
}se;
/*初始化顺序表置空表*/

void init(se *p)
{
	p->size = 0;
}

/*在结构体尾部进行插入操作*/
void append(se *p, da x)
{
	if (p->size == MAXSIZE)
	{
		printf("顺序表时满的");
		exit(1);
	}
	p->a[p->size] = x;
	p->size++;
}

/*打印顺序表各节点的值*/
void dis(se t)
{
	int i;
	if (!t.size)
		printf("空表！");
	else
		for (i = 0; i < t.size; i++)
		{
			printf("%d", t.a[i]);
		}
}

/*判断顺序表是否为空*/
int err(se *p)
{
	return(p->size == 0 ? 1 : 0);
}

/*查找顺序表中值为x的位置*/

int cha(se *p, int x)
{
	int i = 0;
	while (i < p->size&&p->a[i] != x)
		i++;
	return(i < p->size ? i : -1);
}

/*获取顺序表中地i格节点的值*/
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
	 /*调运init初始化顺序表*/
	init(&h);
	/*调运apperd函数在尾部插入*/
	printf("输入初始顺序表的长度\n");
	int pp;
	scanf_s("%d", &pp);
	printf("请输入初始数字\n");
	for (i = 0; i < pp; i++)
	{
		scanf_s("%d", &f);
		append(&h, f);
	}
	printf("初始顺序表是：\n");
	dis(h);
	printf("\n");
	int c;
	printf("请输入要在尾部插入的数字\n");
	scanf_s("%d",&c);
	append(&h,c);
	printf("尾部插入后的顺序表时:\n");
	/*调运se函数打印顺序表*/
	dis(h);
	 printf("\n");
	/*调运cha函数查找x的位置*/
	int m,g;
	printf("请输入要查找的元素\n");
	scanf_s("%d",&m);
	g=cha(&h,m);
	 printf("%d的位置是 %d  \n",m,g);
	/*调运huo函数获取顺序表中第i个值*/
	int j,cc;
	printf("请输入要获取的值的位置\n");
	scanf_s("%d",&j);
	cc=huo(&h,j);
	printf("%d的位置在  %d  \n",j,cc);
	fun(&h);
	dis(h);
	system("pause");
	return 0;
}