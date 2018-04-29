#if !defined(AFX_PAYMODE_H__AD262D29_294D_4345_94C1_96CA697B8148__INCLUDED_)
#define AFX_PAYMODE_H__AD262D29_294D_4345_94C1_96CA697B8148__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PayMode.h : header file
//
#include "dlg\\dlginput.h"
/////////////////////////////////////////////////////////////////////////////
// PayMode dialog

class PayMode : public CDlgInput
{
// Construction
public:
	PayMode(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PayMode)
	enum { IDD = IDD_DLG_PAYMODE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PayMode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PayMode)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAYMODE_H__AD262D29_294D_4345_94C1_96CA697B8148__INCLUDED_)
