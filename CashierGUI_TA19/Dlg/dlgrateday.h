#if !defined(AFX_DLGRATEDAY_H__B498FD82_3F3B_4F56_BB8A_984851D0E0B3__INCLUDED_)
#define AFX_DLGRATEDAY_H__B498FD82_3F3B_4F56_BB8A_984851D0E0B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgrateday.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRateDay dialog

class CDlgRateDay : public CDialog
{
// Construction
public:
	void ShowTheRule();
	CDlgRateDay(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRateDay)
	enum { IDD = IDD_RATE_DAY };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRateDay)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRateDay)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonRefrash();
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRATEDAY_H__B498FD82_3F3B_4F56_BB8A_984851D0E0B3__INCLUDED_)
