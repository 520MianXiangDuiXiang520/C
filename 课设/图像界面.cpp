#include <graphics.h>      // 引用图形库头文件
#include <conio.h>
# define width 1280
# define height 660
# define buttleNum 3
int main()
{
	initgraph(width, height);   // 创建绘图窗口，大小为 640x480 像素
	int buttleWidth = (width - 200) / 3;
	int buttleHeight = (height - 200 - 80);
	loadimage(NULL, _T("pic12.jpg"), width, height);
	fillrectangle(100, 60, width - 100, height - 200);
	fillrectangle(100, height - 200 + 40, 100 + buttleWidth, height - 80);
	fillrectangle(width - 475, width - 100 - buttleWidth, width - 100, height - 80);
	char name[20];
	InputBox(name, 20, "%s", "请输入你要查询的姓名", "查询", 300);   /*用于以对话框形式获取用户输入*/
	_getch();              // 按任意键继续
	closegraph();           // 关闭绘图窗口
}
