/*********************************/
/*       ���ݽṹ����ͼ          */
/*********************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*********************************/
/*      �ڽӾ������͵Ķ���       */
/*********************************/

#define FINITY 2000
#define MAXSIZE 20
int visited[MAXSIZE];
typedef struct
{
	char vexs[MAXSIZE];   /*���涥����Ϣ*/
	int edges[MAXSIZE][MAXSIZE];   /*������붥��Ĺ�ϵ*/
	int e;   /*�ߵ���Ŀ*/
	int n;   /*������Ŀ*/
}Mgraph;

/*********************************/
/*      �ڽӱ�Ľṹ�嶨��       */
/*********************************/

typedef struct node   /*��ڵ�*/
{
	int adjvex;   /*�ڽӵ���*/
	node * next;   /*ָ����*/
	int power;   /*Ȩֵ��Ϣ*/
}edgeNode;

typedef struct   /*ͷ�ڵ�*/
{
	char vertex;   /*����*/
	edgeNode * firstedge;
}vertexNode;

typedef struct   /*�ڽӱ�*/
{
	vertexNode adjlist[MAXSIZE];
	int n;   /*�ߵ���Ŀ*/
	int e;   /*������Ŀ*/
}linkedGraph;

/*********************************/
/*    ��Ȩ�����ڽӾ���Ĵ���     */
/*********************************/

void creat(Mgraph * p,char * s)
{
	FILE *rf;
	int i,j,k,w;
	int c;   /*c=0����ͼ������ͼ*/
	rf=fopen(s,"r");
	if (rf)
	{
		fscanf(rf, "%d", &c);
		fscanf(rf, "%d%d", &p->n, &p->e);   /*���붥�����ͱ���*/
		for (i = 0; i < p->n; i++)   /*��ȡ������Ϣ*/
		{
			fscanf(rf, "%ls", &p->vexs[i]);
		}
		for (i = 0; i < p->n; i++)   /*��ʼ���ڽӾ���*/
		{
			for (j = 0; j < p->n; j++)
			{
				if (i == j)
					p->edges[i][j] = 0;
				else
					p->edges[i][j] = FINITY;
			}
		}
		for (k = 0; k < p->e; k++)
		{
			fscanf(rf, "%d%d%d", &i, &j, &w);
			p->edges[i][j] = w;
			if (c == 0)
				p->edges[j][i] = w;
		}
		fclose(rf);
	}
	else
	{
		p->n = 0;
		printf("��ȡ�ļ�ʧ��");
	}
	for ( i = 0; i < p->n; i++)
	{
		for ( j = 0; j < p->n; j++)
		{
			printf("%8d", p->edges[i][j]);
		}
		printf("\n");
	}
}


/*********************************/
/*    ��Ȩ������ڽӱ�Ĵ���     */
/*********************************/
linkedGraph * linkCreat(linkedGraph * s, char * path )
{
	FILE * rf;
	edgeNode *p;
	int c;   /*��־�Ƿ�������ͼ*/
	int h;   /*��־�Ƿ�������*/
	int i, j,power,a,b;
	rf = fopen(path, "r");
	if (rf)
	{
		fscanf(rf, "%d", &c);   /*����c��ֵ��cΪ0����ʾ��������ͼ*/
		fscanf(rf, "%d", &h);   /*���� h ��ֵ����h!=0����Ϊ����*/
		fscanf(rf, "%d%d", &s->n, &s->e);   /*���붥����������*/
		for (i = 0; i < s->n; i++)
		{
			fscanf(rf, "%ls", &s->adjlist[i].vertex);   /*���붥����Ϣ*/
			s->adjlist[i].firstedge = NULL;   /*��ʼ���߱��ÿ�*/
		}
		for (j = 0; j < s->e; j++)
		{
			fscanf(rf, "%d%d", &a, &b);   /*����ߵ���Ϣ*/
			if (h)
			{
				fscanf(rf, "%d", &power);   /*����ߵ�Ȩֵ*/
			}
			p=(edgeNode*)malloc(sizeof(edgeNode));   /*���ƴ�ͷ�ڵ�ĵ�����Ĳ���*/
			p->adjvex = b;
			if (h)
			{
				p->power = power;
			}
			p->next = s->adjlist[a].firstedge;
			s->adjlist[a].firstedge = p;
			if (c == 0)
			{
				p = (edgeNode*)malloc(sizeof(edgeNode));   /*���ƴ�ͷ�ڵ�ĵ�����Ĳ���*/
				p->adjvex = a;
				if (h)
				{
					p->power = power;
				}
				p->next = s->adjlist[b].firstedge;
				s->adjlist[b].firstedge = p;
			}
		}
		fclose(rf);
	}
	else
	{
		s->n = 0;
		printf("��ȡ�ļ�ʧ�ܣ�");
		exit(1);
	}
	return s;
}

/*********************************/
/*     ������ȱ�����ͨ����      */
/*********************************/

void dfs(linkedGraph s, int i)
{
	edgeNode *p;
	printf("visit vertex: %c \n", s.adjlist[i].vertex);   /*���ʶ���i*/
	visited[i] = 1;
	p = s.adjlist[i].firstedge;
	while (p)    /*��p���ڽӵ��������*/
	{
		if (!visited[p->adjvex])
			dfs(s, p->adjvex);
		p = p->next;
	}
}

/*********************************/
/*       ͼ��������ȱ���        */
/*********************************/

void DfsTraverse(linkedGraph  s)
{
	int i;
	for (i = 0; i < s.n; i++)
	{
		visited[i] = 0;   /*��ʼ����־����*/
	}
	for ( i = 0; i < s.n; i++)
	{
		if (!visited[i])
			dfs(s, i);
	}
}

int main()
{
	//Mgraph * p;
	linkedGraph * m;
	//p=  (Mgraph *)malloc(sizeof(Mgraph));
	m = (linkedGraph *)malloc(sizeof(linkedGraph));
	//char s[] = "E:/vs2019/ͼ/mgraph.txt";
	char c[] = "E:/vs2019/ͼ/mgraph1.txt";
	//creat(p,s);
	m=linkCreat(m, c);
	DfsTraverse(*m);
	system("pause");
	return 0;
}