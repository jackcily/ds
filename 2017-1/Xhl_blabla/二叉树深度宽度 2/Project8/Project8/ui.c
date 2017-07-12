// 引用的头文件
#include <windows.h> // Windows窗口程序编程，需要引用头文件 Windows.h
#include"game.h"
#include"stack.h"
#pragma comment(lib, "winmm.lib")
// 画图时使用的表示蛇和食物的圆形的直径像素点个数。
#define CELL_PIXEL			20
// 用来绘图的颜色
#define COLOR_BOUNDARY		RGB(139, 134, 130)
#define COLOR_TEXT			RGB(46,139,87)
//设置的游戏界面的大小
#define MAX_X		20// 游戏界面大小
#define MAX_Y		20// 游戏界面大小


// 全局变量
HINSTANCE hinst; /// HINSTANCE是用来表示程序运行实例的句柄，某些API函数会使用到这个变量。
RECT rectBoundary;
HBITMAP hbmpBackground;//用于绘制背景
HBITMAP hbmpFighter;//用于绘制飞机
INT flag ;//用于判断游戏是否正式开始
// 函数声明
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(	HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,  int nCmdShow) 
{
	WNDCLASS wc;
	HWND hwnd;// 窗口句柄，hwnd变量是主窗口的句柄，这个程序中只用到了一个窗口。
	MSG msg;
	int fGotMessage;
	hinst = hinstance;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hinstance;
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL,	IDC_CROSS);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = "MainMenu";
	wc.lpszClassName = "MainWClass";
	flag = 0;//进行游戏初始化
	if (!RegisterClass(&wc))
	{
		// 窗口注册失败，消息框提示，并退出。
		MessageBox(NULL, "创建窗口class失败", "错误！", MB_ICONERROR | MB_OK);
		return -1;
	}
	// 窗口注册成功，继续运行。

	//创建窗口时会触发事件   在绘制窗口之前首先会进入   那个事件   去处理绘制窗口之前的事件
	hwnd = CreateWindow("MainWClass",				"Pop Star!!",	
		//WS_OVERLAPPEDWINDOW,	// 窗口的style，这个表示为top-level window 
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX& ~WS_THICKFRAME,//固定窗口大小
		CW_USEDEFAULT,			// 窗口水平位置default horizontal POINT 
		CW_USEDEFAULT,			// 窗口垂直位置default vertical POINT 
		CW_USEDEFAULT,			// 窗口宽度 default width 
		CW_USEDEFAULT,			// 窗口高度 default height 
		(HWND)NULL,				// 父窗口句柄 no owner window 
		(HMENU)NULL,			// 窗口菜单的句柄 use class menu 
		hinstance,				// 应用程序实例句柄 handle to application instance 
		(LPVOID)NULL);			// 指向附加数据的指针 no window-creation data 

	if (!hwnd)
	{
		// 窗口创建失败，消息框提示，并退出。
		MessageBox(NULL, "创建窗口失败", "错误！", MB_ICONERROR | MB_OK);
		return -1;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while ((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0	&& fGotMessage != -1)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}



void GamePaint2(HWND hwnd,int x)
{//只用来绘画图片
//RedrawWindow(hwnd);
	HPEN hpen;
	HDC hdc, hdcmem;
	HBITMAP hbmMem;

	HPEN hPenBoundary;
	HBRUSH hOldBrush;
	HFONT hFont, hOldFont;

	RECT rect;
	int i, j;  
	
	GetClientRect(hwnd, &rect);
	//GetWindowRect(hwnd, &rect);
	//hdc = GetDC(hwnd);
	hdc = GetWindowDC(hwnd);
	hdcmem = CreateCompatibleDC(hdc);
	hbmMem = CreateCompatibleBitmap(hdc,rect.right - rect.left, rect.bottom - rect.top);
      
	SelectObject(hdcmem, hbmMem);
	hpen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));  // PEN， PS_NULL表示不可见
	hPenBoundary = CreatePen(0, 3, COLOR_BOUNDARY);
	//画背景
	FillRect(hdcmem, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	SelectObject(hdcmem, hpen);
	//添加位图
	  BITMAP bmp;
	  if (x == 1)   hbmpBackground = LoadImage(NULL, BITMAP_FILE_BK,IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//如果是 1 就是切换关卡的图片
	  else if(x==2) hbmpBackground = LoadImage(NULL, BITMAP_FILE_BK2, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//如果是2 就是开始的关卡
	  else if(x==3) hbmpBackground = LoadImage(NULL, BITMAP_FILE_BK3, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//如果是3 就是菜单的关卡
       SelectObject(hdcmem, hbmpBackground);
	  //画方格  画出所有的星星  后期只要再改变笔刷就行了



	GetObject(hbmpBackground, sizeof(BITMAP), &bmp);
	//将图片进行绘制  由内存绘制到图片
	  SelectObject(hdcmem, hPenBoundary);

	

	///  FillRect(hdcmem, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	  //为什么我后来清空内存的时候无法清空之前的内存呢

	// 在内存DC中画完，一次输出的窗口DC上。
	BitBlt(hdc, 10, 10, rect.right - rect.left, rect.bottom - rect.top, hdcmem, 0, 0, SRCCOPY);

	//回收资源
	DeleteObject(hbmMem);
	DeleteObject(hdcmem);
	DeleteObject(hpen);
	DeleteObject(hPenBoundary);
	//释放占用的DC等资源
	ReleaseDC(hwnd, hdc);
}
void GamePaint(HWND hwnd)
{
	
	HPEN hpen;
	HDC hdc, hdcmem, hdcBitmapSrc;////////
	HBITMAP hbmMem;
	BITMAP bmp;///////////

	HPEN hPenBoundary;
	HPEN hOldPen;

	HBRUSH hOldBrush;
	HBRUSH  hb0= CreateSolidBrush(RGB(255, 255, 0));//黄
    HBRUSH  hb1 = CreateSolidBrush(RGB(238, 44, 44));//红
	HBRUSH  hb2 = CreateSolidBrush(RGB(70, 130, 180));//蓝
	HBRUSH  hb3 = CreateSolidBrush(RGB(0, 100, 0));//绿
	HBRUSH  hb4 = CreateSolidBrush(RGB(255, 193, 193));//粉
	HFONT hFont, hOldFont;

	RECT rect;
	int i, j;

    
	GetClientRect(hwnd, &rect);
        hdc = GetDC(hwnd); 
	hdcmem = CreateCompatibleDC(hdc);//一个是创建dc
	hbmMem = CreateCompatibleBitmap(hdc,//一个是创建位图
	rect.right - rect.left, rect.bottom - rect.top);
	SelectObject(hdcmem, hbmMem);
	hpen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));  // PEN， PS_NULL表示不可见
	hPenBoundary = CreatePen(0, 3, COLOR_BOUNDARY);	


	/****************************************************************/	




	hbmpFighter = LoadImage(NULL, "dee.bmp",
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hbmpFighter == NULL)
	{
		MessageBox(hwnd, "bmp file not find", "ERROR!",
			MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}


	hdcBitmapSrc = CreateCompatibleDC(hdc);//又创建了一个和hecmem相同等级的  hdc
	SelectObject(hdcBitmapSrc, hbmpFighter);  //这次是直接把图片选了进来

	GetObject(hbmpFighter, sizeof(BITMAP), &bmp);

FillRect(hdcmem, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	StretchBlt(hdcmem,
		20,
		20,100,100,
		hdcBitmapSrc,
		0, 0, bmp.bmWidth, bmp.bmHeight,
		SRCCOPY);





	/*****************************************************************/

    // 画背景
	
	//FillRect(hdcmem, &rect, hb3);
	hOldPen = (HPEN)SelectObject(hdcmem, hpen);


	//画方格  画出所有的星星  后期只要再改变笔刷就行了
	for (j= 0; j < 10; j++)
	{
    for (i= 0; i < 10; i++)
	{
	if (StarMap[i][j] == 0)	hOldPen =SelectObject(hdcmem, hb1);//红
		else if(StarMap[i][j]==1)  SelectObject(hdcmem, hb2);//蓝
		else if(StarMap[i][j]==2)  SelectObject(hdcmem, hb3);//绿
		else if(StarMap[i][j]==3)  SelectObject(hdcmem, hb4);//黄
		else if(StarMap[i][j]==4)  SelectObject(hdcmem, hb0);//粉
		else if (StarMap[i][j] == 5) SelectObject(hdcmem, GetStockObject(WHITE_BRUSH));
		Rectangle(hdcmem,
			rectBoundary.left+j*CELL_PIXEL*2,
			rectBoundary.top+ i*CELL_PIXEL * 2, 
			rectBoundary.left + j*CELL_PIXEL * 2+ CELL_PIXEL * 2, 
			rectBoundary.top + i*CELL_PIXEL * 2 + CELL_PIXEL * 2);
	}
}
	
	SelectObject(hdcmem, hPenBoundary);
//	 将PEN移动到需要绘制的方框的左上角
	MoveToEx(hdcmem, rectBoundary.left, rectBoundary.top, NULL);
//	 画了一个方框。演示LineTo函数
	LineTo(hdcmem, rectBoundary.left, rectBoundary.bottom);
	LineTo(hdcmem, rectBoundary.right, rectBoundary.bottom);
	LineTo(hdcmem, rectBoundary.right, rectBoundary.top);
	LineTo(hdcmem, rectBoundary.left, rectBoundary.top);

	//	 创建了一个字体对象
	hFont = CreateFont(25, 0, 0, 0, FW_DONTCARE, 0, 1, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));
	// 将这个FONT对象放入DC中
	if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
	{
		CHAR szSourceInfo[1024];
		wsprintf(szSourceInfo, "Goal %d Score %d Level %d", GetLevelScore(),score,level);
		//	 设置输出颜色
		SetTextColor(hdcmem, COLOR_TEXT);
		//	 输出字符串。
		TextOut(hdcmem, rectBoundary.left + 3, rectBoundary.bottom + 3,
			szSourceInfo, lstrlen(szSourceInfo));
		//	 输出完成，将原来的字体对象放回DC中
		SelectObject(hdcmem, hOldFont);
	}

	/*BitBlt(hdc,
		0, 0, rect.right - rect.left, rect.bottom - rect.top,
		hdcmem, 0, 0, SRCCOPY);
*/

	BitBlt(hdc,
		rect.left, rect.top,
		rect.right - rect.left, rect.bottom - rect.top,
		hdcmem,
		0, 0,
		SRCCOPY);


  //   回收资源
	DeleteObject(hbmMem);
	DeleteObject(hdcmem);
	DeleteObject(hpen);
	DeleteObject(hPenBoundary);
	DeleteObject(hFont);
	DeleteObject(hb1);
	DeleteObject(hb2);
	DeleteObject(hb3);
	DeleteObject(hb4);

	//释放占用的DC等资源
	ReleaseDC(hwnd, hdc);
}
 ///根据游戏界面的坐标系大小设置游戏窗口大小    
void ReSizeGameWnd(HWND hwnd)
{
	POINT ptLeftTop;		// 左上角
	POINT ptRightBottom;	// 右下角
	RECT rectWindow;
	POINT* pCoordBoundary = GetBoundary();

	// 设置游戏边界
	rectBoundary.left = 10;
	rectBoundary.top = 10;
	rectBoundary.right = 10 + CELL_PIXEL*(pCoordBoundary->x );
	rectBoundary.bottom = 10 + CELL_PIXEL*(pCoordBoundary->y );
	
	// 计算上下左右角的位置
	ptLeftTop.x = rectBoundary.left;
	ptLeftTop.y = rectBoundary.top;
	ptRightBottom.x = rectBoundary.right;
	ptRightBottom.y = rectBoundary.bottom;
	ClientToScreen(hwnd, &ptLeftTop);//取得相对整个屏幕的坐标
	ClientToScreen(hwnd, &ptRightBottom);
	
	GetWindowRect(hwnd, &rectWindow);
	// 计算好了，设置窗口大小。
	MoveWindow(hwnd,  	rectWindow.left,rectWindow.top,
		ptLeftTop.x - rectWindow.left + ptRightBottom.x - rectWindow.left,//同时向左移一定的空间   同时减去一个值
	  rectBoundary.bottom+120, //给积分信息留出显示空间。   //没有改变窗口的大小只是改变了窗口的相对位置
		TRUE);
}
LONG CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int i, j;
	POINT pt;
	switch (msg)
	{
		// 当窗口被创建时，收到的第一个消息就是WM_CREATE，一般收到这个消息处理过程中，可以用来进行一些初始化的工作
	case WM_CREATE:
		SetBoundary();
		InitGame();
		InitLevel();
		InitStarmap(GetColorNum());//初始化迷宫
		ReSizeGameWnd(hwnd);
		break;
	case WM_PAINT:
	/*	if (flag == 0)
		{
			GamePaint2(hwnd, 2);
		}
		else*/ 	//GamePaint(hwnd);
		FightWindowPaint(hwnd);
		break;
	case WM_KEYDOWN:
	//	GamePaint(hwnd);
		FightWindowPaint(hwnd);
		break;
	case WM_LBUTTONDOWN:	//当鼠标左键击中窗口  触发该事件
		////if (flag == 0)
		////{
		////	if (wParam && MK_LBUTTON)
		////	{
		////		pt.x = LOWORD(lParam);
		////		pt.y = HIWORD(lParam);
		////		//然后进行相应的处理
		////		JudgeChange(&pt);
		////		if (Judge(pt) == 1) flag = 1;
		////		else if (Judge(pt) == 2) GamePaint2(hwnd, 3);//帮助的图片
		////		else if (Judge(pt) == 3)  ExitProcess(0);
		////		GamePaint(hwnd);//重绘
		////		
		////	}
		////}
		//flag = 1;
		///*else*/ if (flag == 1)
		//{
		//
		//	if (wParam && MK_LBUTTON)
		//	{
		//		pt.x = LOWORD(lParam);
		//		pt.y = HIWORD(lParam);
		//		GetSeat(&pt);
		//		//进行星星消除判断
		//		if (RemoveStar(pt))
		//		{
		//			PlaySound("d:\\Documents\\Visual Studio 2017\\Projects\\Project8\\Project8\\touch.wav", NULL, SND_FILENAME | SND_ASYNC);
		//		}
		//		AddScore(NumOfStar);//对消除的星星进行加分	
		//		if (ChangeSit())  Sleep(50000);
		//		GamePaint(hwnd);//重绘
		//		if (CloseStar())	 Sleep(30000);
		//		GamePaint(hwnd);//重绘
		//   //PlaySound("SystemStart", NULL, SND_ASYNC | SND_ASYNC);

		////PlaySound("d:\\Documents\\Visual Studio 2017\\Projects\\Project8\\Project8\\remove.wav", NULL, SND_FILENAME | SND_ASYNC);
		//		if (isWin())//判断是否已经赢了
		//		{
		//			AddLevel();
		//			if (level > 6)
		//			{
		//				MessageBox(NULL, "恭喜", "你已经通关！", MB_ICONEXCLAMATION | MB_OK);
		//				ExitProcess(0);
		//			}
		//			else
		//			{
		//				//进入下一关
		//				Sleep(500);
		//				GamePaint2(hwnd, 1);
		//				InitGame();
		//				InitStarmap(GetColorNum());//初始化迷宫
		//				Sleep(800);
		//				GamePaint(hwnd);
		//			}
		//		}
		//		if (isDead() == 0 && isWin() == 0)
		//		{//如果没赢的话就判断游戏是否已经结束
		//			MessageBox(NULL, "很遗憾 ", "你失败了！", MB_ICONEXCLAMATION | MB_OK);
		//			ExitProcess(0);
		//		}
		//		break;
		//	}
		//}
		FightWindowPaint(hwnd);
	case WM_DESTROY:
		ExitProcess(0);
		break;

	default:
		break;
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
