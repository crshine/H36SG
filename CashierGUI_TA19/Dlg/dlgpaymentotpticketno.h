#if !defined(AFX_DLGPAYMENTOTPTICKETNO_H__1DE96F8F_E1F0_400D_B7BF_24D2D1D09B7D__INCLUDED_)
#define AFX_DLGPAYMENTOTPTICKETNO_H__1DE96F8F_E1F0_400D_B7BF_24D2D1D09B7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgpaymentotpticketno.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentOTPTicketNo dialog

class CDlgPaymentOTPTicketNo : public CDlgInput
{
// Construction
public:
	CDlgPaymentOTPTicketNo(CWnd* pParent = NULL);   // standard constructor
	static CString CardNo(){return _CardNo;}
// Dialog Data
	//{{AFX_DATA(CDlgPaymentOTPTicketNo)
	enum { IDD = IDD_PAYMENT_HAND_OTP_TICKET };
	int		m_nTicketType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPaymentOTPTicketNo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPaymentOTPTicketNo)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	static CString _CardNo;
	void InitControl();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPAYMENTOTPTICKETNO_H__1DE96F8F_E1F0_400D_B7BF_24D2D1D09B7D__INCLUDED_)
