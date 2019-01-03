# 题目：家族关系查询系统
<hr />
## 设计目的：
《数据结构》课程主要介绍最常用的数据结构，阐明各种数据结构内在的逻辑关系，讨论其在计算机中的存储表示，以及在其上进行各种运算时的实现算法，并对算法的效率进行简单的分析和讨论。进行数据结构课程设计要达到以下目的：
*	了解并掌握数据结构与算法的设计方法，具备初步的独立分析和设计能力；
*	初步掌握软件开发过程的问题分析、系统设计、程序编码、测试等基本方法和技能；
*	提高综合运用所学的理论知识和方法独立分析和解决问题的能力；
训练用系统的观点和软件开发一般规范进行软件开发，培养软件工作者所应具备的科学的工作方法和作风。

## 1.设计内容和要求：
### 1.1 设计内容：
设计一个家族关系查询系统，实现对家族成员关系的相关查询。
*	建立家族关系并存储到文件中。
*	实现家族成员的添加。
*	查询家族成员的双亲、祖先、兄弟、孩子及后代信息。
### 1.2 设计要求：
（1）符合课题要求，实现相应功能；
（2）要求界面友好美观，操作方便易行；
（3）注意程序的实用性、安全性；
## 2 设计工作任务及工作量的要求：
1）选择合适的数据结构，并定义数据结构的结构体；
2）根据程序所要完成的基本要求和程序实现提示，设计出完整的算法；
3）按组讨论、确定设计方案，确定程序模块，并进行明确分工；
4）写出课程设计说明书(按格式要求，每人根据自己的工作写出说明书)。
## 3 分工：

|姓名|学号|任务|
|---|---|---|
|刘仕轲|17070046 |结构体的创建，树的创建，文件的读取,修改|
|葛强湦|1707004649 |插入节点|
|范晋玉|17070046 |查询节点|
|张君保|1707004650 |图形化界面|

## 4 功能模块详细设计
### 4.1 图形化界面设计
#### 4.1.1 详细设计思想
* 总体思路：使用easyx绘制，其中，输出界面使用fillrectangle()函数绘制一个白色矩形，输出使用outtextxy()和drawtext()函数完成，每次输出完重新绘制一个白色矩形，实现清空输出区域的效果；按钮的制作同样使用fillrectangle()绘制一个矩形作为按钮，然后通过while(true)不断捕捉鼠标位置，并且通过显示屏幕长宽定位每个按钮的坐标，检测到鼠标在特定区域按下左键后，按钮对应单击数自增一，单击数是奇数执行对应按钮的功能，如果是偶数则执行初始化界面函数，依次实现点一下打开，再点一次关闭的效果，在树的图形化中，使用递归的思想，先给定树的根节点的坐标以及每次递归坐标向左右上下的偏移量，绘制出根节点后递归调用画树函数，绘制出左子树和右子树
![404](E:/TIM/数据结构课设.png)
#### 4.1.2 完整代码
* 初始化界面
```c
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
```
* 树的图形化
```c

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
```
* 按钮及菜单制作
```c
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
	char *s[] = { s0,s1,s2,s3};
	for (i = 0; i < buttleNum; i++)
	{
		fillrectangle(left, top, left + buttleWidth, top + buttleHeight);
		outtextxy(left + 85, top + 6, s[i]);
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
```
* 鼠标相关
```c
/* 鼠标事件*/

char * GetMouse(char out[500] )
{
	person * t;
	char file[20] = "02.txt";
	FILE *fp = fopen(file, "r+");
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
				ifgetfather = InputBox(getfather, 20, "", "请输入你要添加的成员的父亲", "查询", 300);
				sscanf(getfather, "%s", findfather);   /*findfather 是根据用户输入的父亲姓名，用来作为findname()的参数找到要插入的人的父亲节点*/
				person *newone= (person*)malloc(sizeof(person));
				if (ifgetfather)
				{
					newone = &addinfo(newpeople);   /*newonw就是要插入的节点信息*/
					person *addfather = findname(t, getfather);
					while (addfather->child != NULL)
					{
						addfather = addfather->child;
					}
					addfather->child = newone;

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
					GetMouse(out);
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
```
### 4.2 创建及文件读取
#### 4.2.1 详细设计思想

#### 4.2.2 完整代码
```c
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
```
文件内容 02.txt
```txt
GoergeJoestar 1	18440101	UK	19090101	1	noble	Meili	None
JonathanJoestar 2	18680404	UK	18890207	1	noble	Alina	GoergeJostar+Meili
JosephJoestar 3	19200927	USA	00000000	1	businessman	sijiq	Jonathan+Alina
Herli 4	1944	USA	00000000	0	Unknown	Kujo	Joseph+sijiq
KujoJotaro 5	1970	JPN	20120321	1	Doctor	Unknown	Herli	
# # HigashikataJosuke 4	1983	JPN	00000000	1	Student	None	Joseph+pengzi
# # # DioBrando 2	1867	UK	1988	1	Vampire	Unknown	DarleoBrando
GiornoGiovanna 3	19850416	Italy	00000000	1	Gangster	Unknown	Dio
# Unglo 3	1988	Unknown	00000000	1	Unknown	Unknown	Dio
# Rikiel 3	1988	Unknown	00000000	1	Unknown	Unknown	Dio
# # # # 
```
### 4.3 寻找后三代中任意一代（范晋玉编写）
#### 4.3.1 详细设计思想
运用队列 进行广度优先非递归遍历来寻找后三代任意一代信息。首先判断当前节点是否有孩子，若没有则退出函数。若有孩子，如果寻找的是第一代，将第一个孩子输出并压入队列，如果第一个孩子存在兄弟结点，就把他的兄弟结点全部输出并压入队列。此时全部儿子都在队列中。
再将每一个儿子依次弹出队列，分别判断他们是否存在儿子结点，若有儿子则将他们的儿子结点依次入队，若要查找的是第二代则输出并计数。此时全部的孙子在队列中。
再用同样的方法将孙子弹出队列并依次查找他们的儿子，直至队列为空。
#### 4.3.2 核心代码
```c
if (!q->child)                                         //判断当前节点是否有孩子结点
	{
		RECT r = { Frame + 15, 75,width - 135,  height - 215 };
		//fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*清空输出区域*/
		drawtext("他，没有孩子...", &r, DT_CENTER | DT_VCENTER);
		return;
	}
	else
	{
		if (strcmp(dai, "1") == 0)                    //如果查询的是第一代信息的话输出
		{
			outtextxy(300, Buttom + 20, "他的孩子有：");
			/*printf("%s的孩子有", r->record.name);*/
		}
		q = q->child;                                                  
		if (strcmp(dai, "1") == 0)                                //查询的是第一代输出
			outtextxy(400, Buttom + 50, q->record.name);              //输出第一个孩子
		/*display(q);*/

		qq.push(q);                                             //将第一个孩子压入队列
		while (q->brother)                              //判断第一个孩子是否有兄弟节点
		{
			q = q->brother;
			qq.push(q);                                              //将兄弟压入队列
			if (strcmp(dai, "1") == 0)
				outtextxy(400, Buttom + jianju, q->record.name)   //如果查询的是第一代输出兄弟
			//display(q);
			jianju += 30;
		}
	}                                                       //此时全部儿子都进入了队列
	if (qq.front()->child)
		p = qq.front()->child;                                         
	int kk = 0;
	while (!qq.empty() && (qq.front() != p))               //当队首结点不等于第一个孙子
	{
		q = qq.front(); qq.pop();               //将所有的儿子依次出队对每一个儿子遍历
		if (q->child)
		{
			q = q->child;                                              
			qq.push(q);                                        //将儿子的儿子入队
			if (strcmp(dai, "2") == 0)
			{
				outtextxy(400, Buttom + jianju2, q->record.name)//如果查询的是第二代信息则输出
				jianju2 += 30;
				kk++;
			}
			while (q->brother)                                   //判断孙子是否有兄弟
			{
				q = q->brother;
				qq.push(q);                                          //压入队列
				if (strcmp(dai, "2") == 0)
				{
					//display(q);
					outtextxy(400, Buttom + jianju2, q->record.name);  //如果查询的是第二代则输出
					jianju2 += 30;
					kk++;
				}

			}
		}
	}
	if ((kk == 0) && (strcmp(dai, "2") == 0))
	{
		//printf("%s没有孙子\n", r->record.name);
		RECT r = { Frame + 15, 75,width - 135,  height - 215 };
		drawtext("他，没有孙子...", &r, DT_CENTER | DT_VCENTER);
		return;
	}

```
### 4.4 寻找成员的兄弟信息（范晋玉编写）
#### 4.4.1 详细设计思想
运用二叉树的后序遍历，在每次出栈后判断当前节点的姓名是否与已知姓名相等，若相等，如果当前结点存在兄弟结点，则将他的兄弟们依次输出并计数。此时在栈中如果存在被标记为1的结点，则将它们全部输出并计数。如果没有输出兄弟，就输出当前节点没有兄弟，退出当前函数。

#### 4.4.2 完整代码
```c
while ((s->top > 0) && (s->tag[s->top - 1] == 1))
		{
			t = pop(s);
			if (strcmp(t->record.name, q->record.name) == 0)    //通过姓名找到查询结点
			{
				if (t->brother)                           //判断该节点是否有兄弟节点
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
				if ((s->tag[s->top - 1] == 1) && (s->top > 0) && (k == 0))  //如果栈中结点被标记为1 并且没有兄弟节点
				{
					/*printf("%s的兄弟为\n", q->record.name);*/
					outtextxy(300, Buttom + 20, "他的兄弟为：");
				}
				while ((s->tag[s->top - 1] == 1) && (s->top > 0))//将标记为1的结点全部弹出栈并输出
				{
					t = pop(s);
					//display(t); 
					outtextxy(400, Buttom + jianju1, t->record.name);
					jianju1 += 30;
					a++;
				}
				jianju1 = 50;
				if (a == 0)                                                //如果没有输出过任何兄弟
					/*printf("%s无兄弟\n", q->recorde.name); */
					outtextxy(300, Buttom + 20, "他是独生子女...");
				return;
			}
		}

```
### 4.5 寻找成员父母信息（范晋玉编写）
#### 4.5.1 详细设计思想
运用二叉树的后序遍历，在每次出栈后判断当前节点的姓名是否与已知姓名相等，如果相等，将栈首被标记为1的全部弹出，再将第一个标记为0的结点即为父亲结点。如果栈中第一个被标记为0的结点不存在，则输出没有找到父母的信息。
#### 4.5.2 完整代码
```c
while ((s->top > 0) && (s->tag[s->top - 1] == 1))
		{
			t = pop(s);
			if (strcmp(t->record.name, q->record.name) == 0)    //判断是否找到查询节点
			{
				while ((s->tag[s->top - 1] == 1) && (s->top > 0)) //将栈中所有标记为1的结点弹出
					t = pop(s);
				if (s->top > 0)                                 //如果栈不为空 
				{
					t = pop(s);                          //将栈中第一个结点弹出并输出 
					//printf("%s的父母信息为\n", q->recorde.name);
					outtextxy(300, Buttom + 20, "他的父亲为：");
					outtextxy(400, Buttom + 80, t->record.name);
					//display(t);
					return;
				}
				else
					//printf("没有%s的父亲信息\n", q->record.name);              //如果为空栈 则没有父母信息
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

```
### 4.6 寻找祖先信息（范晋玉编写）
#### 4.6.1 详细设计思想
运用二叉树的后序遍历，在每次出栈后判断当前节点的姓名是否与已知姓名相等，若相等，则将栈中全部被标记为0的结点输出。如果没有输出结点信息，则输出没有祖先的信息。
#### 4.6.2 完整代码
```c
while ((s->top > 0) && (s->tag[s->top - 1] == 1))
		{
			t = pop(s);
			if (strcmp(t->record.name, q->record.name) == 0)    //判断是否找到查询节点
			{
				if (s->top > 0)
					outtextxy(300, Buttom + 20, "他的祖先为：");       //如果不是空栈
				//printf("%s的祖先有\n", q->record.name);
				while (s->top > 0)                                 //依次遍历栈中结点
				{
				 if (s->tag[s->top - 1] != 1) //如果栈中结点没被标记为1，将出栈并输出
					{
						t = pop(s);
						outtextxy(400, Buttom + jianju, t->record.name);
						jianju += 30;
						//display(t);
						a++;
					}
					else t = pop(s);                     //如果栈中标记为了1 直接出栈
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

```
### 4.7 寻找孩子信息（范晋玉编写）
#### 4.7.1 详细设计思想
判断当前节点是否存在孩子结点，如果有孩子结点，则输出第一个孩子，如果当前的孩子结点存在兄弟结点，再将他的兄弟输出，如果没有孩子节点，则输出没有找到孩子。
#### 4.7.2 完整代码
```c
void children1(person *q)//寻找孩子信息
{
	int jianju = 80;
	if (!q->child)                                                 //如果不存在孩子结点 
		outtextxy(300, Buttom + 20, "他，没有孩子...");
	else
	{
		//printf("%s的孩子有\n", q->record.name);                      
		outtextxy(300, Buttom + 20, "他的孩子有：");                   
		q = q->child;                                             //指向第一个孩子结点
		//display(q);
		outtextxy(400, Buttom + jianju, q->record.name);            //将第一个孩子输出
		jianju += 30;
		while (q->brother)                                  //如果第一个孩子有兄弟节点
		{
			q = q->brother;                                   //将兄弟结点依次输出
			//display(q);
			outtextxy(400, Buttom + jianju, q->record.name);
			jianju += 30;
		}
	}
}

```

### 4.8 修改
#### 4.8.1 详细设计思想
首先，利用InputBox()函数弹窗要求输入新增节点的信息，InputBox如果输入并且单击了确定，会返回true，根据这个特点定义布尔类型变量，如果上一个弹窗被填写确定后，再产生下一个弹窗，直到输入完所有节点信息。运用二叉树的前序遍历，先通过findname()函数查找到需要添加新成员的父亲，判断找到的节点的child指针是否为空，如果为空，直接将child指针指向新节点，否则，沿着child指针向下遍历，直到找到child指针为NULL的节点，把该节点child指针指向新节点。 
#### 4.8.2 完整代码
```c
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
sscanf(addName, "%s", newPeople-> record.name);   /*获取用户输入的字符串*/
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
newPeople->child = NULL;
newPeople->brother = NULL;
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



```
