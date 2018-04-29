#if !defined(AFX_DLGPAYMENTRECEIPTCLOSEACCOUNT_H__CB6F432F_38F7_4EC2_8D59_0BEB65FCEBB4__INCLUDED_)
#define AFX_DLGPAYMENTRECEIPTCLOSEACCOUNT_H__CB6F432F_38F7_4EC2_8D59_0BEB65FCEBB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgpaymentreceiptcloseaccount.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentReceiptCloseAccount dialog

class CDlgPaymentReceiptCloseAccount : public CDlgInput
{
// Construction
public:
	CDlgPaymentReceiptCloseAccount(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPaymentReceiptCloseAccount)
	enum { IDD = IDD_PAYMENT_RECEIPT_CLOSEACCOUNT };
	CString	m_Balance;
	CString	m_LoginTime;
	CString	m_LogoutTime;
	CString	m_OldBalance;
	CString	m_Operater;
	CString	m_ReceiptNo;
	CString	m_WithDrawal;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPaymentReceiptCloseAccount)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPaymentReceiptCloseAccount)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPAYMENTRECEIPTCLOSEACCOUNT_H__CB6F432F_38F7_4EC2_8D59_0BEB65FCEBB4__INCLUDED_)
