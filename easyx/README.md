
## 先了解一下easy-x库
EasyX 是针对 C++ 的图形库，可以帮助 C++语言初学者快速上手图形和游戏编程。
可以通过[官网](https://www.easyx.cn/)下载，文件很小，
easy-x的支持头文件是

    #include<graphics.h>

下载之后双击打开会有所有easy-x函数的语法和作用，中文软件，上手很快![在这里插入图片描述](https://img-blog.csdnimg.cn/20181102205040765.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3pqYnlvdWdo,size_16,color_FFFFFF,t_70)
-----------------------------------------------------
分割线，开始钟表制作
------------------
这是最终的效果图
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181102205301216.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3pqYnlvdWdo,size_16,color_FFFFFF,t_70)

## 第一步：
新建画布

    initgraph(Width,High);

Width,High在开头定义为常量

## 第二步
在画布中央绘制一个圆
定义圆心坐标为（Width/2，High/2）
```
int center_x=Width/2;
	int center_y=High/2;
```
绘制一个圆，颜色为蓝色，半径为Width/5+20

```
setcolor(BLUE);
	circle(center_x,center_y,Width/5+20);
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181102210447723.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3pqYnlvdWdo,size_16,color_FFFFFF,t_70)

## 第三步
绘制秒针

```
	//定义秒针长度
	int secondlength=Width/5;
	//画秒针
		setlinestyle(PS_SOLID,2);//定义线的类型，宽度为2
		setcolor(BLUE);//定义颜色为蓝色
		line(center_x,center_y,secondend_x,secondend_y);
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181102210938886.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3pqYnlvdWdo,size_16,color_FFFFFF,t_70)

## 第三部
实现转动
思路：使用三角函数知识，控制secondend_x,secondend_y的移动
1.  转动角度：每分钟转动`2*PI`,则每秒转动`2*PI/60`，获得当前系统时间的秒值，乘以每秒转动的角度，即可得出当前时间应该转动的角度
**注意：三角函数需要`#include<math.h>`支持**
```
//实现秒针转动
SYSTEMTIME ti;//获取系统时间
GetLocalTime(&ti);//得当当前系统时间
		float secondangle=0;//秒针转动的角度
		secondangle=ti.wSecond*2*PI/60;//每秒转动的角度等于当前时间*2*PI/60
		secondend_x=center_x+secondlength*sin(secondangle);
		secondend_y=center_y-secondlength*cos(secondangle);
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181102213006155.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3pqYnlvdWdo,size_16,color_FFFFFF,t_70)
2. 动画的实现：思路：每次绘制完一帧图像后，绘制一个与背景颜色一样的秒针，隐藏前一个秒针，并使用`while（1）`实现死循环

```
SYSTEMTIME ti;//获取系统时间
while(1)
	{
		GetLocalTime(&ti);//得当当前系统时间
		//实现秒针转动
		secondangle=ti.wSecond*2*PI/60;
		secondend_x=center_x+secondlength*sin(secondangle);
		secondend_y=center_y-secondlength*cos(secondangle);
		
		//画秒针
		setlinestyle(PS_SOLID,2);//定义线的类型，宽度为2
		setcolor(BLUE);//定义颜色为蓝色
		line(center_x,center_y,secondend_x,secondend_y);

		//隐藏前一个秒针
		setcolor(BLACK);
		line(center_x,center_y,secondend_x,secondend_y);
	
	}
```
但是我们发现图像一直在闪烁我们加上`sleep`也不行，easyx提供了批量绘图函数`BeginBatchDraw();FlushBatchDraw();EndBatchDraw();`
具体[使用方法](https://zhidao.baidu.com/question/470277767.html)看百度
**注意：sleep需要`#include<conio.h>`支持**

```
SYSTEMTIME ti;//获取系统时间
	BeginBatchDraw();
	while(1)
	{
		GetLocalTime(&ti);//得当当前系统时间
		//实现秒针转动
		secondangle=ti.wSecond*2*PI/60;
		secondend_x=center_x+secondlength*sin(secondangle);
		secondend_y=center_y-secondlength*cos(secondangle);
		//画秒针
		setlinestyle(PS_SOLID,2);//定义线的类型，宽度为2
		setcolor(BLUE);//定义颜色为蓝色
		line(center_x,center_y,secondend_x,secondend_y);
		FlushBatchDraw();
		Sleep(50);
		//隐藏前一个秒针
		setcolor(BLACK);
		line(center_x,center_y,secondend_x,secondend_y);
	}
	
	EndBatchDraw();
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181102214229129.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3pqYnlvdWdo,size_16,color_FFFFFF,t_70)

类似的，画出分针和时针，注意时针一个周期是12小时，所以时针的角度应该是
`hourAngle=ti.wHour*2*PI/12;`
注意代码结构，先是定义，然后`FlushBatchDraw();`批量绘制，最后隐藏
拿出代码

```
float secondangle=0;//秒针转动的角度
	float minuteangle=0;//分针转动的角
	float hourAngle=0;//定义时针转动的角
	SYSTEMTIME ti;//获取系统时间
	BeginBatchDraw();
	while(1)
	{
		GetLocalTime(&ti);//得当当前系统时间
		//实现秒针转动
		secondangle=ti.wSecond*2*PI/60;
		secondend_x=center_x+secondlength*sin(secondangle);
		secondend_y=center_y-secondlength*cos(secondangle);
		
		//实现分针转动
		minuteangle=ti.wMinute*2*PI/60;
		minuteend_x=center_x+minutelength*sin(minuteangle);
		minuteend_y=center_y-minutelength*cos(minuteangle);
		//实现时针转动
		hourAngle=ti.wHour*2*PI/12;
		hourEnd_x=center_x+hourlength*sin(hourAngle);
		hourEnd_y=center_y-hourlength*cos(hourAngle);
		//画秒针
		setlinestyle(PS_SOLID,2);//定义线的类型，宽度为2
		setcolor(BLUE);//定义颜色为蓝色
		line(center_x,center_y,secondend_x,secondend_y);
	
		//画分针
		setlinestyle(PS_SOLID,2);//定义线的类型，宽度为2
		setcolor(YELLOW);//定义颜色为黄色
		line(center_x,center_y,minuteend_x,minuteend_y);
			
		//画分针
		setlinestyle(PS_SOLID,3);//定义线的类型，宽度为3
		setcolor(RED);//定义颜色为黄色
		line(center_x,center_y,hourEnd_x,hourEnd_y);
		setcolor(BLUE);
		FlushBatchDraw();
		Sleep(50);
		//隐藏前一个秒针
		setcolor(BLACK);
		line(center_x,center_y,secondend_x,secondend_y);
		
		//隐藏前一个分针	
		setcolor(BLACK);
		line(center_x,center_y,minuteend_x,minuteend_y);
		//隐藏前一个时针
		setcolor(BLACK);
		line(center_x,center_y,hourEnd_x,hourEnd_y);
	}
	
	EndBatchDraw();
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181102214829226.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3pqYnlvdWdo,size_16,color_FFFFFF,t_70)

## 最后，刻画表盘
同样是使用三角函数知识，可以类比指针画，我使用了一种及其复杂和智障的方法画，先画出了12，3，6，9，然后再一个一个刻画，写完才想到懒得改了
easyx中文字的输入用到`outtextxy`函数以下为`outtextxy`的用法和实例

```
outtextxy
这个函数用于在指定位置输出字符串。

void outtextxy(
    int x,
    int y,
    LPCTSTR str
);void outtextxy(
    int x,
    int y,
    TCHAR c
);参数：

x 
字符串输出时头字母的 x 轴的坐标值 
y 
字符串输出时头字母的 y 轴的坐标值。 
str 
待输出的字符串的指针。 
c 
待输出的字符。 
返回值：

（无）

说明：

该函数不会改变当前位置。

字符串常见的编码有两种：MBCS 和 Unicode。VC6 新建的项目默认为 MBCS 编码，VC2008 及高版本的 VC 默认为 Unicode 编码。LPCTSTR 可以同时适应两种编码。为了适应两种编码，请使用 TCHAR 字符串及相关函数。

```
来自easyx官网


```
TCHAR s[] = _T("*输入文字*");
	outtextxy(x_11+R/3-10, y_11+sqrt(3.0)/2*R+R/2, s);
```

## 最后贴上完整代码和最终效果

```
#include<graphics.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#define High 480
#define Width 640
#define PI 3.1415926
int main()
{
	//初始化画布
	initgraph(Width,High);
	
	//定义钟表中点坐标
	int center_x=Width/2;
	int center_y=High/2;
	//定义秒针长度
	int secondlength=Width/5;
	//定义分针长度
	int minutelength=secondlength-50;
	//定义时针长度
	int hourlength=minutelength-20;
	//定义秒针终点坐标
	int secondend_x,secondend_y;
	secondend_x=center_x+secondlength;
	secondend_y=center_y;
	//定义分针终点坐标
	int minuteend_x=center_x+minutelength;
	int minuteend_y=center_y;
	//定义时针终点坐标
	int hourEnd_x=center_x+hourlength;
	int hourEnd_y=center_y;

	setcolor(BLUE);
	circle(center_x,center_y,secondlength+20);
	//绘制6：00
	setfillcolor(GREEN);
	solidcircle(Width/2+4, High/2+secondlength+15, 4);
	TCHAR s_6[5];
	_stprintf(s_6, _T("%d"), 6);        // 高版本 VC 推荐使用 _stprintf_s 函数
	outtextxy(Width/2-2, High/2+secondlength-5, s_6);
	//绘制12：00
	solidcircle(Width/2, High/2-secondlength-17, 4);
	TCHAR s_12[5];
	_stprintf(s_12, _T("%d"), 12);        // 高版本 VC 推荐使用 _stprintf_s 函数
	outtextxy(Width/2-6, High/2-secondlength-13, s_12);
	//绘制3：00
	solidcircle(center_x+secondlength+17,center_y , 4);
	TCHAR s_3[5];
	_stprintf(s_3, _T("%d"), 3);        // 高版本 VC 推荐使用 _stprintf_s 函数
	outtextxy(center_x+secondlength, center_y-5, s_3);
	//绘制9：00
	solidcircle(center_x-secondlength-17,center_y , 4);
	TCHAR s_9[5];
	_stprintf(s_9, _T("%d"), 9);        // 高版本 VC 推荐使用 _stprintf_s 函数
	outtextxy(center_x-secondlength-8, center_y-5, s_9);


	//绘制其他刻度

	int R=secondlength+20;
	int x_11,y_11;
	x_11=Width/2-R/2;//11:00刻度横坐标
	y_11=High/2-sqrt(3.0)/2*R;//11:00刻度纵坐标
	solidcircle(x_11,y_11, 3);
	TCHAR s_11[5];
	_stprintf(s_11, _T("%d"), 11);        // 高版本 VC 推荐使用 _stprintf_s 函数
	outtextxy(x_11,y_11, s_11);

	int x_10,y_10;
	x_10=Width/2-sqrt(3.0)/2*R;//10:00刻度横坐标
	y_10=High/2-R/2;//11:00刻度纵坐标
	solidcircle(x_10,y_10, 3);
	TCHAR s_10[5];
	_stprintf(s_10, _T("%d"), 10);        // 高版本 VC 推荐使用 _stprintf_s 函数
	outtextxy(x_10,y_10, s_10);

	int x_8,y_8;
	x_8=x_10;
	y_8=y_10+R;
	solidcircle(x_8,y_8, 3);
	TCHAR s_8[5];
	_stprintf(s_8, _T("%d"), 8);        // 高版本 VC 推荐使用 _stprintf_s 函数
	outtextxy(x_8,y_8, s_8);

	int x_7,y_7;
	x_7=x_11;
	y_7=y_11+sqrt(3.0)*R;
	solidcircle(x_7,y_7, 3);
	TCHAR s_7[5];
	_stprintf(s_7, _T("%d"), 7);        // 高版本 VC 推荐使用 _stprintf_s 函数
	outtextxy(x_7,y_7, s_7);

	int x_5,y_5;
	x_5=x_7+R;
	y_5=y_7;
	solidcircle(x_5,y_5, 3);
	TCHAR s_5[5];
	_stprintf(s_5, _T("%d"), 5);        // 高版本 VC 推荐使用 _stprintf_s 函数
	outtextxy(x_5,y_5, s_5);

	int x_4,y_4;
	x_4=x_8+sqrt(3.0)*R;
	y_4=y_8;
	solidcircle(x_4,y_4, 3);
	TCHAR s_4[5];
	_stprintf(s_4, _T("%d"), 4);        // 高版本 VC 推荐使用 _stprintf_s 函数
	outtextxy(x_4,y_4, s_4);

	int x_2,y_2;
	x_2=x_10+sqrt(3.0)*R;
	y_2=y_10;
	solidcircle(x_2,y_2, 3);
	TCHAR s_2[5];
	_stprintf(s_2, _T("%d"), 2);        // 高版本 VC 推荐使用 _stprintf_s 函数
	outtextxy(x_2,y_2, s_2);

	int x_1,y_1;
	x_1=x_11+R;
	y_1=y_11;
	solidcircle(x_1,y_1, 3);
	TCHAR s_1[5];
	_stprintf(s_1, _T("%d"), 1);        // 高版本 VC 推荐使用 _stprintf_s 函数
	outtextxy(x_1,y_1, s_1);
	
	float secondangle=0;//秒针转动的角度
	float minuteangle=0;//分针转动的角
	float hourAngle=0;//定义时针转动的角
	SYSTEMTIME ti;//获取系统时间
	BeginBatchDraw();
	while(1)
	{
		GetLocalTime(&ti);//得当当前系统时间
		//实现秒针转动
		secondangle=ti.wSecond*2*PI/60;
		secondend_x=center_x+secondlength*sin(secondangle);
		secondend_y=center_y-secondlength*cos(secondangle);
		
		//实现分针转动
		minuteangle=ti.wMinute*2*PI/60;
		minuteend_x=center_x+minutelength*sin(minuteangle);
		minuteend_y=center_y-minutelength*cos(minuteangle);
		//实现时针转动
		hourAngle=ti.wHour*2*PI/12;
		hourEnd_x=center_x+hourlength*sin(hourAngle);
		hourEnd_y=center_y-hourlength*cos(hourAngle);
		//画秒针
		setlinestyle(PS_SOLID,2);//定义线的类型，宽度为2
		setcolor(BLUE);//定义颜色为蓝色
		line(center_x,center_y,secondend_x,secondend_y);
	
		//画分针
		setlinestyle(PS_SOLID,2);//定义线的类型，宽度为2
		setcolor(YELLOW);//定义颜色为黄色
		line(center_x,center_y,minuteend_x,minuteend_y);
			
		//画分针
		setlinestyle(PS_SOLID,3);//定义线的类型，宽度为3
		setcolor(RED);//定义颜色为黄色
		line(center_x,center_y,hourEnd_x,hourEnd_y);
		setcolor(BLUE);
		TCHAR s[] = _T("*小张钟表*");
	outtextxy(x_11+R/3-10, y_11+sqrt(3.0)/2*R+R/2, s);
		FlushBatchDraw();
		Sleep(50);
		//隐藏前一个秒针
		setcolor(BLACK);
		line(center_x,center_y,secondend_x,secondend_y);
		
		//隐藏前一个分针	
		setcolor(BLACK);
		line(center_x,center_y,minuteend_x,minuteend_y);
		//隐藏前一个时针
		setcolor(BLACK);
		line(center_x,center_y,hourEnd_x,hourEnd_y);
	}
	
	EndBatchDraw();
	
	getch();
	closegraph();
	system("pause");
	return 0;
}

```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181102220014509.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3pqYnlvdWdo,size_16,color_FFFFFF,t_70)

## **欧克，大功告成**
