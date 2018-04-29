#if !defined(AFX_DLGINPUT_H__8E139DDC_2FA6_460D_9C79_0C563576A65B__INCLUDED_)
#define AFX_DLGINPUT_H__8E139DDC_2FA6_460D_9C79_0C563576A65B__INCLUDED_

#include "DlgInput.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlginput.h : header file
//
/////////////////////////////////////////////////////////////////////////////
//输入对话框基类
//		用来改变键盘定义
//		用来添加必要提示
//		用来改变字体

/////////////////////////////////////////////////////////////////////////////
// CDlgInput dialog

class CDlgInput : public CDialog
{
// Construction
public:
	CDlgInput(UINT uResourceID, CWnd* pParent = NULL);
private:
    CDlgInput(CWnd* pParent = NULL);
	CDlgInput(LPCTSTR pszResourceID, CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CDlgInput)
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInput)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnCancel();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont m_fontEdit;

	// Generated message map functions
	//{{AFX_MSG(CDlgInput)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINPUT_H__8E139DDC_2FA6_460D_9C79_0C563576A65B__INCLUDED_)
