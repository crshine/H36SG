#if !defined(AFX_DLGRATEGROUP_H__FA06455B_51A3_4348_9127_1ADB15401535__INCLUDED_)
#define AFX_DLGRATEGROUP_H__FA06455B_51A3_4348_9127_1ADB15401535__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgrategroup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRateGroup dialog

class CDlgRateGroup : public CDialog
{
// Construction
public:
	void ShowTheRule();
	CDlgRateGroup(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRateGroup)
	enum { IDD = IDD_RATE_GROUP };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRateGroup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation269 0166 861  and 269 0167 336

protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRateGroup)
	afx_msg void OnButtonRefrash();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRATEGROUP_H__FA06455B_51A3_4348_9127_1ADB15401535__INCLUDED_)
