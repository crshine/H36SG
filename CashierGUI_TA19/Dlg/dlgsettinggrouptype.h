#if !defined(AFX_DLGSETTINGGROUPTYPE_H__97980E92_1C01_4552_86CF_32E2C13AF41A__INCLUDED_)
#define AFX_DLGSETTINGGROUPTYPE_H__97980E92_1C01_4552_86CF_32E2C13AF41A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgsettinggrouptype.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingGroupType dialog

class CDlgSettingGroupType : public CDialog
{
// Construction
public:
	ShowTheRule();
	CDlgSettingGroupType(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSettingGroupType)
	enum { IDD = IDD_SETTING_GROUPTYPE };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSettingGroupType)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSettingGroupType)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETTINGGROUPTYPE_H__97980E92_1C01_4552_86CF_32E2C13AF41A__INCLUDED_)
