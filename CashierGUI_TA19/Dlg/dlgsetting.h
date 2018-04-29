#if !defined(AFX_DLGSETTING_H__DD59CEAC_5407_4F10_8306_ACFA5D433B3F__INCLUDED_)
#define AFX_DLGSETTING_H__DD59CEAC_5407_4F10_8306_ACFA5D433B3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSetting.h : header file
//
#include "..\ZZ\ZZMovetabctrl.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgSetting dialog

class CDlgSetting : public CDialog
{
// Construction
public:
	CDlgSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSetting)
	enum { IDD = IDD_SETTING };
	CZZMoveTabCtrl	m_tab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSetting)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSetting)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CDialog * m_pdlgsystem;
	CDialog * m_pdlgperipheral;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETTING_H__DD59CEAC_5407_4F10_8306_ACFA5D433B3F__INCLUDED_)
