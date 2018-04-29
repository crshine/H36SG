#if !defined(AFX_DLGRATEFEE_H__E8B9BA7F_3422_44A2_9279_F89FC2308D96__INCLUDED_)
#define AFX_DLGRATEFEE_H__E8B9BA7F_3422_44A2_9279_F89FC2308D96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgratefee.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRateFee dialog

class CDlgRateFee : public CDialog
{
// Construction
public:
	void ShowTheRule();
	CDlgRateFee(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRateFee)
	enum { IDD = IDD_RATE_FEE };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRateFee)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRateFee)
	afx_msg void OnButtonRefrash();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString showHH(short sec);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRATEFEE_H__E8B9BA7F_3422_44A2_9279_F89FC2308D96__INCLUDED_)
