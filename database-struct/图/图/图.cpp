/*********************************/
/*       数据结构——图          */
/*********************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*********************************/
/*      邻接矩阵类型的定义       */
/*********************************/

#define FINITY 2000
#define MAXSIZE 20
int visited[MAXSIZE];
typedef struct
{
	char vexs[MAXSIZE];   /*储存顶点信息*/
	int edges[MAXSIZE][MAXSIZE];   /*储存边与顶点的关系*/
	int e;   /*边的数目*/
	int n;   /*顶点数目*/
}Mgraph;

/*********************************/
/*      邻接表的结构体定义       */
/*********************************/

typedef struct node   /*表节点*/
{
	int adjvex;   /*邻接点域*/
	node * next;   /*指针域*/
	int power;   /*权值信息*/
}edgeNode;

typedef struct   /*头节点*/
{
	char vertex;   /*顶点*/
	edgeNode * firstedge;
}vertexNode;

typedef struct   /*邻接表*/
{
	vertexNode adjlist[MAXSIZE];
	int n;   /*边的数目*/
	int e;   /*顶点数目*/
}linkedGraph;

/*********************************/
/*    带权网络邻接矩阵的创建     */
/*********************************/

void creat(Mgraph * p,char * s)
{
	FILE *rf;
	int i,j,k,w;
	int c;   /*c=0代表图是无向图*/
	rf=fopen(s,"r");
	if (rf)
	{
		fscanf(rf, "%d", &c);
		fscanf(rf, "%d%d", &p->n, &p->e);   /*读入顶点数和边数*/
		for (i = 0; i < p->n; i++)   /*读取顶点信息*/
		{
			fscanf(rf, "%ls", &p->vexs[i]);
		}
		for (i = 0; i < p->n; i++)   /*初始化邻接矩阵*/
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
		printf("读取文件失败");
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
/*    带权网络的邻接表的创建     */
/*********************************/
linkedGraph * linkCreat(linkedGraph * s, char * path )
{
	FILE * rf;
	edgeNode *p;
	int c;   /*标志是否是无向图*/
	int h;   /*标志是否是网络*/
	int i, j,power,a,b;
	rf = fopen(path, "r");
	if (rf)
	{
		fscanf(rf, "%d", &c);   /*读入c的值，c为0，表示建立无向图*/
		fscanf(rf, "%d", &h);   /*读入 h 的值，若h!=0，则为网络*/
		fscanf(rf, "%d%d", &s->n, &s->e);   /*读入顶点数，边数*/
		for (i = 0; i < s->n; i++)
		{
			fscanf(rf, "%ls", &s->adjlist[i].vertex);   /*读入顶点信息*/
			s->adjlist[i].firstedge = NULL;   /*初始化边表，置空*/
		}
		for (j = 0; j < s->e; j++)
		{
			fscanf(rf, "%d%d", &a, &b);   /*读入边的信息*/
			if (h)
			{
				fscanf(rf, "%d", &power);   /*读入边的权值*/
			}
			p=(edgeNode*)malloc(sizeof(edgeNode));   /*类似带头节点的单链表的插入*/
			p->adjvex = b;
			if (h)
			{
				p->power = power;
			}
			p->next = s->adjlist[a].firstedge;
			s->adjlist[a].firstedge = p;
			if (c == 0)
			{
				p = (edgeNode*)malloc(sizeof(edgeNode));   /*类似带头节点的单链表的插入*/
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
		printf("读取文件失败！");
		exit(1);
	}
	return s;
}

/*********************************/
/*     深度优先遍历连通分量      */
/*********************************/

void dfs(linkedGraph s, int i)
{
	edgeNode *p;
	printf("visit vertex: %c \n", s.adjlist[i].vertex);   /*访问顶点i*/
	visited[i] = 1;
	p = s.adjlist[i].firstedge;
	while (p)    /*从p的邻接点出发搜索*/
	{
		if (!visited[p->adjvex])
			dfs(s, p->adjvex);
		p = p->next;
	}
}

/*********************************/
/*       图的深度优先遍历        */
/*********************************/

void DfsTraverse(linkedGraph  s)
{
	int i;
	for (i = 0; i < s.n; i++)
	{
		visited[i] = 0;   /*初始化标志数组*/
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
	//char s[] = "E:/vs2019/图/mgraph.txt";
	char c[] = "E:/vs2019/图/mgraph1.txt";
	//creat(p,s);
	m=linkCreat(m, c);
	DfsTraverse(*m);
	system("pause");
	return 0;
}