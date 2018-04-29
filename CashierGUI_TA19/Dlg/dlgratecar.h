#if !defined(AFX_DLGRATECAR_H__2CA93F29_87D9_4C5D_BD1D_63D6528275BF__INCLUDED_)
#define AFX_DLGRATECAR_H__2CA93F29_87D9_4C5D_BD1D_63D6528275BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgratecar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRateCar dialog

class CDlgRateCar : public CDialog
{
// Construction
public:
	void ShowTheRule();
	CDlgRateCar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRateCar)
	enum { IDD = IDD_RATE_CARTYPE };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRateCar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRateCar)
	afx_msg void OnButtonRefrash();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRATECAR_H__2CA93F29_87D9_4C5D_BD1D_63D6528275BF__INCLUDED_)
