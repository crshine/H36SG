#if !defined(AFX_ZZCTRLTOOLBAR_H__9C133EAA_6797_443A_B88D_03E5C59E202D__INCLUDED_)
#define AFX_ZZCTRLTOOLBAR_H__9C133EAA_6797_443A_B88D_03E5C59E202D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZZCtrltoolbar.h : header file
//

#include "ZZClockText.h"

/////////////////////////////////////////////////////////////////////////////
// CZZCtrlToolBar window

class CZZCtrlToolBar : public CToolBar
{
// Construction
public:
	CZZCtrlToolBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZZCtrlToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL LoadToolBarEx(UINT nIDResource, UINT nID);
	virtual ~CZZCtrlToolBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CZZCtrlToolBar)
	//}}AFX_MSG
	CZZClockText m_ZZClockText;

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZZCTRLTOOLBAR_H__9C133EAA_6797_443A_B88D_03E5C59E202D__INCLUDED_)
