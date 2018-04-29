#if !defined(AFX_DLGPAYMENTPARKFEE1_H__5E715195_DF74_4173_9D6A_672D1A6AFDC0__INCLUDED_)
#define AFX_DLGPAYMENTPARKFEE1_H__5E715195_DF74_4173_9D6A_672D1A6AFDC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPaymentParkFee1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgPaymentParkFee1 dialog

class DlgPaymentParkFee1 : public CDialog
{
// Construction
public:
	DlgPaymentParkFee1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgPaymentParkFee1)
	enum { IDD = IDD_PAYMENT_PARK_FEE1 };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgPaymentParkFee1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgPaymentParkFee1)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPAYMENTPARKFEE1_H__5E715195_DF74_4173_9D6A_672D1A6AFDC0__INCLUDED_)
