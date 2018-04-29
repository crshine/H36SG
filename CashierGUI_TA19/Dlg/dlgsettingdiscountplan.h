#if !defined(AFX_DLGSETTINGDISCOUNTPLAN_H__511C21D4_DB0C_4C91_BF23_E2230F2176AF__INCLUDED_)
#define AFX_DLGSETTINGDISCOUNTPLAN_H__511C21D4_DB0C_4C91_BF23_E2230F2176AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSettingDiscountPlan.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingDiscountPlan dialog

class CDlgSettingDiscountPlan : public CDialog
{
// Construction
public:
	void ShowTheRule();
	CDlgSettingDiscountPlan(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSettingDiscountPlan)
	enum { IDD = IDD_SETTING_DISCOUNTPLAN };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSettingDiscountPlan)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSettingDiscountPlan)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETTINGDISCOUNTPLAN_H__511C21D4_DB0C_4C91_BF23_E2230F2176AF__INCLUDED_)
