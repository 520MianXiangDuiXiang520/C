#include <graphics.h>      // 引用图形库头文件
#include <conio.h>
#include<stdio.h>
#include<stdlib.h>
# include<math.h>
#include<Windows.h>

# define width 1280         /*定义页面宽度*/
# define height 660         /*定义页面高度*/
# define buttleNum 4       /*定义按钮数量*/
# define Frame 100          /*定义边框宽度*/
# define Spacing 30         /*定义按钮间间距*/
# define Buttom 60          /*定义到底部的距离*/
# define MenuNum 2          /*定义查询菜单数量*/
# define relationMenuNum 5  /*定义关系菜单的数量*/

/*成员信息结构体定义*/

struct info
{
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
struct person
{
	info record;    //族谱个人节点
	person *child;  //指向长子
	person *brother;//指向一个兄弟
};



/*全局变量*/
int buttleWidth = ((width - 200) / buttleNum) - Spacing;   /*定义按钮大小*/
int buttleHeight = 40;
int MenuWidth = ((width / 2 - 200) / MenuNum) - Spacing;   /*定义菜单按钮大小*/
int MenuHeight = 30;   /*定义菜单按钮高度*/
int MouseFindNum = 0;   /*记录查找单击次数*/
int MouseAddNum = 0;   /*记录添加按钮的单击次数*/
int MouseTreeNum = 0;   /*定义查看单机次数*/
int MenuSpacing = 15;   /*初始化菜单间间隔*/
char name[100];   /*定义用户输入的用来查询的姓名*/
char year[100];   /*定义用户输入的用来查询的年月日*/
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
info *newpeople = NULL;
int relationMenuWidth = (width - 2 * Frame) / 3;   /*定义关系菜单宽度*/
int relationMenuHeight = 400 / relationMenuNum - 6;   /*定义关系菜单高度*/
bool ifgetName;
int Left = 50;   /*定义画树时左右间距*/
int Top = 10;   /*定义画树时上下间距*/
int SuoJin = 1;   /*定义每次缩进的倍数*/

/************************************************************************************
										 创建
*************************************************************************************/

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

/************************************************************************************
										 画树
*************************************************************************************/

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

/************************************************************************************
								   初始化图像界面
**************************************************************************************/

void initImg()
{

	IMAGE imgbk;
	loadimage(&imgbk, _T("E:/vs2019/数据结构课设/10.jpg"), 1280, 660);
	putimage(0, 0, &imgbk);//显示图片

	//loadimage(NULL, _T("10.jpg"), width, height);    /*图片填充*/
	//fillrectangle(Frame, 60, width - 100, height - 200);   /*绘制输出区域*/
	IMAGE img;
	loadimage(&img, _T("E:/vs2019/数据结构课设/11.jpg"), 1080, 400);
	putimage(100, 60, &img);   //显示图片

}

/*************************************************************************************
								   绘制按钮
**************************************************************************************/

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
	char *s[] = { s0,s1,s2,s3 };
	for (i = 0; i < buttleNum; i++)
	{
		fillrectangle(left, top, left + buttleWidth, top + buttleHeight);
		outtextxy(left + 85, top + 6, s[i]);
		left = left + buttleWidth + Spacing;
	}
}

/**************************************************************************************
								  绘制查询菜单
***************************************************************************************/

void queryMenu()
{
	int i;
	int menuLeft = Frame + Spacing / 2;   /*定义菜单按钮初始化位置*/
	int MenuTop = height - 2 * Frame + Buttom + buttleHeight + 20;   /*菜单初始化高度*/

	for (i = 0; i < MenuNum; i++)
	{
		fillrectangle(menuLeft, MenuTop, menuLeft + MenuWidth, MenuTop + MenuHeight);
		menuLeft = menuLeft + MenuWidth + MenuSpacing;
	}
}

/**************************************************************************************
								  插入
***************************************************************************************/

info addinfo(info * newPeople)
{
	bool ifaddName;
	bool ifaddDataBirth;
	bool ifaddPlaceBirth;
	bool ifaddSex;
	bool ifaddProfession;
	bool ifaddSpouseName;
	bool ifaddparent;

	/*输入要插入的节点信息*/
	newPeople = (info*)malloc(sizeof(info));
	ifaddName = InputBox(addName, 20, "", "请输入你要添加的成员的姓名", "查询", 300);
	sscanf(addName, "%s", newPeople->name);   /*获取用户输入的字符串*/
	if (ifaddName)
	{
		ifaddDataBirth = InputBox(addData_birth, 20, "", "请输入出生日期", "查询", 300);
		sscanf(addData_birth, "%s", newPeople->date_birth);   /*获取用户输入的字符串*/
	}
	if (ifaddDataBirth)
	{
		ifaddPlaceBirth = InputBox(addPlace_birth, 20, "", "请输入出生地", "查询", 300);
		sscanf(addPlace_birth, "%s", newPeople->place_birth);   /*获取用户输入的字符串*/
	}
	if (ifaddPlaceBirth)
	{
		ifaddSex = InputBox(addSex, 20, "", "请输入性别", "查询", 300);
		sscanf(addSex, "%d", newPeople->sex);   /*获取用户输入的字符串*/
	}
	if (ifaddSex)
	{
		ifaddProfession = InputBox(addProfession, 20, "", "请输入职业", "查询", 300);
		sscanf(addProfession, "%s", newPeople->profession);   /*获取用户输入的字符串*/
	}
	if (ifaddProfession)
	{
		ifaddSpouseName = InputBox(addSpouse_name, 20, "", "请输入配偶", "查询", 300);
		sscanf(addSpouse_name, "%s", newPeople->spouse_name);   /*获取用户输入的字符串*/
	}
	if (ifaddSpouseName)
	{
		ifaddparent = InputBox(addParent_name, 20, "", "请输入父亲姓名", "查询", 300);
		sscanf(addParent_name, "%s", newPeople->parent_name);   /*获取用户输入的字符串*/
	}
	if (ifaddparent)
	{

		LOGFONT f;
		gettextstyle(&f);
		f.lfHeight = 35;
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

/****************************************************************************************
									绘制关系菜单
*****************************************************************************************/

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
	char *p[] = { r0,r1,r2 ,r3,r4 };
	int relaMenuLeft = Frame + (width - 2 * Frame) / 3;   /*定义关系菜单左侧坐标*/
	int relaMenuRight = relaMenuLeft + relationMenuWidth;   /*定义关系菜单右侧左边*/
	int relaMenuTop = 63;   /*定义第一个关系按钮顶部坐标*/
	int relaMenuButton = relaMenuTop + relationMenuHeight;   /*定义关系按钮底部坐标*/
	for (g = 0; g < relationMenuNum; g++)
	{
		setfillcolor(RGB(72, 81, 81));
		fillrectangle(relaMenuLeft, relaMenuTop, relaMenuRight, relaMenuButton);
		outtextxy(relaMenuLeft + 120, relaMenuTop + 26, p[g]);
		//setfillcolor(RGB(255, 255, 255));
		relaMenuTop = relaMenuTop + relationMenuHeight + 3;
		relaMenuButton = relaMenuTop + relationMenuHeight;
	}
	setfillcolor(RGB(255, 255, 255));
}



/****************************************************************************************
									   鼠标事件
******************************************************************************************/

char * GetMouse(char out[500])
{
	person * t;
	char file[20] = "02.txt";
	FILE *fp = fopen(file, "r");
	t = create_family(fp);
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
					GetMouse(out);
				}
			}
			/*插入*/
			else if ((x > (Frame + Spacing / 2) + buttleWidth + Spacing) && (x < (Frame + Spacing / 2) + 2 * buttleWidth + Spacing) && mklButton)
			{
				fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*清空输出区域*/
				info *newone = (info*)malloc(sizeof(info));
				newone = &addinfo(newpeople);   /*newonw就是要插入的节点信息*/
				FlushMouseMsgBuffer();   /*清空鼠标缓存区*/
				/****************************************
				*                                       *
				*          插入的代码                   *
				*		   变量名：newone               *
				*                                       *
				*****************************************/
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
				setfillcolor(RGB(0, 0, 0));
				fillrectangle(0, 60, width, height - 2 * Frame);
				MouseTreeNum++;
				setlinecolor(BLUE);
				if (MouseTreeNum % 2 != 0)
				{
					imctree(t, 640, 60 + 10 + 5);
					setfillcolor(RGB(255, 255, 255));
				}
				else
				{
					setfillcolor(RGB(255, 255, 255));
					setlinecolor(RGB(255, 255, 255));
					fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*清空输出区域*/
					initImg();
					DrawButtle();
					GetMouse(out);
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

			char s[] = "根据姓名查找";
			outtextxy(Frame + Spacing / 2 + 15, height - 200 + Buttom + buttleHeight + 25, s);
			char d[] = "根据出生查找";
			outtextxy((Frame + Spacing / 2) + MenuWidth + MenuSpacing + 15, height - 200 + Buttom + buttleHeight + 25, d);

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
					ifgetName = InputBox(name, 20, "", "请输入你要查询的姓名", "查询", 300);   /*用于以对话框形式获取用户输入*/
					sscanf(name, "%s", getInfo);   /*获取用户输入的字符串*/
					/****************************************
					*                                       *
					*           按姓名查找的代码            *
					*		    变量名：name                *
					*                                       *
					*****************************************/
					RECT r = { Frame + 15, 75,width - 135,  height - 215 };
					//drawtext(name, &r, DT_CENTER | DT_VCENTER);   /*drawtext中的参数name是查找出结果后返回的字符串*/
					FlushMouseMsgBuffer();   /*清空鼠标缓存区*/
				}
				/*根据出生年月查找*/
				else if (x > (Frame + Spacing / 2) + MenuWidth + MenuSpacing && x < (Frame + Spacing / 2) + 2 * MenuWidth + MenuSpacing && mklButton)
				{
					InputBox(year, 20, "", "请输入你要查询的出生年月", "查询", 300, 0, false);   /*用于以对话框形式获取用户输入*/
					sscanf(year, "%s", getInfo);
					/****************************************
					*                                       *
					*           按日期查找的代码            *
					*		    变量名：year                *
					*                                       *
					*****************************************/
					fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*清空输出区域*/
					RECT r = { Frame + 15, 75,width - 135,  height - 215 };
					drawtext(year, &r, DT_CENTER | DT_VCENTER);    /*drawtext中的参数name是查找出结果后返回的字符串*/
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
						RECT r = { Frame + 15, 75,width - 135,  height - 215 };
						drawtext("父亲：%s\n母亲：%s", &r, DT_CENTER | DT_VCENTER);   /*drawtext中的参数name是查找出结果后返回的字符串*/
						break;
					}
					else if ((y1 > (63 + relationMenuHeight + 3)) && (y1 < (63 + 2 * relationMenuHeight + 3)) && mklButton1)   /*单击第二个按钮，查询祖先*/
					{
						fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*清空输出区域*/
						RECT r = { Frame + 15, 75,width - 135,  height - 215 };
						drawtext(newpeople->name, &r, DT_CENTER | DT_VCENTER);
						break;
					}
					else if ((y1 > (63 + 2 * relationMenuHeight + 6)) && (y1 < (63 + 3 * relationMenuHeight + 6)) && mklButton1)   /*单击第三个按钮，查询兄弟*/
					{
						fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*清空输出区域*/
						RECT r = { Frame + 15, 75,width - 135,  height - 215 };
						drawtext("他的兄弟是：", &r, DT_CENTER | DT_VCENTER);
						break;
					}
					else if ((y1 > (63 + 3 * relationMenuHeight + 9)) && (y1 < (63 + 4 * relationMenuHeight + 9)) && mklButton1)   /*单击第四个按钮，查询孩子*/
					{
						fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*清空输出区域*/
						RECT r = { Frame + 15, 75,width - 135,  height - 215 };
						drawtext("他的孩子是：\n孩子1：...\n孩子2：", &r, DT_CENTER | DT_VCENTER);
						break;
					}
					else if ((y1 > (63 + 4 * relationMenuHeight + 12)) && (y1 < (63 + 5 * relationMenuHeight + 12)) && mklButton1)   /*单击第五个按钮，查询后代*/
					{
						fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*清空输出区域*/
						ifgetGener = InputBox(getGeneration, 20, "", "您要查询第几代", "查询", 300);
						if (ifgetGener)
						{
							RECT r = { Frame + 15, 75,width - 135,  height - 215 };
							drawtext("父亲：%s\n母亲：%s", &r, DT_CENTER | DT_VCENTER);
						}
						break;
					}
				}
			}
		}
	}
	return getInfo;
}

/************************************************************************************
									   title
*************************************************************************************/

void title()
{
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 35; // 设置字体高度为 12
	settextcolor(RGB(72, 81, 81));
	setbkmode(TRANSPARENT);
	_tcscpy_s(f.lfFaceName, _T("黑体"));    // 设置字体为“黑体”
	settextstyle(&f);
	char s[] = "家庭族谱查询";
	outtextxy(15, 15, s);
}

int main()
{
	char * info[100];
	char out[500] = "hhhhhhh";   /*之后把输出结果赋值给out数组*/
	initgraph(width, height);   /*创建绘图窗口*/
	initImg();
	title();
	DrawButtle();
	info[100] = GetMouse(out);   /*info数组为输入内容*/
	_getch();              // 按任意键继续
	closegraph();           // 关闭绘图窗口
}
