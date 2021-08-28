// welcome.cpp : Defines the entry point for the application.
//

#include "Stdafx.h"
#include "resource.h"
#include "config.h"
#include "stdio.h"
#include "time.h"
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The   title bar text
HINSTANCE hInstGame;

HANDLE handleOutput=0;

Image *imageGif[GMax];

int iXpos;
int iYpos;


int iATest[100];

char flg=0;
char cFollowFlg = NO;
char cShovelFlg = NO;
// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;
	
// 	AllocConsole();
//   	handleOutput=GetStdHandle(STD_OUTPUT_HANDLE);

	hInstGame=hInstance;
	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PLANTVSZOMBIE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	//srand((unsigned)time(NULL)); 
	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_PLANTVSZOMBIE);
	
	windowInit(hInstance);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_ICONbig);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= NULL;
	wcex.lpszMenuName	= (LPCSTR)IDC_PLANTVSZOMBIE;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_ICONsmall);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInstGame = hInstance; // Store instance handle in our global variable

   hwndWindow= CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, C_TILE_W*C_MAP_W,C_TILE_H*C_MAP_H+50, NULL, NULL, hInstance, NULL);

   if (!hwndWindow)
   {
      return FALSE;
   }

   ShowWindow(hwndWindow, nCmdShow);
   UpdateWindow(hwndWindow);

   return TRUE;
}

void mouseMove(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
    CHAR szText[256]={0};
	sprintf(szText,"WM_LBUTTONDOWN:wParam:%08X,x=%d,y=%d\n",wParam,LOWORD(lParam),HIWORD(lParam));
	WriteConsole(handleOutput,szText,strlen(szText),NULL,NULL);
}

void mapClear( int cROw, int cCol ) 
{
	 _MAP[cROw][cCol].cName = NO;
	 _MAP[cROw][cCol].cSun = NO;    
	 _MAP[cROw][cCol].cChomper = NO;
	 _MAP[cROw][cCol].cSquash = NO;
	 _MAP[cROw][cCol].cBomb = NO;
	 _MAP[cROw][cCol].iLife = 0;
}

void sunRandom ()
{
__RANDOM:
	iRandomXpos =rand()%5;
	iRandomYpos =rand()%6;
	if (_MAP[iRandomXpos][iRandomYpos].cName == SunFlower)
		goto __RANDOM;
}
//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static UINT uiGifCount[GMax];
	static WCHAR cGifStrGuid[GMax][39];
	static UINT uiGifFrameCount[GMax];
	static PropertyItem* pItemGif[GMax];
	static UINT uiGifFcount[GMax];
	static GUID guidGif[GMax];
	static long lGiflPause[GMax];
	static int iGifsize[GMax];
	static GUID *pGifDimensionIDs[GMax];

	int wmId, wmEvent;
	HINSTANCE hInstance;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);
	//gdi+用到的两个变量
	GdiplusStartupInput m_gdiplusStartupInput;
    ULONG_PTR m_pGdiToken;
	//装载gdi+
	GdiplusStartup(&m_pGdiToken,&m_gdiplusStartupInput,NULL); 

	switch (message) 
	{
		case WM_CREATE:
			{
				allInit();
				SetTimer(hWnd,TIMER_FIR,0,NULL);
				SetTimer( hWnd, TIMER_REDRAW, 1, NULL );	                //设置定时器为1毫秒   	
			}break;
		case WM_TIMER:
			{
				switch (wParam)
				{	
				case TIMER_REDRAW:{
							DWORD dwTime = GetTickCount();
							if( frameInto( hInstGame,dwTime ) )
							{
								InvalidateRect( hWnd, NULL, FALSE );
							}
						}break;
				case TIMER_FIR:
					{
						hdc=GetDC(hWnd);
						gifLoad();
						for ( int iGifIndex = GPeashooter; iGifIndex < GMax; iGifIndex++ ) {
							uiGifCount[iGifIndex] = 0;
							uiGifCount[iGifIndex] = imageGif[iGifIndex]->GetFrameDimensionsCount();
							pGifDimensionIDs[iGifIndex] = (GUID*)new GUID[uiGifCount[iGifIndex]];
							imageGif[iGifIndex]->GetFrameDimensionsList(pGifDimensionIDs[iGifIndex] ,uiGifCount[iGifIndex]);
								
							//StringFromGUID2(pGifDimensionIDs[iGifIndex][0],strGuid,39);//需要将 DBTYPE_GUID 类型的数据转换为字符串显
							uiGifFrameCount[iGifIndex]=imageGif[iGifIndex]->GetFrameCount(&pGifDimensionIDs[iGifIndex][0]);
							delete []pGifDimensionIDs[iGifIndex];

							iGifsize[iGifIndex]=imageGif[iGifIndex]->GetPropertyItemSize(PropertyTagFrameDelay);
							pItemGif[iGifIndex]=(PropertyItem*)new PropertyItem[iGifsize[iGifIndex]];
							imageGif[iGifIndex]->GetPropertyItem(PropertyTagFrameDelay,iGifsize[iGifIndex],pItemGif[iGifIndex]);

							uiGifFcount[iGifIndex]=0;
							guidGif[iGifIndex]=FrameDimensionTime;
						}
					
						KillTimer (hWnd, TIMER_FIR) ;
						SetTimer(hWnd,TIMER_SEC,lGiflPause[GChomperAttack],NULL);
						InvalidateRect (hWnd, NULL, FALSE) ;			
					}break;
				case TIMER_SEC:
					{
						for ( int iGifIndex = GPeashooter; iGifIndex < GMax; iGifIndex++ ) {
							imageGif[iGifIndex]->SelectActiveFrame(&guidGif[iGifIndex],uiGifFcount[iGifIndex]++);
							if(uiGifFcount[iGifIndex]==uiGifFrameCount[iGifIndex])
								uiGifFcount[iGifIndex]=0;		    
						}
						lGiflPause[GChomperAttack]=((long*)pItemGif[GChomperAttack]->value)[uiGifFcount[GChomperAttack]]*10;
						KillTimer(hWnd,TIMER_SEC);
						SetTimer(hWnd,TIMER_SEC,lGiflPause[GChomperAttack],NULL);
						InvalidateRect (hWnd, NULL, FALSE) ;
					}break;
				}
			}break;
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			{		
				picturerDraw();
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_LBUTTONDOWN:                               //处理鼠标左键单击事件
			{   
				POINT ptShiftSite;
				// mouseMove(hWnd,wParam,lParam);
				cardChoose(hWnd,wParam,lParam);

				if( grasslandEnsure(hWnd,wParam,lParam) == Grassland)
					 ptShiftSite = coordLocate(hWnd,wParam,lParam);

				if ( cCardChoose != NO && grasslandEnsure(hWnd,wParam,lParam) == Grassland ) { 
					if ( _MAP[ptShiftSite.x][ptShiftSite.y].cName == NO ) {	
						_MAP[ptShiftSite.x][ptShiftSite.y].cName = cCardChoose;	
						_MAP[ptShiftSite.x][ptShiftSite.y].iLife = iAMapLife[cCardChoose];
						_CARD[cCardChoose].cCanFlg=NO;
 						if ( cCardChoose == PeaShooter || cCardChoose == Repeater) {
 							_BULLET[ptShiftSite.x*6+ptShiftSite.y].cOpen = OK;
							_BULLET[ptShiftSite.x*6+ptShiftSite.y].cAlive = OK;
							if ( cCardChoose == Repeater ) {
								_TWOBULLET[ptShiftSite.x*6+ptShiftSite.y].cOpen = OK;
								_TWOBULLET[ptShiftSite.x*6+ptShiftSite.y].cAlive = OK;
							}
 						}
						if ( cCardChoose == Chomper ) {
							_MAP[ptShiftSite.x][ptShiftSite.y].cChomper = OK;
						}
						if ( cCardChoose == CherryBomb ) {
							_MAP[ptShiftSite.x][ptShiftSite.y].cCherryBomb = OK;
							_MAP[ptShiftSite.x][ptShiftSite.y].cBomb = OK;
							if (ptShiftSite.y <= 5)
								_MAP[ptShiftSite.x][ptShiftSite.y+1].cBomb = OK;
							if (ptShiftSite.y >=1)
								_MAP[ptShiftSite.x][ptShiftSite.y-1].cBomb = OK;
							if(ptShiftSite.x <= 3)
								_MAP[ptShiftSite.x+1][ptShiftSite.y].cBomb = OK;
							if(ptShiftSite.x >= 1)
								_MAP[ptShiftSite.x-1][ptShiftSite.y].cBomb = OK;
						}
						if ( cCardChoose == Jalapeno ) {
							
							_MAP[ptShiftSite.x][ptShiftSite.y].cBomb = OK;
							if (ptShiftSite.y <= 5)
								_MAP[ptShiftSite.x][ptShiftSite.y+1].cBomb = OK;
							if (ptShiftSite.y >=1)
								_MAP[ptShiftSite.x][ptShiftSite.y-1].cBomb = OK;
						}
						iSunCount -= _CARD[cCardChoose].iMoney;
						CHAR szText[256]={0};
						sprintf(szText,"x= %d  ,y= %d  ,name=%d \n",ptShiftSite.x,ptShiftSite.y,_MAP[ptShiftSite.x][ptShiftSite.y].cName);
  						WriteConsole(handleOutput,szText,strlen(szText),NULL,NULL);
						cFollowFlg = NO;
						cCardChoose = NO;
					} 
				}	

				if ( shovelEnsure(hWnd,wParam,lParam) == Shovel) {
					cShovelFlg = OK;
				}
				
				if ( cShovelFlg == OK && grasslandEnsure(hWnd,wParam,lParam) == Grassland) {
					mapClear(ptShiftSite.x,ptShiftSite.y);
					_BULLET[ptShiftSite.x*6+ptShiftSite.y].cOpen = NO;
					_BULLET[ptShiftSite.x*6+ptShiftSite.y].cAlive = NO;
					_TWOBULLET[ptShiftSite.x*6+ptShiftSite.y].cOpen = NO;
					_TWOBULLET[ptShiftSite.x*6+ptShiftSite.y].cAlive = NO;
				}

                if( grasslandEnsure(hWnd,wParam,lParam) == Grassland)  {
					if ( cCardChoose == NO && cShovelFlg == NO && _MAP[ptShiftSite.x][ptShiftSite.y].cSun == OK ) {
						_MAP[ptShiftSite.x][ptShiftSite.y].cSun = NO;
						iSunCount += 25;
					}
				}
				//if ( _MAP[ptShiftSite.x][ptShiftSite.y].cSun == OK )
 				if ( iSunCount < _CARD[cCardChoose].iMoney) {
 					cCardChoose = NO;
 				}

				sunRandom ();	
			}
			break; 
		case WM_RBUTTONDOWN: 
			{
				cFollowFlg = NO;
			    cCardChoose = NO;
				cShovelFlg = NO;
                iShovelXpos = ShovelInitXpos;
				iShovelYpos = ShovelInitYpos;
			}break;
		case WM_KEYDOWN:
			{
				keyDeal(wParam);                         //用户操作处理  
			}break;
		case WM_MOUSEMOVE:
			{
				if( cCardChoose != NO && grasslandEnsure(hWnd,wParam,lParam) == Grassland ) {
					cFollowFlg = OK;
					iFollowXpos = LOWORD(lParam)-35;
					iFollowYpos = HIWORD(lParam)-40;
					if( cCardChoose == Chomper )
						iFollowYpos = HIWORD(lParam)-80;
				}

				if ( cShovelFlg == OK )
				{
					iShovelXpos = LOWORD(lParam)-35;
					iShovelYpos = HIWORD(lParam);
				}

				if ( cardEnsure(hWnd,wParam,lParam) == Card) {
					cShovelFlg = NO;
					iShovelXpos = ShovelInitXpos;
					iShovelYpos = ShovelInitYpos;
				}

				
// 				else 
// 					cFollowFlg = NO;
			}break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;
		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
