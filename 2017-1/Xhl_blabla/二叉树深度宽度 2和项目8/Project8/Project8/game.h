//先写一个C语言版本的
//然后再慢慢进行改进
//#ifdef a

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

//#define BITMAP_FILE_BK		"cloud.bmp"
#define BITMAP_FILE_BK		"dee111.bmp"
#define BITMAP_FILE_BK2	"face3.bmp"
#define BITMAP_FILE_BK3	"dee.bmp"
#define BITMAP_FILE_BK4  "blue.bmp"
#define REMOVE -1//被消除为  -1
#define BLANK 5  //空格为5
#define INIT_SCORE 1000//初始通关分数

#define SCORE_TWO_TO_FOUR  10//2-4  每个砖块的分值
#define  SCORE_FIVE_TO_EIGHT  15//5-8  每个砖块的分值  15
#define  SCORE_NINE_  16   //9个及以上    每个砖块的分值  16

// 画图时使用的表示直径像素点个数。
#define CELL_PIXEL			20

//用来绘图的颜色
#define COLOR_BOUNDARY		RGB(139, 134, 130)
#define COLOR_TEXT			RGB(173,216,230)
#define MAX_X		20// 游戏界面大小
#define MAX_Y		20// 游戏界面大小


extern POINT boundary;
extern int StarMap[10][10];//记录星星的状态的二维数组
extern int level;//玩家玩游戏的等级
extern int score;//玩家的分数

int  GetColorNum();//返回星星的颜色数目
int InitStarmap(int size);//初始化二维数组
int InitGame();//初始化游戏各个变量
int  AddScore(int num);//每一次消除后增加分数
int isDead();//判断是否进入死局 即游戏是否结束
int ChangeSit();//被消除的星星设为-1 当所有星星被设为 -1后  集中进行消除  然后检索每排是不是有被消除的  进行相应的移位操作
int RemoveStar(POINT pt);
double  GetRate();//根据等级将需要 返回需要的初始分数的增长
double GetGainScoreRate() ;//根据等级返回计分时需要增加的分数比例
int  GetLevelScore();//根据不同的等级返回该等级需要达到的分数
int isWin();//判断是否进入下一关
int  GetSeat(POINT *p);
int CloseStar();//判断是否需要进行真正意义上的重绘
int AddLevel();//如果赢了就行等级的加加
int InitLevel();
int  Judge(POINT pt);//如果返回	1 就执行开始游戏 如果返回2 就执行游戏帮助  如果返回三就结束游戏
int JudgeChange(POINT *pt);
//#endif


