#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <string.h>


struct info {
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
struct person {
	info record;    //���׸��˽ڵ�
	person *child;  //ָ����
	person *brother;//ָ��һ���ֵ�
};

//˳��ջ��ͷ�ļ�
typedef struct stack
{
	person *data[100];
	int tag[100]; /*Ϊջ�е�ÿ��Ԫ�����õı��*/
	int top; /*ջ��ָ��*/
} seqstack;


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

void preorder(person *t)
{
	if (t)
	{
		printf("%s \n", t->record.name);
		preorder(t->brother);
		preorder(t->child);
	}
}


// �������ķǵݹ�ʵ��
void push(seqstack *s, person *t)  /*��ջ*/
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
	outtextxy(x - 5, y - 5, *c);   //���Ԫ��
}

int SuoJin = 1;
int Left = 50;
int Top = 35;

void imctree(person * tree,int x, int y)
{
	if (tree != NULL)
		draw(x, y, tree->record.name);
	if (tree->child != NULL) {
		SuoJin++;//����ֵ����1
		line(x - 14, y + 14, x - Left, y + 100 - 20); Sleep(100);//���߲���ͣ100ms
		imctree(tree->child, x - Left, y + 100);//�ݹ����������
	}
	if (tree->brother != NULL)
	{
		SuoJin++;//����ֵ����1
		line(x + 14, y + 14, x + Left, y + 100 - 20); Sleep(100);//���߲���ͣ100ms
		imctree(tree->brother, x + Left, y + 100);//�ݹ����������
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