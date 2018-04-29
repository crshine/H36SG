#if !defined(AFX_DLGPAYMENTKDE_H__4EBA08A4_559F_4904_AAB3_09A5C7FEE0C5__INCLUDED_)
#define AFX_DLGPAYMENTKDE_H__4EBA08A4_559F_4904_AAB3_09A5C7FEE0C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgpaymentkde.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentKDE dialog

class CDlgPaymentKDE : public CDialog
{
// Construction
public:
	CDlgPaymentKDE(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPaymentKDE)
	enum { IDD = IDD_PAYMENT_KDE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPaymentKDE)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPaymentKDE)
	afx_msg void OnPay();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPAYMENTKDE_H__4EBA08A4_559F_4904_AAB3_09A5C7FEE0C5__INCLUDED_)
