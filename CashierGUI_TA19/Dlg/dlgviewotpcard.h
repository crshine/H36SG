#if !defined(AFX_DLGVIEWOTPCARD_H__B0282050_6CAA_4987_9D39_B6CF5EE2D25E__INCLUDED_)
#define AFX_DLGVIEWOTPCARD_H__B0282050_6CAA_4987_9D39_B6CF5EE2D25E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgviewotpcard.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgViewOtpCard dialog

class CDlgViewOtpCard : public CDialog
{
// Construction
public:
	~CDlgViewOtpCard();
	CDlgViewOtpCard(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgViewOtpCard)
	enum { IDD = IDD_VIEW_OTP_CARD };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgViewOtpCard)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgViewOtpCard)
	afx_msg void OnWaitOtpPoll();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIEWOTPCARD_H__B0282050_6CAA_4987_9D39_B6CF5EE2D25E__INCLUDED_)
