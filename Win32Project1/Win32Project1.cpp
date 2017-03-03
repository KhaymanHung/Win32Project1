// Win32Project1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project1.h"
#include "resource.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	DialogProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

    MSG msg;

	m_nInitDialog = 0;
	HWND hDlg;
	hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, DialogProc, 0);

	//設定預設跑馬燈文字
	Edit_SetText(GetDlgItem(hDlg, IDC_EDIT1), _T("跑馬燈測試壹貳參肆伍陸柒捌玖拾"));

	//設定可選顏色選項
	ComboBox_AddString(GetDlgItem(hDlg, IDC_COMBO1), _T("白色"));
	ComboBox_AddString(GetDlgItem(hDlg, IDC_COMBO1), _T("紅色"));
	ComboBox_AddString(GetDlgItem(hDlg, IDC_COMBO1), _T("綠色"));
	ComboBox_AddString(GetDlgItem(hDlg, IDC_COMBO1), _T("藍色"));
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO1), 0);

	//設定可選字體選項
	ComboBox_AddString(GetDlgItem(hDlg, IDC_COMBO2), _T("細明體"));
	ComboBox_AddString(GetDlgItem(hDlg, IDC_COMBO2), _T("微軟正黑體"));
	ComboBox_AddString(GetDlgItem(hDlg, IDC_COMBO2), _T("新細明體"));
	ComboBox_AddString(GetDlgItem(hDlg, IDC_COMBO2), _T("標楷體"));
	ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO2), 0);

	//設定預設移動類別群組
	Button_SetCheck(GetDlgItem(hDlg, IDC_RADIO_MUTIL), BST_CHECKED);
	SelectRadioButton(hDlg, IDC_RADIO_MUTIL);

	//開始初始設定視窗
	ShowWindow(hDlg, nCmdShow);
	while (m_nInitDialog == 0 && GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (m_nInitDialog == 2) return (int)msg.wParam;

	//初始化設定完畢後才顯示主視窗
	ShowWindow(m_hMainWnd, SW_SHOW);
	UpdateWindow(m_hMainWnd);

    // Main message loop:
	int nLastTime, nNowTime;
	nLastTime = GetTickCount();
    while (GetMessage(&msg, nullptr, 0, 0))
    {
		/*
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
		*/
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		nNowTime = GetTickCount();
		if (nNowTime - nLastTime > DelayTime && m_bMove == TRUE)
		{
			StringMove();
			nLastTime = GetTickCount();
		}
		if (nNowTime - nLastTime > WaitingTime && m_bMove == FALSE)
		{
			m_nNowList++;
			if (m_nNowList >= m_vecMoveList.size())
			{
				m_nNowList = 0;
			}
			SetMoveType(m_vecMoveList[m_nNowList]);
		}

		RECT rectClient;
		GetClientRect(m_hMainWnd, &rectClient);
		InvalidateRect(m_hMainWnd, &rectClient, TRUE);
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL; //MAKEINTRESOURCEW(IDC_WIN32PROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	m_hMainWnd = hWnd;


	for (int i = 0; i < 160; i++)
	{
		for (int k = 0; k < 16; k++)
		{
			m_bPointMap[i][k] = RGB(0, 0, 0);
		}
	}
	MoveWindow(hWnd, 0, 0, 1600 + 18, 160 + 40, TRUE);

	//ShowWindow(hWnd, SW_HIDE);
	//UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
		/*
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
		*/
		// TODO: 在此加入任何繪圖程式碼...
		{
			// Gathering current client area's info.
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			RECT rectClient;
			GetClientRect(hWnd, &rectClient);
			int cx = rectClient.right - rectClient.left;
			int cy = rectClient.bottom - rectClient.top;

			// For comparing the effect, we use if statement to select different code.
			HDC hdcMem = CreateCompatibleDC(hdc);
			HBITMAP bmpMem = CreateCompatibleBitmap(hdc, cx, cy);
			SelectObject(hdcMem, bmpMem);
			FillRect(hdcMem, &rectClient, (HBRUSH)GetStockObject(WHITE_BRUSH));
			//
			for (int i = 0; i < 160; i++)
			{
				for (int k = 0; k < 16; k++)
				{
					RECT rect;
					rect.left = i * 10 + 2;
					rect.top = k * 10 + 2;
					rect.right = rect.left + 8;
					rect.bottom = rect.top + 8;
					
					HBRUSH hBrush = CreateSolidBrush(m_bPointMap[i][k]);
					FillRect(hdcMem, &rect, hBrush);
					DeleteObject(hBrush);
				}
			}
			//
			BitBlt(hdc, 0, 0, cx, cy, hdcMem, 0, 0, SRCCOPY);

			// end
			// prevent from GDI objects Leak (can detect by "GDIView, nirsoft")
			DeleteObject(bmpMem);
			DeleteDC(hdcMem);

			EndPaint(hWnd, &ps);
		}
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_KEYDOWN:
		KeyDownEvent(hWnd, wParam, lParam);
		break;
	case WM_ERASEBKGND:
		//避免重繪畫面時因背景重繪造成閃爍
		if (!TRUE) {
			DefWindowProc(hWnd, message, wParam, lParam);
		}
		else {
			return 0;
		}
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LPWSTR str = (LPWSTR)malloc(sizeof(LPWSTR) * 256);
	switch (uMsg)
	{
	case WM_CLOSE:
		//如果尚未完成初始設定，則初始設定旗標設定為取消，這會在設定視窗關閉後離開程式
		if (m_nInitDialog != 1) m_nInitDialog = 2;
		ShowWindow(hDlg, SW_HIDE);
		return TRUE;
	case WM_DESTROY:
		//如果尚未完成初始設定，則初始設定旗標設定為取消，這會在設定視窗關閉後離開程式
		if (m_nInitDialog != 1) m_nInitDialog = 2;
		ShowWindow(hDlg, SW_HIDE);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			//取得輸入文字
			GetDlgItemTextW(hDlg, IDC_EDIT1, str, sizeof(LPWSTR) * 256);
			m_strShow = str;

			//判斷是否有輸入文字
			if (m_strShow.GetLength() > 1)
			{
				//初始設定旗標設定為已完成
				m_nInitDialog = 1;

				//設定文字顏色
				int nSel = SendDlgItemMessageW(hDlg, IDC_COMBO1, CB_GETCURSEL, 0, 0);
				if (nSel == 0) setColor(RGB(255, 255, 255));
				else if (nSel == 1) setColor(RGB(255, 0, 0));
				else if (nSel == 2) setColor(RGB(0, 255, 0));
				else if (nSel == 3) setColor(RGB(0, 0, 255));

				//設定文字字體
				nSel = SendDlgItemMessageW(hDlg, IDC_COMBO1, CB_GETCURSEL, 0, 0);
				if (nSel == 0) m_strFont = L"細明體";
				else if (nSel == 1) m_strFont = L"微軟正黑體";
				else if (nSel == 2) m_strFont = L"新細明體";
				else if (nSel == 3) m_strFont = L"標楷體";

				//設定文字移動循環
				m_vecMoveList.clear();
				if (Button_GetCheck(GetDlgItem(hDlg, IDC_RADIO_MUTIL)))
				{
					if (Button_GetCheck(GetDlgItem(hDlg, IDC_CHECK_RIGHTTOLEFT))) m_vecMoveList.push_back(RIGHTTOLEFT);
					if (Button_GetCheck(GetDlgItem(hDlg, IDC_CHECK_LEFTTORIGHT))) m_vecMoveList.push_back(LEFTTORIGHT);
					if (Button_GetCheck(GetDlgItem(hDlg, IDC_CHECK_UPTODOWN))) m_vecMoveList.push_back(UPTODOWN);
					if (Button_GetCheck(GetDlgItem(hDlg, IDC_CHECK_DOWNTOUP))) m_vecMoveList.push_back(DOWNTOUP);
					if (Button_GetCheck(GetDlgItem(hDlg, IDC_CHECK_FLIPOVERLEFT))) m_vecMoveList.push_back(FLIPOVERLEFT);
					if (Button_GetCheck(GetDlgItem(hDlg, IDC_CHECK_FLIPOVERRIGHT))) m_vecMoveList.push_back(FLIPOVERRIGHT);
					if (Button_GetCheck(GetDlgItem(hDlg, IDC_CHECK_FLIPOVERUP))) m_vecMoveList.push_back(FLIPOVERUP);
					if (Button_GetCheck(GetDlgItem(hDlg, IDC_CHECK_FLIPOVERDOWN))) m_vecMoveList.push_back(FLIPOVERDOWN);
					if (Button_GetCheck(GetDlgItem(hDlg, IDC_CHECK_SNOW))) m_vecMoveList.push_back(SNOW);
				}
				else if (Button_GetCheck(GetDlgItem(hDlg, IDC_RADIO_SINGEL)))
				{
					if (Button_GetCheck(GetDlgItem(hDlg, IDC_RADIO_RIGHTTOLEFT))) m_vecMoveList.push_back(RIGHTTOLEFT);
					else if (Button_GetCheck(GetDlgItem(hDlg, IDC_RADIO_LEFTTORIGHT))) m_vecMoveList.push_back(LEFTTORIGHT);
					else if (Button_GetCheck(GetDlgItem(hDlg, IDC_RADIO_UPTODOWN))) m_vecMoveList.push_back(UPTODOWN);
					else if (Button_GetCheck(GetDlgItem(hDlg, IDC_RADIO_DOWNTOUP))) m_vecMoveList.push_back(DOWNTOUP);
					else if (Button_GetCheck(GetDlgItem(hDlg, IDC_RADIO_FLIPOVERLEFT))) m_vecMoveList.push_back(FLIPOVERLEFT);
					else if (Button_GetCheck(GetDlgItem(hDlg, IDC_RADIO_FLIPOVERRIGHT))) m_vecMoveList.push_back(FLIPOVERRIGHT);
					else if (Button_GetCheck(GetDlgItem(hDlg, IDC_RADIO_FLIPOVERUP))) m_vecMoveList.push_back(FLIPOVERUP);
					else if (Button_GetCheck(GetDlgItem(hDlg, IDC_RADIO_FLIPOVERDOWN))) m_vecMoveList.push_back(FLIPOVERDOWN);
					else if (Button_GetCheck(GetDlgItem(hDlg, IDC_RADIO_SNOW))) m_vecMoveList.push_back(SNOW);
				}
				m_nNowList = 0;
				SetMoveType(m_vecMoveList[m_nNowList]);

				SendMessage(hDlg, WM_CLOSE, 0, 0);
			}
			else
			{
				MessageBoxW(hDlg, _T("文字不可以為空。"), NULL, MB_OK);
			}
			return TRUE;
		case IDCANCEL:
			SendMessage(hDlg, WM_CLOSE, 0, 0);
			return TRUE;
		case IDC_RADIO_MUTIL:
			//文字移動循環選項enable設定
			SelectRadioButton(hDlg, IDC_RADIO_MUTIL);
			return TRUE;
		case IDC_RADIO_SINGEL:
			//文字移動循環選項enable設定
			SelectRadioButton(hDlg, IDC_RADIO_SINGEL);
			return TRUE;
		}
		break;
	default:
		//MessageBoxW(hDlg, _T("test"), NULL, MB_OK);
		return FALSE;
	}

	free(str);
	return FALSE;
}

void KeyDownEvent(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case VK_ESCAPE:
		//在跑馬燈主視窗按下ESC鍵時關閉程式
		PostQuitMessage(0);
		break;
	default:
		break;
	}
}

//將文字 ch 的點陣圖存入 buf 中, 點陣圖大小記錄於 bytes 中傳回
//字體=face, 字形大小=size, [此函式在 Unicode 模式下測試正常]
int string_bitmap(HDC hdc, UINT ch, char* buf, GLYPHMETRICS& gm, int size/* = 16 */, wchar_t* wfont/* = L"細明體" */)
{
	MAT2 mat = {{ 0,1 },{ 0,0 },{ 0,0 },{ 0,1 } };    //轉置矩陣
	HFONT font = CreateFont(size, 0, 0, 0, 400, 0, 0, 0, 0, 0, 0, 0, 0, wfont);
	HGDIOBJ oldFont = SelectObject(hdc, font);

	int bytes = GetGlyphOutline(hdc, ch, 1, &gm, 0, 0, &mat);
	if (bytes != GDI_ERROR)
	{
		GetGlyphOutline(hdc, ch, 1, &gm, bytes, buf, &mat);
	}

	SelectObject(hdc, oldFont);
	DeleteObject(font);
	return bytes;
}

//文字移動起始參數設定
void SetMoveType(moveType type)
{
	m_bMove = TRUE;
	switch (type)
	{
	case RIGHTTOLEFT:
		m_nNowStartX = 160;
		m_nNowEndX = m_nNowStartX + (m_strShow.GetLength() * 16);
		m_nNowStartY = 0;
		m_nNowEndY = 16;
		m_nowType = RIGHTTOLEFT;
		break;
	case LEFTTORIGHT:
		m_nNowEndX = 0;
		m_nNowStartX = m_nNowEndX - (m_strShow.GetLength() * 16);
		m_nNowStartY = 0;
		m_nNowEndY = 16;
		m_nowType = LEFTTORIGHT;
		break;
	case UPTODOWN:
		m_nNowStartX = 0;
		m_nNowEndX = m_nNowStartX + (m_strShow.GetLength() * 16);
		m_nNowStartY = -16;
		m_nNowEndY = 0;
		m_nowType = UPTODOWN;
		break;
	case DOWNTOUP:
		m_nNowStartX = 0;
		m_nNowEndX = m_nNowStartX + (m_strShow.GetLength() * 16);
		m_nNowStartY = 16;
		m_nNowEndY = 32;
		m_nowType = DOWNTOUP;
		break;
	case FLIPOVERLEFT:
		m_nNowStartX = 0;
		m_nNowEndX = 0;
		m_nNowStartY = 0;
		m_nNowEndY = 16;
		m_nowType = FLIPOVERLEFT;
		break;
	case FLIPOVERRIGHT:
		m_nNowEndX = m_strShow.GetLength() * 16;
		if (m_nNowEndX > 160)
		{
			m_nNowStartX = 160;
		}
		else
		{
			m_nNowStartX = m_nNowEndX;
		}
		m_nNowStartY = 0;
		m_nNowEndY = 16;
		m_nowType = FLIPOVERRIGHT;
		break;
	case FLIPOVERUP:
		m_nNowStartX = 0;
		m_nNowEndX = m_nNowStartX + (m_strShow.GetLength() * 16);
		m_nNowStartY = 0;
		m_nNowEndY = 0;
		m_nowType = FLIPOVERUP;
		break;
	case FLIPOVERDOWN:
		m_nNowStartX = 0;
		m_nNowEndX = m_nNowStartX + (m_strShow.GetLength() * 16);
		m_nNowStartY = 16;
		m_nNowEndY = 16;
		m_nowType = FLIPOVERDOWN;
		break;
	case SNOW:
		m_nNowStartX = 0;
		m_nNowEndX = m_strShow.GetLength() * 16;
		m_nNowStartY = 0;
		m_nNowEndY = 16;
		m_nSnowOrder = 0;
		SetSnowList();
		m_nowType = SNOW;
		break;
	default:
		m_nNowStartX = 160;
		m_nNowEndX = m_nNowStartX + (m_strShow.GetLength() * 16);
		m_nNowStartY = 0;
		m_nNowEndY = 16;
		m_nowType = RIGHTTOLEFT;
		break;
	}
}

//文字顏色設定
void setColor(COLORREF color, int start/* = 0*/, int end/* = 0*/)
{
	if (m_strShow.GetLength() < 1) return;

	if (end < start)
	{
		end = start;
	}
	if (start < 1) start = 1;
	if (start > m_strShow.GetLength()) start = m_strShow.GetLength();
	if (end < 1) end = m_strShow.GetLength();
	if (end > m_strShow.GetLength()) end = m_strShow.GetLength();

	for (int i = start - 1; i < end; i++)
	{
		if (m_vecColor.size() <= size_t(i))
		{
			m_vecColor.push_back(color);
		}
		else
		{
			m_vecColor[i] = color;
		}
	}
}

//文字移動總匯
void StringMove()
{
	if (m_bMove == FALSE) return;

	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(m_hMainWnd, &ps);
	
	for (int i = 0; i < 160; i++)
	{
		for (int k = 0; k < 16; k++)
		{
			m_bPointMap[i][k] = RGB(0, 0, 0);
		}
	}

	switch (m_nowType)
	{
	case RIGHTTOLEFT:
		RightToLeft(hdc, m_strShow, FontSize, m_strFont);
		break;
	case LEFTTORIGHT:
		LeftToRight(hdc, m_strShow, FontSize, m_strFont);
		break;
	case UPTODOWN:
		UpToDown(hdc, m_strShow, FontSize, m_strFont);
		break;
	case DOWNTOUP:
		DownToUp(hdc, m_strShow, FontSize, m_strFont);
		break;
	case FLIPOVERLEFT:
		FlipOverLeft(hdc, m_strShow, FontSize, m_strFont);
		break;
	case FLIPOVERRIGHT:
		FlipOverRight(hdc, m_strShow, FontSize, m_strFont);
		break;
	case FLIPOVERUP:
		FlipOverUp(hdc, m_strShow, FontSize, m_strFont);
		break;
	case FLIPOVERDOWN:
		FlipOverDown(hdc, m_strShow, FontSize, m_strFont);
		break;
	case SNOW:
		Snow(hdc, m_strShow, FontSize, m_strFont);
		break;
	default:
		RightToLeft(hdc, m_strShow, FontSize, m_strFont);
	}
}

//實際設定跑馬燈每個點的顏色
void SetPoint(HDC hdc, CString str, int size, wchar_t* font)
{
	GLYPHMETRICS gm;
	char buf[256];

	for (int len = 0; len < str.GetLength(); len++)
	{
		CString str2(str[len]);
		wchar_t* wStr = T2W(str2.GetBuffer());
		str.ReleaseBuffer();

		int sz = string_bitmap(hdc, *wStr, buf, gm, size, font);
		int nx = sz / gm.gmBlackBoxY;     //每行占幾Byte, gmBlackBoxX=位元寬度

		int pointMapX = 0;
		int pointMapY = 0;
		for (int x, j, i = 0; i < sz;)
		{
			if (m_nNowStartX <= 0 || m_nowType != FLIPOVERRIGHT)
			{
				pointMapX = len * 16 + m_nNowStartX;
			}
			else
			{
				pointMapX = len * 16;
			}

			for (x = 0; x < nx; x++, i++)
			{
				for (j = 1 << 8; j; j >>= 1)
				{
					if ((pointMapX >= 0 && pointMapX >= m_nNowStartX) && (pointMapX <= m_nNowEndX && pointMapX < 160) &&
						(pointMapY >= 0 && pointMapY >= m_nNowStartY) && (pointMapY <= m_nNowEndY && pointMapY < 16))
					{
						if (buf[i] & j)
						{
							if (m_nowType != SNOW)
							{
								m_bPointMap[pointMapX][pointMapY] = m_vecColor[len];
							}
							else
							{
								if (m_nSnowList[pointMapX][pointMapY] <= m_nSnowOrder)
								{
									m_bPointMap[pointMapX][pointMapY] = m_vecColor[len];
								}
								else
								{
									m_bPointMap[pointMapX][pointMapY] = RGB(0, 0, 0);
								}
							}
						}
						else
						{
							m_bPointMap[pointMapX][pointMapY] = RGB(0, 0, 0);
						}
					}
					pointMapX++;
				}
			}
			pointMapY++;
		}
	}
}

//RIGHTTOLEFT參數變動設定
void RightToLeft(HDC hdc, CString str, int size/* = 16 */, wchar_t* font/* = L"細明體" */)
{
	SetPoint(hdc, str, size, font);

	if (str.GetLength() > 10 && m_nNowEndX < 160)
	{
		m_bMove = FALSE;
	}
	else if (str.GetLength() <= 10 && m_nNowStartX == 0)
	{
		m_bMove = FALSE;
	}
	m_nNowStartX--;
	m_nNowEndX--;
}

//LEFTTORIGHT參數變動設定
void LeftToRight(HDC hdc, CString str, int size/* = 16 */, wchar_t* font/* = L"細明體" */)
{
	SetPoint(hdc, str, size, font);

	m_nNowStartX++;
	m_nNowEndX++;
	if (m_nNowStartX >= 0) m_bMove = FALSE;
}

//UPTODOWN參數變動設定
void UpToDown(HDC hdc, CString str, int size/* = 16 */, wchar_t* font/* = L"細明體" */)
{
	SetPoint(hdc, str, size, font);

	if (m_nNowStartY <= 0)
	{
		m_nNowStartY++;
		m_nNowEndY++;
	}
	if (m_nNowStartY > 0)
	{
		if (str.GetLength() > 10 && m_nNowEndX < 160)
		{
			m_bMove = FALSE;
		}
		else if (str.GetLength() <= 10 && m_nNowStartX == 0)
		{
			m_bMove = FALSE;
		}

		m_nNowStartX--;
		m_nNowEndX--;
	}
}

//DOWNTOUP參數變動設定
void DownToUp(HDC hdc, CString str, int size/* = 16 */, wchar_t* font/* = L"細明體" */)
{
	SetPoint(hdc, str, size, font);

	if (m_nNowStartY >= 0)
	{
		m_nNowStartY--;
		m_nNowEndY--;
	}
	if (m_nNowStartY < 0)
	{
		if (str.GetLength() > 10 && m_nNowEndX < 160)
		{
			m_bMove = FALSE;
		}
		else if (str.GetLength() <= 10 && m_nNowStartX == 0)
		{
			m_bMove = FALSE;
		}

		m_nNowStartX--;
		m_nNowEndX--;
	}
}

//FLIPOVERLEFT參數變動設定
void FlipOverLeft(HDC hdc, CString str, int size/* = 16 */, wchar_t* font/* = L"細明體" */)
{
	SetPoint(hdc, str, size, font);

	int len = m_nNowStartX + (m_strShow.GetLength() * 16);
	if (m_nNowEndX <= len) m_nNowEndX++;
	if (m_nNowEndX > len || m_nNowEndX >= 160)
	{
		if (str.GetLength() > 10 && m_nNowEndX < 160)
		{
			m_bMove = FALSE;
		}
		else if (str.GetLength() <= 10 && m_nNowStartX == 0)
		{
			m_bMove = FALSE;
		}

		m_nNowStartX--;
		m_nNowEndX--;
	}
}

//FLIPOVERRIGHT參數變動設定
void FlipOverRight(HDC hdc, CString str, int size/* = 16 */, wchar_t* font/* = L"細明體" */)
{
	SetPoint(hdc, str, size, font);

	if (m_nNowStartX >= 0) m_nNowStartX--;
	if (m_nNowStartX < 0)
	{
		if (str.GetLength() > 10 && m_nNowEndX < 160)
		{
			m_bMove = FALSE;
		}
		else if (str.GetLength() <= 10 && m_nNowStartX == 0)
		{
			m_bMove = FALSE;
		}

		m_nNowStartX--;
		m_nNowEndX--;
	}
}

//FLIPOVERUP參數變動設定
void FlipOverUp(HDC hdc, CString str, int size/* = 16 */, wchar_t* font/* = L"細明體" */)
{
	SetPoint(hdc, str, size, font);

	if (m_nNowEndY <= 16) m_nNowEndY++;
	if (m_nNowEndY > 16)
	{
		if (str.GetLength() > 10 && m_nNowEndX < 160)
		{
			m_bMove = FALSE;
		}
		else if (str.GetLength() <= 10 && m_nNowStartX == 0)
		{
			m_bMove = FALSE;
		}

		m_nNowStartX--;
		m_nNowEndX--;
	}
}

//FLIPOVERDOWN參數變動設定
void FlipOverDown(HDC hdc, CString str, int size/* = 16 */, wchar_t* font/* = L"細明體" */)
{
	SetPoint(hdc, str, size, font);

	if (m_nNowStartY >= 0) m_nNowStartY--;
	if (m_nNowStartY < 0)
	{
		if (str.GetLength() > 10 && m_nNowEndX < 160)
		{
			m_bMove = FALSE;
		}
		else if (str.GetLength() <= 10 && m_nNowStartX == 0)
		{
			m_bMove = FALSE;
		}

		m_nNowStartX--;
		m_nNowEndX--;
	}
}

//SNOW參數變動設定
void Snow(HDC hdc, CString str, int size/* = 16 */, wchar_t* font/* = L"細明體" */)
{
	SetPoint(hdc, str, size, font);
	
	if (m_nSnowOrder <= (160 * 16) / SnowNumber) m_nSnowOrder++;
	if (m_nSnowOrder > (160 * 16) / SnowNumber)
	{
		if (str.GetLength() > 10 && m_nNowEndX < 160)
		{
			m_bMove = FALSE;
		}
		else if (str.GetLength() <= 10 && m_nNowStartX == 0)
		{
			m_bMove = FALSE;
		}

		m_nNowStartX--;
		m_nNowEndX--;
	}
}

//設定視窗移動類別Group選擇設定
void SelectRadioButton(HWND hDlg, int nIDDlgItem)
{
	BOOL bEnable = TRUE;
	if (nIDDlgItem == IDC_RADIO_SINGEL)
	{
		bEnable = FALSE;
		Button_SetCheck(GetDlgItem(hDlg, IDC_RADIO_RIGHTTOLEFT), BST_CHECKED);
	}

	std::list<int> itemListGroup1;
	itemListGroup1.push_back(IDC_CHECK_RIGHTTOLEFT);
	itemListGroup1.push_back(IDC_CHECK_LEFTTORIGHT);
	itemListGroup1.push_back(IDC_CHECK_UPTODOWN);
	itemListGroup1.push_back(IDC_CHECK_DOWNTOUP);
	itemListGroup1.push_back(IDC_CHECK_FLIPOVERLEFT);
	itemListGroup1.push_back(IDC_CHECK_FLIPOVERRIGHT);
	itemListGroup1.push_back(IDC_CHECK_FLIPOVERUP);
	itemListGroup1.push_back(IDC_CHECK_FLIPOVERDOWN);
	itemListGroup1.push_back(IDC_CHECK_SNOW);

	for (std::list<int>::iterator i = itemListGroup1.begin(); i != itemListGroup1.end(); ++i)
	{
		HWND item = GetDlgItem(hDlg, *i);
		Button_Enable(item, bEnable);
		if (bEnable == FALSE) Button_SetCheck(item, bEnable);
	}

	std::list<int> itemListGroup2;
	itemListGroup2.push_back(IDC_RADIO_RIGHTTOLEFT);
	itemListGroup2.push_back(IDC_RADIO_LEFTTORIGHT);
	itemListGroup2.push_back(IDC_RADIO_UPTODOWN);
	itemListGroup2.push_back(IDC_RADIO_DOWNTOUP);
	itemListGroup2.push_back(IDC_RADIO_FLIPOVERLEFT);
	itemListGroup2.push_back(IDC_RADIO_FLIPOVERRIGHT);
	itemListGroup2.push_back(IDC_RADIO_FLIPOVERUP);
	itemListGroup2.push_back(IDC_RADIO_FLIPOVERDOWN);
	itemListGroup2.push_back(IDC_RADIO_SNOW);

	for (std::list<int>::iterator i = itemListGroup2.begin(); i != itemListGroup2.end(); ++i)
	{
		HWND item = GetDlgItem(hDlg, *i);
		Button_Enable(item, !bEnable);
		if (bEnable == TRUE) Button_SetCheck(item, !bEnable);
	}

	itemListGroup1.clear();
	itemListGroup2.clear();
}

//決定雪花顯示順序
void SetSnowList()
{
	struct snowTemp
	{
		int x;
		int y;
	};
	std::list<snowTemp> snowRandomList;
	for (int i = 0; i < 160; i++)
	{
		for (int k = 0; k < 16; k++)
		{
			snowTemp temp;
			temp.x = i;
			temp.y = k;
			snowRandomList.push_back(temp);
		}
	}

	int nSize = snowRandomList.size();
	std::list<snowTemp> listTemp = snowRandomList;
	for (int i = 0; i < nSize; i++)
	{
		if (listTemp.size() > 0)
		{
			srand((unsigned)time(NULL));
			int nRandom = 1 + (int)(rand() % listTemp.size());
			for (std::list<snowTemp>::iterator iter = listTemp.begin(); iter != listTemp.end(); ++iter)
			{
				if (nRandom == 1)
				{
					m_nSnowList[iter->x][iter->y] = (int)(i / SnowNumber);
					listTemp.erase(iter);
					break;
				}
				nRandom--;
			}
		}
		else
		{
			break;
		}
	}
}