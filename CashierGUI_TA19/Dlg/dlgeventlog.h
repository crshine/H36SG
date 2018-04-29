#if !defined(AFX_DlgEventLog_H__F79489E7_84CE_48D9_9641_CF0EC2D109AC__INCLUDED_)
#define AFX_DlgEventLog_H__F79489E7_84CE_48D9_9641_CF0EC2D109AC__INCLUDED_

#include "..\zz\ZZcolorbutton.h"	// Added by ClassView

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEventLog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgEventLog dialog

class CDlgEventLog : public CDialog
{
// Construction
public:
	BOOL OnInitDialog();
	CZZColorButton m_Colorbtn[3];
	CDlgEventLog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgEventLog)
	enum { IDD = IDD_EVENTLOG };
	CComboBox	m_ComboType;
	CListCtrl	m_listLog;
	CString	m_sKey;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEventLog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgEventLog)
	afx_msg void OnSearch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DlgEventLog_H__F79489E7_84CE_48D9_9641_CF0EC2D109AC__INCLUDED_)
