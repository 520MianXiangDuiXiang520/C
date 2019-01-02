#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <string.h>


struct info {
	//个人信息
	char name[20];
	int generation;      //第几代
	char date_birth[9];  //例如20181205
	char place_birth[20];//出生地
	char date_death[9];  //逝世日期,未逝世则记为00000000
	int sex;             //0指女性，1为男性
	char profession[15]; //职业
	char spouse_name[20];//配偶姓名
	char parent_name[20];//双亲姓名
};
struct person {
	info record;    //族谱个人节点
	person *child;  //指向长子
	person *brother;//指向一个兄弟
};

//顺序栈的头文件
typedef struct stack
{
	person *data[100];
	int tag[100]; /*为栈中的每个元素设置的标记*/
	int top; /*栈顶指针*/
} seqstack;


person *create_family(FILE *fp)
{
	person *t = (person*)malloc(sizeof(person));
	fscanf(fp, "%s", t->record.name);    //姓名后的标记为空格' '
	if (t->record.name[0] == '#')          //姓名为#时，建立空树
		t = NULL;
	else
	{
		fscanf(fp, "%d%s%s%s%d%s%s%s", &t->record.generation,
			t->record.date_birth, t->record.place_birth, t->record.date_death,
			&t->record.sex, t->record.profession, t->record.spouse_name,
			t->record.parent_name);
		t->child = create_family(fp);
		t->brother = create_family(fp);
	}
	return t;
}

void preorder(person *t)
{
	if (t)
	{
		printf("%s \n", t->record.name);
		preorder(t->brother);
		preorder(t->child);
	}
}


// 二叉树的非递归实现
void push(seqstack *s, person *t)  /*进栈*/
{
	s->data[s->top] = t;
	s->top++;
}

person *pop(seqstack *s)
{
	if (s->top != 0)
	{
		s->top--;
		return (s->data[s->top]);
	}
	else
		return NULL;
}

void draw(int x, int y, char *c) {
	circle(x, y, 10); 
	outtextxy(x - 5, y - 5, *c);   //输出元素
}

int SuoJin = 1;
int Left = 50;
int Top = 35;

void imctree(person * tree,int x, int y)
{
	if (tree != NULL)
		draw(x, y, tree->record.name);
	if (tree->child != NULL) {
		SuoJin++;//缩减值自增1
		line(x - 14, y + 14, x - Left, y + 100 - 20); Sleep(100);//画线并暂停100ms
		imctree(tree->child, x - Left, y + 100);//递归调用右子树
	}
	if (tree->brother != NULL)
	{
		SuoJin++;//缩减值自增1
		line(x + 14, y + 14, x + Left, y + 100 - 20); Sleep(100);//画线并暂停100ms
		imctree(tree->brother, x + Left, y + 100);//递归调用左子树
	}
	
	SuoJin--;

	}
	

person add(person * tree, info newperson)
{

}

int main()
{
	person * t;
	char file[20] = "02.txt";
	FILE *fp = fopen(file,"r");
	t=create_family(fp);
	initgraph(1280,640);
	imctree(t, 640, 30);
	system("pause");
	return 0;
}