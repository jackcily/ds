#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define MAXSIZE 100
#define MAXNUM 10
typedef char InfoType;
typedef char vertex;
typedef struct ANode
{
	int adjvex;//存储下标
	struct ANode *nextarc;//next指针
	InfoType Info;//char 用来干什么的
}ArcNode;//建立的图的元素

typedef struct
{
	vertex data;
	ArcNode *fistarc;
}VertexNode;//用来存数据的
typedef struct
{
	VertexNode adjlist[MAXSIZE];
	int n, e;
}ALGraph;//图的构成

struct QUEUE
{
	int _vertex;
	int pre;
}queue[MAXSIZE];//数组队列用于存储路径 
int front = -1, rear = -1;

void  _print(int front)
{
	int k = front, j, cnt = 0;
	do
	{
		j = k;
		k = queue[k].pre;
		queue[j].pre = -1;
	} while (k != 0);
	k = 0;
	while (k<MAXSIZE)
	{
		if (queue[k].pre == -1)
		{
			printf("%d ", queue[k]._vertex+1);
			cnt++;
		}
		k++;
	}
	//printf("/n%d/n", cnt - 1);
}
//void CreateALGraph(ALGraph*&, int**, int);
//void shortest_path(ALGraph*, int, int, int*);
void CreateALGraph(ALGraph **g, int array[][MAXSIZE], int k)
{//用了什么存储方式
	(*g) = (ALGraph *)malloc(sizeof(ALGraph));
	for (int i = 0; i<k; i++)
		(*g)->adjlist[i].fistarc = NULL;
	int cnt = 0;
	ArcNode *p;
	int i;
	for (i = 0; i<k; i++)
		for (int j = 0; j<k; j++)
			if (array[i][j] != 0)
			{
				p = (ArcNode *)malloc(sizeof(ArcNode));
				p->adjvex = j;
				p->nextarc = (*g)->adjlist[i].fistarc;
				(*g)->adjlist[i].fistarc = p;
			}
	(*g)->n = k; (*g)->e = cnt;
}
void shortest_path(ALGraph *g, int v, int u, int visited[])
{
	ArcNode *p;
	int m, find = 0;
	rear++;
	//我加的
   int nn;
	for (nn = 0; nn < MAXSIZE; nn++)
	{
		queue[nn]._vertex = 0;
		queue[nn].pre = 0;
	}
	//我加的
	//rear 
	queue[rear]._vertex = v;
	queue[rear].pre = -1;
	//
	visited[v] = 1;//把该点设为已经访问过
	while (front != rear && !find)
	{
		front++;
		m = queue[front]._vertex;
		if (m == u)
		{
			find = 1;
			_print(front);
			return;
		}
		p = g->adjlist[m].fistarc;
		while (p != NULL)
		{
			if (visited[p->adjvex] == 0)
			{
				visited[p->adjvex] = 1;
				rear++;
				queue[rear]._vertex = p->adjvex;
				queue[rear].pre = front;
			}
			p = p->nextarc;
		}
	}
}

int main()
{
	int graph_array[][MAXSIZE] = {
		{ 1,1,1 ,1,0,0, 1,0,0 },
		{ 1,1,1 ,0,0,0, 0,0,0 },
		{ 1,1,1, 0,0,0, 0,0,0 },
		{ 1,0,0, 1,1,1, 0,0,0 },
		{ 0,0,0, 1,1,1, 0,0,0 },
		{ 0,0,0, 1,1,1, 0,1,0 },
		{1,0,0, 0,0,0, 1,1,1},
		{ 0,0,0 ,0,0,1, 1,1,1},
		{0,0,0 ,0,0,0, 1,1,1}
	};
	ALGraph *g;
	CreateALGraph(&g, graph_array, MAXNUM);//最多存储的点数为MAXNUM
	int i, j;
	for (i = 0; i < 9; i++)
	{
		printf("\n");

		for (j = 0; j < 9; j++)
		{
			if (i == j)
			{
			}
			else
			{
	    
			front = -1, rear = -1;
			int visited[MAXSIZE] = { 0 };
			printf("%d<->%d    ", i+1, j+1);
			shortest_path(g, i, j, visited);
			printf("\n");
			}
	
		}
	}


	return 0;
}
