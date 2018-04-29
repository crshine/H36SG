#ifndef _ZZTITLESTATIC_H
#define _ZZTITLESTATIC_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZZTitleStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZZTitleStatic window

class CZZTitleStatic : public CStatic
{
// Construction
public:
	CZZTitleStatic();

// Attributes
public:
	void SetTextColor( COLORREF rgb, BOOL ISTitle = FALSE );
	void SetBackgroundColor( COLORREF rgb);
	void SetFont( LPCTSTR lpszFaceName, int nPointSize, BOOL ISTitle = FALSE);
	void SetFont(LOGFONT *pLogFont, BOOL ISTitle = FALSE );
	void SetBold(BOOL bFlag, BOOL ISTitle = FALSE );
	void SetMargins(int x, int y , BOOL ISTitle = FALSE );

// Operations
public:
	BOOL SetWindowText( LPCTSTR lpszString, BOOL ISTitle = FALSE );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZZTitleStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetAllAttrib( COLORREF rgbBackground,
		 COLORREF rgbTitle, int iTitleXMargin, int iTitleYMargin, LPCTSTR lpszTitleFaceName, int nTitlePointSize, bool bTitleBold, LPCTSTR lpszTitleString,
		 COLORREF rgbText, int iTextXMargin, int iTextYMargin, LPCTSTR lpszTextFaceName, int nTextPointSize, bool bTextBold, LPCTSTR lpszTextString);
	virtual ~CZZTitleStatic();

	// Generated message map functions
protected:
	typedef struct _STRUCT_TEXTATTRIB
	{
		CFont		font;
		COLORREF	rgb;
		BOOL		bBold;
		int			nXMargin;
		int			nYMargin;
		CString *	sText;
		_STRUCT_TEXTATTRIB::_STRUCT_TEXTATTRIB()
		{::ZeroMemory(this, sizeof(_STRUCT_TEXTATTRIB));}
	} STRUCT_TEXTATTRIB;

	STRUCT_TEXTATTRIB	m_Title;
	STRUCT_TEXTATTRIB	m_Text;

	COLORREF	m_rgbBackground;
	CBrush *	m_pBrush;
	CString		sText, sTitle;
	//{{AFX_MSG(CZZTitleStatic)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZZTITLESTATIC_H__8298BD29_2EF0_4E8D_B375_37A96D1D3FD1__INCLUDED_)
