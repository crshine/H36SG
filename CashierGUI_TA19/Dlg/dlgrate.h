#if !defined(AFX_DLGRATE_H__9061817F_F8C1_4270_83E7_F31730BD5DB8__INCLUDED_)
#define AFX_DLGRATE_H__9061817F_F8C1_4270_83E7_F31730BD5DB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgrate.h : header file
//
#include "..\ZZ\ZZMovetabctrl.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgRate dialog

class CDlgRate : public CDialog
{
// Construction
public:
	CDlgRate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRate)
	enum { IDD = IDD_RATE };
	CZZMoveTabCtrl	m_tab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRate)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CDialog * m_pdlgFee;
	CDialog * m_pdlgTimezone;
	CDialog * m_pdlgCar;
	CDialog * m_pdlgGroup;
	CDialog * m_pdlgDay;
	CDialog * m_pdlgFix;
	CDialog * m_pdlgCalculate;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRATE_H__9061817F_F8C1_4270_83E7_F31730BD5DB8__INCLUDED_)
