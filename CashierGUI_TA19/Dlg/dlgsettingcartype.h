#if !defined(AFX_DLGSETTINGCARTYPE_H__68235D6C_183E_47C1_9E8C_8E4B9482D809__INCLUDED_)
#define AFX_DLGSETTINGCARTYPE_H__68235D6C_183E_47C1_9E8C_8E4B9482D809__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgsettingcartype.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingCarType dialog

class CDlgSettingCarType : public CDialog
{
// Construction
public:
	void ShowTheRule();
	CDlgSettingCarType(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSettingCarType)
	enum { IDD = IDD_SETTING_CARTYPE };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSettingCarType)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSettingCarType)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETTINGCARTYPE_H__68235D6C_183E_47C1_9E8C_8E4B9482D809__INCLUDED_)
