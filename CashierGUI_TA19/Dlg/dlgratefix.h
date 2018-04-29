#if !defined(AFX_DLGRATEFIX_H__5E7F8D97_3D97_4CDD_845F_62F8999C9A90__INCLUDED_)
#define AFX_DLGRATEFIX_H__5E7F8D97_3D97_4CDD_845F_62F8999C9A90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgratefix.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRateFix dialog

class CDlgRateFix : public CDialog
{
// Construction
public:
	void ShowTheRule();
	CDlgRateFix(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRateFix)
	enum { IDD = IDD_RATE_FIX };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRateFix)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRateFix)
	afx_msg void OnButtonRefrash();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString showHHMM(short mins);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRATEFIX_H__5E7F8D97_3D97_4CDD_845F_62F8999C9A90__INCLUDED_)
