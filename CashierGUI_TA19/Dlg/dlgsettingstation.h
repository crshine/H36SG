#if !defined(AFX_DLGSETTINGSTATION_H__C7CB0586_0306_4339_9531_37061295557A__INCLUDED_)
#define AFX_DLGSETTINGSTATION_H__C7CB0586_0306_4339_9531_37061295557A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgsettingstation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingStation dialog

class CDlgSettingStation : public CDialog
{
// Construction
public:
	void ShowTheRule();
	CDlgSettingStation(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSettingStation)
	enum { IDD = IDD_SETTING_STATION };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSettingStation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSettingStation)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETTINGSTATION_H__C7CB0586_0306_4339_9531_37061295557A__INCLUDED_)
