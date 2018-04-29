#if !defined(AFX_DLGPAYMENTOTPPREADDVALUE_H__C5975FD4_DADD_40ED_8AD8_7263AEAE57BB__INCLUDED_)
#define AFX_DLGPAYMENTOTPPREADDVALUE_H__C5975FD4_DADD_40ED_8AD8_7263AEAE57BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgpaymentotppreaddvalue.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentOTPPreAddvalue dialog

class CDlgPaymentOTPPreAddvalue : public CDlgInput
{
// Construction
public:
	CDlgPaymentOTPPreAddvalue(CWnd* pParent = NULL);   // standard constructor
	~CDlgPaymentOTPPreAddvalue();
	static double Amount(){return _Amount;}
	static double OctopusRemain(){return _OctopusRemain;}
	static CString OctopusCardNo(){return _OctopusCardNo;}

// Dialog Data
	//{{AFX_DATA(CDlgPaymentOTPPreAddvalue)
	enum { IDD = IDD_PAYMENT_OTP_PRE_ADDVALUE };
	CString	m_Amount;
	CString	m_OctopusCardNo;
	CString	m_OctopusRemain;
	int		m_AvSel;
	CString	m_CUR_STATUS;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPaymentOTPPreAddvalue)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL CardStatus;

	// Generated message map functions
	//{{AFX_MSG(CDlgPaymentOTPPreAddvalue)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusAMOUNT();
	afx_msg void OnWaitOtpPoll();
	afx_msg void OnAv50();
	afx_msg void OnAv100();
	afx_msg void OnAv200();
	afx_msg void OnAv300();
	afx_msg void OnAv400();
	afx_msg void OnAv500();
	afx_msg void OnEditchangeAvsel();
	afx_msg void OnSelchangeAvsel();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	static void CALLBACK PollDetect(const CCmdOtp::PATRON &CardInfo);

	void InitControl();
	static CDlgPaymentOTPPreAddvalue * pThis;
	static CString _OctopusCardNo;		//八达通卡号
	static double _OctopusRemain;		//八达通余额
	static double _Amount;				//冲值金额
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPAYMENTOTPPREADDVALUE_H__C5975FD4_DADD_40ED_8AD8_7263AEAE57BB__INCLUDED_)
