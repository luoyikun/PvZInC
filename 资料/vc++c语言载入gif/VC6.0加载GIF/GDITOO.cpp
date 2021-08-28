// GDITOO.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include<stdio.h>
#define TIMER_FIR 1
#define TIMER_SEC 2


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text
HWND g_hWnd;
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

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GDITOO, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_GDITOO);

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
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_GDITOO);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_GDITOO;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

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
/*Image *image=NULL;
		bool			m_bPause=false;
	PropertyItem*	m_pPropertyItem;
		HANDLE			m_hExitEvent=CreateEvent(NULL,TRUE,FALSE,NULL);

	HANDLE m_hPause = CreateEvent(NULL,TRUE,TRUE,NULL);*/
void __cdecl showimage(LPVOID)
{
	HDC hdc=GetDC(g_hWnd);
	/*Graphics graphics(hdc);
	Image image(L"001.jpg");
	graphics.DrawImage(&image,0,0);*/
	/* image = new Image(L"123.gif");

   // How many frame dimensions does the Image object have?
   UINT count = 0;
   count = image->GetFrameDimensionsCount();
   //printf("The number of dimensions is %d.\n", count);
   GUID* pDimensionIDs = (GUID*)malloc(sizeof(GUID)*count);

   // Get the list of frame dimensions from the Image object.
   image->GetFrameDimensionsList(pDimensionIDs, count);

   // Display the GUID of the first (and only) frame dimension.
   WCHAR strGuid[39];
   StringFromGUID2(pDimensionIDs[0], strGuid, 39);
   wprintf(L"The first (and only) dimension ID is %s.\n", strGuid);

   // Get the number of frames in the first dimension.
   UINT frameCount = image->GetFrameCount(&pDimensionIDs[0]);
   //printf("The number of frames in that dimension is %d.\n", frameCount);
   UINT nFramePosition=1;
   int nSize=image->GetPropertyItemSize(PropertyTagFrameDelay);
   m_pPropertyItem=(PropertyItem*)malloc(nSize);
   image->GetPropertyItem(PropertyTagFrameDelay,nSize,m_pPropertyItem);
	Graphics graphics(hdc);
	graphics.DrawImage(image,20,20);
	while(1)
	{
	WaitForSingleObject(m_hPause, INFINITE);
	GUID pageGuid=FrameDimensionTime;
	image->SelectActiveFrame(&pageGuid,nFramePosition++);
	if(nFramePosition==frameCount)
    nFramePosition=1;
	long lPause = ((long*) m_pPropertyItem->value)[nFramePosition] * 10;

	DWORD dwErr = WaitForSingleObject(m_hExitEvent, lPause);
	}
   free(pDimensionIDs);

   //GdiplusShutdown(gdiplusToken);
   //return 0;*/
	Image *image=new Image(L"123.gif");
	UINT count=0;
	count=image->GetFrameDimensionsCount();
	GUID *pDimensionIDs=(GUID*)new GUID[count];
	image->GetFrameDimensionsList(pDimensionIDs,count);
	WCHAR strGuid[39];
	StringFromGUID2(pDimensionIDs[0],strGuid,39);
	UINT frameCount=image->GetFrameCount(&pDimensionIDs[0]);
	delete []pDimensionIDs;
	int size=image->GetPropertyItemSize(PropertyTagFrameDelay);
	PropertyItem* pItem=NULL;
	pItem=(PropertyItem*)malloc(size);
	image->GetPropertyItem(PropertyTagFrameDelay,size,pItem);
	UINT fcount=0;
	GUID Guid=FrameDimensionTime;
	while(true)
	{
		Graphics graphics(hdc);
		graphics.DrawImage(image,0,0,image->GetWidth(),image->GetHeight());
		image->SelectActiveFrame(&Guid,fcount++);
		if(fcount==frameCount)
			fcount=0;
		long lPause=((long*)pItem->value)[fcount]*10;
		Sleep(lPause);
	}
	ReleaseDC(g_hWnd,hdc);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }
g_hWnd=hWnd;
   ShowWindow(hWnd, nCmdShow|SW_MAXIMIZE);
   UpdateWindow(hWnd);

   return TRUE;
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
	static Image *image;
	static UINT count;
	static WCHAR strGuid[39];
	static UINT frameCount;
static PropertyItem* pItem=NULL;
static UINT fcount;
static GUID Guid;
static long lPause;
static int size;
static GUID *pDimensionIDs;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
//	HANDLE hThread;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);
	//为了方便这里把函数中用到的变量都变成静态变量

//static Graphics graphics;
	//gdi+用到的两个变量
	GdiplusStartupInput m_gdiplusStartupInput;
    ULONG_PTR m_pGdiToken;
	//装载gdi+
	GdiplusStartup(&m_pGdiToken,&m_gdiplusStartupInput,NULL); 
	
	switch (message) 
	{
	case WM_CREATE:
		SetTimer(hWnd,TIMER_FIR,0,NULL);
		break;
	case WM_TIMER:
		{
			switch(wParam)
			{
	case TIMER_FIR:
		{
		hdc=GetDC(hWnd);
	image=new Image(L"123.gif");
 count=0;
  count=image->GetFrameDimensionsCount();
pDimensionIDs=(GUID*)new GUID[count];
  image->GetFrameDimensionsList(pDimensionIDs,count);
  StringFromGUID2(pDimensionIDs[0],strGuid,39);
frameCount=image->GetFrameCount(&pDimensionIDs[0]);
  delete []pDimensionIDs;
 size=image->GetPropertyItemSize(PropertyTagFrameDelay);
 //PropertyItem* pItem=NULL;
 // pItem=(PropertyItem*)malloc(size);
  pItem=(PropertyItem*)new PropertyItem[size];
  image->GetPropertyItem(PropertyTagFrameDelay,size,pItem);
fcount=0;
Guid=FrameDimensionTime;

Graphics  graphics(hdc);
   graphics.DrawImage(image,0,0);
    image->SelectActiveFrame(&Guid,fcount++);
    if(fcount==frameCount)
      fcount=0;
 lPause=((long*)pItem->value)[fcount]*10;
		//ReleaseDC(hWnd,hdc);
		KillTimer (hWnd, TIMER_FIR) ;
		SetTimer(hWnd,TIMER_SEC,lPause,NULL);
			  InvalidateRect (hWnd, NULL, FALSE) ;
		break;
		}
	case TIMER_SEC:
		{
		image->SelectActiveFrame(&Guid,fcount++);
		if(fcount==frameCount)
      fcount=0;
	 lPause=((long*)pItem->value)[fcount]*10;
	KillTimer(hWnd,TIMER_SEC);
	SetTimer(hWnd,TIMER_SEC,lPause,NULL);
	InvalidateRect (hWnd, NULL, FALSE) ;
		}
			}
		}
		break; 
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
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			RECT rt;
			GetClientRect(hWnd, &rt);
			//MessageBox(NULL,"SDF","SDF",MB_OK);
			Graphics graphics(hdc);
			graphics.DrawImage(image,0,0);
		//	hThread=(HANDLE)_beginthread(showimage,0,0);
			//showimage(hdc);
			//WaitForSingleObject(hThread,INFINITE);
			EndPaint(hWnd, &ps);
			}
			break;
		case WM_DESTROY:
				//卸载gdi+
			   //delete(image);
			GdiplusShutdown(m_pGdiToken);
			PostQuitMessage(0);
			break;
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
