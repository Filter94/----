
// GameDoc.h : interface of the CGameDoc class
//


#pragma once


class CGameDoc : public CDocument
{
private:
	int** Array;
	const int N = 4;
	int bestScore;
	int score;
public:
	bool	flag;
	int		GetElementMatrix(int i, int j)
		{ return Array[i][j]; }
	void	SetElementMatrix(int i, int j, int number)
	{
		Array[i][j] = number;
	}

protected: // create from serialization only
	CGameDoc();
	DECLARE_DYNCREATE(CGameDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditRedo(CCmdUI *pCmdUI);
};
