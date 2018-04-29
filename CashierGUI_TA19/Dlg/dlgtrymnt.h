#if !defined(AFX_DLGTRYMNT_H__06D4801B_1466_488A_A8CB_89535482B177__INCLUDED_)
#define AFX_DLGTRYMNT_H__06D4801B_1466_488A_A8CB_89535482B177__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgtrymnt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTryMnt dialog

class CDlgTryMnt : public CDialog
{
// Construction
public:
	CDlgTryMnt(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTryMnt)
	enum { IDD = IDD_TRY_MNT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTryMnt)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTryMnt)
	afx_msg void OnOperatoractionlog();
	afx_msg void OnPayment();
	afx_msg void OnTimesynchronize();
	afx_msg void OnNonparkingpayment();
	afx_msg void OnFinancialmaintain();
	afx_msg void OnErrorwarnnoticelog();
	afx_msg void OnUploadotpxfile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRYMNT_H__06D4801B_1466_488A_A8CB_89535482B177__INCLUDED_)
