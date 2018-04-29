#if !defined(AFX_DLGPAYMENTOTPSUBADDVALUE_H__DFEF7E20_C2F0_4DF8_93DC_A5FBFFA9B20D__INCLUDED_)
#define AFX_DLGPAYMENTOTPSUBADDVALUE_H__DFEF7E20_C2F0_4DF8_93DC_A5FBFFA9B20D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgpaymentotpsubaddvalue.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentOTPSubAddvalue dialog

class CDlgPaymentOTPSubAddvalue : public CDlgInput
{
// Construction
public:
	CDlgPaymentOTPSubAddvalue(CWnd* pParent = NULL);   // standard constructor
	~CDlgPaymentOTPSubAddvalue();
	static void SetAmount(double d){_Amount = d;}
	static void SetOctopusRemain(double d){_OctopusRemain = d;}
	static void SetOctopusCardNo(CString s)
	{ASSERT(s.GetLength() > 1); _OctopusCardNo = s.Right(s.GetLength() - 1);}

// Dialog Data
	//{{AFX_DATA(CDlgPaymentOTPSubAddvalue)
	enum { IDD = IDD_PAYMENT_OTP_SUB_ADDVALUE };
	CString	m_Amount;
	CString	m_OctopusCardNo;
	CString	m_OctopusRemain;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPaymentOTPSubAddvalue)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPaymentOTPSubAddvalue)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitControl();
	static CDlgPaymentOTPSubAddvalue * pThis;
	static CString _OctopusCardNo;		//八达通卡号
	static double _OctopusRemain;		//八达通余额
	static double _Amount;				//冲值金额
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPAYMENTOTPSUBADDVALUE_H__DFEF7E20_C2F0_4DF8_93DC_A5FBFFA9B20D__INCLUDED_)
