// ZZTitleStatic.cpp : implementation file
//

#include "stdafx.h"
#include "ZZTitleStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZZTitleStatic

CZZTitleStatic::CZZTitleStatic()
{
	sTitle = _T("Title");
	sText = _T("Text");

	m_Text.sText = & sText;
	m_Text.rgb = GetSysColor(COLOR_BTNTEXT); 
	m_Text.bBold = FALSE;
	m_Text.nXMargin = 14;
	m_Text.nYMargin = 14;

	m_Title.sText = & sTitle;
	m_Title.rgb = GetSysColor(COLOR_BTNTEXT); 
	m_Title.bBold = FALSE;
	m_Title.nXMargin = 0;
	m_Title.nYMargin = 0;

	m_rgbBackground = GetSysColor(COLOR_BTNFACE);
	m_pBrush        = new CBrush(m_rgbBackground);
}

CZZTitleStatic::~CZZTitleStatic()
{
	m_pBrush->DeleteObject();
	delete m_pBrush;
}


BEGIN_MESSAGE_MAP(CZZTitleStatic, CStatic)
	//{{AFX_MSG_MAP(CZZTitleStatic)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZZTitleStatic message handlers

void CZZTitleStatic::OnPaint() 
{

	CPaintDC dc(this); // device context for painting
	dc.SaveDC();

	UINT nFormat = 0;
	nFormat |= DT_LEFT;
	nFormat |= DT_SINGLELINE;//wordbreak & left

	dc.SetBkColor(m_rgbBackground);
	dc.SelectObject(m_pBrush);

	CRect rect;

	//draw title 
	GetClientRect(rect); 
	dc.SetBkMode(OPAQUE);
	dc.SelectObject(&m_Title.font);
	dc.SetTextColor(m_Title.rgb);
	rect.left += m_Title.nXMargin;
	rect.top  += m_Title.nYMargin;
	dc.DrawText((const CString)* m_Title.sText, rect, nFormat);


	//draw text
	GetClientRect(rect); 
	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(&m_Text.font);
	dc.SetTextColor(m_Text.rgb);
	rect.left += m_Text.nXMargin;
	rect.top  += m_Text.nYMargin;
	dc.DrawText((const CString)* m_Text.sText, rect, nFormat);

	dc.RestoreDC(-1);
}

BOOL CZZTitleStatic::OnEraseBkgnd(CDC* pDC) 
{
	CRect cr;
	GetClientRect(cr);
	pDC->FillRect(&cr, m_pBrush);
	return TRUE;
}

void CZZTitleStatic::SetFont( LPCTSTR lpszFaceName, int nPointSize, BOOL ISTitle /*= FALSE*/ )
{
	LOGFONT lf;
	memset(&lf, 0, sizeof(lf));

	if (lpszFaceName == NULL)
	{
		CFont *pFont = GetFont();
		ASSERT(pFont);
		pFont->GetLogFont(&lf);
	}
	else
	{
		_tcsncpy(lf.lfFaceName, lpszFaceName, sizeof(lf.lfFaceName)/sizeof(TCHAR)-1);
	}

	//font size
	HDC hdc = ::CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
	ASSERT(hdc);
	int cyPixelsPerInch = ::GetDeviceCaps(hdc, LOGPIXELSY);
	::DeleteDC(hdc);
	lf.lfHeight = -MulDiv(nPointSize, cyPixelsPerInch, 72);

	SetFont(&lf, ISTitle);
}

void CZZTitleStatic::SetFont(LOGFONT *pLogFont, BOOL ISTitle /*= FALSE*/)
{
	ASSERT(pLogFont);
	if (!pLogFont)
		return;

	STRUCT_TEXTATTRIB	*pText;
	if (ISTitle)
		pText = & m_Title;
	else
		pText = & m_Text;


	if (pText->font.GetSafeHandle())
		pText->font.DeleteObject();

	LOGFONT lf = *pLogFont;

	lf.lfWeight = pText->bBold ? FW_BOLD : FW_NORMAL;

	pText->font.CreateFontIndirect(&lf);

}

void CZZTitleStatic::SetTextColor( COLORREF rgb, BOOL ISTitle /*= FALSE*/ )
{
	if (ISTitle)
		m_Title.rgb = rgb;
	else
		m_Text.rgb = rgb;
}

void CZZTitleStatic::SetBackgroundColor( COLORREF rgb )
{
	m_rgbBackground = rgb; 
	if (m_pBrush)
	{
		m_pBrush->DeleteObject();
		delete m_pBrush;
	}
	m_pBrush = new CBrush(m_rgbBackground);
	RedrawWindow();
}

BOOL CZZTitleStatic::SetWindowText( LPCTSTR lpszString, BOOL ISTitle /*= FALSE*/ )
{
	if (ISTitle)
		sTitle = lpszString;
	else
		sText = lpszString;
	RedrawWindow();
	return true;
}

void CZZTitleStatic::SetMargins(int x, int y , BOOL ISTitle /*= FALSE*/ )
{
	if (ISTitle)
	{
		m_Title.nXMargin = x;
		m_Title.nYMargin = y;
	}else{
		m_Text.nXMargin = x;
		m_Text.nYMargin = y;
	}
}

void CZZTitleStatic::SetBold(BOOL bFlag, BOOL ISTitle /*= FALSE*/ )
{
	if (ISTitle)
	{
		m_Title.bBold = bFlag;
	}else{
		m_Text.bBold = bFlag;
	}
}

void CZZTitleStatic::SetAllAttrib( COLORREF rgbBackground,
		 COLORREF rgbTitle, int iTitleXMargin, int iTitleYMargin, LPCTSTR lpszTitleFaceName, int nTitlePointSize, bool bTitleBold, LPCTSTR lpszTitleString,
		 COLORREF rgbText, int iTextXMargin, int iTextYMargin, LPCTSTR lpszTextFaceName, int nTextPointSize, bool bTextBold, LPCTSTR lpszTextString)
{
	SetBackgroundColor(rgbBackground);
	//Title
	SetTextColor(rgbTitle, TRUE);
	SetBold(bTitleBold, TRUE);
	SetMargins(iTitleXMargin, iTitleYMargin, TRUE);
	SetFont(lpszTitleFaceName, nTitlePointSize, TRUE);
	SetWindowText(lpszTitleString, TRUE);
	//Text
	SetTextColor(rgbText);
	SetBold(bTextBold);
	SetMargins(iTextXMargin, iTextYMargin);
	SetFont(lpszTextFaceName, nTextPointSize);
	SetWindowText(lpszTextString);
}
