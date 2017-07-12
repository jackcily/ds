// ���õ�ͷ�ļ�
#include <windows.h> // Windows���ڳ����̣���Ҫ����ͷ�ļ� Windows.h
#include"game.h"
#include"stack.h"
#pragma comment(lib, "winmm.lib")
// ��ͼʱʹ�õı�ʾ�ߺ�ʳ���Բ�ε�ֱ�����ص������
#define CELL_PIXEL			20
// ������ͼ����ɫ
#define COLOR_BOUNDARY		RGB(139, 134, 130)
#define COLOR_TEXT			RGB(46,139,87)
//���õ���Ϸ����Ĵ�С
#define MAX_X		20// ��Ϸ�����С
#define MAX_Y		20// ��Ϸ�����С


// ȫ�ֱ���
HINSTANCE hinst; /// HINSTANCE��������ʾ��������ʵ���ľ����ĳЩAPI������ʹ�õ����������
RECT rectBoundary;
HBITMAP hbmpBackground;//���ڻ��Ʊ���
HBITMAP hbmpFighter;//���ڻ��Ʒɻ�
INT flag ;//�����ж���Ϸ�Ƿ���ʽ��ʼ
// ��������
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(	HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,  int nCmdShow) 
{
	WNDCLASS wc;
	HWND hwnd;// ���ھ����hwnd�����������ڵľ�������������ֻ�õ���һ�����ڡ�
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
	flag = 0;//������Ϸ��ʼ��
	if (!RegisterClass(&wc))
	{
		// ����ע��ʧ�ܣ���Ϣ����ʾ�����˳���
		MessageBox(NULL, "��������classʧ��", "����", MB_ICONERROR | MB_OK);
		return -1;
	}
	// ����ע��ɹ����������С�

	//��������ʱ�ᴥ���¼�   �ڻ��ƴ���֮ǰ���Ȼ����   �Ǹ��¼�   ȥ������ƴ���֮ǰ���¼�
	hwnd = CreateWindow("MainWClass",				"Pop Star!!",	
		//WS_OVERLAPPEDWINDOW,	// ���ڵ�style�������ʾΪtop-level window 
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX& ~WS_THICKFRAME,//�̶����ڴ�С
		CW_USEDEFAULT,			// ����ˮƽλ��default horizontal POINT 
		CW_USEDEFAULT,			// ���ڴ�ֱλ��default vertical POINT 
		CW_USEDEFAULT,			// ���ڿ�� default width 
		CW_USEDEFAULT,			// ���ڸ߶� default height 
		(HWND)NULL,				// �����ھ�� no owner window 
		(HMENU)NULL,			// ���ڲ˵��ľ�� use class menu 
		hinstance,				// Ӧ�ó���ʵ����� handle to application instance 
		(LPVOID)NULL);			// ָ�򸽼����ݵ�ָ�� no window-creation data 

	if (!hwnd)
	{
		// ���ڴ���ʧ�ܣ���Ϣ����ʾ�����˳���
		MessageBox(NULL, "��������ʧ��", "����", MB_ICONERROR | MB_OK);
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
{//ֻ�����滭ͼƬ
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
	hpen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));  // PEN�� PS_NULL��ʾ���ɼ�
	hPenBoundary = CreatePen(0, 3, COLOR_BOUNDARY);
	//������
	FillRect(hdcmem, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	SelectObject(hdcmem, hpen);
	//���λͼ
	  BITMAP bmp;
	  if (x == 1)   hbmpBackground = LoadImage(NULL, BITMAP_FILE_BK,IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//����� 1 �����л��ؿ���ͼƬ
	  else if(x==2) hbmpBackground = LoadImage(NULL, BITMAP_FILE_BK2, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//�����2 ���ǿ�ʼ�Ĺؿ�
	  else if(x==3) hbmpBackground = LoadImage(NULL, BITMAP_FILE_BK3, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//�����3 ���ǲ˵��Ĺؿ�
       SelectObject(hdcmem, hbmpBackground);
	  //������  �������е�����  ����ֻҪ�ٸı��ˢ������



	GetObject(hbmpBackground, sizeof(BITMAP), &bmp);
	//��ͼƬ���л���  ���ڴ���Ƶ�ͼƬ
	  SelectObject(hdcmem, hPenBoundary);

	

	///  FillRect(hdcmem, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	  //Ϊʲô�Һ�������ڴ��ʱ���޷����֮ǰ���ڴ���

	// ���ڴ�DC�л��꣬һ������Ĵ���DC�ϡ�
	BitBlt(hdc, 10, 10, rect.right - rect.left, rect.bottom - rect.top, hdcmem, 0, 0, SRCCOPY);

	//������Դ
	DeleteObject(hbmMem);
	DeleteObject(hdcmem);
	DeleteObject(hpen);
	DeleteObject(hPenBoundary);
	//�ͷ�ռ�õ�DC����Դ
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
	HBRUSH  hb0= CreateSolidBrush(RGB(255, 255, 0));//��
    HBRUSH  hb1 = CreateSolidBrush(RGB(238, 44, 44));//��
	HBRUSH  hb2 = CreateSolidBrush(RGB(70, 130, 180));//��
	HBRUSH  hb3 = CreateSolidBrush(RGB(0, 100, 0));//��
	HBRUSH  hb4 = CreateSolidBrush(RGB(255, 193, 193));//��
	HFONT hFont, hOldFont;

	RECT rect;
	int i, j;

    
	GetClientRect(hwnd, &rect);
        hdc = GetDC(hwnd); 
	hdcmem = CreateCompatibleDC(hdc);//һ���Ǵ���dc
	hbmMem = CreateCompatibleBitmap(hdc,//һ���Ǵ���λͼ
	rect.right - rect.left, rect.bottom - rect.top);
	SelectObject(hdcmem, hbmMem);
	hpen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));  // PEN�� PS_NULL��ʾ���ɼ�
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


	hdcBitmapSrc = CreateCompatibleDC(hdc);//�ִ�����һ����hecmem��ͬ�ȼ���  hdc
	SelectObject(hdcBitmapSrc, hbmpFighter);  //�����ֱ�Ӱ�ͼƬѡ�˽���

	GetObject(hbmpFighter, sizeof(BITMAP), &bmp);

FillRect(hdcmem, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	StretchBlt(hdcmem,
		20,
		20,100,100,
		hdcBitmapSrc,
		0, 0, bmp.bmWidth, bmp.bmHeight,
		SRCCOPY);





	/*****************************************************************/

    // ������
	
	//FillRect(hdcmem, &rect, hb3);
	hOldPen = (HPEN)SelectObject(hdcmem, hpen);


	//������  �������е�����  ����ֻҪ�ٸı��ˢ������
	for (j= 0; j < 10; j++)
	{
    for (i= 0; i < 10; i++)
	{
	if (StarMap[i][j] == 0)	hOldPen =SelectObject(hdcmem, hb1);//��
		else if(StarMap[i][j]==1)  SelectObject(hdcmem, hb2);//��
		else if(StarMap[i][j]==2)  SelectObject(hdcmem, hb3);//��
		else if(StarMap[i][j]==3)  SelectObject(hdcmem, hb4);//��
		else if(StarMap[i][j]==4)  SelectObject(hdcmem, hb0);//��
		else if (StarMap[i][j] == 5) SelectObject(hdcmem, GetStockObject(WHITE_BRUSH));
		Rectangle(hdcmem,
			rectBoundary.left+j*CELL_PIXEL*2,
			rectBoundary.top+ i*CELL_PIXEL * 2, 
			rectBoundary.left + j*CELL_PIXEL * 2+ CELL_PIXEL * 2, 
			rectBoundary.top + i*CELL_PIXEL * 2 + CELL_PIXEL * 2);
	}
}
	
	SelectObject(hdcmem, hPenBoundary);
//	 ��PEN�ƶ�����Ҫ���Ƶķ�������Ͻ�
	MoveToEx(hdcmem, rectBoundary.left, rectBoundary.top, NULL);
//	 ����һ��������ʾLineTo����
	LineTo(hdcmem, rectBoundary.left, rectBoundary.bottom);
	LineTo(hdcmem, rectBoundary.right, rectBoundary.bottom);
	LineTo(hdcmem, rectBoundary.right, rectBoundary.top);
	LineTo(hdcmem, rectBoundary.left, rectBoundary.top);

	//	 ������һ���������
	hFont = CreateFont(25, 0, 0, 0, FW_DONTCARE, 0, 1, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));
	// �����FONT�������DC��
	if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
	{
		CHAR szSourceInfo[1024];
		wsprintf(szSourceInfo, "Goal %d Score %d Level %d", GetLevelScore(),score,level);
		//	 ���������ɫ
		SetTextColor(hdcmem, COLOR_TEXT);
		//	 ����ַ�����
		TextOut(hdcmem, rectBoundary.left + 3, rectBoundary.bottom + 3,
			szSourceInfo, lstrlen(szSourceInfo));
		//	 �����ɣ���ԭ�����������Ż�DC��
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


  //   ������Դ
	DeleteObject(hbmMem);
	DeleteObject(hdcmem);
	DeleteObject(hpen);
	DeleteObject(hPenBoundary);
	DeleteObject(hFont);
	DeleteObject(hb1);
	DeleteObject(hb2);
	DeleteObject(hb3);
	DeleteObject(hb4);

	//�ͷ�ռ�õ�DC����Դ
	ReleaseDC(hwnd, hdc);
}
 ///������Ϸ���������ϵ��С������Ϸ���ڴ�С    
void ReSizeGameWnd(HWND hwnd)
{
	POINT ptLeftTop;		// ���Ͻ�
	POINT ptRightBottom;	// ���½�
	RECT rectWindow;
	POINT* pCoordBoundary = GetBoundary();

	// ������Ϸ�߽�
	rectBoundary.left = 10;
	rectBoundary.top = 10;
	rectBoundary.right = 10 + CELL_PIXEL*(pCoordBoundary->x );
	rectBoundary.bottom = 10 + CELL_PIXEL*(pCoordBoundary->y );
	
	// �����������ҽǵ�λ��
	ptLeftTop.x = rectBoundary.left;
	ptLeftTop.y = rectBoundary.top;
	ptRightBottom.x = rectBoundary.right;
	ptRightBottom.y = rectBoundary.bottom;
	ClientToScreen(hwnd, &ptLeftTop);//ȡ�����������Ļ������
	ClientToScreen(hwnd, &ptRightBottom);
	
	GetWindowRect(hwnd, &rectWindow);
	// ������ˣ����ô��ڴ�С��
	MoveWindow(hwnd,  	rectWindow.left,rectWindow.top,
		ptLeftTop.x - rectWindow.left + ptRightBottom.x - rectWindow.left,//ͬʱ������һ���Ŀռ�   ͬʱ��ȥһ��ֵ
	  rectBoundary.bottom+120, //��������Ϣ������ʾ�ռ䡣   //û�иı䴰�ڵĴ�Сֻ�Ǹı��˴��ڵ����λ��
		TRUE);
}
LONG CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int i, j;
	POINT pt;
	switch (msg)
	{
		// �����ڱ�����ʱ���յ��ĵ�һ����Ϣ����WM_CREATE��һ���յ������Ϣ��������У�������������һЩ��ʼ���Ĺ���
	case WM_CREATE:
		SetBoundary();
		InitGame();
		InitLevel();
		InitStarmap(GetColorNum());//��ʼ���Թ�
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
	case WM_LBUTTONDOWN:	//�����������д���  �������¼�
		////if (flag == 0)
		////{
		////	if (wParam && MK_LBUTTON)
		////	{
		////		pt.x = LOWORD(lParam);
		////		pt.y = HIWORD(lParam);
		////		//Ȼ�������Ӧ�Ĵ���
		////		JudgeChange(&pt);
		////		if (Judge(pt) == 1) flag = 1;
		////		else if (Judge(pt) == 2) GamePaint2(hwnd, 3);//������ͼƬ
		////		else if (Judge(pt) == 3)  ExitProcess(0);
		////		GamePaint(hwnd);//�ػ�
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
		//		//�������������ж�
		//		if (RemoveStar(pt))
		//		{
		//			PlaySound("d:\\Documents\\Visual Studio 2017\\Projects\\Project8\\Project8\\touch.wav", NULL, SND_FILENAME | SND_ASYNC);
		//		}
		//		AddScore(NumOfStar);//�����������ǽ��мӷ�	
		//		if (ChangeSit())  Sleep(50000);
		//		GamePaint(hwnd);//�ػ�
		//		if (CloseStar())	 Sleep(30000);
		//		GamePaint(hwnd);//�ػ�
		//   //PlaySound("SystemStart", NULL, SND_ASYNC | SND_ASYNC);

		////PlaySound("d:\\Documents\\Visual Studio 2017\\Projects\\Project8\\Project8\\remove.wav", NULL, SND_FILENAME | SND_ASYNC);
		//		if (isWin())//�ж��Ƿ��Ѿ�Ӯ��
		//		{
		//			AddLevel();
		//			if (level > 6)
		//			{
		//				MessageBox(NULL, "��ϲ", "���Ѿ�ͨ�أ�", MB_ICONEXCLAMATION | MB_OK);
		//				ExitProcess(0);
		//			}
		//			else
		//			{
		//				//������һ��
		//				Sleep(500);
		//				GamePaint2(hwnd, 1);
		//				InitGame();
		//				InitStarmap(GetColorNum());//��ʼ���Թ�
		//				Sleep(800);
		//				GamePaint(hwnd);
		//			}
		//		}
		//		if (isDead() == 0 && isWin() == 0)
		//		{//���ûӮ�Ļ����ж���Ϸ�Ƿ��Ѿ�����
		//			MessageBox(NULL, "���ź� ", "��ʧ���ˣ�", MB_ICONEXCLAMATION | MB_OK);
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
