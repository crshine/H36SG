#if !defined(AFX_DLGSETTINGCARDTYPE_H__B098CE3F_6AAB_4244_AB1B_27BB9CD080A7__INCLUDED_)
#define AFX_DLGSETTINGCARDTYPE_H__B098CE3F_6AAB_4244_AB1B_27BB9CD080A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgsettingcardtype.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingCardType dialog

class CDlgSettingCardType : public CDialog
{
// Construction
public:
	void ShowTheRule();
	CDlgSettingCardType(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSettingCardType)
	enum { IDD = IDD_SETTING_CARDTYPE };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSettingCardType)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSettingCardType)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETTINGCARDTYPE_H__B098CE3F_6AAB_4244_AB1B_27BB9CD080A7__INCLUDED_)
