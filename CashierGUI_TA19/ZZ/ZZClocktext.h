#ifndef _ZZCLOCKTEXT_H
#define _ZZCLOCKTEXT_H

#include "ZZTitleStatic.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZZClocktext.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZZClockText window

class CZZClockText : public CZZTitleStatic
{
// Construction
public:
	CZZClockText();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZZClockText)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL Start();
	static UINT thrClock(LPVOID pParam);
	virtual ~CZZClockText();

	// Generated message map functions
protected:
	void Refresh();
	typedef struct _STRUCT_THRCLOCK
	{
		BOOL		bRun;
		int			nStep;
		LPVOID		pParent;
		HANDLE		hThrHandle;
		DWORD		dwThrId;

		_STRUCT_THRCLOCK::_STRUCT_THRCLOCK()
		{::ZeroMemory(this, sizeof(_STRUCT_THRCLOCK));}
	} STRUCT_THRCLOCK;

	STRUCT_THRCLOCK m_thrParam;
	//{{AFX_MSG(CZZClockText)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
