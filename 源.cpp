#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 100
typedef struct
{
	char name[20];
	int cardid;
	char xueyuan[20];
	char classname[20];
}node;
typedef struct
{
	node a[MAXSIZE + 1];
	int len;
}table;
void init(table *s)
{
	s->len = 0;
}
//读取文件
void creat(table *s, char *filename)
{
	int i;
	FILE *fp;
	fp = fopen(filename, "r");
	if (fp)
	{
		fscanf(fp, "%d", &s->len);
		for (i = 1; i <= s->len; i++)
		{
			fscanf(fp, "%s%d%s%s", &s->a[i].name, &s->a[i].cardid, &s->a[i].xueyuan, &s->a[i].classname);
		}
		fclose(fp);
	}
	else
	{
		s->len = 0;
	}
}
//输出
void display(table *s)
{
	int i;
	printf("         姓名       卡号         学院          班级 \n");
	for (i = 1; i <= s->len; i++)
	{
		printf("%15s%15d%15s%15s\n", s->a[i].name, s->a[i].cardid, s->a[i].xueyuan, s->a[i].classname);
	}
}
//根据卡号排序
table *quicksort(table *s, int left, int right)
{
	int i, j;
	if (left < right)
	{
		i = left;
		j = right;
		s->a[0] = s->a[i];
		do
		{
			while ((s->a[j].cardid > s->a[0].cardid) && i < j)
				j--;
			if (i < j)
			{
				s->a[i] = s->a[j];
				i++;
			}
			while ((s->a[i].cardid < s->a[0].cardid) && i < j)
				i++;
			if (i < j)
			{
				s->a[j] = s->a[i];
				j--;
			}
		} while (i != j);
		s->a[i] = s->a[0];
		quicksort(s, left, i - 1);
		quicksort(s, i + 1, right);
	}
	return s;
}
/*node erfen(table *s, char xibiek[20])
{
	int low = 1, high = s->len, mid;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (strcmp(s->a[mid].xueyuan, xibiek) == 0)
			printf("%15s%15d%15s%15s%15s\n", s->a[mid].name, s->a[mid].xuehao, s->a[mid].phonenumber, s->a[mid].xueyuan, s->a[mid].zhuanye);
		if (strcmp(s->a[mid].zhuanye, xibiek) == 1)
			high = mid - 1;
		else
			low = mid + 1;
	}
}*/
//通过学院检索
void find_xueyuan(table *s)
{
	int i;
	char findbyxueyuan[20];
	printf("\n请输入你要查询的学院：\n");
	scanf("%s", findbyxueyuan);
	int count = 0;
	for (i = 1; i <= s->len; i++)
	{
		if (strcmp(s->a[i].xueyuan, findbyxueyuan) == 0)
		{
			printf("%15s%15d%15s%15s\n", s->a[i].name, s->a[i].cardid, s->a[i].xueyuan, s->a[i].classname);
			count++;
		}
	}
	if (count == 0)
	{
		printf("\n未检索到该学院信息！\n");
	}
}
//通过班级检索
void find_class(table *s)
{
	int i;
	char findbyclass[20];
	printf("\n请输入你要查询的班级：\n");
	scanf("%s", findbyclass);
	int count = 0;
	for (i = 1; i <= s->len; i++)
	{
		if (strcmp(s->a[i].classname, findbyclass) == 0)
		{
			printf("%15s%15d%15s%15s\n", s->a[i].name, s->a[i].cardid, s->a[i].xueyuan, s->a[i].classname);
			count++;
		}
	}
	if (count == 0)
	{
		printf("\n未检索到该班级信息！\n");
	}
}
//通过姓名检索
void find_name(table *s)
{
	int i;
	char findbyname[20];
	printf("\n请输入你要查询的姓名：\n");
	scanf("%s", findbyname);
	int count = 0;
	for (i = 1; i <= s->len; i++)
	{
		if (strcmp(s->a[i].name, findbyname) == 0)
		{
			printf("%15s%15d%15s%15s\n", s->a[i].name, s->a[i].cardid, s->a[i].xueyuan, s->a[i].classname);
			count++;
		}
	}
	if (count == 0)
	{
		printf("\n未检索到该学生信息！\n");
	}
}
//通过卡号检索
void find_cardid(table *s)
{
	int i;
	int findbycardid;
	printf("\n请输入你要查询的卡号：\n");
	scanf("%d", &findbycardid);
	int count = 0;
	for (i = 1; i <= s->len; i++)
	{
		if (s->a[i].cardid == findbycardid)
		{
			printf("%15s%15d%15s%15s\n", s->a[i].name, s->a[i].cardid, s->a[i].xueyuan, s->a[i].classname);
			count++;
		}
	}
	if (count == 0)
	{
		printf("\n未检索到该卡信息！\n");
	}
}
void nume(table *s)
{
	int i;
	printf("\n输入你要进行的操作：\n");
	scanf("%d", &i);
	switch (i)
	{
	case 1:find_cardid(s); break;
	case 2:find_class(s); break;
	case 3:find_name(s); break;
	case 4:find_xueyuan(s); break;
	default:exit(1);
		break;
	}
}
void show()
{
	printf("\n\t\t\t\t*****借书系统*****\t\t\t\t\n");
	printf("\n\t\t\t\t  1. 通过卡号检索\t\t\t\t\n");
	printf("\n\t\t\t\t  2. 通过班级检索\t\t\t\t\n");
	printf("\n\t\t\t\t  3. 通过姓名检索\t\t\t\t\n");
	printf("\n\t\t\t\t  4. 通过学院检索\t\t\t\t\n");
	printf("\n\t\t\t\t  5. 按其退出\t\t\t\t\n");
}
int main()
{
	table *s;
	s = (table *)malloc(sizeof(table));
	init(s);
	printf("输入存放信息的文件名");
	char filename[100];
	scanf("%s", filename);
	creat(s, filename);
	printf("创建的学生借书证信息:\n");
	display(s);
	s = quicksort(s, 1, s->len);
	printf("排序后的借书证信息:\n");
	display(s);
	show();
	while (true)
	{
		nume(s);

	}
	return 0;
}