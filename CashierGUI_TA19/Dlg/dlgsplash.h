#if !defined(AFX_DLGSPLASH_H__3BBA9AF4_C911_4B78_B3EB_63ADD656D1DF__INCLUDED_)
#define AFX_DLGSPLASH_H__3BBA9AF4_C911_4B78_B3EB_63ADD656D1DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgsplash.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSplash dialog

class CDlgSplash : public CDialog
{
// Construction
public:
	void ShowText(LPCSTR s);
	CDlgSplash(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSplash)
	enum { IDD = IDD_SPLASH };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSplash)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSplash)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSPLASH_H__3BBA9AF4_C911_4B78_B3EB_63ADD656D1DF__INCLUDED_)
