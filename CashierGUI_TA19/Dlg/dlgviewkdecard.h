#if !defined(AFX_DLGVIEWKDECARD_H__270DE32B_004D_487B_8A89_0BDAACF21313__INCLUDED_)
#define AFX_DLGVIEWKDECARD_H__270DE32B_004D_487B_8A89_0BDAACF21313__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgviewkdecard.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgViewKdeCard dialog

class CDlgViewKdeCard : public CDialog
{
// Construction
public:
	CDlgViewKdeCard(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgViewKdeCard)
	enum { IDD = IDD_VIEW_KDE_CARD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgViewKdeCard)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgViewKdeCard)
	afx_msg void OnReadTicket();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ClearAll();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIEWKDECARD_H__270DE32B_004D_487B_8A89_0BDAACF21313__INCLUDED_)
