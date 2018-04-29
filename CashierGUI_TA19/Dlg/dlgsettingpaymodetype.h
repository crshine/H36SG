#if !defined(AFX_DLGSETTINGPAYMODETYPE_H__2ECA8C1E_A703_4DB9_9E5F_D0C9081C8A9D__INCLUDED_)
#define AFX_DLGSETTINGPAYMODETYPE_H__2ECA8C1E_A703_4DB9_9E5F_D0C9081C8A9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgsettingpaymodetype.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingPaymodeType dialog

class CDlgSettingPaymodeType : public CDialog
{
// Construction
public:
	void ShowTheRule();
	CDlgSettingPaymodeType(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSettingPaymodeType)
	enum { IDD = IDD_SETTING_PAYMODETYPE };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSettingPaymodeType)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSettingPaymodeType)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETTINGPAYMODETYPE_H__2ECA8C1E_A703_4DB9_9E5F_D0C9081C8A9D__INCLUDED_)
