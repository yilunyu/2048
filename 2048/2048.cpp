// 2048.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "2048.h"
#include <time.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <stdlib.h>
#include <afx.h>
#include <time.h>
#include "GameBoard.h"
#define _AFXDLL
#define MAX_LOADSTRING 100

#define  TIMER_ESC  10
#define  SPEED  7.5
#define  TILE_WIDTH  90
#define  TILE_HEIGHT  135
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void CALLBACK TimerProc(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY2048, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2048));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
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
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2048));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY2048);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
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

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//





KGameBoard *game;
bool init =true;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
    HANDLE hOld;
    RECT clientR;
    HBITMAP hBMMem;
	CString s,i;
	CString tex;
    HDC mdc;
	int n = 0;
	switch (message)
	{
	case WM_CREATE:
		game = new KGameBoard;
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		

		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_KEYDOWN:
        if(game->m_okay)
        {    switch(wParam)
		    {
			    case VK_LEFT:
                    game->makeMove(1);
                    game->m_okay=false;
                    ::SetTimer(hWnd, 2, TIMER_ESC, TimerProc);
                
			    break;
			    case VK_UP:
			    game->makeMove(2);
                game->m_okay=false;
			    ::SetTimer(hWnd, 2, TIMER_ESC, TimerProc);
			    break;
			    case VK_RIGHT:
			    game->makeMove(3);
                game->m_okay=false;
			    ::SetTimer(hWnd, 2, TIMER_ESC, TimerProc);
			    break;
			    case VK_DOWN:
			    game->makeMove(4);
                game->m_okay=false;
			    ::SetTimer(hWnd, 2, TIMER_ESC, TimerProc);
			    break;
			    default:
			    break;
                
            }
        }
        break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
        /*CRect ctrlRect; 
        CStatic *pDegreePicCtrl = (CStatic *)GetDlgItem(IDC_STC_DEGREEPIC); 
        pDegreePicCtrl->GetClientRect(&ctrlRect);//获取静态控件尺寸 

        CDC *pdc = pDegreePicCtrl->GetWindowDC();//获取控件DC 
    
        HDC mdc = ::CreateCompatibleDC(hdc);
        CBitmap mapMemory;
        mapMemory.CreateCompatibleBitmap(pdc, ctrlRect.Width(), ctrlRect.Height());
		 pOldMapMemory = SelectObject(mdc,&mapMemory);*/
         mdc = CreateCompatibleDC(hdc);
        
        GetClientRect(hWnd,&clientR);
         hBMMem = CreateCompatibleBitmap(hdc,clientR.right-clientR.left,clientR.bottom-clientR.top);
         hOld = SelectObject(mdc,hBMMem);
         
         SelectObject(mdc, GetStockObject(BLACK_PEN));

         Rectangle(mdc,30,0,400,600);
         Rectangle(mdc,game->m_xstart[0],game->m_ystart[0],game->m_xend[0],game->m_yend[0]);
         Rectangle(mdc,game->m_xstart[1],game->m_ystart[0],game->m_xend[1],game->m_yend[0]);
         Rectangle(mdc,game->m_xstart[2],game->m_ystart[0],game->m_xend[2],game->m_yend[0]);
         Rectangle(mdc,game->m_xstart[3],game->m_ystart[0],game->m_xend[3],game->m_yend[0]);
         Rectangle(mdc,game->m_xstart[0],game->m_ystart[1],game->m_xend[0],game->m_yend[1]);
         Rectangle(mdc,game->m_xstart[1],game->m_ystart[1],game->m_xend[1],game->m_yend[1]);
         Rectangle(mdc,game->m_xstart[2],game->m_ystart[1],game->m_xend[2],game->m_yend[1]);
         Rectangle(mdc,game->m_xstart[3],game->m_ystart[1],game->m_xend[3],game->m_yend[1]);
         Rectangle(mdc,game->m_xstart[0],game->m_ystart[2],game->m_xend[0],game->m_yend[2]);
         Rectangle(mdc,game->m_xstart[1],game->m_ystart[2],game->m_xend[1],game->m_yend[2]);
         Rectangle(mdc,game->m_xstart[2],game->m_ystart[2],game->m_xend[2],game->m_yend[2]);
         Rectangle(mdc,game->m_xstart[3],game->m_ystart[2],game->m_xend[3],game->m_yend[2]);
         Rectangle(mdc,game->m_xstart[0],game->m_ystart[3],game->m_xend[0],game->m_yend[3]);
         Rectangle(mdc,game->m_xstart[1],game->m_ystart[3],game->m_xend[1],game->m_yend[3]);
         Rectangle(mdc,game->m_xstart[2],game->m_ystart[3],game->m_xend[2],game->m_yend[3]);
         Rectangle(mdc,game->m_xstart[3],game->m_ystart[3],game->m_xend[3],game->m_yend[3]);
        /* Rectangle(mdc,40,195,120,195+125);
         Rectangle(mdc,130,195,210,195+125);
         Rectangle(mdc,220,195,300,320);
         Rectangle(mdc,310,195,390,320);
         Rectangle(mdc,40,330,120,455);
         Rectangle(mdc,130,195+135,210,195+260);
         Rectangle(mdc,220,195+135,300,195+260);
         Rectangle(mdc,310,195+135,390,195+260);
         Rectangle(mdc,40,465,120,590);
         Rectangle(mdc,130,195+260+10,210,195+260+10+125);
         Rectangle(mdc,220,195+260+10,300,195+260+10+125);
         Rectangle(mdc,310,195+260+10,390,195+260+10+125);*/
        if(init) {
            
            game->addTile();
            init = false;
        }
		//TextOut(mdc,600,30,TEXT("TEST"),4); 
        if(!game->m_lastcall)   {
            game->drawBoard(mdc);
            s = TEXT("Score: ");
            i.Format(TEXT("%d"),game->m_score);
            tex = s + i;
            TextOut(mdc,40,30,tex,tex.GetLength());
        }
        else {
            game->addTile();
            game->drawBoard(mdc);
            game->m_lastcall = false;
            s = TEXT("Score: ");
            i.Format(TEXT("%d"),game->m_score);
            tex = s + i;
            TextOut(mdc,40,30,tex,tex.GetLength());
            for(int i=0;i<4;i++)
            {
                for(int j=0;j<4;j++)
                {
                    if(!(game->m_newpos[i][j]==0||game->m_oldpos[i][j]==game->m_newpos[i][j])){
                        CString pointsInStr;
                        pointsInStr.Format(TEXT("%d"),game->m_board[i][j].val);
                        TextOut(mdc,game->m_xstart[i]+37,game->m_ystart[j]+60,pointsInStr, pointsInStr.GetLength());
                    }
                }
            }
            
        }
        if(!game->canMove())   
        {
            game->gameOver(mdc,hWnd);
        }
		n = ::GetLastError();
        BitBlt(hdc,clientR.left,clientR.top,clientR.right-clientR.left,clientR.bottom-clientR.top,mdc,0,0,SRCCOPY);
        SelectObject(mdc,hOld);
        DeleteObject(hBMMem);
        DeleteDC(mdc);

        /*SelectObject(mdc,pOldMapMemory);
        ::DeleteObject(mapMemory);
        ::DeleteDC(mdc);
        ReleaseDC(pdc);*/
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
    case WM_ERASEBKGND:
        return (LRESULT)1;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void CALLBACK TimerProc(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime)
{
    switch(nTimerid)
    {
         case 2:
         if(game->m_moved)
         { 
             game->m_offset++;
           if(((game->m_hov==1||game->m_hov==3)&&game->m_offset ==TILE_WIDTH/SPEED)
               ||((game->m_hov==2||game->m_hov==4)&&game->m_offset == TILE_HEIGHT/SPEED))
            {
                KillTimer(hWnd,nTimerid);
                //画最终的界面
                // todo: redraw white space and shit
              //  if(game->m_moved){
                    game->m_lastcall =true;
                    game->m_moved=false;
                    RECT r;
                    GetClientRect(hWnd,&r);
                    InvalidateRect(hWnd,&r,FALSE);
                    UpdateWindow(hWnd);
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            game->m_oldpos[i][j] = 0;
                            game->m_newpos[i][j] =0;
                        }
                    }
                    game->m_offset=0;
                    game->m_okay=true;
               // }
             }
            else
            {
                RECT r;
                GetClientRect(hWnd,&r);
                InvalidateRect(hWnd,&r,TRUE);
                UpdateWindow(hWnd);
            }
         
         }
         else {
             KillTimer(hWnd,nTimerid);
             for(int i=0;i<4;i++)
             {
                for(int j = 0;j<4;j++)
                {
                    game->m_oldpos[i][j] = 0;
                    game->m_newpos[i][j] = 0;
                }
             }
             game->m_okay=true;
         }
         //horizontal = 450 ms, tick 45 times;
         //vertical = 670 ms, tick 67 times
   
        
        break;
    }
}