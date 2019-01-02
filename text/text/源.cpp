#include <graphics.h>      // 引用图形库头文件
#include <conio.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
	initgraph(1280,640);   /*创建绘图窗口*/
	bool fingName;
	bool findYear;
	char getInfo[100];   /*获取用户输入的信息*/
	char name[100];
	char year[100];
	char * info[100];
	fingName = InputBox(name, 20, "", "请输入你要查询的姓名", "查询", 300);   /*用于以对话框形式获取用户输入*/
	sscanf(name, "%s", getInfo);   /*获取用户输入的字符串*/
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 35; // 设置字体高度为 12
	settextcolor(RGB(255,255,255));
	setbkmode(TRANSPARENT);
	_tcscpy_s(f.lfFaceName, _T("黑体"));    // 设置字体为“黑体”
	settextstyle(&f);
	char s[] = "家庭族谱查询";
	outtextxy(15, 15, name);
	_getch();              // 按任意键继续
	closegraph();           // 关闭绘图窗口
}