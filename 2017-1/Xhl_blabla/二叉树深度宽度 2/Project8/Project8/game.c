
//实现所有游戏主要功能
#include"game.h"
#include"stack.h"
 int StarMap[10][10];//记录星星的状态的二维数组
int level;//玩家玩游戏的等级
 int score;//玩家的分数
 POINT boundary;

int InitStarmap(int size)//初始化二维数组
{
	srand(time(NULL));
	int i;
	int j;
	int temp;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			StarMap[i][j] = rand() % size;
			/*scanf("%d", &temp);
			StarMap[i][j] = temp;*/
		}
	}
	return 0;
}
// 设置边界坐标
 void SetBoundary()
 {
	 boundary.x = MAX_X;
	 boundary.y =  MAX_Y;
 }
// 获得边界坐标
POINT*  GetBoundary()
 {
	 return &boundary;
 }
int  GetColorNum()//返回星星的颜色数目
{
	if (level <= 3)return 4;
	return 5;
}
int InitLevel()
{
	level = 1;
	return 0;
}
int AddLevel()
{
	level++;
	return 0;
}
int InitGame()//初始化游戏各个变量
{
	score = 0;
	return 0;
}
int  AddScore(int num)//每一次消除后增加分数
{//要分段进行计分  方块消得越多就越高
	if(num<5)
	score += GetGainScoreRate()*SCORE_TWO_TO_FOUR *num;
	else if(num<9)
		score += GetGainScoreRate()*SCORE_FIVE_TO_EIGHT*num;
	else 
		score += GetGainScoreRate()*SCORE_NINE_*num;
	
	return 0;
}
int isDead()//判断是否进入死局 即游戏是否结束
{
	int i;
	int j;
	for (i = 0; i <10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (StarMap[i][j] != 5)//如果不是空格
			{
				//如果只有两个邻接块
				if (i == 9 && j == 9)
				{
					if (StarMap[9][9] == StarMap[9][8] || StarMap[9][9] == StarMap[8][9])   return 1;
				}
				else if (i == 0 && j == 0)
				{
					if (StarMap[0][0] == StarMap[0][1] || StarMap[0][0] == StarMap[1][0])   return 1;
				}
				else if (i == 0 && j == 9)
				{
                          if(StarMap[0][9] == StarMap[0][8] || StarMap[0][9] == StarMap[1][9])  return 1;
				}
				else if (i == 9 && j == 0)
				{
					if (StarMap[9][0] == StarMap[9][1] || StarMap[9][0] == StarMap[8][0])    return 1;
				}
		      //如果只有三个邻接块
				else if (i == 0)
				{
					if (StarMap[i][j] == StarMap[i + 1][j] || StarMap[i][j] == StarMap[i][j + 1] || StarMap[i][j] == StarMap[i][j - 1])  return 1;
				}
				else if (i == 9)
				{
					if ( StarMap[i][j] == StarMap[i][j + 1] || StarMap[i][j] == StarMap[i][j - 1] || StarMap[i][j] == StarMap[i - 1][j])  return 1;

				}
				else if (j == 0)
				{
					if (StarMap[i][j] == StarMap[i + 1][j] || StarMap[i][j] == StarMap[i][j + 1]  || StarMap[i][j] == StarMap[i - 1][j])  return 1;

				}
				else if (j == 9)
				{
					if (StarMap[i][j] == StarMap[i + 1][j]|| StarMap[i][j] == StarMap[i][j - 1] || StarMap[i][j] == StarMap[i - 1][j])  return 1;

				}
				else
				{
					if (StarMap[i][j] == StarMap[i + 1][j] || StarMap[i][j] == StarMap[i][j + 1] || StarMap[i][j] == StarMap[i][j - 1]||StarMap[i][j]==StarMap[i-1][j])  return 1;
				}
			}	
		 }
	}
	return 0;//死亡
}
int ChangeSit()//被消除的星星设为-1 当所有星星被设为 -1后  集中进行消除  然后检索每排是不是有被消除的  进行相应的移位操作
{
	int i;
	int j;
	int k;
	int flag = 0;
	int flag2 = 0;
	int leftnum=9;
	for (j = 0; j < 10; j++)
	{
		flag = 0;
		leftnum = 9;
		int n[10];
		for (i = 9; i >= 0; i--)
		{  //将一行筛选后存进去
			if (flag == 1) flag = 2;
			if (StarMap[i][j] != -1)
			{
				n[leftnum--] = StarMap[i][j];
			}
			else if (flag == 0) flag = 1;
		}
		while (leftnum >= 0)
		{
			n[leftnum--] = 5;//将剩余的地方设为空格
		}

		for (i = 0; i < 10; i++)
		{
			StarMap[i][j] = n[i];//再复制回去
		}
		if (flag == 2)
		{
			flag2 = 1;
		}
	}
	if (flag == 1)return 1;
	return 0;
}
int RemoveStar(POINT pt)//返回值返回消除的星星个数 根据传入的坐标和二维数组判断能消除的星星个数
{
	Mystack path;//记录路径的栈
	Initstack(&path);//初始化路径 ，初始化栈长?
	int  flag;
	POINT curp;//正在走的坐标块
	curp.x = pt.x;//初始化入口
	curp.y = pt.y;
	int curstep = 1;//探索的步数
	NumOfStar = 0;
	int  InitColor = StarMap[pt.x][pt.y];
	if (InitColor == 5)  return 0;//如果初始颜色块为空格，就直接返回
	SetColor(pt);
	//记录最初的颜色如果最后只有一个星星块的话  可以退回去
	do
	{
		if (Pass(curp))//当前位置可以通过
		{//将当前位置存入栈
			Footprint(curp);
			SElement e;
			e.di = 1;//设定探索方向
			e.ord = curstep;
			e.seat.x = curp.x;
			e.seat.y = curp.y;
			Push(&path, e);
			//printf("将（%d %d)入栈\n\n", curp.x, curp.y);
			GetRightDirection(curp, &e.di);//保证传入的数值是  正确的方向  
										   //因为起始值是1
								   //不用判断还要不要走了
			curp = Nextposition(curp, e.di);////找下一个被试块
											//找到前一个被试块东面的路径块作为被试块，优先试最东边的块
	
			curstep++;//探步数增加
		}
		else
		{
			if (isStackempty(&path))//如果栈不空
			{
				SElement e;
				Pop(&path, &e);//退回上一步
				curstep--;
				//弹出来的这个坐标就是当前的被测坐标

				//难道这时候
				e.di++;
				GetRightDirection(e.seat, &e.di);//保证传入的数值是  正确的方向  
				e.di--;						 //将所有周围被测试过的路从栈中清除
				while (e.di >=4 && isStackempty(&path))
				{
					//Markprint(e.seat);
					//printf("四个方向均不可走 弹出（%d %d)  ", e.seat.x, e.seat.y);
					Pop(&path, &e);
				//	printf("退回 (%d %d)\n\n", e.seat.x, e.seat.y);
					//如果之前的e被弹出来   那么新的e 的方向将会被使用 
					//所有e 在使用之前都要进行检验
					e.di++;
					GetRightDirection(e.seat, &e.di);//保证传入的数值是  正确的方向  
					e.di--;						 //将所有周围被测试过的路从栈中清除
				}
				//如果当前栈顶还有没有被测试的路径就进行测试
				if (e.di < 4)
				{
					curp = Nextposition(e.seat, e.di+1);
					e.di++;
					curstep++;
					Push(&path, e);
				}

			}

		}

	} while (isStackempty(&path));
	if (NumOfStar == 1)
	{
       StarMap[pt.x][pt.y]=InitColor ;
	   NumOfStar--;
	    //如果只有一个星星要消除的话 就不消除了
	   flag = 0;
	}	
	else flag = 1;
	//进行这一步本来就是要行数组写入而已
	clear(&path);
	return  flag;
}
double GetRate()//根据等级将需要 返回需要的初始分数的增长
{
	return 1 + level*0.15;
}
double   GetGainScoreRate()//根据等级返回计分时需要增加的分数比例
{
	return 1 + level*0.2;
}
int  GetLevelScore()//根据不同的等级返回该等级需要达到的分数
{
	return  GetRate()*INIT_SCORE;
}
int isWin()//判断是否进入下一关
{//只返回下一级
	if (GetLevelScore() <= score)
	{
	 return 1;
	}
	return 0;
}
int  GetSeat(POINT* p)
{
	int k;
	p->x = (p->x - 10) / 40;
	p->y = (p->y - 10) / 40;
	k = p->x;
	p->x = p->y;
	p->y = k;
	return 0;
}
//就按照正常的行序 列序写 所有的主要函数都这样
int CloseStar()
{//写错了  真尴尬
	int  num=0;
	int n[10];
	int i, j;
	int k = 0;
	int flag = 0;
	//先将不是空列的元素存进数组
	for (j = 0; j < 10; j++)
	{
		for (i = 0; i < 10; i++)
		{
			if (StarMap[i][j] != 5)
			{
				if (flag == 1)flag == 2;
				n[num++] = j;
				break;
			}
			else  if(flag==0)
			{
				flag = 1;
			}
		}
	}
	//进行依次赋值
	for (j = 0; j < num; j++)
	{
		for (i = 0; i < 10; i++)
		{
			StarMap[i][j] = StarMap[i][n[k]];
		}
		k++;
   }
	//空白处填入空格
	while (j < 10)
	{
		for (i = 0; i < 10; i++)
		{
			StarMap[i][j] = 5;
		}
		j++;
	}
	if (flag == 2)  return 1;
	return 0;
}
//如果返回	1 就执行开始游戏 如果返回2 就执行游戏帮助  如果返回三就结束游戏
int  JudgeChange(POINT *pt)
{
	
	pt->x = pt->x-10;
	pt->y = pt->y-10;
	return 0;
}
int  Judge(POINT pt)
{
	if (pt.x < 130 && pt.x>60)
	{
		if (pt.y < 232 && pt.y>190) return 1;
		else if (pt.y < 282 && pt.y>240)  return 2;
		else if (pt.y < 332 && pt.y>290)   return 3;
	}
	else  return 0;
}

