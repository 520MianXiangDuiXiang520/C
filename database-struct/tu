#include<stdio.h>
#include<stdlib.h>
#include "ljb.h"
//邻接表存储结构
#define M 20
typedef char DataType;//定点
int visited[M]
//边表节点
typedef struct node{
int adjvex;//邻接点
struct node *next;
}EdgeNode;
//头节点类型
typedef struct vnode{
DataType vertex;//定点信息
EdgeNode *FirstEdge;//邻接链表头指针
}VertexNode;
//邻接表类型
typedef struct{
VertexNode adjlist[M];//存放头节点的顺序表
int n,e;//图的顶点数和边数
}LinkedGraph;
//建立图的邻接表
void creat(LinkedGraph *g,char *filename,int c)
{
    int i,j,k;
    EdgeNode *s;
    FILE *fp;
    fp=fopen(filename,"r");
    if(fp)
    {
        fscanf(fp,"%d%d",&g->n,&g->e);
        for(i=0;i<g->n;i++)
        {
            fscanf(fp,"%ls",&g->adjlist[i].vertex);
            g->adjlist[i].FirstEdge=NULL;
        }
    for(k=0;k<g->e;k++)
    {
        fscanf(fp,"%d%d",&i,&j);
        s=(EdgeNode *)malloc(sizeof(EdgeNode));
        s->adjvex=j;
        s->next=g->adjlist[i].FirstEdge;
        g->adjlist[i].FirstEdge=s;
        if(c==0)
        {
            s=(EdgeNode *)malloc(sizeof(EdgeNode));
            s->adjvex=i;
            s->next=j->adjlist[j].FirstEdge;
            g->adjlist[j].FirstEdge=s;
        }
    }
    fclose(fp);
    }
    else
        g->n=0;
}
//深度优先遍历
void dfs(LinkedGraph g,int i)
{
    EdgeNode *p;
    printf("visit vertex:%c \n",g.adjlist[i].vertex);
    visited[i]=1;
    p=g.adjlist[i].FirstEdge;
    while(p)
    {
        if(!visited[p->adjvex])
            dfs(g,p->adjvex);
        p=p->next;
    }
}
