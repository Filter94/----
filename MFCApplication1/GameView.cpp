#include <time.h>  
// GameView.cpp : implementation of the CGameView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Game.h"
#endif

#include "GameDoc.h"
#include "GameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//#define #FFF5EE 2;
//#define RGB(255,228,196) 4;
//#define RGB(255,165,79)  8;
//#define RGB(205,102,29) 16;
//#define RGB(238,99,99)  32;
//#define RGB(238,44,44)  64;

// CGameView

IMPLEMENT_DYNCREATE(CGameView, CView)

BEGIN_MESSAGE_MAP(CGameView, CView)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CGameView construction/destruction

CGameView::CGameView()
{
	// TODO: add construction code here

}

CGameView::~CGameView()
{
}

BOOL CGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CGameView::OnDraw(CDC* pDC)
{
	CGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	int r = GetUpdateRect(&rect);

	//pDC->BitBlt(rect.left, rect.top, rect.right, rect.bottom, &memDC, rect.left, rect.top, SRCCOPY); // клиентской области окна
	pDC->BitBlt(0, 0, cxFullScreen, cyFullScreen, &memDC, 0, 0, SRCCOPY); // клиентской области окна
}

#ifdef _DEBUG
void CGameView::AssertValid() const
{
	CView::AssertValid();
}

void CGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGameDoc* CGameView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGameDoc)));
	return (CGameDoc*)m_pDocument;
}
#endif

void CGameView::MyPaint(int cx, int cy)
{
	PatBlt(memDC, 0, 0, cxFullScreen, cyFullScreen, WHITENESS);
		
	int x = cx / 8;
	int y = cy / 6;
	memDC.Rectangle(x * 2, y, x * 6, y * 5);

	COLORREF  crBrush;
	int _i = 0;
	int _j = 0;
	CString str;
	for (int i = 1; i < 5; i++, _i++, _j = 0)
		for (int j = 2; j < 6; j++, _j++)
		{
			int n = GetDocument()->GetElementMatrix(_i, _j);
			switch (n)
			{
				case 0:
				{
					crBrush = RGB(122,103,238);
					break;
				}
				case 2:
				{
					crBrush = RGB(255, 245, 238);
					break;
				}
				case 4:
				{
					crBrush = RGB(255, 228, 196);
					break;
				}
				case 8:
				{
					crBrush = RGB(255, 165, 79);
					break;
				}
				case 16:
				{
					crBrush = RGB(205, 102, 29);
					break;
				}
				case 32:
				{
					crBrush = RGB(238, 99, 99);
					break;
				}
				case 64:
				{
					crBrush = RGB(238, 44, 44);
					break;
				}
				case 128:
				{
					crBrush = RGB(139,35,35);
					break;
				}
				case 256:
				{
					crBrush = RGB(255,165,0);
					break;
				}
				case 512:
				{
					crBrush = RGB(205,133,0);
					break;
				}
				case 1024:
				{
					crBrush = RGB(224,102,255);
					break;
				}
				case 2048:
				{
					crBrush = RGB(144,238,144);
					break;
				}
				defaulf:break;
			}

			CBrush brush;
			brush.CreateSolidBrush(crBrush);
			CBrush* pOldBrush = memDC.SelectObject(&brush);
//			hBrushOld = (HBRUSH)SelectObject(memDC, hBrush);
		

			char buffer[10];
			if (n == 0)
				strcpy_s(buffer, "");
			else
				_itoa_s(n, buffer, 10);
			CString s(buffer);
			
			_itoa_s(GetDocument()->GetScore(), buffer, 10);
			memDC.Rectangle(x * j, y * i, x * (j + 1), y * (i + 1));
			memDC.TextOut(x * j + 10, y * i + 10, s);

			_itoa_s(GetDocument()->GetScore(), buffer, 10);
			s = buffer;
			memDC.TextOut(50, 50, s);

			memDC.SelectObject(pOldBrush);

		}
}

int CGameView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	srand(time(NULL));
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	

	GetDocument()->SetElementMatrix(rand() % 4, rand() % 4, 2);

	Point pt1;
	do
	{
		pt1.x = rand() % 4;
		pt1.y = rand() % 4;
	} while (GetDocument()->GetElementMatrix(pt1.x, pt1.y) != 0);

	if (GetDocument()->flag)
	{
		if ((rand() % 2))
			GetDocument()->SetElementMatrix(pt1.x, pt1.y, 2);
		else
			GetDocument()->SetElementMatrix(pt1.x, pt1.y, 4);
	}

	cxFullScreen = GetSystemMetrics(SM_CXFULLSCREEN);
	cyFullScreen = GetSystemMetrics(SM_CYFULLSCREEN);

	CDC* pDC = GetDC();
	memDC.CreateCompatibleDC(pDC);
	hBmpOffscreen.CreateCompatibleBitmap(pDC, cxFullScreen, cyFullScreen);
	memDC.SelectObject(&hBmpOffscreen);
	PatBlt(memDC, 0, 0, cxFullScreen, cyFullScreen, WHITENESS);

	LOGFONT		font;
	HFONT		hfont;
	COLORREF	crPen;
	HPEN	    hPen, hPenOld;
	HBRUSH	    hBrush, hBrushOld;

	font.lfHeight = 60;// Устанавливает высоту шрифта или символа
	font.lfWidth = 0;// Устанавливает среднюю ширину символов в шрифте
	font.lfEscapement = 0;// Устанавливает угол, между вектором наклона и осью X устройства
	font.lfOrientation = 0;// Устанавливает угол, между основной линией каждого символа и осью X устройства
	font.lfWeight = 100;// Устанавливает толщину шрифта в диапазоне от 0 до 1000
	font.lfItalic = 0;// Устанавливает курсивный шрифт
	font.lfUnderline = 0;// Устанавливает подчеркнутый шрифт
	font.lfStrikeOut = 0;// Устанавливает зачеркнутый шрифт
	font.lfCharSet = RUSSIAN_CHARSET;// Устанавливает набор символов
	font.lfOutPrecision = 0;// Устанавливает точность вывода
	font.lfClipPrecision = 0;// Устанавливает точность отсечения
	font.lfQuality = 0;// Устанавливает качество вывода
	font.lfPitchAndFamily = 0;// Устанавливает ширину символов и семейство шрифта
	lstrcpyn(font.lfFaceName, _T("Razer Header Light"), LF_FACESIZE);
	hfont = ::CreateFontIndirect(&font);
	SelectObject(memDC, hfont);
	SetBkMode(memDC, TRANSPARENT);

	crPen = RGB(71,60,139);
	hPen = CreatePen(PS_SOLID, SIZE_BORDER, crPen);
	hPenOld = (HPEN)SelectObject(memDC, hPen);

	ReleaseDC(pDC);
	return 0;
}

void CGameView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	CRect rect;
	GetClientRect(rect);
	MyPaint(rect.right, rect.bottom);
	InvalidateRect(rect);
}

void CGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CView::OnKeyDown(nChar, nRepCnt, nFlags);

	switch (nChar)
	{
	case VK_LEFT :
		{
			GetDocument() -> flag = GetDocument()->Left();
			break;
		}
		case 39: //right
		{
			GetDocument()->flag = GetDocument()->Right();
			break;
		}
		case 38: //up
		{
			GetDocument()->flag = GetDocument()->Up();
			break;
		}
		case 40: //down
		{ 
			GetDocument()->flag = GetDocument()->Down();
			break;
		}
		default:return;
	}

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
			int n = GetDocument()->GetElementMatrix(i, j);
	}

	Point pt1;
	do
	{
		pt1.x = rand() % 4;
		pt1.y = rand() % 4;
	} while (GetDocument()->GetElementMatrix(pt1.x, pt1.y) != 0);

	if (GetDocument()->flag)
	{
		if ((rand() % 2))
			GetDocument()->SetElementMatrix(pt1.x, pt1.y, 2);
		else
			GetDocument()->SetElementMatrix(pt1.x, pt1.y, 4);
	}

	GetDocument()->UpdateAllViews(NULL);

}

void CGameView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	MyPaint(cx,cy);
}

