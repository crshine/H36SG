#if !defined(AFX_DLGPAYMENTRECEIPTSHIFTACCOUNT_H__2086DF3A_68B3_458B_BC98_225F02C924F4__INCLUDED_)
#define AFX_DLGPAYMENTRECEIPTSHIFTACCOUNT_H__2086DF3A_68B3_458B_BC98_225F02C924F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgpaymentreceiptshiftaccount.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentReceiptShiftAccount dialog

class CDlgPaymentReceiptShiftAccount : public CDialog
{
// Construction
public:
	CDlgPaymentReceiptShiftAccount(CWnd* pParent = NULL);   // standard constructor
	static void SetBalance(double d){_Balance = d;}
	static void SetCash(double d){	_Cash = d; }
	static void SetOctupos(double d){_Octupos = d;}
	static void SetStoreValue(double b){_StoreValue = b;}
	static void SetActionTime(COleDateTime t){_ActionTime = t;}
	static void SetReceiptNo(CString s){_ReceiptNo = s;}

// Dialog Data
	//{{AFX_DATA(CDlgPaymentReceiptShiftAccount)
	enum { IDD = IDD_PAYMENT_RECEIPT_SHIFTACCOUNT };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPaymentReceiptShiftAccount)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPaymentReceiptShiftAccount)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitControl();
private:
	static double		_Balance;
	static double		_Cash;
	static double		_Octupos;
	static double		_StoreValue;
	static COleDateTime _ActionTime;
	static CString		_ReceiptNo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPAYMENTRECEIPTSHIFTACCOUNT_H__2086DF3A_68B3_458B_BC98_225F02C924F4__INCLUDED_)
