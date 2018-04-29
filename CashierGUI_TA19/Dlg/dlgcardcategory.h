#if !defined(AFX_DLGCARDCATEGORY_H__A2BDA152_889D_496D_AA65_7141DFFACFA6__INCLUDED_)
#define AFX_DLGCARDCATEGORY_H__A2BDA152_889D_496D_AA65_7141DFFACFA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgcardcategory.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCardCategory dialog

class CDlgCardCategory : public CDialog
{
// Construction
public:
	void ShowTheRule();
	CDlgCardCategory(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCardCategory)
	enum { IDD = IDD_CARD_CATEGROY };
	CEdit	m_Category;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCardCategory)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCardCategory)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonRefrash();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCARDCATEGORY_H__A2BDA152_889D_496D_AA65_7141DFFACFA6__INCLUDED_)
