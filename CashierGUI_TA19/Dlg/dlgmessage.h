#if !defined(AFX_DLGMESSAGE_H__4BBBBC93_A18A_48E0_8F8D_74865B465CE7__INCLUDED_)
#define AFX_DLGMESSAGE_H__4BBBBC93_A18A_48E0_8F8D_74865B465CE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgmessage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMessage dialog

class CDlgMessage : public CDialog
{
// Construction
public:
	CDlgMessage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMessage)
	enum { IDD = IDD_MESSAGEBOX };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMessage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMessage)
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMESSAGE_H__4BBBBC93_A18A_48E0_8F8D_74865B465CE7__INCLUDED_)
