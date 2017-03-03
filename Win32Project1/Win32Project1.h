#pragma once

#include "resource.h"

#define FontSize	16						//�]���O��r�j�p
#define DelayTime	20						//��r���ʶ��j(�@��)
#define WaitingTime 1000					//���ʧ������d�ɶ�(�@��)
#define SnowNumber  16						//����C����ܼƶq

//��r�������O�N�X
enum moveType
{
	RIGHTTOLEFT = 1,						//�ѥk�ܥ�����
	LEFTTORIGHT = 2,						//�ѥ��ܥk����
	UPTODOWN = 3,							//���ѤW�ܤU���ʡA�쩳����Y��r���׶W�L10�r�A�h�ѥk�ܥ����ʨ���ܧ�������r
	DOWNTOUP = 4,							//���ѤU�ܤW���ʡA�쩳����Y��r���׶W�L10�r�A�h�ѥk�ܥ����ʨ���ܧ�������r
	FLIPOVERLEFT = 5,						//���ѥk�ܥ�½����ܤ�r�A������ܫ�Y��r���׶W�L10�r�A�h�ѥk�ܥ����ʨ���ܧ�������r
	FLIPOVERRIGHT = 6,						//���ѥ��ܥk½����ܤ�r�A������ܫ�Y��r���׶W�L10�r�A�h�ѥk�ܥ����ʨ���ܧ�������r
	FLIPOVERUP = 7,							//���ѤW�ܤU½����ܤ�r�A������ܫ�Y��r���׶W�L10�r�A�h�ѥk�ܥ����ʨ���ܧ�������r
	FLIPOVERDOWN = 8,						//���ѤU�ܤW½����ܤ�r�A������ܫ�Y��r���׶W�L10�r�A�h�ѥk�ܥ����ʨ���ܧ�������r
	SNOW = 9								//������ܤ�r�A������ܫ�Y��r���׶W�L10�r�A�h�ѥk�ܥ����ʨ���ܧ�������r
};

HWND m_hMainWnd;							//�D����HWND
int m_nInitDialog;							//��l�Ƴ]�w�X��

COLORREF m_bPointMap[160][16];				//�x�s�]���O�C���C��
std::vector<COLORREF> m_vecColor;			//�x�s��r�C��
CString m_strShow;							//�x�s�]���O��r
wchar_t* m_strFont;							//�x�s�]���O��r�r��
moveType m_nowType;							//�{�b���b���檺�]���O�������O
BOOL m_bMove;								//�������ʬO�_���槹��
std::vector<moveType> m_vecMoveList;		//�x�s�����]���O���ʤ覡�C��
int m_nNowList;								//�x�s���b���檺���ʦC��ǦC

int m_nNowStartX = 0;						//�������ʪ��]���O���W��X�y��
int m_nNowEndX = 0;							//�������ʪ��]���O�k�U��X�y��
int m_nNowStartY = 0;						//�������ʪ��]���O���W��Y�y��
int m_nNowEndY = 0;							//�������ʪ��]���O�k�U��Y�y��

int m_nSnowList[160][16];					//������ܶ���
int m_nSnowOrder;							//�{�b������ܶ���

//����Event
void KeyDownEvent(HWND hWnd, WPARAM wParam, LPARAM lParam);

//�V�q�r���I�}�r�A�u�����@�r��
int string_bitmap(HDC hdc, UINT ch, char* buf, GLYPHMETRICS& gm, int size = 16, wchar_t* wfont = L"�ө���");

//��r���ʰ_�l�ѼƳ]�w
void SetMoveType(moveType type);

//��r�C��]�w
void setColor(COLORREF color, int start = 0, int end = 0);

//��r�����`��
void StringMove();

//��ڳ]�w�]���O�C���I���C��
void SetPoint(HDC hdc, CString str, int size, wchar_t* font);

//RIGHTTOLEFT�Ѽ��ܰʳ]�w
void RightToLeft(HDC hdc, CString str, int size = 16, wchar_t* font = L"�ө���");

//LEFTTORIGHT�ܰʳ]�w
void LeftToRight(HDC hdc, CString str, int size = 16, wchar_t* font = L"�ө���");

//UPTODOWN�Ѽ��ܰʳ]�w
void UpToDown(HDC hdc, CString str, int size = 16, wchar_t* font = L"�ө���");

//DOWNTOUP�Ѽ��ܰʳ]�w
void DownToUp(HDC hdc, CString str, int size = 16, wchar_t* font = L"�ө���");

//FLIPOVERLEFT�Ѽ��ܰʳ]�w
void FlipOverLeft(HDC hdc, CString str, int size = 16, wchar_t* font = L"�ө���");

//FLIPOVERRIGHT�Ѽ��ܰʳ]�w
void FlipOverRight(HDC hdc, CString str, int size = 16, wchar_t* font = L"�ө���");

//FLIPOVERUP�Ѽ��ܰʳ]�w
void FlipOverUp(HDC hdc, CString str, int size = 16, wchar_t* font = L"�ө���");

//FLIPOVERDOWN�Ѽ��ܰʳ]�w
void FlipOverDown(HDC hdc, CString str, int size = 16, wchar_t* font = L"�ө���");

//SNOW�Ѽ��ܰʳ]�w
void Snow(HDC hdc, CString str, int size = 16, wchar_t* font = L"�ө���");

//�]�w�����������OGroup��ܳ]�w
void SelectRadioButton(HWND hDlg, int nIDDlgItem);

//�M�w������ܶ���
void SetSnowList();