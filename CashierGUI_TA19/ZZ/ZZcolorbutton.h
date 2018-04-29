#ifndef _ZZCOLORBUTTON_H
#define _ZZCOLORBUTTON_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZZcolorbutton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZZColorButton window

class CZZColorButton : public CButton
{
DECLARE_DYNAMIC(CZZColorButton)

// Construction
public:
	CZZColorButton();
	BOOL Attach(const UINT nID, CWnd* pParent, 
		const COLORREF BGColor = RGB(255, 165, 0),		// gray button
		const COLORREF FGColor = RGB(255, 255, 255),				// black text 
		const COLORREF DisabledColor = RGB(245, 222, 179),	// dark gray disabled text
		const UINT nBevel = 2
	);
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZZColorButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CZZColorButton();

	// Generated message map functions
protected:
	void DrawButtonText(CDC *DC, CRect R, const char *Buf, COLORREF TextColor);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	void DrawFilledRect(CDC *DC, CRect R, COLORREF color);
	void DrawFrame(CDC *DC, CRect R, int Inset);
	void DrawLine(CDC *DC, CRect EndPoints, COLORREF color);
	void DrawLine(CDC *DC, long left, long top, long right, long bottom, COLORREF color);

	COLORREF GetBGColor() { return m_bg; }
    COLORREF GetDisabledColor() { return m_disabled; }
	COLORREF GetFGColor() { return m_fg; };
	UINT GetBevel() { return m_bevel; }
	//{{AFX_MSG(CZZColorButton)
	//}}AFX_MSG
private:
	COLORREF m_fg, m_bg, m_disabled;
	UINT m_bevel;

//	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
