#include <graphics.h>      // ����ͼ�ο�ͷ�ļ�
#include <conio.h>
# define width 1280
# define height 660
# define buttleNum 3
int main()
{
	initgraph(width, height);   // ������ͼ���ڣ���СΪ 640x480 ����
	int buttleWidth = (width - 200) / 3;
	int buttleHeight = (height - 200 - 80);
	loadimage(NULL, _T("pic12.jpg"), width, height);
	fillrectangle(100, 60, width - 100, height - 200);
	fillrectangle(100, height - 200 + 40, 100 + buttleWidth, height - 80);
	fillrectangle(width - 475, width - 100 - buttleWidth, width - 100, height - 80);
	char name[20];
	InputBox(name, 20, "%s", "��������Ҫ��ѯ������", "��ѯ", 300);   /*�����ԶԻ�����ʽ��ȡ�û�����*/
	_getch();              // �����������
	closegraph();           // �رջ�ͼ����
}
