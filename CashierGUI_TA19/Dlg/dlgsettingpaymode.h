#if !defined(AFX_DLGSETTINGPAYMODE_H__BF5DCF97_F87E_4030_9AD1_AAE49D746B2F__INCLUDED_)
#define AFX_DLGSETTINGPAYMODE_H__BF5DCF97_F87E_4030_9AD1_AAE49D746B2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSettingPaymode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingPaymode dialog

class CDlgSettingPaymode : public CDialog
{
// Construction
public:
	void ShowTheRule();
	CDlgSettingPaymode(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSettingPaymode)
	enum { IDD = IDD_SETTING_PAYMODE };
	BOOL	m_Check1;
	BOOL	m_Check2;
	BOOL	m_Check3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSettingPaymode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSettingPaymode)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETTINGPAYMODE_H__BF5DCF97_F87E_4030_9AD1_AAE49D746B2F__INCLUDED_)
