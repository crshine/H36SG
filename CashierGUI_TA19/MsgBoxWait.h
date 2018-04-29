#if !defined(AFX_MSGBOXWAIT_H__07F00A04_5A34_476A_9450_9F5214DAE384__INCLUDED_)
#define AFX_MSGBOXWAIT_H__07F00A04_5A34_476A_9450_9F5214DAE384__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgBoxWait.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MsgBoxWait dialog

class MsgBoxWait : public CDialog
{
// Construction
public:
	MsgBoxWait(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MsgBoxWait)
	enum { IDD = IDD_MSGBOX_WAIT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MsgBoxWait)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MsgBoxWait)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGBOXWAIT_H__07F00A04_5A34_476A_9450_9F5214DAE384__INCLUDED_)
