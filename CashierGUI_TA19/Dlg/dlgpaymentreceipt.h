#if !defined(AFX_DLGPAYMENTRECEIPT_H__5E95D772_8874_4484_A960_CE5BA4D59EC5__INCLUDED_)
#define AFX_DLGPAYMENTRECEIPT_H__5E95D772_8874_4484_A960_CE5BA4D59EC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgpaymentreceipt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentReceipt dialog

class CDlgPaymentReceipt : public CDialog
{
// Construction
public:
	void InitControl();
	CDlgPaymentReceipt(CWnd* pParent = NULL);   // standard constructor
	static SetReceiptNo(CString s){_ReceiptNo = s;}
// Dialog Data
	//{{AFX_DATA(CDlgPaymentReceipt)
	enum { IDD = IDD_PAYMENT_RECEIPT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPaymentReceipt)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPaymentReceipt)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	static CString _ReceiptNo;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPAYMENTRECEIPT_H__5E95D772_8874_4484_A960_CE5BA4D59EC5__INCLUDED_)
