#if !defined(AFX_DLGCREATECARD2_H__F19735E8_DEDF_4E30_86D4_5D9321FFF52F__INCLUDED_)
#define AFX_DLGCREATECARD2_H__F19735E8_DEDF_4E30_86D4_5D9321FFF52F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgcreatecard2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateCard2 dialog

class CDlgCreateCard2 : public CDialog
{
	DECLARE_DYNCREATE(CDlgCreateCard2)

// Construction
public:
	bool CheckInput();
	CDlgCreateCard2();
	~CDlgCreateCard2();

// Dialog Data
	//{{AFX_DATA(CDlgCreateCard2)
	enum { IDD = IDD_CARD_CREATE2 };
	COleDateTime	m_ValidFrom;
	COleDateTime	m_ValidTo;
	CString	m_StoreValue;
	short	m_TransTimes;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgCreateCard2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgCreateCard2)
	afx_msg void On1m();
	afx_msg void On2m();
	afx_msg void On3m();
	afx_msg void On6m();
	afx_msg void On12m();
	afx_msg void On24m();
	virtual BOOL OnInitDialog();
	virtual void OnOK(){};
	virtual void OnCancel(){};
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	LPVOID m_pDlg;
	void AddMonth(short Month);
	void InitControl();
	enum Direction {dir_Obj2Dlg, dir_Dlg2Obj};
	void PassValue(Direction);	//对象与对话框之间值的传递
public: 
	void SetParentDlg(LPVOID pDlg){m_pDlg = pDlg;}
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCREATECARD2_H__F19735E8_DEDF_4E30_86D4_5D9321FFF52F__INCLUDED_)
