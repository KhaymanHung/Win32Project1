#pragma once

#include "resource.h"

#define FontSize	16						//跑馬燈文字大小
#define DelayTime	20						//文字移動間隔(毫秒)
#define WaitingTime 1000					//移動完畢停留時間(毫秒)
#define SnowNumber  16						//雪花每次顯示數量

//文字移動類別代碼
enum moveType
{
	RIGHTTOLEFT = 1,						//由右至左移動
	LEFTTORIGHT = 2,						//由左至右移動
	UPTODOWN = 3,							//先由上至下移動，到底部後若文字長度超過10字，則由右至左移動到顯示完全部文字
	DOWNTOUP = 4,							//先由下至上移動，到底部後若文字長度超過10字，則由右至左移動到顯示完全部文字
	FLIPOVERLEFT = 5,						//先由右至左翻轉顯示文字，全部顯示後若文字長度超過10字，則由右至左移動到顯示完全部文字
	FLIPOVERRIGHT = 6,						//先由左至右翻轉顯示文字，全部顯示後若文字長度超過10字，則由右至左移動到顯示完全部文字
	FLIPOVERUP = 7,							//先由上至下翻轉顯示文字，全部顯示後若文字長度超過10字，則由右至左移動到顯示完全部文字
	FLIPOVERDOWN = 8,						//先由下至上翻轉顯示文字，全部顯示後若文字長度超過10字，則由右至左移動到顯示完全部文字
	SNOW = 9								//雪花顯示文字，全部顯示後若文字長度超過10字，則由右至左移動到顯示完全部文字
};

HWND m_hMainWnd;							//主視窗HWND
int m_nInitDialog;							//初始化設定旗標

COLORREF m_bPointMap[160][16];				//儲存跑馬燈每格顏色
std::vector<COLORREF> m_vecColor;			//儲存文字顏色
CString m_strShow;							//儲存跑馬燈文字
wchar_t* m_strFont;							//儲存跑馬燈文字字體
moveType m_nowType;							//現在正在執行的跑馬燈移動類別
BOOL m_bMove;								//此次移動是否執行完畢
std::vector<moveType> m_vecMoveList;		//儲存此次跑馬燈移動方式列表
int m_nNowList;								//儲存正在執行的移動列表序列

int m_nNowStartX = 0;						//此次移動的跑馬燈左上角X座標
int m_nNowEndX = 0;							//此次移動的跑馬燈右下角X座標
int m_nNowStartY = 0;						//此次移動的跑馬燈左上角Y座標
int m_nNowEndY = 0;							//此次移動的跑馬燈右下角Y座標

int m_nSnowList[160][16];					//雪花顯示順序
int m_nSnowOrder;							//現在雪花顯示順序

//按鍵Event
void KeyDownEvent(HWND hWnd, WPARAM wParam, LPARAM lParam);

//向量字轉點陣字，只能轉單一字元
int string_bitmap(HDC hdc, UINT ch, char* buf, GLYPHMETRICS& gm, int size = 16, wchar_t* wfont = L"細明體");

//文字移動起始參數設定
void SetMoveType(moveType type);

//文字顏色設定
void setColor(COLORREF color, int start = 0, int end = 0);

//文字移動總匯
void StringMove();

//實際設定跑馬燈每個點的顏色
void SetPoint(HDC hdc, CString str, int size, wchar_t* font);

//RIGHTTOLEFT參數變動設定
void RightToLeft(HDC hdc, CString str, int size = 16, wchar_t* font = L"細明體");

//LEFTTORIGHT變動設定
void LeftToRight(HDC hdc, CString str, int size = 16, wchar_t* font = L"細明體");

//UPTODOWN參數變動設定
void UpToDown(HDC hdc, CString str, int size = 16, wchar_t* font = L"細明體");

//DOWNTOUP參數變動設定
void DownToUp(HDC hdc, CString str, int size = 16, wchar_t* font = L"細明體");

//FLIPOVERLEFT參數變動設定
void FlipOverLeft(HDC hdc, CString str, int size = 16, wchar_t* font = L"細明體");

//FLIPOVERRIGHT參數變動設定
void FlipOverRight(HDC hdc, CString str, int size = 16, wchar_t* font = L"細明體");

//FLIPOVERUP參數變動設定
void FlipOverUp(HDC hdc, CString str, int size = 16, wchar_t* font = L"細明體");

//FLIPOVERDOWN參數變動設定
void FlipOverDown(HDC hdc, CString str, int size = 16, wchar_t* font = L"細明體");

//SNOW參數變動設定
void Snow(HDC hdc, CString str, int size = 16, wchar_t* font = L"細明體");

//設定視窗移動類別Group選擇設定
void SelectRadioButton(HWND hDlg, int nIDDlgItem);

//決定雪花顯示順序
void SetSnowList();