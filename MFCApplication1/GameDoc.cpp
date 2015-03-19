
// GameDoc.cpp : implementation of the CGameDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Game.h"
#endif

#include "GameDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGameDoc

IMPLEMENT_DYNCREATE(CGameDoc, CDocument)

BEGIN_MESSAGE_MAP(CGameDoc, CDocument)
	ON_COMMAND(ID_EDIT_UNDO, &CGameDoc::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CGameDoc::OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_REDO, &CGameDoc::OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, &CGameDoc::OnUpdateEditRedo)
END_MESSAGE_MAP()


// CGameDoc construction/destruction

CGameDoc::CGameDoc()
{
	Array = new int*[N];
	for (size_t i = 0; i < N; i++)
		Array[i] = new int[N];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			Array[i][j] = 0;

	flag = true;
	score = 0;
}

CGameDoc::~CGameDoc()
{
	for (size_t i = 0; i < N; i++)
	{
		delete[] Array[i];
	}
	delete[] Array;
}

BOOL CGameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}


// CGameDoc serialization

void CGameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CGameDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CGameDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CGameDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CGameDoc diagnostics

#ifdef _DEBUG
void CGameDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGameDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGameDoc commands


void CGameDoc::OnEditUndo()
{
	int t = 0;
	// TODO: добавьте свой код обработчика команд
}


void CGameDoc::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}


void CGameDoc::OnEditRedo()
{
	// TODO: добавьте свой код обработчика команд
}


void CGameDoc::OnUpdateEditRedo(CCmdUI *pCmdUI)
{
	// TODO: добавьте свой код обработчика ИП обновления команд
}
