# include <graphics.h>      // 引用图形库头文件
# include <conio.h>
# include<stdio.h>
# include<stdlib.h>
# include<math.h>
# include<Windows.h>
# include<queue>

# define width 1280         /*定义页面宽度*/
# define height 660         /*定义页面高度*/
# define buttleNum 5       /*定义按钮数量*/
# define Frame 100          /*定义边框宽度*/
# define Spacing 30         /*定义按钮间间距*/
# define Buttom 60          /*定义到底部的距离*/
# define MenuNum 5          /*定义查询菜单数量*/
# define relationMenuNum 6  /*定义关系菜单的数量*/

struct info
{
	//个人信息
	char name[20];
	int generation;      //第几代
	char data_birth[9];  //例如20181205
	char place_birth[20];//出生地
	char data_death[9];  //逝世日期,未逝世则记为00000000
	char sex[9];             //0指女性，1为男性
	char profession[15]; //职业
	char spouse_name[20];//配偶姓名
	char parent_name[20];//双亲姓名
};

struct person
{
	info record;    //族谱个人节点
	person *child;  //指向长子
	person *brother;//指向一个兄弟
};

typedef struct stack {
	person *data[100];
	int tag[100];
	int top;
}seqstack;
void push(seqstack *s, person *t)//压栈
{
	s->data[s->top] = t;
	s->top++;
}
person *  pop(seqstack *s)//出栈
{
	if (s->top != 0)
	{
		s->top--;
		return s->data[s->top];
	}
	else
		return NULL;
}


/*全局变量*/
int buttleWidth = ((width - 200) / buttleNum) - Spacing;   /*定义按钮大小*/
int buttleHeight = 40;
int MenuWidth = ((width - 200) / MenuNum) - Spacing;   /*定义菜单按钮大小*/
int MenuHeight = 30;   /*定义菜单按钮高度*/
int MouseFindNum = 0;   /*记录查找单击次数*/
int MouseAddNum = 0;   /*记录添加按钮的单击次数*/
int MouseTreeNum = 0;   /*定义查看单机次数*/
int MenuSpacing = 15;   /*初始化菜单间间隔*/

/*添加，查询相关全局变量*/

char name[100];   /*定义用户输入的用来查询的姓名*/
char year[100];   /*定义用户输入的用来查询的年月日*/
char finddeath[100];
char findprofe[100];
char findspouse[100];
char gener[20];
char getfather[20];
char addName[20];
int addGeneration;         /*第几代*/
char addData_birth[20];    /*生日*/
char addPlace_birth[20];   /*出生地*/
char addSex[20];                /*0 女性 1 男性*/
char addProfession[20];    /*职业*/
char addSpouse_name[20];   /*配偶姓名*/
char addParent_name[20];   /*双亲姓名*/
char getInfo[100];   /*获取用户输入的信息*/
char getGeneration[20];   /*获取用户输入的代数*/
person *newpeople = NULL;
int relationMenuWidth = (width - 2 * Frame) / 3;   /*定义关系菜单宽度*/
int relationMenuHeight = 400 / relationMenuNum - 6;   /*定义关系菜单高度*/
char findfather[30];
bool ifgetName;
bool ifgetfather;

/*以下全局变量用来定义树的左右上下间隔，调用位置：imctree()  */

int Left = 50;   /*定义画树时左右间距*/
int Top = 10;   /*定义画树时上下间距*/
int SuoJin = 1;   /*定义每次缩进的倍数*/

/*以下全局变量用来拼接输出时的字符串，调用位置：display() */

/*创建*/
person *create_family(FILE *fp)
{
	person *t = (person*)malloc(sizeof(person));
	fscanf(fp, "%s", t->record.name);    //姓名后的标记为空格' '
	if (t->record.name[0] == '#')          //姓名为#时，建立空树
		t = NULL;
	else
	{
		fscanf(fp, "%d%s%s%s%s%s%s%s", &t->record.generation,
			t->record.data_birth, t->record.place_birth, t->record.data_death,
			&t->record.sex, t->record.profession, t->record.spouse_name,
			t->record.parent_name);
		t->child = create_family(fp);
		t->brother = create_family(fp);
	}
	return t;
}



/*查找*/
using namespace std;
void display(person *g)//输出
{
	fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*清空输出区域*/
	char bir[200] = "生日：";
	char na[200] = "姓名：";
	char sx[200] = "性别：";
	char csd[200] = "出生地：";
	char dxxm[200] = "配偶姓名: ";
	char ds[200] = "第几代：";
	char fqxm[200] = "父亲姓名：";
	char zy[200] = "职业：";
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 25;
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	_tcscpy_s(f.lfFaceName, _T("黑体"));    // 设置字体为“黑体”
	settextstyle(&f);

	outtextxy( 400, Buttom + 20, strcat(na,g->record.name));
	
	if(strcmp(g->record.sex,"1")==0)
		outtextxy(400, Buttom + 50,strcat(sx,"男"));
	else
		outtextxy(400, Buttom + 50, strcat(sx,"女"));
	//outtextxy(400, Buttom + 50, strcat(sx, g->record.sex));
	outtextxy( 400, Buttom + 80, strcat(bir,g->record.data_birth));
	outtextxy( 400, Buttom + 110, strcat(csd,g->record.place_birth));
	outtextxy( 400, Buttom + 140, strcat(zy,g->record.profession));
	outtextxy(400, Buttom + 170, strcat(dxxm,g->record.spouse_name));
	outtextxy( 400, Buttom + 200, strcat(fqxm,g->record.parent_name));

	/*printf("姓名：%s\n", g->record.name);
	printf("性别：\n", g->record.sex);
	printf("出生日期：%s\n", g->record.data_birth);
	printf("出生地：%s\n", g->record.place_birth);
	printf("职业：%s\n", g->record.profession);
	printf("配偶姓名：%s\n", g->record.spouse_name);
	printf("父母姓名：%s\n\n", g->record.parent_name);*/
}
void modify(person *p, char *info_type, char *info_content)
{
	//p为个人节点，info_type为将要修改的信息类型，info_content为修改后的内容
	if (strcmp(info_type , "name")==0)
		strcpy(p->record.name, info_content);
	else if (strcmp(info_type, "generation")==0)
	{
		p->record.generation = int(info_content);
	}
	else if (strcmp(info_type, "datebirth")==0)
		strcpy(p->record.data_birth, info_content);
	else if (strcmp(info_type, "placebirth") == 0)
		strcpy(p->record.place_birth, info_content);
	else if (strcmp(info_type, "datedeath")==0)
		strcpy(p->record.data_death, info_content);
	else if (strcmp(info_type, "sex")==0)
		strcpy(p->record.sex, info_content);
	else if (strcmp(info_type, "profession")==0)
		strcpy(p->record.profession, info_content);
	else if (strcmp(info_type, "parentname")==0)
		strcpy(p->record.parent_name, info_content);
	display(p);
}
person *findname(person *t, char findname[20] )//根据姓名查找
{
	seqstack *s;
	person *k;
	k = (person *)malloc(sizeof(person));
	k = t;
	s = (seqstack *)malloc(sizeof(seqstack));
	s->top = 0;
	while ((k != NULL) || (s->top != 0))      //结点不为空结点或栈不为空
	{
		while (k)
		{
			if (strcmp(k->record.name, findname) == 0)//判断与已知姓名与结点姓名是否相等
			{
				//display(k);
				return k;  //若相等则将该节点返回
			}
			push(s, k); //不相等将当前节点压栈
			k = k->child; //指向孩子结点
		}
		if (s->top > 0)
		{
			k = pop(s);//栈不为空时弹出该节点
			k = k->brother;  //指向兄弟结点
		}
	}
	 return NULL;
}
person *findbirth(person *t, char birthday[20])//根据生日查找
{
	seqstack *s;
	person *k;
	k = (person *)malloc(sizeof(person));
	k = t;
	s = (seqstack *)malloc(sizeof(seqstack));
	s->top = 0;
	while ((k != NULL) || (s->top != 0))
	{
		while (k)
		{
			if (strcmp(k->record.data_birth, birthday) == 0)
			{
				display(k);
				return k;
			}
			push(s, k);
			k = k->child;
		}
		if (s->top > 0)
		{
			k = pop(s);
			k = k->brother;
		}
	}
	 return NULL;
}

person *fdeathdata(person *t, char deathday[20])//根据逝世日期查找
{
	seqstack *s;
	person *k;
	k = (person *)malloc(sizeof(person));
	k = t;
	s = (seqstack *)malloc(sizeof(seqstack));
	s->top = 0;
	while ((k != NULL) || (s->top != 0))
	{
		while (k)
		{
			if (strcmp(k->record.data_death, deathday) == 0)
			{
				display(k);
				return k;
			}
			push(s, k);
			k = k->child;
		}
		if (s->top > 0)
		{
			k = pop(s);
			k = k->brother;
		}
	}
	outtextxy(300, Buttom + 20, "没有找到此人信息!");
	return NULL;
}

person *findpro(person *t, char findprofession[50])//根据职业查找
{
	seqstack *s;
	person *k;
	k = (person *)malloc(sizeof(person));
	k = t;
	s = (seqstack *)malloc(sizeof(seqstack));
	s->top = 0;
	while ((k != NULL) || (s->top != 0))
	{
		while (k)
		{
			if (strcmp(k->record.profession, findprofession) == 0)
			{
				display(k);
				return k;
			}
			push(s, k);
			k = k->child;
		}
		if (s->top > 0)
		{
			k = pop(s);
			k = k->brother;
		}
	}
	outtextxy(300, Buttom + 20, "没有找到此人信息!");
	return NULL;
}


person *findspous(person *t, char findspouse[50])//根据配偶姓名查找
{
	seqstack *s;
	person *k;
	k = (person *)malloc(sizeof(person));
	k = t;
	s = (seqstack *)malloc(sizeof(seqstack));
	s->top = 0;
	while ((k != NULL) || (s->top != 0))
	{
		while (k)
		{
			if (strcmp(k->record.spouse_name, findspouse) == 0)
			{
				display(k);
				return k;
			}
			push(s, k);
			k = k->child;
		}
		if (s->top > 0)
		{
			k = pop(s);
			k = k->brother;
		}
	}
	//printf("没有找到此人信息\n");
	outtextxy(300, Buttom + 20, "没有找到此人信息!");
	return NULL;
}


void children(person *q,char dai[10])//寻找后三代任意一代的信息
{
	int jianju = 80;
	int jianju2 = 80;
	int jianju3 = 80;
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 25;
	settextstyle(&f);
	queue<person*>qq;
	person *p = NULL, *r = NULL;
	p = (person *)malloc(sizeof(person));
	r = (person *)malloc(sizeof(person));
	r = q;
	if (!q->child)  //判断当前节点是否有孩子结点
	{
		RECT r = { Frame + 15, 75,width - 135,  height - 215 };
		//fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*清空输出区域*/
		drawtext("他，没有孩子...", &r, DT_CENTER | DT_VCENTER);
		return;
	}
	else
	{
		if (strcmp(dai, "1")==0) //如果查询的是第一代信息的话输出
		{
			outtextxy(300, Buttom + 20, "他的孩子有：");
			/*printf("%s的孩子有", r->record.name);*/
		}
		q = q->child;
		if (strcmp(dai, "1")==0)   //查询的是第一代输出
			outtextxy(400, Buttom + 50, q->record.name); //输出第一个孩子
			/*display(q);*/

		qq.push(q); //将第一个孩子压入队列
		while (q->brother) //判断第一个孩子是否有兄弟节点
		{
			q = q->brother;
			qq.push(q);   //将兄弟压入队列
			if (strcmp(dai, "1")==0)
				outtextxy(400, Buttom + jianju, q->record.name);//如果查询的是第一代输出兄弟
				//display(q);
			jianju += 30;
		}                    //此时全部儿子都进入了队列
	}
	if (qq.front()->child) 
		p = qq.front()->child;
	int kk = 0;
	while (!qq.empty() && (qq.front() != p))  //当队首结点不等于第一个孙子
	{
		q = qq.front(); qq.pop();  //将所有的儿子依次出队对每一个儿子遍历
		if (q->child)
		{
			q = q->child;
			qq.push(q);  //将儿子的儿子入队
			if (strcmp(dai, "2")==0)
			{
				outtextxy(400, Buttom + jianju2, q->record.name);  //如果查询的是第二代信息则输出
				jianju2 += 30;
				kk++;
			}
			while (q->brother)  //判断孙子是否有兄弟
			{
				q = q->brother;
				qq.push(q); //压入队列
				if (strcmp(dai, "2")==0)
				{
					//display(q);
					outtextxy(400, Buttom + jianju2, q->record.name);//如果查询的是第二代则输出
					jianju2 += 30;
					kk++;
				}

			}
		}
	}
	if ((kk == 0) && (strcmp(dai, "2")==0))
	{
		//printf("%s没有孙子\n", r->record.name);
		RECT r = { Frame + 15, 75,width - 135,  height - 215 };
		drawtext("他，没有孙子...", &r, DT_CENTER | DT_VCENTER);
		return;
	}

	int bb = 0;
	while (!qq.empty())  //如果队列不为空
	{
		q = qq.front(); 
		qq.pop();//将孙子依次出队 并遍历
		if (q->child)
		{
			q = q->child;
			qq.push(q);//如果孙子有孩子则压入队列
			if (strcmp(dai, "3")==0)      //如果查询的是第三代则输出
			{
				//display(q);
				outtextxy(400, Buttom + jianju3, q->record.name);
				jianju3 += 30;
				bb++;
			}
			while (q->brother) //重孙是否有兄弟节点
			{
				q = q->brother;
				qq.push(q); //查询的是第三代则输出
				if (strcmp(dai, "3")==0)
				{
					//display(q);
					outtextxy(400, Buttom + jianju3, q->record.name);
					jianju3 += 30;
					bb++;
				}

			}
		}
	}
	if ((bb == 0) && (strcmp(dai, "3")==0))
	{
		//printf("%s没有重孙子\n", r->record.name);
		RECT r = { Frame + 15, 75,width - 135,  height - 215 };
		drawtext("他，没有重孙子...", &r, DT_CENTER | DT_VCENTER);
	}
		
}

void brother(person *t, person *q)//寻找兄弟信息
{
	int jianju1 = 80;
	seqstack *s; int a = 0, k = 0;
	s = (seqstack *)malloc(sizeof(seqstack));
	s->top = 0;
	while ((t) || (s->top > 0))
	{
		while (t)
		{
			push(s, t);
			s->tag[s->top - 1] = 0;
			t = t->child;
		}
		while ((s->top > 0) && (s->tag[s->top - 1] == 1))
		{
			t = pop(s);
			if (strcmp(t->record.name, q->record.name) == 0)  //通过姓名找到查询结点
			{
				if (t->brother) //判断该节点是否有兄弟节点
				{
					/*printf("%s的兄弟为\n", q->record.name);*/
					outtextxy(300, Buttom + 20, "他的兄弟为：");
					k++;
				}
				while (t->brother)//如果有兄弟节点  将兄弟结点以及兄弟的兄弟结点全部输出
				{
					t = t->brother;
					//display(t);
					outtextxy(400, Buttom + jianju1, t->record.name);
					jianju1 += 30;
					a++;
				}
				jianju1 = 50;
				if ((s->tag[s->top - 1] == 1) && (s->top > 0) && (k == 0))//如果栈中结点被标记为1 并且没有兄弟节点
				{
					/*printf("%s的兄弟为\n", q->record.name);*/
					outtextxy(300, Buttom + 20, "他的兄弟为：");
				}
				while ((s->tag[s->top - 1] == 1) && (s->top > 0)) //将标记为1的结点全部弹出栈并输出
				{
					t = pop(s);
					//display(t); 
					outtextxy(400, Buttom + jianju1, t->record.name);
					jianju1 += 30;
					a++;
				}
				jianju1 = 50;
				if (a == 0)   //如果没有输出过任何兄弟
					/*printf("%s无兄弟\n", q->recorde.name); */
					outtextxy(300, Buttom + 20, "他是独生子女...");
				return;
			}
		}
		if (s->top > 0)
		{
			t = s->data[s->top - 1];
			s->tag[s->top - 1] = 1;
			t = t->brother;
		}
		else t = NULL;
	}

}

void parents(person *t, person *q)//查找父母信息
{
	seqstack *s;
	s = (seqstack *)malloc(sizeof(seqstack));
	s->top = 0;
	while ((t) || (s->top > 0))
	{
		while (t)
		{
			push(s, t);
			s->tag[s->top - 1] = 0;
			t = t->child;
		}
		while ((s->top > 0) && (s->tag[s->top - 1] == 1))
		{
			t = pop(s);
			if (strcmp(t->record.name, q->record.name)==0)
			{
				while ((s->tag[s->top - 1] == 1) && (s->top > 0)) 
					t = pop(s);
				if (s->top > 0)
				{
					t = pop(s);
					//printf("%s的父母信息为\n", q->recorde.name);
					outtextxy(300, Buttom + 20, "他的父亲为：");
					outtextxy(400, Buttom + 80, t->record.name);
					//display(t);
					return;
				}
				else 
					//printf("没有%s的父亲信息\n", q->record.name);
					outtextxy(300, Buttom + 20, "父母信息未被录入族谱！！！");
			}
		}
		if (s->top > 0)
		{
			t = s->data[s->top - 1];
			s->tag[s->top - 1] = 1;
			t = t->brother;
		}
		else t = NULL;
	}
}

void ancestor(person *t, person *q)//寻找祖先信息
{
	seqstack *s; int a = 0;
	s = (seqstack *)malloc(sizeof(seqstack));
	s->top = 0;
	int jianju = 80;
	while ((t != NULL) || (s->top != 0))
	{
		while (t)
		{
			push(s, t);
			s->tag[s->top - 1] = 0;
			t = t->child;
		}
		while ((s->top > 0) && (s->tag[s->top - 1] == 1))
		{
			t = pop(s);
			if (strcmp(t->record.name, q->record.name) == 0)
			{
				if (s->top > 0)
					outtextxy(300, Buttom + 20, "他的祖先为：");
					//printf("%s的祖先有\n", q->record.name);
				while (s->top > 0)
				{
					if (s->tag[s->top - 1] != 1)
					{
						t = pop(s);
						outtextxy(400, Buttom + jianju, t->record.name);
						jianju += 30;
						//display(t);
						a++;
					}
					else t = pop(s);
				}
				return;
			}
		}
		if (s->top > 0)
		{
			t = s->data[s->top - 1];
			s->tag[s->top - 1] = 1;
			t = t->brother;
		}
		else t = NULL;
	}
	if (a == 0) 
		outtextxy(300, Buttom + 20, "祖先信息未被录入族谱！！！");
		//printf("没有%s的祖先的信息\n", q->record.name);
}

void children1(person *q)//寻找孩子信息
{
	int jianju = 80;
	if (!q->child)  
		outtextxy(300, Buttom + 20, "他，没有孩子...");
	else
	{
		//printf("%s的孩子有\n", q->record.name);
		outtextxy(300, Buttom + 20,  "他的孩子有：");
		q = q->child;
		//display(q);
		outtextxy(400, Buttom + jianju, q->record.name);
		jianju += 30;
		while (q->brother)
		{
			q = q->brother;
			//display(q);
			outtextxy(400, Buttom + jianju, q->record.name);
			jianju += 30;
		}
	}
}

/*画圈*/
void draw(int x, int y, char *c) {
	circle(x, y, 10);
	outtextxy(x - 5, y - 5, *c);   //输出元素
}
/*递归画树*/
void imctree(person * tree, int x, int y)
{
	if (tree != NULL)
		draw(x, y, tree->record.name);
	if (tree->child != NULL) {
		SuoJin++;
		line(x - 14, y + 14, x - Left, y + 50);
		Sleep(100);
		imctree(tree->child, x - Left, y + 70);
	}
	if (tree->brother != NULL)
	{
		SuoJin++;
		line(x + 14, y + 14, x + Left, y + 50);
		Sleep(100);
		imctree(tree->brother, x + Left, y + 70);
	}

	SuoJin--;

}

/*初始化图形界面*/

void initImg()
{
	
	IMAGE imgbk;
	loadimage(&imgbk, _T("E:/vs2019/数据结构课设/数据结构课设/10.jpg"), 1280, 660);
	putimage(0, 0, &imgbk);//显示图片

	//loadimage(NULL, _T("10.jpg"), width, height);    /*图片填充*/
	//fillrectangle(Frame, 60, width - 100, height - 200);   /*绘制输出区域*/
	IMAGE img;
	loadimage(&img, _T("E:/vs2019/数据结构课设/数据结构课设/11.jpg"), 1080, 400);
	putimage(100, 60, &img);   //显示图片

}

/*绘制按钮*/

void DrawButtle()
{
	LOGFONT f;
	gettextstyle(&f);                   
	f.lfHeight = 35; 
	settextcolor(BLACK);
	int left = Frame + Spacing / 2;
	int top = height - 200 + Buttom;
	int i;
	char s0[15] = "查找";
	char s1[15] = "插入";
	char s2[15] = "退出";
	char s3[15] = "查看";
	char s4[15] = "修改";
	char *s[] = { s0,s1,s2,s3,s4};
	for (i = 0; i < buttleNum; i++)
	{
		fillrectangle(left, top, left + buttleWidth, top + buttleHeight);
		outtextxy(left + 65, top + 6, s[i]);
		left = left + buttleWidth + Spacing;		
	}
}

/*绘制查询菜单*/

void queryMenu()
{
	int i;
	char s0[15] = "根据姓名查询";
	char s1[15] = "根据出生日期";
	char s2[15] = "根据逝世日期";
	char s3[15] = "根据职业查询";
	char s4[30] = "根据配偶查询";
	char *s[] = { s0,s1,s2,s3,s4 };
	int g;
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 25;
	settextstyle(&f);
	int menuLeft = Frame + Spacing / 2;   /*定义菜单按钮初始化位置*/
	int MenuTop = height - 2*Frame + Buttom + buttleHeight + 20;   /*菜单初始化高度*/
	
	for (i = 0; i < MenuNum; i++)
	{
		fillrectangle(menuLeft, MenuTop, menuLeft + MenuWidth, MenuTop + MenuHeight);
		outtextxy(menuLeft + 15, MenuTop + 6, s[i]);
		menuLeft = menuLeft + MenuWidth + MenuSpacing;
	}
}

/*插入*/

person addinfo(person * newPeople)
{
	bool ifaddName;
	bool ifaddDataBirth;
	bool ifaddPlaceBirth;
	bool ifaddSex;
	bool ifaddProfession;
	bool ifaddSpouseName;
	bool ifaddparent;

	/*输入要插入的节点信息*/
	newPeople = (person*)malloc(sizeof(person));
	ifaddName = InputBox(addName, 20, "", "请输入你要添加的成员的姓名", "查询", 300);
	sscanf(addName, "%s", newPeople->record.name);   /*获取用户输入的字符串*/
	if (ifaddName)
	{
		ifaddDataBirth = InputBox(addData_birth, 20, "", "请输入出生日期", "查询", 300);
		sscanf(addData_birth, "%s", newPeople->record.data_birth);   /*获取用户输入的字符串*/
	}	
	if (ifaddDataBirth)
	{
		ifaddPlaceBirth= InputBox(addPlace_birth, 20, "", "请输入出生地", "查询", 300);
		sscanf(addPlace_birth, "%s", newPeople->record.place_birth);   /*获取用户输入的字符串*/
	}
	if (ifaddPlaceBirth)
	{
		ifaddSex= InputBox(addSex, 20, "", "请输入性别", "查询", 300);
		sscanf(addSex, "%d", newPeople->record.sex);   /*获取用户输入的字符串*/
	}
	if (ifaddSex)
	{
		ifaddProfession= InputBox(addProfession, 20, "", "请输入职业", "查询", 300);
		sscanf(addProfession, "%s", newPeople->record.profession);   /*获取用户输入的字符串*/
	}
	if (ifaddProfession)
	{
		ifaddSpouseName = InputBox(addSpouse_name, 20, "", "请输入配偶", "查询", 300);
		sscanf(addSpouse_name, "%s", newPeople->record.spouse_name);   /*获取用户输入的字符串*/
	}
	if (ifaddSpouseName)
	{
		ifaddparent = InputBox(addParent_name, 20, "", "请输入父母姓名", "查询", 300);
		sscanf(addParent_name, "%s", newPeople->record.parent_name);   /*获取用户输入的字符串*/
	}
	if (ifaddparent)
	{
		
		LOGFONT f;
		gettextstyle(&f);                     
		f.lfHeight =35; 
		settextcolor(BLACK);
		setbkmode(TRANSPARENT);
		_tcscpy_s(f.lfFaceName, _T("黑体"));    
		settextstyle(&f);
		char add[] = "新成员信息录入成功\n欢迎新成员加入！！";
		RECT r = { Frame + 15, 75,width - 135,  height - 215 };
		drawtext(add, &r, DT_CENTER | DT_VCENTER);
	}
	return *newPeople;
}

void write(FILE *fp, person *t)
{
	//新树写入文件（递归-前序遍历）
	//fp为指向文件开头的指针,t为树的根节点
	fprintf(fp, "%s ", t->record.name);//姓名后的标记为空格' '
	if (t->record.name[0] != '#')          //姓名不为#时，继续写入
		fprintf(fp, "%d\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", t->record.generation,
			t->record.data_birth, t->record.place_birth, t->record.data_death,
			t->record.sex, t->record.profession, t->record.spouse_name,
			t->record.parent_name);
	if (t->child == NULL)
		fprintf(fp, "%s ", "#");
	else
		write(fp, t->child);    //写入长子节点
	if (t->brother == NULL)
		fprintf(fp, "%s ", "#");
	else
		write(fp, t->brother);  //写入兄弟节点
	//fseek(fp, 0, SEEK_SET);
}





/*  绘制关系菜单*/
void relationshipMenu()
{
	int g;
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 25; 
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	_tcscpy_s(f.lfFaceName, _T("黑体"));    // 设置字体为“黑体”
	settextstyle(&f);
	char r0[15] = "查找父母";
	char r1[15] = "查找祖先";
	char r2[15] = "查找兄弟";
	char r3[15] = "查找孩子";
	char r4[15] = "查找后代";
	char r5[15] = "个人信息";
	char *p[] = {r0,r1,r2 ,r3,r4,r5};
	int relaMenuLeft = Frame + (width - 2 * Frame) / 3;   /*定义关系菜单左侧坐标*/
	int relaMenuRight = relaMenuLeft + relationMenuWidth;   /*定义关系菜单右侧左边*/
	int relaMenuTop = 63;   /*定义第一个关系按钮顶部坐标*/
	int relaMenuButton = relaMenuTop + relationMenuHeight;   /*定义关系按钮底部坐标*/
	fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*清空输出区域*/
	for ( g = 0; g < relationMenuNum; g++)
	{
		setfillcolor(RGB(72, 81, 81));
		fillrectangle(relaMenuLeft, relaMenuTop, relaMenuRight, relaMenuButton);
		outtextxy(relaMenuLeft+120, relaMenuTop + 26, p[g]);
		//setfillcolor(RGB(255, 255, 255));
		relaMenuTop = relaMenuTop + relationMenuHeight+3;
		relaMenuButton = relaMenuTop + relationMenuHeight;
	}
	setfillcolor(RGB(255,255,255 ));
}


/* 鼠标事件*/

char * GetMouse(char out[500],person*t)
{
	
	MOUSEMSG mousemsg;		/* 定义鼠标消息*/
	while (true)
	{
		mousemsg = GetMouseMsg();   /*获取一条鼠标消息*/
		int x, y;
		bool mklButton;
		x = mousemsg.x;   /*获取鼠标当前x坐标*/
		y = mousemsg.y;   /*获取鼠标当前y坐标*/
		mklButton = mousemsg.mkLButton;   /*获取鼠标当前左键是否按下*/

		if ((y > height - 2 * Frame + Buttom) && (y < height - 2 * Frame + Buttom + buttleHeight))
		{
			/*查询*/
			if ((x > Frame + Spacing / 2) && (x < Frame + Spacing / 2 + buttleWidth) && mklButton)   /*鼠标在第一个按钮上单击左键时，激发鼠标事件 1*/
			{
				fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*清空输出区域*/
				MouseFindNum++;
				if (MouseFindNum % 2 != 0)
				{
					queryMenu();
				}
				else   /*再次点击时重新绘制界面，关闭菜单*/
				{
					fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*清空输出区域*/
					initImg();
					DrawButtle();
					GetMouse(out,t);
				}
			}
			/*插入*/
			else if ((x > (Frame + Spacing / 2) + buttleWidth + Spacing) && (x < (Frame + Spacing / 2) + 2 * buttleWidth + Spacing) && mklButton)
			{
				fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*清空输出区域*/
				ifgetfather = InputBox(getfather, 20, "", "请输入你要添加的成员的父亲", "查询", 300);
				sscanf(getfather, "%s", findfather);   /*findfather 是根据用户输入的父亲姓名，用来作为findname()的参数找到要插入的人的父亲节点*/
				person *newone= (person*)malloc(sizeof(person));
				if (ifgetfather)
				{
					newone = &addinfo(newpeople);   /*newonw就是要插入的节点信息*/
					person *addfather = findname(t, getfather);
					if (addfather->child == NULL)
						addfather->child = newone;
					else
					{
						addfather = addfather->child;
						while (addfather->brother != NULL)
							addfather = addfather->brother;
						addfather->brother = newone;
					}
					//addfather->child = newone;
					/*person *s=add_person(t,getfather,*newone);*/

				}
				FlushMouseMsgBuffer();   /*清空鼠标缓存区*/

			}
			/*退出*/
			else if ((x > (Frame + Spacing / 2) + 2 * (buttleWidth + Spacing)) && (x < (Frame + Spacing / 2) + 2 * (buttleWidth + Spacing) + buttleWidth) && mklButton)
			{
				exit(1);
			}
			/*画树*/
			else if ((x > (Frame + Spacing / 2) + 3 * buttleWidth + Spacing) && (x < (Frame + Spacing / 2) + 3 * (buttleWidth + Spacing) + buttleWidth) && mklButton)
			{
				LOGFONT f;
				gettextstyle(&f);                    
				f.lfHeight = 15;
				settextcolor(BLUE);
				setbkmode(TRANSPARENT);
				_tcscpy_s(f.lfFaceName, _T("黑体"));   
				settextstyle(&f);
				setfillcolor(RGB(0,0,0));
				fillrectangle(0, 60, width, height - 2 * Frame);   
				MouseTreeNum++;
				setlinecolor(BLUE);
				if (MouseTreeNum % 2 != 0)
				{
					imctree(t, 640, 60+10+5);
					setfillcolor(RGB(255, 255, 255));
				}
				else
				{
					setfillcolor(RGB(255, 255, 255));
					setlinecolor(RGB(255, 255, 255));
					fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*清空输出区域*/
					initImg();
					DrawButtle();
					GetMouse(out,t);
				}
			}
			/*修改*/
			else if ((x > (Frame + Spacing / 2) + 4 * buttleWidth + Spacing) && (x < (Frame + Spacing / 2) + 4 * (buttleWidth + Spacing) + buttleWidth) && mklButton)
			{
				person *changeper;
				bool ifchangerName;
				bool ifchangeinfo;
				bool ifchangenewinfo;
				char getChangename[30];
				char GetChangeName[30];   /*转换后的输入*/
				char getChangeinfo[30];
				char GetChangeInfo[30];
				char getNewinfo[30];
				char GetNewInfo[30];
				fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*清空输出区域*/
				ifchangerName = InputBox(getChangename, 30, "请输入你要修改的人的姓名：", "修改信息","修改", 300);
				sscanf(getChangename, "%s", GetChangeName);
				changeper = findname(t,GetChangeName);   /*找到要修改的人的节点*/
				if (ifchangerName)
				{
					ifchangeinfo = InputBox(getChangeinfo, 30, "请输入你要修改的信息类型", "修改信息","修改", 300);
					sscanf(getChangeinfo, "%s", GetChangeInfo);
					if (ifchangeinfo)
					{
						ifchangenewinfo=InputBox(getNewinfo, 30, "请输入修改后的信息", "信息修改", "修改", 300);
						sscanf(getNewinfo, "%s", GetNewInfo);
						if (ifchangenewinfo)
						{
							modify(changeper, GetChangeInfo, GetNewInfo);
							char file[20] = "02.txt";
							FILE *fp1 = fopen(file, "r+");
							fseek(fp1, 0, SEEK_SET);
							write(fp1, t);
							//display(changeper);
						}
						FlushMouseMsgBuffer();   /*清空鼠标缓存区*/
					}
				}
			}
		}
		/* 如果单机次数为奇数，说明菜单栏弹出，判断鼠标单击位置*/
		if (MouseFindNum % 2 != 0)
		{
			LOGFONT f;
			gettextstyle(&f);                     // 获取当前字体设置
			f.lfHeight = 25;
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			_tcscpy_s(f.lfFaceName, _T("黑体"));    // 设置字体为“黑体”
			settextstyle(&f);

			if (y > (height - 200 + Buttom + buttleHeight + 20) && y < (height - 200 + Buttom + buttleHeight + 20 + MenuHeight))
			{
				LOGFONT f;
				gettextstyle(&f);                     // 获取当前字体设置
				f.lfHeight = 25; // 设置字体高度
				settextcolor(BLACK);
				setbkmode(TRANSPARENT);
				_tcscpy_s(f.lfFaceName, _T("黑体"));    // 设置字体为“黑体”
				settextstyle(&f);
				/*根据姓名查找*/
				if (x > (Frame + Spacing / 2) && x < (Frame + Spacing / 2 + MenuWidth) && mklButton)
				{
					ifgetName=InputBox(name, 20, "", "请输入你要查询的姓名", "查询", 300);   /*用于以对话框形式获取用户输入*/
					sscanf(name, "%s", getInfo);   /*获取用户输入的字符串*/
					
					RECT r = { Frame + 15, 75,width - 135,  height - 215 };
					FlushMouseMsgBuffer();   /*清空鼠标缓存区*/					
				}
				/*根据出生年月查找*/
				else if (x > (Frame + Spacing / 2) + MenuWidth + MenuSpacing && x < (Frame + Spacing / 2) + 2 * MenuWidth + MenuSpacing && mklButton)
				{
					InputBox(year, 20, "", "请输入你要查询的出生年月", "查询", 300, 0, false);   /*用于以对话框形式获取用户输入*/
					sscanf(year, "%s", getInfo);
					findbirth(t, year);
					FlushMouseMsgBuffer();   /*清空鼠标缓存区*/	
				}
				/*根据逝世日期查找*/
				else if (x > (Frame + Spacing / 2) + 2 * MenuWidth + 2*MenuSpacing && x < (Frame + Spacing / 2) + 3 * MenuWidth +2* MenuSpacing && mklButton)
				{
					InputBox(finddeath, 20, "", "请输入你要查询的逝世年月", "查询", 300, 0, false);   /*用于以对话框形式获取用户输入*/
					sscanf(finddeath, "%s", getInfo);
					fdeathdata(t,finddeath);
					FlushMouseMsgBuffer();   /*清空鼠标缓存区*/
				}
				/*根据职业查找*/
				else if (x > (Frame + Spacing / 2) + 3*MenuWidth +3* MenuSpacing && x < (Frame + Spacing / 2) + 4 * MenuWidth + 3 * MenuSpacing && mklButton)
				{
					InputBox(findprofe, 20, "", "请输入你要查询的职业", "查询", 300, 0, false);   /*用于以对话框形式获取用户输入*/
					sscanf(findprofe, "%s", getInfo);
					findpro(t, findprofe);
					FlushMouseMsgBuffer();   /*清空鼠标缓存区*/
				}
				/*根据配偶姓名查找*/
				else if (x > (Frame + Spacing / 2) + 4 * MenuWidth +4 * MenuSpacing && x < (Frame + Spacing / 2) + 5 * MenuWidth + 4*MenuSpacing && mklButton)
				{
					InputBox(findspouse, 20, "", "请输入你要查询的逝世年月", "查询", 300, 0, false);   /*用于以对话框形式获取用户输入*/
					sscanf(findspouse, "%s", getInfo);
					findspous(t, findspouse);
					FlushMouseMsgBuffer();   /*清空鼠标缓存区*/
				}
			}
		}
		if (ifgetName)   /* 如果输入要查询的姓名后单击确定，则输出关系菜单供选择*/
		{
			
			relationshipMenu();
			ifgetName = FALSE;   /*初始化，避免重复查找不输入*/
			Sleep(60);
			MOUSEMSG mousemsg1;		/* 定义鼠标消息*/
			person *str;
			str = findname(t, name);
			while (true)
			{
				mousemsg1 = GetMouseMsg();   /*获取一条鼠标消息*/
				int x1, y1;
				bool mklButton1;
				bool ifgetGener;
				x1 = mousemsg1.x;   /*获取鼠标当前x坐标*/ 
				y1 = mousemsg1.y;   /*获取鼠标当前y坐标*/
				mklButton1 = mousemsg1.mkLButton;   /*获取鼠标当前左键是否按下*/
				
				if (x1 > Frame + (width - 2 * Frame) / 3 && x1 < Frame + width - 2 * Frame / 3 + relationMenuWidth)   /*判断鼠标是否在关系菜单的宽度区间*/
				{
					if ((y1 > 63) && (y1 < (63 + relationMenuHeight)) && mklButton1)   /*单击第一个按钮查询父母*/
					{
						fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*清空输出区域*/
						parents(t, str);
						break;
					}
					else if ((y1 > (63 + relationMenuHeight + 3)) && (y1 < (63 + 2 * relationMenuHeight + 3)) && mklButton1)   /*单击第二个按钮，查询祖先*/
					{
						fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*清空输出区域*/
						ancestor(t, str);
						break;
					}
					else if ((y1 > (63 + 2 * relationMenuHeight + 6)) && (y1 < (63 + 3 * relationMenuHeight + 6)) && mklButton1)   /*单击第三个按钮，查询兄弟*/
					{
						fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*清空输出区域*/
						brother(t, str);
						break;
					}
					else if ((y1 > (63 + 3 * relationMenuHeight + 9)) && (y1 < (63 + 4 * relationMenuHeight + 9)) && mklButton1)   /*单击第四个按钮，查询孩子*/
					{
						fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*清空输出区域*/
						children1(str);
						break;
					}
					else if ((y1 > (63 + 4 * relationMenuHeight + 12)) && (y1 < (63 + 5 * relationMenuHeight + 12)) && mklButton1)   /*单击第五个按钮，查询后代*/
					{
						fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*清空输出区域*/
						ifgetGener = InputBox(getGeneration, 20, "", "您要查询第几代", "查询", 300);
						sscanf(getGeneration, "%c",gener);
						if (ifgetGener)
						{
							person *find_name = findname(t, name);
							children(find_name, gener);
						}
						break;
					}
					else if ((y1 > (63 + 5 * relationMenuHeight + 12)) && (y1 < (63 + 6 * relationMenuHeight + 12)) && mklButton1)   /*单击第6个按钮，查看个人信息*/
					{
						fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*清空输出区域*/
						
						display(str);
						break;
					}
				}
			}    	
		}
	}
	return getInfo;
}


void title()
{
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 35; // 设置字体高度为 12
	settextcolor(RGB(72,81,81));
	setbkmode(TRANSPARENT);
	_tcscpy_s(f.lfFaceName, _T("黑体"));    // 设置字体为“黑体”
	settextstyle(&f);
	char s[] = "家庭族谱查询";
	outtextxy(15,15, s);
}

int main()
{
	person * t;
	char file[20] = "02.txt";
	FILE *fp = fopen(file, "r+");
	t = create_family(fp);
	char * info[100];
	char out[500];   /*之后把输出结果赋值给out数组*/
	initgraph(width, height);   /*创建绘图窗口*/
	initImg();
	title();
	DrawButtle();
	info[100]=GetMouse(out,t);   /*info数组为输入内容*/
	_getch();              // 按任意键继续
	closegraph();           // 关闭绘图窗口
}
