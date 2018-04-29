#if !defined(AFX_DLGPAYMENTSHIFTACCOUNT_H__9A87FCEB_859E_43A7_8F9D_14B3793590F7__INCLUDED_)
#define AFX_DLGPAYMENTSHIFTACCOUNT_H__9A87FCEB_859E_43A7_8F9D_14B3793590F7__INCLUDED_

#include "DlgInput.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgpaymentshiftaccount.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentShiftAccount dialog

class CDlgPaymentShiftAccount : public CDlgInput
{
// Construction
public:
//	double _ShiftCashMaintain;

	CDlgPaymentShiftAccount(CWnd* pParent = NULL);   // standard constructor
	static void SetOctopusRemain(double d){	_OctopusRemain = d; }
	static void SetStoreValueRemain(double d){ _StoreValueRemain = d; }
	static void SetCashRemain(double d)	{ _CashRemain = d; }
	static void SetOperator(CString d)	{ _Operator = d; }
	static void SetDutyTime(COleDateTime d){ _DutyStart = d; }
	static void SetPayNum(long d) { _PayNum = d; }
	static void SetCashKeepRemain(double d) { _CashKeepRemain = d; }


// Dialog Data
	//{{AFX_DATA(CDlgPaymentShiftAccount)
	enum { IDD = IDD_PAYMENT_SHIFTACCOUNT };
	CString	m_AmountRemain;
	CString	m_CashRemain;
	CString	m_OctopusRemain;
	CString	m_StoreValueRemain;
	CString	m_Operator;
	CString	m_DutyTime;
	long	m_lPayNum;
	CString	m_CashKeepRemain;
	CString	m_ShiftCashMaintain;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPaymentShiftAccount)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPaymentShiftAccount)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitControl();

private:

	static double _CashRemain;			//œ÷Ω”‡∂Ó
	static double _StoreValueRemain;	//¥¢÷µ”‡∂Ó
	static double _OctopusRemain;		//∞À¥ÔÕ®”‡∂Ó
	static CString _Operator;
	static COleDateTime _DutyStart;
	static long _PayNum;
	static double _CashKeepRemain;
	static double _ShiftCashMaintainRemain;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPAYMENTSHIFTACCOUNT_H__9A87FCEB_859E_43A7_8F9D_14B3793590F7__INCLUDED_)
