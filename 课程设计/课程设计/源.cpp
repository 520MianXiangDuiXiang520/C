#include <graphics.h>      // ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include<stdio.h>
#include<stdlib.h>
# include<math.h>
#include<Windows.h>

# define width 1280         /*����ҳ����*/
# define height 660         /*����ҳ��߶�*/
# define buttleNum 4       /*���尴ť����*/
# define Frame 100          /*����߿���*/
# define Spacing 30         /*���尴ť����*/
# define Buttom 60          /*���嵽�ײ��ľ���*/
# define MenuNum 2          /*�����ѯ�˵�����*/
# define relationMenuNum 5  /*�����ϵ�˵�������*/

/*��Ա��Ϣ�ṹ�嶨��*/

struct info
{
	//������Ϣ
	char name[20];
	int generation;      //�ڼ���
	char date_birth[9];  //����20181205
	char place_birth[20];//������
	char date_death[9];  //��������,δ�������Ϊ00000000
	int sex;             //0ָŮ�ԣ�1Ϊ����
	char profession[15]; //ְҵ
	char spouse_name[20];//��ż����
	char parent_name[20];//˫������
};
struct person
{
	info record;    //���׸��˽ڵ�
	person *child;  //ָ����
	person *brother;//ָ��һ���ֵ�
};



/*ȫ�ֱ���*/
int buttleWidth = ((width - 200) / buttleNum) - Spacing;   /*���尴ť��С*/
int buttleHeight = 40;
int MenuWidth = ((width / 2 - 200) / MenuNum) - Spacing;   /*����˵���ť��С*/
int MenuHeight = 30;   /*����˵���ť�߶�*/
int MouseFindNum = 0;   /*��¼���ҵ�������*/
int MouseAddNum = 0;   /*��¼��Ӱ�ť�ĵ�������*/
int MouseTreeNum = 0;   /*����鿴��������*/
int MenuSpacing = 15;   /*��ʼ���˵�����*/
char name[100];   /*�����û������������ѯ������*/
char year[100];   /*�����û������������ѯ��������*/
char addName[20];
int addGeneration;         /*�ڼ���*/
char addData_birth[20];    /*����*/
char addPlace_birth[20];   /*������*/
char addSex[20];                /*0 Ů�� 1 ����*/
char addProfession[20];    /*ְҵ*/
char addSpouse_name[20];   /*��ż����*/
char addParent_name[20];   /*˫������*/
char getInfo[100];   /*��ȡ�û��������Ϣ*/
char getGeneration[20];   /*��ȡ�û�����Ĵ���*/
info *newpeople = NULL;
int relationMenuWidth = (width - 2 * Frame) / 3;   /*�����ϵ�˵����*/
int relationMenuHeight = 400 / relationMenuNum - 6;   /*�����ϵ�˵��߶�*/
bool ifgetName;
int Left = 50;   /*���廭��ʱ���Ҽ��*/
int Top = 10;   /*���廭��ʱ���¼��*/
int SuoJin = 1;   /*����ÿ�������ı���*/

/************************************************************************************
										 ����
*************************************************************************************/

person *create_family(FILE *fp)
{
	person *t = (person*)malloc(sizeof(person));
	fscanf(fp, "%s", t->record.name);    //������ı��Ϊ�ո�' '
	if (t->record.name[0] == '#')          //����Ϊ#ʱ����������
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
										 ����
*************************************************************************************/

/*��Ȧ*/
void draw(int x, int y, char *c) {
	circle(x, y, 10);
	outtextxy(x - 5, y - 5, *c);   //���Ԫ��
}
/*�ݹ黭��*/
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
								   ��ʼ��ͼ�����
**************************************************************************************/

void initImg()
{

	IMAGE imgbk;
	loadimage(&imgbk, _T("E:/vs2019/���ݽṹ����/10.jpg"), 1280, 660);
	putimage(0, 0, &imgbk);//��ʾͼƬ

	//loadimage(NULL, _T("10.jpg"), width, height);    /*ͼƬ���*/
	//fillrectangle(Frame, 60, width - 100, height - 200);   /*�����������*/
	IMAGE img;
	loadimage(&img, _T("E:/vs2019/���ݽṹ����/11.jpg"), 1080, 400);
	putimage(100, 60, &img);   //��ʾͼƬ

}

/*************************************************************************************
								   ���ư�ť
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
	char s0[15] = "����";
	char s1[15] = "����";
	char s2[15] = "�˳�";
	char s3[15] = "�鿴";
	char *s[] = { s0,s1,s2,s3 };
	for (i = 0; i < buttleNum; i++)
	{
		fillrectangle(left, top, left + buttleWidth, top + buttleHeight);
		outtextxy(left + 85, top + 6, s[i]);
		left = left + buttleWidth + Spacing;
	}
}

/**************************************************************************************
								  ���Ʋ�ѯ�˵�
***************************************************************************************/

void queryMenu()
{
	int i;
	int menuLeft = Frame + Spacing / 2;   /*����˵���ť��ʼ��λ��*/
	int MenuTop = height - 2 * Frame + Buttom + buttleHeight + 20;   /*�˵���ʼ���߶�*/

	for (i = 0; i < MenuNum; i++)
	{
		fillrectangle(menuLeft, MenuTop, menuLeft + MenuWidth, MenuTop + MenuHeight);
		menuLeft = menuLeft + MenuWidth + MenuSpacing;
	}
}

/**************************************************************************************
								  ����
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

	/*����Ҫ����Ľڵ���Ϣ*/
	newPeople = (info*)malloc(sizeof(info));
	ifaddName = InputBox(addName, 20, "", "��������Ҫ��ӵĳ�Ա������", "��ѯ", 300);
	sscanf(addName, "%s", newPeople->name);   /*��ȡ�û�������ַ���*/
	if (ifaddName)
	{
		ifaddDataBirth = InputBox(addData_birth, 20, "", "�������������", "��ѯ", 300);
		sscanf(addData_birth, "%s", newPeople->date_birth);   /*��ȡ�û�������ַ���*/
	}
	if (ifaddDataBirth)
	{
		ifaddPlaceBirth = InputBox(addPlace_birth, 20, "", "�����������", "��ѯ", 300);
		sscanf(addPlace_birth, "%s", newPeople->place_birth);   /*��ȡ�û�������ַ���*/
	}
	if (ifaddPlaceBirth)
	{
		ifaddSex = InputBox(addSex, 20, "", "�������Ա�", "��ѯ", 300);
		sscanf(addSex, "%d", newPeople->sex);   /*��ȡ�û�������ַ���*/
	}
	if (ifaddSex)
	{
		ifaddProfession = InputBox(addProfession, 20, "", "������ְҵ", "��ѯ", 300);
		sscanf(addProfession, "%s", newPeople->profession);   /*��ȡ�û�������ַ���*/
	}
	if (ifaddProfession)
	{
		ifaddSpouseName = InputBox(addSpouse_name, 20, "", "��������ż", "��ѯ", 300);
		sscanf(addSpouse_name, "%s", newPeople->spouse_name);   /*��ȡ�û�������ַ���*/
	}
	if (ifaddSpouseName)
	{
		ifaddparent = InputBox(addParent_name, 20, "", "�����븸������", "��ѯ", 300);
		sscanf(addParent_name, "%s", newPeople->parent_name);   /*��ȡ�û�������ַ���*/
	}
	if (ifaddparent)
	{

		LOGFONT f;
		gettextstyle(&f);
		f.lfHeight = 35;
		settextcolor(BLACK);
		setbkmode(TRANSPARENT);
		_tcscpy_s(f.lfFaceName, _T("����"));
		settextstyle(&f);
		char add[] = "�³�Ա��Ϣ¼��ɹ�\n��ӭ�³�Ա���룡��";
		RECT r = { Frame + 15, 75,width - 135,  height - 215 };
		drawtext(add, &r, DT_CENTER | DT_VCENTER);
	}
	return *newPeople;
}

/****************************************************************************************
									���ƹ�ϵ�˵�
*****************************************************************************************/

void relationshipMenu()
{
	int g;
	LOGFONT f;
	gettextstyle(&f);                     // ��ȡ��ǰ��������
	f.lfHeight = 25;
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	_tcscpy_s(f.lfFaceName, _T("����"));    // ��������Ϊ�����塱
	settextstyle(&f);
	char r0[15] = "���Ҹ�ĸ";
	char r1[15] = "��������";
	char r2[15] = "�����ֵ�";
	char r3[15] = "���Һ���";
	char r4[15] = "���Һ��";
	char *p[] = { r0,r1,r2 ,r3,r4 };
	int relaMenuLeft = Frame + (width - 2 * Frame) / 3;   /*�����ϵ�˵��������*/
	int relaMenuRight = relaMenuLeft + relationMenuWidth;   /*�����ϵ�˵��Ҳ����*/
	int relaMenuTop = 63;   /*�����һ����ϵ��ť��������*/
	int relaMenuButton = relaMenuTop + relationMenuHeight;   /*�����ϵ��ť�ײ�����*/
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
									   ����¼�
******************************************************************************************/

char * GetMouse(char out[500])
{
	person * t;
	char file[20] = "02.txt";
	FILE *fp = fopen(file, "r");
	t = create_family(fp);
	MOUSEMSG mousemsg;		/* ���������Ϣ*/
	while (true)
	{
		mousemsg = GetMouseMsg();   /*��ȡһ�������Ϣ*/
		int x, y;
		bool mklButton;
		x = mousemsg.x;   /*��ȡ��굱ǰx����*/
		y = mousemsg.y;   /*��ȡ��굱ǰy����*/
		mklButton = mousemsg.mkLButton;   /*��ȡ��굱ǰ����Ƿ���*/


		if ((y > height - 2 * Frame + Buttom) && (y < height - 2 * Frame + Buttom + buttleHeight))
		{
			/*��ѯ*/
			if ((x > Frame + Spacing / 2) && (x < Frame + Spacing / 2 + buttleWidth) && mklButton)   /*����ڵ�һ����ť�ϵ������ʱ����������¼� 1*/
			{
				fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*����������*/
				MouseFindNum++;
				if (MouseFindNum % 2 != 0)
				{
					queryMenu();
				}
				else   /*�ٴε��ʱ���»��ƽ��棬�رղ˵�*/
				{
					fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*����������*/
					initImg();
					DrawButtle();
					GetMouse(out);
				}
			}
			/*����*/
			else if ((x > (Frame + Spacing / 2) + buttleWidth + Spacing) && (x < (Frame + Spacing / 2) + 2 * buttleWidth + Spacing) && mklButton)
			{
				fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*����������*/
				info *newone = (info*)malloc(sizeof(info));
				newone = &addinfo(newpeople);   /*newonw����Ҫ����Ľڵ���Ϣ*/
				FlushMouseMsgBuffer();   /*�����껺����*/
				/****************************************
				*                                       *
				*          ����Ĵ���                   *
				*		   ��������newone               *
				*                                       *
				*****************************************/
			}
			/*�˳�*/
			else if ((x > (Frame + Spacing / 2) + 2 * (buttleWidth + Spacing)) && (x < (Frame + Spacing / 2) + 2 * (buttleWidth + Spacing) + buttleWidth) && mklButton)
			{
				exit(1);
			}
			/*����*/
			else if ((x > (Frame + Spacing / 2) + 3 * buttleWidth + Spacing) && (x < (Frame + Spacing / 2) + 3 * (buttleWidth + Spacing) + buttleWidth) && mklButton)
			{
				LOGFONT f;
				gettextstyle(&f);
				f.lfHeight = 15;
				settextcolor(BLUE);
				setbkmode(TRANSPARENT);
				_tcscpy_s(f.lfFaceName, _T("����"));
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
					fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*����������*/
					initImg();
					DrawButtle();
					GetMouse(out);
				}
			}
		}
		/* �����������Ϊ������˵���˵����������ж���굥��λ��*/
		if (MouseFindNum % 2 != 0)
		{
			LOGFONT f;
			gettextstyle(&f);                     // ��ȡ��ǰ��������
			f.lfHeight = 25;
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			_tcscpy_s(f.lfFaceName, _T("����"));    // ��������Ϊ�����塱
			settextstyle(&f);

			char s[] = "������������";
			outtextxy(Frame + Spacing / 2 + 15, height - 200 + Buttom + buttleHeight + 25, s);
			char d[] = "���ݳ�������";
			outtextxy((Frame + Spacing / 2) + MenuWidth + MenuSpacing + 15, height - 200 + Buttom + buttleHeight + 25, d);

			if (y > (height - 200 + Buttom + buttleHeight + 20) && y < (height - 200 + Buttom + buttleHeight + 20 + MenuHeight))
			{
				LOGFONT f;
				gettextstyle(&f);                     // ��ȡ��ǰ��������
				f.lfHeight = 25; // ��������߶�
				settextcolor(BLACK);
				setbkmode(TRANSPARENT);
				_tcscpy_s(f.lfFaceName, _T("����"));    // ��������Ϊ�����塱
				settextstyle(&f);
				/*������������*/
				if (x > (Frame + Spacing / 2) && x < (Frame + Spacing / 2 + MenuWidth) && mklButton)
				{
					ifgetName = InputBox(name, 20, "", "��������Ҫ��ѯ������", "��ѯ", 300);   /*�����ԶԻ�����ʽ��ȡ�û�����*/
					sscanf(name, "%s", getInfo);   /*��ȡ�û�������ַ���*/
					/****************************************
					*                                       *
					*           ���������ҵĴ���            *
					*		    ��������name                *
					*                                       *
					*****************************************/
					RECT r = { Frame + 15, 75,width - 135,  height - 215 };
					//drawtext(name, &r, DT_CENTER | DT_VCENTER);   /*drawtext�еĲ���name�ǲ��ҳ�����󷵻ص��ַ���*/
					FlushMouseMsgBuffer();   /*�����껺����*/
				}
				/*���ݳ������²���*/
				else if (x > (Frame + Spacing / 2) + MenuWidth + MenuSpacing && x < (Frame + Spacing / 2) + 2 * MenuWidth + MenuSpacing && mklButton)
				{
					InputBox(year, 20, "", "��������Ҫ��ѯ�ĳ�������", "��ѯ", 300, 0, false);   /*�����ԶԻ�����ʽ��ȡ�û�����*/
					sscanf(year, "%s", getInfo);
					/****************************************
					*                                       *
					*           �����ڲ��ҵĴ���            *
					*		    ��������year                *
					*                                       *
					*****************************************/
					fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*����������*/
					RECT r = { Frame + 15, 75,width - 135,  height - 215 };
					drawtext(year, &r, DT_CENTER | DT_VCENTER);    /*drawtext�еĲ���name�ǲ��ҳ�����󷵻ص��ַ���*/
					FlushMouseMsgBuffer();   /*�����껺����*/
				}

			}
		}
		if (ifgetName)   /* �������Ҫ��ѯ�������󵥻�ȷ�����������ϵ�˵���ѡ��*/
		{
			relationshipMenu();
			ifgetName = FALSE;   /*��ʼ���������ظ����Ҳ�����*/
			Sleep(60);
			MOUSEMSG mousemsg1;		/* ���������Ϣ*/
			while (true)
			{
				mousemsg1 = GetMouseMsg();   /*��ȡһ�������Ϣ*/
				int x1, y1;
				bool mklButton1;
				bool ifgetGener;
				x1 = mousemsg1.x;   /*��ȡ��굱ǰx����*/
				y1 = mousemsg1.y;   /*��ȡ��굱ǰy����*/
				mklButton1 = mousemsg1.mkLButton;   /*��ȡ��굱ǰ����Ƿ���*/
				if (x1 > Frame + (width - 2 * Frame) / 3 && x1 < Frame + width - 2 * Frame / 3 + relationMenuWidth)   /*�ж�����Ƿ��ڹ�ϵ�˵��Ŀ������*/
				{
					if ((y1 > 63) && (y1 < (63 + relationMenuHeight)) && mklButton1)   /*������һ����ť��ѯ��ĸ*/
					{
						fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*����������*/
						RECT r = { Frame + 15, 75,width - 135,  height - 215 };
						drawtext("���ף�%s\nĸ�ף�%s", &r, DT_CENTER | DT_VCENTER);   /*drawtext�еĲ���name�ǲ��ҳ�����󷵻ص��ַ���*/
						break;
					}
					else if ((y1 > (63 + relationMenuHeight + 3)) && (y1 < (63 + 2 * relationMenuHeight + 3)) && mklButton1)   /*�����ڶ�����ť����ѯ����*/
					{
						fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*����������*/
						RECT r = { Frame + 15, 75,width - 135,  height - 215 };
						drawtext(newpeople->name, &r, DT_CENTER | DT_VCENTER);
						break;
					}
					else if ((y1 > (63 + 2 * relationMenuHeight + 6)) && (y1 < (63 + 3 * relationMenuHeight + 6)) && mklButton1)   /*������������ť����ѯ�ֵ�*/
					{
						fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*����������*/
						RECT r = { Frame + 15, 75,width - 135,  height - 215 };
						drawtext("�����ֵ��ǣ�", &r, DT_CENTER | DT_VCENTER);
						break;
					}
					else if ((y1 > (63 + 3 * relationMenuHeight + 9)) && (y1 < (63 + 4 * relationMenuHeight + 9)) && mklButton1)   /*�������ĸ���ť����ѯ����*/
					{
						fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*����������*/
						RECT r = { Frame + 15, 75,width - 135,  height - 215 };
						drawtext("���ĺ����ǣ�\n����1��...\n����2��", &r, DT_CENTER | DT_VCENTER);
						break;
					}
					else if ((y1 > (63 + 4 * relationMenuHeight + 12)) && (y1 < (63 + 5 * relationMenuHeight + 12)) && mklButton1)   /*�����������ť����ѯ���*/
					{
						fillrectangle(Frame, 60, width - 100, height - 2 * Frame);   /*����������*/
						ifgetGener = InputBox(getGeneration, 20, "", "��Ҫ��ѯ�ڼ���", "��ѯ", 300);
						if (ifgetGener)
						{
							RECT r = { Frame + 15, 75,width - 135,  height - 215 };
							drawtext("���ף�%s\nĸ�ף�%s", &r, DT_CENTER | DT_VCENTER);
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
	gettextstyle(&f);                     // ��ȡ��ǰ��������
	f.lfHeight = 35; // ��������߶�Ϊ 12
	settextcolor(RGB(72, 81, 81));
	setbkmode(TRANSPARENT);
	_tcscpy_s(f.lfFaceName, _T("����"));    // ��������Ϊ�����塱
	settextstyle(&f);
	char s[] = "��ͥ���ײ�ѯ";
	outtextxy(15, 15, s);
}

int main()
{
	char * info[100];
	char out[500] = "hhhhhhh";   /*֮�����������ֵ��out����*/
	initgraph(width, height);   /*������ͼ����*/
	initImg();
	title();
	DrawButtle();
	info[100] = GetMouse(out);   /*info����Ϊ��������*/
	_getch();              // �����������
	closegraph();           // �رջ�ͼ����
}
