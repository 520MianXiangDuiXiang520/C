#include <graphics.h>      // ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
	initgraph(1280,640);   /*������ͼ����*/
	bool fingName;
	bool findYear;
	char getInfo[100];   /*��ȡ�û��������Ϣ*/
	char name[100];
	char year[100];
	char * info[100];
	fingName = InputBox(name, 20, "", "��������Ҫ��ѯ������", "��ѯ", 300);   /*�����ԶԻ�����ʽ��ȡ�û�����*/
	sscanf(name, "%s", getInfo);   /*��ȡ�û�������ַ���*/
	LOGFONT f;
	gettextstyle(&f);                     // ��ȡ��ǰ��������
	f.lfHeight = 35; // ��������߶�Ϊ 12
	settextcolor(RGB(255,255,255));
	setbkmode(TRANSPARENT);
	_tcscpy_s(f.lfFaceName, _T("����"));    // ��������Ϊ�����塱
	settextstyle(&f);
	char s[] = "��ͥ���ײ�ѯ";
	outtextxy(15, 15, name);
	_getch();              // �����������
	closegraph();           // �رջ�ͼ����
}