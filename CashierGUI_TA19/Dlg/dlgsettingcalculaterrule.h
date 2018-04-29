#if !defined(AFX_DLGSETTINGCALCULATERRULE_H__DEE927F4_24B2_4E4A_B00D_307470540EDE__INCLUDED_)
#define AFX_DLGSETTINGCALCULATERRULE_H__DEE927F4_24B2_4E4A_B00D_307470540EDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgsettingcalculaterrule.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingCalculaterRule dialog

class CDlgSettingCalculaterRule : public CDialog
{
// Construction
public:
	CDlgSettingCalculaterRule(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSettingCalculaterRule)
	enum { IDD = IDD_SETTING_CALCULATERULE };
	BOOL	m_Check1;
	BOOL	m_Check2;
	BOOL	m_Check3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSettingCalculaterRule)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSettingCalculaterRule)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ShowTheRule();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETTINGCALCULATERRULE_H__DEE927F4_24B2_4E4A_B00D_307470540EDE__INCLUDED_)
