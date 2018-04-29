#if !defined(AFX_DLGPAYMENTACCOUNT_H__A9112FDD_0AE3_4624_BB13_A56B92A38550__INCLUDED_)
#define AFX_DLGPAYMENTACCOUNT_H__A9112FDD_0AE3_4624_BB13_A56B92A38550__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPaymentAccount.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentAccount dialog

class CDlgPaymentAccount : public CDialog
{
// Construction
public:
	CDlgPaymentAccount(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPaymentAccount)
	enum { IDD = IDD_PAYMENT_ACCOUNT };
	CListBox	m_cList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPaymentAccount)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPaymentAccount)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ShowAccount();
	void InitControl();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPAYMENTACCOUNT_H__A9112FDD_0AE3_4624_BB13_A56B92A38550__INCLUDED_)
