#if !defined(AFX_DLGCARDSEARCH_H__63A122F8_DDF8_4AD8_A78F_CE1AE17E118E__INCLUDED_)
#define AFX_DLGCARDSEARCH_H__63A122F8_DDF8_4AD8_A78F_CE1AE17E118E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgcardsearch.h : header file
//
#include "DlgInput.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgCardSearch dialog

class CDlgCardSearch : public CDlgInput
{
// Construction
public:
	CDlgCardSearch(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCardSearch)
	enum { IDD = IDD_CARD_SEARCH };
	CEdit	m_Description;
	CString	m_CardNo;
	CString	m_CardType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCardSearch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCardSearch)
	afx_msg void OnSearch();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCARDSEARCH_H__63A122F8_DDF8_4AD8_A78F_CE1AE17E118E__INCLUDED_)
