#if !defined(AFX_DLGPAYMENT_H__844E4FA6_468C_47B1_8926_4A1AC1C31D47__INCLUDED_)
#define AFX_DLGPAYMENT_H__844E4FA6_468C_47B1_8926_4A1AC1C31D47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgpayment.h : header file
//
#include "..\Include\Sxbutton.h"

#define IDC_CLOSEACCOUNT1               WM_USER+13

/////////////////////////////////////////////////////////////////////////////
// CDlgPayment dialog

class CDlgPayment : public CDialog
{
// Construction
public:
	static void AddAccountLog();
	static void AddPaymentLog( CString	CardNo,
						CString		Category,
						CString		CarType,
						CString		StationID,
						CString		Paytime,
						CString		ReceiptNo,
						CString		Amount,
						//CString		PayMode1,
						CString		Amount1,
						//CString		PayMode2,
						CString		Amount2,
						//CString		PayMode3,
						CString		Amount3,
						CString		TransactionNo);
	void InitControl();
	CDlgPayment(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPayment)
	enum { IDD = IDD_PAYMENT };
	CListBox	m_TipCtrl2; // [PY]: 06 Jun 2005 - added lower msg box
	CListBox	m_TipCtrl;
	CListCtrl	m_Payment_List;
	CSXButton	m_Error_OTP_Card;
	CSXButton	m_Error_KDE_Card;
	CSXButton	m_Otp_Card_Add_Value;
	CString	m_label_0;
	double	m_fCashAmt;
	CString	m_CurOptr;
	CString	m_DutyStart;
	double	m_fOTPAmt;
	long	m_nPayNum;
	double	m_fSVAmt;
	double	m_fTotAmt;
	CString	m_strWMode;
	double	m_fShiftCashAmt;
	double	m_fShiftOTPAmt;
	double	m_fShiftSVAmt;
	double	m_fShiftTotalAmt;
	double	m_fCashKeep;
	double	m_fCashMaintain;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPayment)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool m_AutoXFileDoneFlag;
	CBrush m_brush;

	// Generated message map functions
	//{{AFX_MSG(CDlgPayment)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnOtpCardAddValue();
	afx_msg void OnErrorKdeCard();
	afx_msg void OnTimesynchronize();
	afx_msg void OnErrorOtpCard();
	afx_msg void OnShiftAccount();
	afx_msg void OnCloseaccount();
	afx_msg void OnCloseaccount1(LPVOID wParam,LPVOID lParam);
	afx_msg void OnButton1();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelDiscount();
	afx_msg LRESULT OnTip(WPARAM wParam, LPARAM lParam);
	afx_msg void OnEntCreate();
	afx_msg void OnLast4record();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	static CDlgPayment* m_pThis;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPAYMENT_H__844E4FA6_468C_47B1_8926_4A1AC1C31D47__INCLUDED_)
