
// GameView.h : interface of the CGameView class
//

#pragma once

const int SIZE_BORDER = 5;

struct Point
{
	int x;
	int y;
};


class CGameView : public CView
{

private:
	CDC			memDC;
	CBitmap		hBmpOffscreen;

	int			cxFullScreen;
	int			cyFullScreen;


protected: // create from serialization only
	CGameView();
	DECLARE_DYNCREATE(CGameView)

// Attributes
public:
	CGameDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	void MyPaint(int, int);
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // debug version in GameView.cpp
inline CGameDoc* CGameView::GetDocument() const
   { return reinterpret_cast<CGameDoc*>(m_pDocument); }
#endif

