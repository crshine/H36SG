#if !defined(AFX_DLGCREATECARD4_H__F516D9D6_C654_4C80_9C84_DF915881A45A__INCLUDED_)
#define AFX_DLGCREATECARD4_H__F516D9D6_C654_4C80_9C84_DF915881A45A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgcreatecard4.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateCard4 dialog

class CDlgCreateCard4 : public CDialog
{
	DECLARE_DYNCREATE(CDlgCreateCard4)

// Construction
public:
	bool CheckInput();
	CDlgCreateCard4();
	~CDlgCreateCard4();

// Dialog Data
	//{{AFX_DATA(CDlgCreateCard4)
	enum { IDD = IDD_CARD_CREATE4 };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgCreateCard4)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgCreateCard4)
	virtual BOOL OnInitDialog();
	virtual void OnOK(){};
	virtual void OnCancel(){};
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	LPVOID m_pDlg;
	void InitControl();
public: 
	void SetParentDlg(LPVOID pDlg){m_pDlg = pDlg;}
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCREATECARD4_H__F516D9D6_C654_4C80_9C84_DF915881A45A__INCLUDED_)
